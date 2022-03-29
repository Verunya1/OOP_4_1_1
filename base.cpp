//
// Created by vera3 on 29.03.2022.
//

#include "base.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

base::base(base *parent_, string headline_) {
	this->parent = parent_;
	this->headline = headline_;
	if (this->parent != nullptr) {
		parent_->children.push_back(this);
	}
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
			cout<<children[i]->getrootName();
		}
	}

	for (int i = 0; i < children.size(); i++) {
		children[i]->print();
	}
}

void base :: redefinition(base * newParent) {
	if(this -> parent != nullptr) {
		for(int i = 0; i < this -> parent -> children.size(); i++) {
			if (this -> parent -> children[i] == this)
				this -> parent ->children.erase(this ->parent -> children.begin() + i);
		}
	}
	if(newParent != nullptr) newParent -> children.push_back(this);
	this -> parent = newParent;

}

base *base::getParent() { return parent; }

