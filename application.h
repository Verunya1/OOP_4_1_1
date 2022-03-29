//
// Created by vera3 on 29.03.2022.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#include "base.h"
#include <iostream>
#include "baseT.h"

class application : public base {

public:
	application(baseT * parent);

	void buildTreeObjects();

	int execApp();
};


#endif //OOP_4_1_1_APPLICATION_H
