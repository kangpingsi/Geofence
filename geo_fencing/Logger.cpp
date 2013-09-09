#include "stdafx.h"
#include "Logger.h"
#include <sys/stat.h>
#include <fstream>


bool Logger::File_Exists(string file_name)
{
	struct stat buf;
    if (stat(file_name.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}


void Logger::Write_Out(string content)
{
	std::ofstream ofs;
	if (File_Exists(this->log_file_name)) 
	{
		ofs.open (log_file_name, std::ofstream::out | std::ofstream::app);
	}
	else
	{
		ofs.open (log_file_name);
	}

	ofs << content;

	ofs.close();
}


Logger::~Logger(void)
{
}
