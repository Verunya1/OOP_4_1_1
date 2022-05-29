//
// Created by vera3 on 29.03.2022.
//

#include "application.h"
#include <iostream>
#include "base.h"
#include <string>
#include "Class2.h"
#include "Class3.h"
#include "Class4.h"
#include "Class5.h"
#include "Class6.h"

using namespace std;

application::application(base *parent) : base(parent, "root") {}

void application::buildTreeObjects() {
	string rootName, parA, chB;
	cin >> rootName;
	this->setrootName(rootName);
	int classN;

	do {
		cin >> parA;
		if (parA != "endtree") {
			cin >> chB >> classN;
			base *curParA = findElem(parA);
			switch (classN) {
				case 2:
					new Class2(curParA, chB);
					break;
				case 3:
					new Class3(curParA, chB);
					break;
				case 4:
					new Class4(curParA, chB);
					break;
				case 5:
					new Class5(curParA, chB);
					break;
				case 6:
					new Class6(curParA, chB);
					break;
				default:
					break;
			}
		}
	} while (parA != "endtree");


}

int application::execApp() {
	string obj_name;
	int readiness;
	while (cin >> obj_name) {
		if (obj_name == "3") {
			break;
		}
		cin >> readiness;
		findElem(obj_name)->setReadiness(readiness);
	}
	cout << "Object tree" << endl;
	printTree();
	cout << endl << "The tree of objects and their readiness" << endl;
	printReadiness();

	return 0;
}

