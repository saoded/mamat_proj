#ifndef _VARIABLES_MAP_H_
#define _VARIABLES_MAP_H_

#include <map>
#include <algorithm> 
#include <list>
#include "Variable.h"

#define VALID_VAR_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"
#define VALID_ALPHA_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define VALID_VAR_CHARS_SIZE sizeof(VALID_VAR_CHARS)

using namespace std;

class VariablesMap
{
public:
	VariablesMap()
	{
	}

	void SetSavedName(const string& newSavedName) 
	{
		savedName_ = newSavedName;
	}

	string GetTmpVariable();
	void ClearTmpVars(); // deletes temp vars from map
	VarPtr& operator[](const string& x);
	//const VarPtr& operator[](const string& x) const;

	VarPtr& at(const string& x);
	void erase(const string& x);

	static bool isVarNameValid(string x); // verifies if x is a valid var name
	static string genRandomString(int len);

private:
	map<string, VarPtr> varsMap_;
	string savedName_;
	list<string> tmpVarsList_;
};



#endif // _VARIABLES_MAP_H_
