#include "stdafx.h"
#include "Output_ord.h"


void Output_ord::Add(int id_pt, string value)
{
	std::lock_guard<std::mutex> guard(output_mutex);
	this->results.insert(pair<int,string>(id_pt,value));
}
void Output_ord::Write_to_File()
{
	ofstream out_file;
	out_file.open(this->out_file_name);
	if (out_file.is_open())
	{
		auto it = results.cbegin();
		while(it != results.cend())
		{
			out_file << it->second;
			++it;
		}
		out_file.close();
	}
	else
	{
		cout <<"ERROR: Can not create output file: " << this->out_file_name <<" !"<< endl;
	}
}


Output_ord::~Output_ord(void)
{
}
