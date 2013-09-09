#pragma once
#include <string>

using namespace std;

class IOutput
{
public:
	string out_file_name;
	virtual void Add(int key, string value) = 0;
	virtual void Add(string value) = 0;
	virtual void Write_to_File() = 0;
};

