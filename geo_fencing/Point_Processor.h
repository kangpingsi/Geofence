#pragma once
#include "Output_unord.h"
#include "Text_File_Reader.h"
#include "Point_Factory.h"
#include "Polygon_File.h"
#include "Point.h"

class Point_Processor
{
private:
	Output_unord& out_set;
    Text_File_Reader& tr;
	Point_Factory& pfac;
	Polygon_File& pfile;

public:

	Point_Processor(Output_unord& _out, Text_File_Reader& _tr, Point_Factory& _pfac, Polygon_File& _pf): 
		out_set(_out), tr(_tr), pfac(_pfac), pfile(_pf){}
	
	void operator() ();
public:
	Point_Processor(void);
	~Point_Processor(void);
};

