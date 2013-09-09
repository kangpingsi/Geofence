#pragma once
#include "LinearRing.h"

class InnerBoundary
{
public:
	LinearRing* lr;
	InnerBoundary(LinearRing* lr);
	~InnerBoundary(void);
};

