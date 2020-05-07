#pragma once

#include "TFracEditor.h"
#include <string>

using namespace std;

class History
{
public:
	string _str;
	History();
	~History();
	void AddRecord(int op, string num1, string num2, string res);
	string get_op(int op);
	void clear();
};
