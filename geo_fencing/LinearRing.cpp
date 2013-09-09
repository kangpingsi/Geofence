#include "stdafx.h"
#include "LinearRing.h"


LinearRing::LinearRing(void)
{
	this->length = 0;
}

int LinearRing::Get_Length()
{
	return this->length;
}

void LinearRing::Add_Point(Point* pt)
{
	this->pointList.push_back(pt);
	this->length++;
}

LinearRing::~LinearRing(void)
{
	for (Point* pt :this->pointList)
	{
		delete pt;
		pt = NULL;
	}
	pointList.clear();
	pointList.~vector();
}
