#include "stdafx.h"
#include "Point.h"
#include "Polygon.h"
#include "BoundingBox.h"
#include <iostream>



Point::Point(double x,double y)
{
	this->x = x;
	this->y = y;
}

Point::Point(double x, double y, int id, int seq){
	this->x = x;
	this->y = y;
	this->ID = id;
	this->Seq = seq;
}

bool Point::operator==(const Point& pt)
{
	if ((this->x == pt.Get_X()) && (this->y == pt.Get_Y())){ return true;}
	else return false;
}

double Point::Distance(Point* pt)
{
	return sqrt(pow((this->x - pt->Get_X()),2) + pow((this->y - pt->Get_Y()),2));
}

inline double Point::Sqr_Distance(Point* pt)
{
	return (this->x - pt->Get_X()) * (this->x - pt->Get_X()) + (this->y - pt->Get_Y())* (this->y - pt->Get_Y());
}


bool Point::Point_In_Line(Point* st_pt, Point* end_pt)
{
	double min_x, max_x, min_y, max_y, temp;
	min_y = std::min(st_pt->Get_Y(), end_pt->Get_Y());
	max_y = std::max(st_pt->Get_Y(), end_pt->Get_Y());

	min_x = std::min(st_pt->Get_X(), end_pt->Get_X());
	max_x = std::max(st_pt->Get_X(), end_pt->Get_X());

	if (this->Get_Y() > max_y || this->Get_Y() < min_y)
	{
		return false;
	}
	else if (this->Get_X() > max_x || this->Get_X() < min_x)
	{
		return false;
	}
	else
	{
		temp = this->Get_Y()*(st_pt->Get_X() - end_pt->Get_X()) - (st_pt->Get_Y() - end_pt->Get_Y())*(this->Get_X() - st_pt->Get_X()) - st_pt->Get_Y()*(st_pt->Get_X() - end_pt->Get_X());
		return (temp == 0);
	}
} 


bool Point::Out_of_Bound(Polygon* poly)
{
	return (this->Get_X() > poly->BB->Get_Right() || (this->Get_Y() < poly->BB->Get_Left()) || (this->Get_Y() > poly->BB->Get_Up()) || (this->Get_Y() < poly->BB->Get_Bottom()));
}

int Point::Quadrant(BoundingBox* BB)
{
	if (this->Get_X() <= BB->Get_Left() && this->Get_Y() >= BB->Get_Up()) return 1;
	if (this->Get_X() > BB->Get_Left() && this->Get_X() < BB->Get_Right() && this->Get_Y() >= BB->Get_Up()) return 2;
	if (this->Get_X() >= BB->Get_Right() && this->Get_Y() >= BB->Get_Up()) return 3;
	if (this->Get_X() >= BB->Get_Right() && this->Get_Y() < BB->Get_Up() && this->Get_Y() > BB->Get_Bottom()) return 4;
	if (this->Get_X() >= BB->Get_Right() && this->Get_Y() <= BB->Get_Bottom()) return 5;
	if (this->Get_X() > BB->Get_Left() && this->Get_X() < BB->Get_Right() && this->Get_Y() <= BB->Get_Bottom()) return 6;
	if (this->Get_X() <= BB->Get_Left() && this->Get_Y() <= BB->Get_Bottom()) return 7;
	if (this->Get_X() < BB->Get_Left() && this->Get_Y() > BB->Get_Bottom() && this->Get_Y() < BB->Get_Up()) return 8;
	return 0;
}

