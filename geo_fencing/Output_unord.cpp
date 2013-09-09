#include "stdafx.h"
#include "Output_unord.h"


void Output_unord::Add(string value)
{
	std::lock_guard<std::mutex> guard(output_mutex);
	this->results.push_back(value);
}
void Output_unord::Write_to_File()
{
	ofstream out_file;
	out_file.open(this->out_file_name);
	if (out_file.is_open())
	{
		auto it = results.cbegin();
		while(it != results.cend())
		{
			out_file << *it;
			++it;
		}
		out_file.close();
	}
	else
	{
		cout <<"ERROR: Can not create output file: " << this->out_file_name <<" !"<< endl;
	}
}


Output_unord::~Output_unord(void)
{
}
