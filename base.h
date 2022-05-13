//
// Created by vera3 on 29.03.2022.
//

#ifndef BASE_H
#define BASE_H

#include <vector>
#include <iostream>
#include <string>

using namespace std;

class base {
public:
	base(base *parent, string headline = "Object");

	~base();

	void setrootName(string headline_);

	string getrootName();

	void print();

	void redefinition(base *newParent);

	base *getParent();

	void printTree();

	void printReadiness(int tab_level = 0);

	void setReadiness(int setStatus);

	base *findElem(const string &headline);

	bool isReady();
	string getName();

private:
	string headline;
	base *parent;
	vector<base *> children;
	int status = 0;

};


#endif //OOP_4_1_1_BASE_H
