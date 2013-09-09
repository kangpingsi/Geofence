#include "stdafx.h"
#include "Predicate.h"


bool Predicate::Validate_Argv()
{
	if (argv_pred.compare("") == 0) return false;
	//inside
	if (case_Insen_Str_Comp(argv_pred,"INSIDE")) 
	{
		if (argv_dist != "") return false;
		p = Pred::INSIDE;
		return true;
	}
	//not inside
	else if(! case_Insen_Str_Comp(argv_pred, "WITHIN")) return false;
	else
	{
		if (argv_dist == "") return false;
		else this->Dist = stod(argv_dist);
		if (Dist < 0) return false;
		else 
		{
			p = Pred::WITHIN;
			return true;
		}
	}
}


bool Predicate::case_Insen_Str_Comp(const string& str1, const string& str2) {
    if (str1.size() != str2.size()) {
        return false;
    }
    for (string::const_iterator c1 = str1.begin(), c2 = str2.begin(); c1 != str1.end(); ++c1, ++c2) {
        if (tolower(*c1) != tolower(*c2)) {
            return false;
        }
    }
    return true;
}

Predicate::~Predicate(void)
{
}