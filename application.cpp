//
// Created by vera3 on 29.03.2022.
//

#include "application.h"
#include <iostream>
#include <string>


using namespace std;

application::application(base *parent) : base(parent, "root") {
	number = 1;
}

void application::buildTreeObjects() {
	string rootName, parA, chB;
	cin >> rootName;
	this->setrootName(rootName);
	int classN;

	do {
		cin >> parA;
		if (parA != "endtree") {
			cin >> chB >> classN;
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
	string distributor_path;
	string receiver_path;
//	base *distributor;
	base *currentNode;
//	base *receiver;
	base *sender;
	while (true) {
		cin >> distributor_path;
		if (distributor_path == "end_of_connections") break;
		cin >> receiver_path;
		currentNode = (base *) (getFindCoord(distributor_path));
		sender = (base *) (getFindCoord(receiver_path));
		currentNode->setConnection(sender, signals[currentNode->getNumber() - 1], handlers[sender->getNumber() - 1]);
	}
}


int application::execApp() {
	cout << "Object tree" << endl;
	printTree();
	if (!buildSuccess) {
		cout << endl << errorMessage;
		return 0;
	}
	setAllReady();

	string command;
	string path;
	string msg;
	base *sender;
	int statusReady;

	while (true) {
		cin >> command;
		if(command=="END"){
			return 0;
		}
		cin >> path;
		//currentNode = getFindCoord(path);

		if (command == "EMIT") {
			getline(cin, msg);
			base *currentNode = getFindCoord(path);
			if (currentNode) {
				currentNode->emitSignal(signals[currentNode->getNumber() - 1], msg);
			} else {
				cout << endl << "Object " << path << " not found";
			}
		} else if (command == "SET_CONNECT") {
			cin >> msg;
			base *currentNode = getFindCoord(path);
			base *sender = getFindCoord(msg);
			if (!currentNode)
				cout << endl << "Object " <<
				     path << "not found";
			if (!sender)
				cout << endl << "Handler object "
				     << msg << " not found";
			if (currentNode && sender) {
				currentNode->setConnection(sender,
				                           signals[currentNode->getNumber() - 1],
				                           handlers[sender->getNumber() -
				                                    1]);
			}
		} else if (command == "DELETE_CONNECT") {
			cin >> msg;
			base *sender = getFindCoord(msg);
			base *currentNode = getFindCoord(path);
			if (currentNode == nullptr)
				cout << endl << "Object " << path << "not found";
			if (sender == nullptr)
				cout << endl << "Handler object " << msg << " not found";
			if (sender != nullptr && currentNode != nullptr)
				currentNode->deleteConnection(sender, signals[currentNode->getNumber() - 1],
				                              handlers[sender->getNumber() - 1]);
		} else if (command == "SET_CONDITION") {
			base *currentNode = getFindCoord(path);
			cin >> statusReady;
			if (currentNode) {
				currentNode->setReadiness(statusReady);
			} else {
				cout << endl << "Object " << path << "not found";
			}
		} else {
			cout << endl <<
			     errorMessage;
		}
	}
}

