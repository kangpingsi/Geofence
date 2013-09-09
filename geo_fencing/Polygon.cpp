#include "stdafx.h"
#include "Polygon.h"

Polygon::Polygon(int id, int seq, OuterBoundary* outBound)
{
	this->ID = id;
	this->Seq = seq;
	this->OB = outBound;
	this->BB = new BoundingBox(this->OB);
}

void Polygon::Add_Inner_Boundary(InnerBoundary* inBound)
{
	this->IBs.push_back(inBound);
}

std::string Polygon::Print_Out()
{
	return std::to_string(this->ID) + ":" + std::to_string(this->Seq);
}

std::string Polygon::Test_Out()
{
	std::ostringstream results;
	results << this->Print_Out() << std::endl;
	results << "Outer Boundary:" << std::endl;
	for (Point* pt : this->OB->lr->pointList) 
		results << pt->Test_Out() << std::endl;

	if(this->IBs.size() != 0)
	{
		for (InnerBoundary* IB : this->IBs)
		{
			results << "Inner Boundary:" << std::endl;
			for (Point* pt : IB->lr->pointList)
				results << pt->Test_Out() << std::endl;
		}
	}
	results << "End Polygon";
	return results.str();

}


Polygon::~Polygon(void)
{
	delete this->BB;
	this->BB = NULL;

	delete this->OB;
	this->OB = NULL;

	for (InnerBoundary* IB : this->IBs){
		delete IB;
		IB = NULL;
	}
	this->IBs.clear();
	this->IBs.~vector();
}
