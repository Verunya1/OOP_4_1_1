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
			//base *curParA = findElem(parA);
			base *curParA = getFindCoord(parA);
			if (curParA == nullptr) {
				this->buildSuccess = false;
				errorMessage = "The head object " + parA
				               + " is not found";
				return;
			}

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
	cout << "Object tree" << endl;
	printTree();
	if (buildSuccess) {
		base *currentNode = this;
		string command;
		while (cin >> command && command != "END") {
			string path;
			cin >> path;
			cout << endl;
			if (command == "SET") {
				base *newCurrentNode = currentNode -> getFindCoord(path);
				if (newCurrentNode != nullptr) {
					currentNode = newCurrentNode;
					cout << "Object is set: " <<
					     currentNode->getrootName();
				} else {
					cout << "Object is not found: " <<
					     this->getrootName() << " " << path;
				}
			} else if (command == "FIND") {
				base *foundObject = currentNode -> getFindCoord(path);
				cout << path;
				if (foundObject != nullptr) {
					cout << "     " << "Object name: " <<foundObject->getrootName();
				} else {
					cout << "     " << "Object is not found";
				}
			}
		}
	} else {
		cout << endl << errorMessage;
	}
	return 0;


}