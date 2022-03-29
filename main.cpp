#include <iostream>
#include "application.h"

using namespace std;
int main() {
	application objApplication(nullptr);
	objApplication.buildTreeObjects();
	return objApplication.execApp();
}
