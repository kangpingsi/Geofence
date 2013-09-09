#pragma once
#include "Polygon.h"
#include <map>
#include <string>
/*
	This class defines polygons of the same ID but different sequence number
*/
class Moving_Polygon
{
private:
	std::map<int,Polygon*> poly_list;    //<seq, polygon>
	std::vector<int> keys;
 	int ID, n_status;

public:
	Moving_Polygon(int id, int n_s = 0):n_status(n_s) {this->ID = id;}
	void Add(Polygon * poly) {poly_list[poly ->Get_Seq()] = poly;}
	int Get_num_Status() 
	{
		n_status = poly_list.size();
		return n_status;
	}
	std::string Predicate_Inside(Point *pt);
	std::string Predicate_Within(Point *pt, double dist);
	int find_key(int pt_seq);
	void Extract_Keys();

	~Moving_Polygon(void);

	//for testing
	void test_out();
};

