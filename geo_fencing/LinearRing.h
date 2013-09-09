#pragma once
#include "Point.h"
#include "stdafx.h"
#include <vector>

class LinearRing
{
private:
	int length;

public:
	LinearRing(void);
	std::vector<Point*> pointList;

	int Get_Length();
	void Add_Point(Point* pt);
	~LinearRing(void);
};