bool Point::Within(Polygon* poly, double dist)
{
	double d = dist * dist; 
	if (this->Out_of_Bound(poly)){
		switch (this->Quadrant(poly->BB)){
		case 1 : 
			{

				//if (this->Distance(new Point(poly->BB->Get_Left(), poly->BB->Get_Up())) > dist) return false;
				if (this->Sqr_Distance(new Point(poly->BB->Get_Left(), poly->BB->Get_Up())) > d) return false;
				else break;
			}
		case 2 : 
			{
				if (this->Get_Y() - poly->BB->Get_Up() > dist) return false;
				else break;
			}
		case 3:
			{
				if (this->Sqr_Distance(new Point(poly->BB->Get_Right(), poly->BB->Get_Up())) > d) return false;
				else break;
			}
		case 4:
			{
				if (this->Get_X() - poly->BB->Get_Right() > dist) return false;
				else break;
			}
		case 5:
			{
				if (this->Sqr_Distance(new Point(poly->BB->Get_Right(), poly->BB->Get_Bottom())) > d) return false;
				else break;
			}
		case 6:
			{
				if (poly->BB->Get_Bottom() - this->Get_Y() > dist) return false;
				else break;
			}
		case 7:
			{
				if (this->Sqr_Distance(new Point(poly->BB->Get_Left(), poly->BB->Get_Bottom())) > d) return false;
				else break;
			}
		case 8:
			{
				if (poly->BB->Get_Left() - this->Get_X() > dist) return false;
				else break;
			}
		default: std::cout<<"Error occured while running within !!" << std::endl;
			break;
		}
	}

	// check all the points on the outboundary
	double a = 0;
	double b,c;
	Point* pt_A;
	Point* pt_B;

	for (unsigned int i = 0; i< poly->OB->lr->pointList.size() - 1; i++)
	{
		pt_A = poly->OB->lr->pointList[i];
		pt_B = poly->OB->lr->pointList[i+1];
		if(i == 0)
		{
			a = this->Sqr_Distance(pt_B);
			b = this->Sqr_Distance(pt_A);
			c = pt_A->Sqr_Distance(pt_B);
		}
		else
		{
			b = a;
			a = this->Sqr_Distance(pt_B);
			c = pt_A->Sqr_Distance(pt_B);
		}

		if(b + c - a <= 0) 
		{
			if(b <= d) return true;
		}
		else if (a + c - b <= 0)
		{
			if(a <= d) return true;
		}
		else if (4*a*c - (a + c - b)*(a + c -b) - 4*c*d < 0) return true;
	}

	if (poly->IBs.size() != 0)
	{
		for (InnerBoundary* IB : poly->IBs)
		{
			for (unsigned int i = 0; i< IB->lr->pointList.size() - 1; i++)
			{
				pt_A = IB->lr->pointList[i];
				pt_B = IB->lr->pointList[i+1];
				if(i == 0)
				{
					a = this->Sqr_Distance(pt_B);
					b = this->Sqr_Distance(pt_A);
					c = pt_A->Sqr_Distance(pt_B);
				}
				else
				{
					b = a;
					a = this->Sqr_Distance(pt_B);
					c = pt_A->Sqr_Distance(pt_B);
				}

				if(b + c - a <= 0) 
				{
					if(b <= d) return true;
				}
				else if (a + c - b <= 0)
				{
					if(a <= d) return true;
				}
				else if (4*a*c - (a + c - b)*(a + c -b)- 4*c*d < 0) return true;
			}

		}
	}

	if (this->ArcInside(poly)){
		return true;
	}

	return false;
}

bool Point::ArcInside(Polygon* poly)
{
	int wn = 0;
	unsigned int i, j;
	double tempvalue;

	if (this->Out_of_Bound(poly))
	{
		return false;
	}
	else
	{
		for (i = 0; i < poly->OB->lr->pointList.size()-1; i++)
		{
			Point* st_pt = poly->OB->lr->pointList[i];
			Point* end_pt = poly->OB->lr->pointList[i+1];

			//Segment seg(st_pt,end_pt);
			//tempvalue = st_pt->Distance(this) + this->Distance(end_pt);
			//if (tempvalue == st_pt->Distance(end_pt)) return true;
			if (this->Point_In_Line(st_pt, end_pt)) return true;
			else
			{
				tempvalue = (end_pt->Get_X() - st_pt->Get_X())*(this->Get_Y() - st_pt->Get_Y()) - (end_pt->Get_Y() - st_pt->Get_Y())*(this->Get_X()-st_pt->Get_X());
				if (this->Get_Y() >= st_pt->Get_Y() && this->Get_Y() < end_pt->Get_Y())
				{
					if (tempvalue >0) wn = wn + 1;
				}
				else if (this->Get_Y() < st_pt->Get_Y() && this->Get_Y() >= end_pt->Get_Y())
				{
					if (tempvalue <0) wn = wn - 1;
				}
			}
		}

		if (poly->IBs.size() != 0){
			for (InnerBoundary* IB: poly->IBs){

				for (j=0; j < IB->lr->pointList.size()-1; j++){

					Point* st_pt = IB->lr->pointList[j];
					Point* end_pt = IB->lr->pointList[j+1];

					//tempvalue = st_pt->Distance(this) + this->Distance(end_pt);
					//Segment seg(st_pt,end_pt);
					//if (tempvalue == st_pt->Distance(end_pt)) return true;
					if (this->Point_In_Line(st_pt, end_pt)) return true;
					else
					{
						tempvalue = (end_pt->Get_X() - st_pt->Get_X())*(this->Get_Y() - st_pt->Get_Y()) - (end_pt->Get_Y() - st_pt->Get_Y())*(this->Get_X()-st_pt->Get_X());
						if (this->Get_Y() >= st_pt->Get_Y() && this->Get_Y() < end_pt->Get_Y())
						{

							if (tempvalue >0) wn = wn + 1;
						}
						else if (this->Get_Y() < st_pt->Get_Y() && this->Get_Y() >= end_pt->Get_Y())
						{

							if (tempvalue <0) wn = wn - 1;
						}
					}
				}
			}
		}

		if (wn == 0) return false;
		else return true;
	}
}

std::string Point::Print_Out()
{
	return std::to_string(this->ID) + ":" + std::to_string(this->Seq);
}

std::string Point::Test_Out()
{
	//std::cout << Print_Out() <<std::endl;
	return std::to_string(Get_X()) + "," + std::to_string(Get_Y());
}

Point::~Point(void)
{
}
