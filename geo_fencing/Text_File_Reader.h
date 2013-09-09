#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <mutex>

using namespace std;

class Text_File_Reader
{
private:
	string file_name;
	ifstream txt_file;
	std::mutex txt_file_mutex;
public:
	Text_File_Reader(string file_name){this->file_name = file_name;}
	bool Open_file();
	void Close_file();
	string Get_new_line();
	~Text_File_Reader(void);
};

