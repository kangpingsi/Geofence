#pragma once
#include "Point.h"
#include <vector>
#include <string>

class Point_Factory
{
private:
	void Point_Factory::split(const std::string &s, char delim, std::vector<std::string>& elems);
public:
	Point_Factory(void);
	Point* Get_Point(std::string& line);
	~Point_Factory(void);
};

