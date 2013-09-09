#pragma once
#include "OuterBoundary.h"

class BoundingBox
{
private:
	double left, right, up, bottom;
public:
	BoundingBox(OuterBoundary* OB);
	double Get_Left(){return left;}
	double Get_Right() {return right;}
	double Get_Up()	{return up;}
	double Get_Bottom() {return bottom;}
	~BoundingBox(void);
};

