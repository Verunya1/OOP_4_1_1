//
// Created by vera3 on 29.03.2022.
//

#ifndef BASE_H
#define BASE_H
class base;

#include <vector>
#include <iostream>
#include <string>
using namespace std;
typedef void(base::*typeSignal)(string&);
typedef void(base::*typeHandler)(string);
#define SIGNAL_D(signal) (typeSignal)(&signal)
#define HANDLER_D(handler) (typeHandler)(&handler)

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


	base *getFindCoord(std::string path);





	int getNumber();
	string getPath();
	void setConnection( base * connectedBase, typeSignal signal, typeHandler
	handler);
	void deleteConnection(base* connectedBase, typeSignal signal, typeHandler
	handler);
	void emitSignal(typeSignal signal, std::string& message);
	void setAllReady();

	void signal(string &str);
	void handler(string str);




private:
	int status=0;
	string headline;
	base *parent;
	vector<base *> children;

protected:
	int number;
	struct Connection{
		base* connectedBase;
		typeSignal signal;
		typeHandler handler;

	};
	vector<Connection> connections;

};


#endif //OOP_4_1_1_BASE_H
