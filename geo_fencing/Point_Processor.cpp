#include "stdafx.h"
#include "Point_Processor.h"


void Point_Processor::operator() ()
{
	string line;
	Point *pt;
	while(true)
	{ 
		line = tr.Get_new_line();
		if(line.compare("END_OF_FILE") != 0)
		{
			//read one point
			if (line.compare("") != 0) 
			{
				pt = pfac.Get_Point(line);

				//process this point
				string msg = pfile.Process_One_Pt(pt);
				if(msg.compare("") != 0) //out_set.Add(pt->Get_ID(),msg);
					out_set.Add(msg);

				delete pt;
				pt = NULL;
			}
		}
		else break;
	}
}

Point_Processor::~Point_Processor(void)
{
}
