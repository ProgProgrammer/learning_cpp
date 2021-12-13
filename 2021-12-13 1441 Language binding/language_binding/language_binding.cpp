#include <iostream>
#include "header.h"

void coutString(std::string str)
{
	std::cout << str << std::endl;
}

int main()
{
	std::string str = "Hello, world!";

	coutString(str);
	output();
}