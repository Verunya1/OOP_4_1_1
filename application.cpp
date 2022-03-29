//
// Created by vera3 on 29.03.2022.
//

#include "application.h"
#include <iostream>
#include "base.h"
#include <string>
using namespace std;
application::application(baseT * parent) : base(parent,"root")
{}

void application::buildTreeObjects() {
	string rootName, parA, chB;
	cin >> rootName;
	this->setrootName(rootName);
	base *current = this;

	do {
		cin >> parA >> chB;
		if (parA != chB) {
			if (current->getrootName() == parA)
				current = new baseT(current, chB);
			else
				current = new baseT(current->getParent(), chB);
		}
	} while (parA != chB);

}
int application::execApp() {
	cout << getrootName();
	print();
	return 0;
}

