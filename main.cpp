#include "package.h"

#include <iostream>

int main(void)
{
	WCMP::Package blah("a");
	std::cout << blah.prepared() << std::endl;
}
