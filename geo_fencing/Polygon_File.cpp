#include "stdafx.h"
#include "Polygon_File.h"
#include <sstream>
#include <iostream>
#include <string>

Polygon_File::Polygon_File(Predicate* p)
{
	this->option = p;
	this->n_Polygons = 0;
	this->n_MPs	= 0;
}

void Polygon_File::Add(Polygon* poly)
{
	if (Moving_Polygons.find(poly->Get_ID()) != Moving_Polygons.end()) Moving_Polygons[poly->Get_ID()]->Add(poly);
	else 
	{
		Moving_Polygon* MP = new Moving_Polygon(poly->Get_ID());
		MP->Add(poly);
		Moving_Polygons[poly->Get_ID()] = MP;
	}
}


std::string Polygon_File::Process_One_Pt(Point *pt)
{
	std::ostringstream results;
	std::string msg("");
	switch(this->option->Get_p())
	{
		case Pred::INSIDE:
		{
			auto it = Moving_Polygons.cbegin();
			while(it != Moving_Polygons.cend())
			{
				msg = it->second->Predicate_Inside(pt);
				if (msg.compare("") != 0) results << msg << std::endl;
				++it;
			}
			break;
		}
		case Pred::WITHIN:
		{
			auto it = Moving_Polygons.cbegin();
			while(it != Moving_Polygons.cend())
			{
				msg = it->second->Predicate_Within(pt,this->option->Get_Dist());
				if (msg.compare("") != 0) results << msg << std::endl;
				++it;
			}
			break;
		}
		default: std::cout<<"predicate word is incorrect!" << std::endl;
			     break;
	}
	return results.str();
}

Polygon_File::~Polygon_File(void)
{
	delete this->option;
	this->option = NULL;

	for (const auto &mp : this->Moving_Polygons)
	{
		delete mp.second;
	}
	this->Moving_Polygons.clear();
}

//for testing
void Polygon_File::test_out()
{
	for (const auto & pair :this->Moving_Polygons)
	{
		std::cout << "ID "<< pair.first << ":" << std::endl;
		pair.second->test_out();		
	}
}
