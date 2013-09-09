/*
This class is to store and write out the result following the order of Point ID
*/
#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include<mutex>
#include"output.h"

using namespace std;

class Output_ord:public IOutput
{
private:
	string out_file_name;
	multimap<int, string> results; 
	std::mutex output_mutex;
public:
	Output_ord(string file_name){ this->out_file_name = file_name;}
	void Add(int id_pt, string value);
	void Add(string value){};
	void Write_to_File();
	size_t Get_Rec_Num(){ return results.size();}
	~Output_ord(void);
};

