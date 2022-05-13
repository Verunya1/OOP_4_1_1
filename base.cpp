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
		cout << '\n' << headline << " ";
	}
	for (int i = 0; i < children.size(); i++) {
		if (i + 1 < children.size()) {
			cout << children[i]->getrootName() << " ";
		} else {
			cout << children[i]->getrootName();
		}
	}

	for (int i = 0; i < children.size(); i++) {
		children[i]->print();
	}
}

void base::redefinition(base *newParent) {
	if (this->parent != nullptr) {
		for (int i = 0; i < this->parent->children.size(); i++) {
			if (this->parent->children[i] == this)
				this->parent->children.erase(this->parent->children.begin() + i);
		}
	}
	if (newParent != nullptr) newParent->children.push_back(this);
	this->parent = newParent;

}

base *base::getParent() { return parent; }

void base::printTree() {
	if (this->getParent() == nullptr) {
		cout << headline;
	}
	string tabs = "   ";
	base *parent = this;
	while (parent->getParent() != nullptr) {
		parent = parent->getParent();
		tabs = tabs + " " + " " + " " + " " + " ";
	}
	for (auto ch: children) {
		cout << endl << tabs << ch->getrootName();
		ch->printTree();
	}

}

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

bool base::isReady() {
	return status != 0;
}
void base::setReadiness(int setStatus) {
	if (parent != nullptr && !parent->isReady())
		return;
	status = setStatus;

	if (status == 0)
		for (auto child: children)
			child->setReadiness(0);
}

void base::printReadiness(int tab_level) {

	if (parent != nullptr)
		cout << endl;

	for (int q = 0; q < tab_level; q++) cout << "    ";
	cout << headline;


	if (status) cout << " is ready";
	else cout << " is not ready";

	for (base *child: children) child->printReadiness(tab_level + 1);

}

string base::getName() {
	return headline;
}

