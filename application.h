//
// Created by vera3 on 29.03.2022.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#include "base.h"
#include <iostream>
#include "Class2.h"
#include "Class3.h"
#include "Class4.h"
#include "Class5.h"
#include "Class6.h"

class application : public base {

public:
	bool buildSuccess = true;
	string errorMessage = "";


	application(base *parent);

	void buildTreeObjects();

	int execApp();




};

const typeSignal signals[] = {
		SIGNAL_D(application::signal),
		SIGNAL_D(Class2::signal),
		SIGNAL_D(Class3::signal),
		SIGNAL_D(Class4::signal),
		SIGNAL_D(Class5::signal),
		SIGNAL_D(Class6::signal),
};
const typeHandler handlers[] = {
		HANDLER_D(application::handler),
		HANDLER_D(Class2::handler),
		HANDLER_D(Class3::handler),
		HANDLER_D(Class4::handler),
		HANDLER_D(Class5::handler),
		HANDLER_D(Class6::handler),
};



#endif //OOP_4_1_1_APPLICATION_H
