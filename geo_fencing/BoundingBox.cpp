#include "stdafx.h"
#include "BoundingBox.h"
#include <algorithm>



BoundingBox::BoundingBox(OuterBoundary* OB)
{
	int i = 0;
	for (Point* pt: OB->lr->pointList)
	{
		if (i==0)
		{
			left = pt->Get_X();
			right = pt->Get_X();
			up = pt->Get_Y();
			bottom = pt->Get_Y();
			i = 1;
		}
		else
		{
			left = std::min(left,pt->Get_X());
			right = std::max(right,pt->Get_X());
			up = std::max(up,pt->Get_Y());
			bottom = std::min(bottom,pt->Get_Y());
		}
	}
}


BoundingBox::~BoundingBox(void)
{
}
