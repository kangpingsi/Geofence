#include "stdafx.h"
#include "Text_File_Reader.h"


bool Text_File_Reader:: Open_file()
{
	txt_file.open(this->file_name);
	if (txt_file.good()) return txt_file.is_open();
	else throw std::runtime_error("ERROR: can't open point file: " + file_name);
}
void Text_File_Reader::Close_file()
{
	txt_file.close();
}

string Text_File_Reader::Get_new_line()
{
	std::lock_guard<std::mutex> guard(txt_file_mutex);
	string line;
	if(txt_file.good())  
	{
		if(txt_file.eof()) return "END_OF_FILE";

		getline(txt_file,line);
		return line;
	}
	else return "END_OF_FILE";
}

Text_File_Reader::~Text_File_Reader(void)
{
	if(txt_file.is_open()) txt_file.close();
}
