#include "stdafx.h"
#include "Moving_Polygon.h"
#include <iostream>

std::string Moving_Polygon::Predicate_Inside(Point *pt)
{
	Polygon* poly = NULL;
	int key = -1;

	/*
	for (const auto &p : this->poly_list)
	{
		if (pt->Get_Seq() >= p.first) poly = p.second;
		else break;
	}
	if (poly != NULL)
	*/

	key = find_key(pt->Get_Seq());

    if (key != -1)
	{
		poly = this->poly_list.find(key)->second;
		if (pt->ArcInside(poly))
		{
			return pt->Print_Out() + ":" + poly->Print_Out();
		}
		else return "";
	}
	else return "";

}

std::string Moving_Polygon::Predicate_Within(Point *pt, double dist)
{
	Polygon* poly = NULL;
	int key = -1;

	/*
	for (const auto &p : this->poly_list)
	{
		if (pt->Get_Seq() >= p.first) poly = p.second;
		else break;
	}
	if (poly != NULL)
	*/

	key = find_key(pt->Get_Seq());

    if (key != -1)
	{
		poly = this->poly_list.find(key)->second;
		if (pt->Within(poly, dist))
		{
			return pt->Print_Out() + ":" + poly->Print_Out();
		}
		else return "";
	}
	else return "";
}

int Moving_Polygon::find_key(int pt_seq)
{
	std::map<int, Polygon*>::iterator cp;
	cp = this->poly_list.upper_bound(pt_seq);
	if (cp == this->poly_list.end())
	{
		return this->poly_list.rbegin()->first;
	}
	else
	{
		cp--;
		if (cp == this->poly_list.end())
		{
			//means there is no polygon meets the criteria
			return -1;
		}
		else
		{
			return  cp->first;
		}
	}
}

void Moving_Polygon::Extract_Keys()
{
	for (std::map<int,Polygon*>::iterator it = this->poly_list.begin();it!= this->poly_list.end(); ++it)
	{
		keys.push_back(it->first);
	}
}

Moving_Polygon::~Moving_Polygon(void)
{
	for (const auto &p : this->poly_list)
	{
		delete p.second;
	}
	this->poly_list.clear();
	//this->poly_list._Destroy_if_not_nil;
}

void Moving_Polygon::test_out()
{
	for (const auto &p :this->poly_list)
	{
		std::cout << p.second->Get_Seq() << std::endl;
	}
}

/*
int Moving_Polygon::find_key(int pt_seq)
{
	//if (this->keys.size == 0) this->Extract_Keys();

	int left,right,mid;
	if (pt_seq < keys.front()) return -1;
	else if (pt_seq >= keys.back()) return keys.back();
	else
	{
		left = 0;
		right = keys.size() - 1;
		mid = (left + right) >> 1;
		while (true)
		{
			if (mid == left || mid == right) break;
			
			if (pt_seq < keys[mid]) right = mid;   //moving left
			else left = mid;                       //moving right

			mid = (left + right) >> 1; 
		}
	}
	return keys[mid];
}
*/