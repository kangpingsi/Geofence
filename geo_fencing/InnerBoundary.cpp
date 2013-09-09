#include "stdafx.h"
#include "InnerBoundary.h"


InnerBoundary::InnerBoundary(LinearRing* lr)
{
	this->lr = lr;
}


InnerBoundary::~InnerBoundary(void)
{
	delete lr;
	lr = NULL;
}
