//
// Created by vera3 on 29.03.2022.
//

#include "base.h"
#include <iostream>
#include <vector>
#include <string>

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

/*bool base::isReady() {
	return status != 0;
}*/
void base::setReadiness(int setStatus) {
	/*if (parent != nullptr && !(parent->isReady()))
		return;
	status = setStatus;

	if (status == 0)
		for (auto child: children)
			child->setReadiness(0);*/
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

	/*if (this->getParent() != nullptr)
		cout << endl;

	for (int q = 0; q < tab_level; q++) cout << "    ";
	cout << headline;


	if (this->status) cout << " is ready";
	else cout << " is not ready";

	for (base *child: children) child->printReadiness(tab_level + 1);
*/
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
		string nameSearchableChild = path.substr(0, indexTransition == -1 ?path.size() : indexTransition);
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




