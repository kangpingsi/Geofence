#pragma once
#include "Polygon_File.h"
#include "Moving_Polygon.h"
#include "Polygon.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

class Polygon_Reader
{
private:
	string poly_file_name;
public:
	Polygon_Reader(string file_name){ this->poly_file_name = file_name;}
	void Build_Polygon_Index(Polygon_File& PF);
	Polygon* Parse_Polygon(string line);
	void split(const std::string& s, char delim, std::vector<std::string>& elems);
	~Polygon_Reader(void);
};

