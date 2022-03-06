#pragma once
#include <iostream>
#include <fstream>

class ErrorFiles
{
public:
	friend void operator << (const std::ofstream& fout, const std::string& error_str);
};