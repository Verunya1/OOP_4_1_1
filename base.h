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
	base(base * parent,string headline = "Object");
	void setrootName(string headline_);
	string getrootName();
	void print();
	void redefinition(base * newParent);
	base * getParent();

private:
	string headline;
	base * parent;
	vector<base *> children;




};


#endif //OOP_4_1_1_BASE_H
