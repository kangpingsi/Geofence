#pragma once
#include "Polygon.h"
#include "Moving_Polygon.h"
#include "Predicate.h"
#include <map>
#include <string>

/*
This class hold the entire polygon file in memory, every line represent a polygon and polygons
with the same ID are stored in one moving polygon. 
*/

class Polygon_File
{
private:	
	std::map<int, Moving_Polygon*> Moving_Polygons;
	Predicate* option;
	int n_Polygons;  //total number of polygon in the file
	int n_MPs;       //number of polygons with unique IDs

public:

	Polygon_File(Predicate* p);
	void Add(Polygon* poly);
	std::string Process_One_Pt(Point *pt);
	~Polygon_File(void);

	void test_out();
};

