#include "stdafx.h"
#include "OuterBoundary.h"


OuterBoundary::OuterBoundary(LinearRing* lr)
{
	this->lr = lr;
}


OuterBoundary::~OuterBoundary(void)
{
	delete lr;
	lr = NULL;
}
