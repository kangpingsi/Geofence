#pragma once
#include <string>

using namespace std;

class Logger
{
private:
	string log_file_name;
		
public:
	Logger(string file_name){ this->log_file_name = file_name;};

	bool File_Exists(string file_name);
	void Write_Out(string content);
	~Logger(void);
};

