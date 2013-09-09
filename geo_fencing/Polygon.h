/*
This class defines the data structure and functions associated with the polygon
*/
#pragma once
#include "OuterBoundary.h"
#include "InnerBoundary.h"
#include "BoundingBox.h"
#include <vector>
#include <string>
#include <sstream>

class Polygon
{
private:
	int ID, Seq;
public:
	OuterBoundary* OB;
	std::vector<InnerBoundary*> IBs;
	BoundingBox* BB;

	Polygon(int id,int seq, OuterBoundary* outBound);
	Polygon(){}
	void Add_Inner_Boundary(InnerBoundary* inBound);
	int Get_ID() {return ID;}
	int Get_Seq() {return Seq;}
	std::string Print_Out();
	std::string Test_Out();
	~Polygon(void);
};
