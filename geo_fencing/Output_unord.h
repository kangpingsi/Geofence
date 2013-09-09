#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <mutex>
#include <vector>
#include "output.h"

using namespace std;

class Output_unord:IOutput
{
private:
	string out_file_name;
	vector<string> results; 
	std::mutex output_mutex;
public:
	Output_unord(string file_name){ this->out_file_name = file_name;}
	void Add(string value);
	void Add(int key, string value){};
	void Write_to_File();
	size_t Get_Rec_Num(){ return results.size();}
	~Output_unord(void);
};
