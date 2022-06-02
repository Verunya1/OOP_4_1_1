//
// Created by vera3 on 29.03.2022.
//

#include "base.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

base::base(base *parent_, string headline_) {
	this->status = 0;
	this->parent = parent_;
	this->headline = headline_;
	if (this->parent != nullptr) {
		parent_->children.push_back(this);
	}
}

base::~base() {
	for (int i = 0; i < children.size(); i++) delete children[i];
}

void base::setrootName(string headline_) {
	headline = headline_;
}

string base::getrootName() {
	return headline;
}

void base::print() {
	if (!children.empty()) {
		cout << '\n' << headline << "  ";
	}
	for (int i = 0; i < children.size(); i++) {
		if (i + 1 < children.size()) {
			cout << children[i]->getrootName() << "  ";
		} else {
			cout << children[i]->getrootName();
		}
	}

	for (int i = 0; i < children.size(); i++) {
		children[i]->print();
	}
}

void base::redefinition(base *newParent) {
	if (this->parent != nullptr && newParent != nullptr) {
		for (int i = 0; i < this->parent->children.size(); i++) {
			if (this->parent->children[i] == this)
				this->parent->children.erase(this->parent
						                             ->children.begin() + i);
		}
		newParent->children.push_back(this);
		parent = newParent;
	}

}

base *base::getParent() { return parent; }


base *base::findElem(const string &sT) {
	if (headline == sT) {
		return this;
	}
	for (auto ch: children) {
		base *result = ch->findElem(sT);
		if (result != nullptr) {
			return result;
		}
	}
	return nullptr;
}


void base::setReadiness(int setStatus) {

	if ((this->getParent() != nullptr && this->getParent()->status != 0)
	    || this->getParent() == nullptr) {
		if (setStatus == 0) {
			for (auto &child: this->children) {
				child->setReadiness(0);
			}
		}
		this->status = setStatus;
	}

}

void base::printTree() {
	if (this->getParent() == nullptr) {
		cout << headline;
	}
	string tabs = "    ";
	base *parent = this;
	while (parent->getParent() != nullptr) {
		parent = parent->getParent();
		tabs = tabs + " " + " " + " " + " ";
	}
	for (auto ch: children) {
		cout << endl << tabs << ch->getrootName();
		ch->printTree();
	}

}

void base::printReadiness() {

	if (this->getParent() == nullptr) {
		cout << headline;
		if (!this->status) { cout << " is not ready"; }
		else { cout << " is ready"; }
	}
	string tabs = "    ";
	base *parent = this;
	while (parent->getParent() != nullptr) {
		parent = parent->getParent();
		tabs = tabs + " " + " " + " " + " ";
	}
	for (auto child: children) {
		cout << endl << tabs << child->getrootName();
		if (!child->status) { cout << " is not ready"; }
		else { cout << " is ready"; }
		child->printReadiness();
	}
}


base *base::getFindCoord(string path) {
	if (path.empty()) return nullptr;
	if (path[0] == '.') return this;
	base *root = this;

	if (path[0] == '/') {
		while (root->getParent() != nullptr) root = root->getParent();

	}
	if (path.size() > 1 && path[0] == '/' && path[1] == '/') {
		path.erase(0, 2);
		return root->findElem(path);
	} else if (path[0] == '/') {
		if (path.size() == 1) return root;
		path.erase(0, 1);
	}


	int indexTransition = path.find('/');
	string nameSearchableChild = path.substr(0, indexTransition == -1 ? path.size() : indexTransition);
	for (auto child: root->children) {
		if (child->getrootName() == nameSearchableChild) {
			if (indexTransition == -1) {
				return child;
			} else {
				path.erase(0, indexTransition + 1);
				return child->getFindCoord(path);
			}
		}
	}
	return nullptr;
}


void base::signal(string &str) {
	if (status) {
		cout << endl << "Signal from " << getPath();
		str = str + " (class: "+ to_string(getNumber())+")";
	}
}

void base::handler(string str) {
	if (status) {
		cout << endl << "Signal to " << getPath() << " Text: " << str;
	}
}

int base::getNumber() {
	return number;
}

string base::getPath() {
	string path = "";
	base *curr = this;
	while (curr->getParent()) {
		path = "/" + curr->getrootName() + path;
		curr = curr->getParent();
	}
	return path.empty() ? "/" : path;
}

void base::setAllReady() {
	this->setReadiness(1);
	for (auto child: children)
		child->setAllReady();
}


void base::setConnection(base *connectedBase, typeSignal signal, typeHandler handler) {
	Connection newConnection;
	newConnection.connectedBase = connectedBase;
	newConnection.handler = handler;
	newConnection.signal = signal;
	for (auto connection: connections)
		if (connection.connectedBase == connectedBase and connection.signal == signal and connection.handler == handler)
			return;
	connections.emplace_back(newConnection);
}


void base::deleteConnection(base *connectedBase, typeSignal signal, typeHandler
handler) {
	Connection shouldBeDeleted;
	shouldBeDeleted.signal = signal;
	shouldBeDeleted.handler = handler;
	shouldBeDeleted.connectedBase = connectedBase;
	for (int q = 0; q < connections.size(); q++)
		if (connections[q].connectedBase == connectedBase and connections[q].signal== signal and connections[q].handler == handler){
			connections.erase(connections.begin() + q);
			return;
		}
}


/*void base::setConnection(base *connectedBase, typeSignal signal, typeHandler handler)  {
	Connection new_connection{
			.connectedBase = connectedBase,
			.signal = signal,
			.handler = handler
	};
	for (auto connection: connections)
		if (connection.connectedBase == connectedBase and connection.signal ==signal and connection.handler == handler)
			return;
	connections.push_back(new_connection);
}
void base::deleteConnection(base *connectedBase, typeSignal signal, typeHandler handler){
	for (int q = 0; q < connections.size(); q++)
		if (connections[q].connectedBase == connectedBase and connections[q].signal== signal and connections[q].handler == handler){
			connections.erase(connections.begin() + q);
			return;
		}
}*/



void base::emitSignal(typeSignal signal, string &msg) {
	if (this->status) {
		(this->*(signal))(msg);
		for (auto connection: connections) {
			if (connection.signal == signal &&
			    connection.connectedBase->status != 0) {
				(connection.connectedBase->*(connection.handler))(msg);
			}
		}
	}
}
