#include"VariablesMap.h"
#include"ScriptExceptions.h"
#include <algorithm>  
#include <ctime>

string VariablesMap::GetTmpVariable()
{
	bool tmpVarFound = true; // init tmp var as found in saved var or current map

	int len = 5;
	string tmpVarName;

	// Randomize tmp variable string name until valid under constraints.
	while (tmpVarFound)
	{
		tmpVarName = genRandomString(len);
		if (!isVarNameValid(tmpVarName)) // not valid tmp var name, randomize name again
			continue;

		auto it = varsMap_.find(tmpVarName);
		if ((it == varsMap_.end()) && (tmpVarName.compare(savedName_)) != 0) // not found
			tmpVarFound = false;
	}

	if (tmpVarFound)
	{
		return (""); // Not happening...
	}
	VarPtr pVar;
	varsMap_.insert(pair<string, VarPtr>(tmpVarName, pVar));
	tmpVarsList_.push_back(tmpVarName); // add tmp var name to list
	return (tmpVarName);
}


void VariablesMap::ClearTmpVars()
{
	// scan list of tmp vars, delete each one from map
	for (list<string>::iterator it = tmpVarsList_.begin(); it != tmpVarsList_.end(); it++)
	{
		varsMap_.erase(*it);
	}
	tmpVarsList_.clear(); // clear tmp vars list
}


VarPtr& VariablesMap::operator[](const string& x)
{
	if (!isVarNameValid(x))
		throw INVALID_VAR_NAME(x);
	
	auto it = varsMap_.find(x);
	if (it == varsMap_.end()) // not found
	{
		VarPtr pVar;
		varsMap_[x] = pVar;
	}
	return varsMap_[x];
}


/*const VarPtr& VariablesMap::operator[](const string& x) const
{
	if (!isVarNameValid(x))
		throw INVALID_VAR_NAME(x);

	auto it = varsMap_.find(x);
	if (it == varsMap_.end()) // not found
	{
		VarPtr pVar();
		varsMap_[x] = pVar;
	}
	return varsMap_[x];
}*/


VarPtr& VariablesMap::at(const string& x)
{
	return (varsMap_.at(x)); // If key does not match the key of any element in the map, throws an out_of_range exception.
}


void VariablesMap::erase(const string& x)
{
	varsMap_.erase(x);

	// Check if x appears in temp variables list and erase it
	for (list<string>::iterator it = tmpVarsList_.begin(); it != tmpVarsList_.end(); it++)
		if ((*it).compare(x) == 0)
			tmpVarsList_.erase(it);
}


bool VariablesMap::isVarNameValid(string x)
{
	char c = x.at(0);
	string alphaChars = VALID_ALPHA_CHARS;
	string alphaNumChars = VALID_VAR_CHARS;

	size_t pos_c = alphaChars.find_first_of(c, 0);
	if (pos_c == string::npos) // c not found in alpha chars
		return false;

	for (string::iterator it = x.begin(); it != x.end(); it++)
	{
		size_t pos_c = alphaNumChars.find_first_of(*it, 0);
		if (pos_c == string::npos) // not found in alpha-numeric chars
			return false;
	}
	return true;
}


string VariablesMap::genRandomString(int len)
{
	/*srand(time(0)); // needs ctime header.
	auto randchar = []() -> char
	{
		const size_t max_index = (sizeof(VALID_VAR_CHARS) - 1);
		return VALID_VAR_CHARS[rand() % max_index];
	};
	string str(len, 0);
	generate_n(str.begin(), len, randchar);
	return str;*/

	//int numAlphaNum = sizeof(VALID_VAR_CHARS);
	string strRnd(VALID_VAR_CHARS_SIZE, 'a');

	for (int i = 0; i < len; ++i)
	{
		int tmpInd = rand() % (sizeof(VALID_VAR_CHARS) - 1);
		strRnd[i] = VALID_VAR_CHARS[tmpInd];
	}
	// strRnd[len] = 0;

	return strRnd;
}
