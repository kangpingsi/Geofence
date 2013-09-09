#pragma once
#include "LinearRing.h"

class OuterBoundary
{
public:
	LinearRing* lr;
	OuterBoundary(LinearRing* lr);
	~OuterBoundary(void);
};

