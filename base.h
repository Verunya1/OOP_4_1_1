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

	void printReadiness();

	void setReadiness(int setStatus);

	base *findElem(const string &headline);

	bool isReady();
	string getName();
	base *getFindCoord(std::string path);


private:
	int status;
	string headline;
	base *parent;
	vector<base *> children;





};


#endif //OOP_4_1_1_BASE_H
