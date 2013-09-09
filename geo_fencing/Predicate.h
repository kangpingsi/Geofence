#pragma once
#include <string>
#include <vector>
#include <sstream>

enum Pred {INSIDE,WITHIN};

using namespace std;

class Predicate
{
private:
	std::string argv_pred, argv_dist;
	Pred p;
	double Dist;

	bool Predicate::case_Insen_Str_Comp(const string& str1, const string& str2);
public:
	Predicate(string pred, string dist) 
	{
		this->argv_pred = pred;
		this->argv_dist = dist;
	} 
	Predicate(string pred)
	{
		this->argv_pred = pred;
	}
	Pred Get_p() { return this->p; }
	double Get_Dist() {return this->Dist;}
	bool Validate_Argv();
	~Predicate(void);
};

