#include "stdafx.h"
#include "Point_Factory.h"
#include <sstream> 


Point_Factory::Point_Factory(void)
{
}

void Point_Factory::split(const std::string& s, char delim, std::vector<std::string>& elems)
{
	std::string ele;
	std::stringstream stream(s);
	while(std::getline(stream,ele, delim))
		elems.push_back(ele);
}

Point* Point_Factory::Get_Point(std::string& line)
{
	size_t start,end, pos;
	std::string head_str, gml_str;
	std::vector<std::string> tmp_str_vec;

	pos = line.find_first_of('<');
	head_str = line.substr(0,pos);
	split(head_str,':',tmp_str_vec);

	gml_str = line.substr(pos);
	start = gml_str.find("<gml:coordinates");
	end = gml_str.find("</gml:coordinates");
	std::string tmp_str = gml_str.substr(start,end - start);

	start = tmp_str.find_first_of("<");
	end = tmp_str.find_first_of(">");

	std::string coord = tmp_str.substr(end + 1);
	std::vector<std::string> xy_vec;
	split(coord,',',xy_vec);

	return new Point(stod(xy_vec[0]),stod(xy_vec[1]),
					 stoi(tmp_str_vec[1]),stoi(tmp_str_vec[2]));

}

Point_Factory::~Point_Factory(void)
{
}
