#ifndef _POINT_H
#define _POINT_H

/*
This class defines the data structure and functions associated with the point
*/

#pragma once
#include <string>

class Polygon;
class BoundingBox;

class Point{
private:
	double x,y;
	int ID,Seq;
public:
	Point (double x,double y);
	Point (double x, double y, int id, int seq);
	double Get_X() const {return x;}
	double Get_Y() const {return y;}
	int Get_ID() const {return ID;}
	int Get_Seq() const {return Seq;}
	bool operator==(const Point& pt);
	double Distance(Point* pt);
	inline double Sqr_Distance(Point* pt);
	bool Point_In_Line(Point* st_pt, Point* end_pt);
	bool Out_of_Bound(Polygon* poly);
	bool Within(Polygon* poly, double dist);
	int Quadrant(BoundingBox* BB);
	bool ArcInside(Polygon* poly);
	std::string Print_Out();
	
	//for test
	std::string Test_Out();

	virtual ~Point();
};

#endif // !_POINT_H