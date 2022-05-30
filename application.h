//
// Created by vera3 on 29.03.2022.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#include "base.h"
#include <iostream>


class application : public base {
private:
	bool buildSuccess = true;
	string errorMessage = "";
public:
	application(base *parent);

	void buildTreeObjects();

	int execApp();

	/*bool buildTreeObjectsMark = true;

	string errorMessage = "";*/

};


#endif //OOP_4_1_1_APPLICATION_H
