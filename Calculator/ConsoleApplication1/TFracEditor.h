#pragma once

#include "TFrac.h"
#include <iostream>

#define MODE_A true
#define MODE_B false

enum Command
{
	C_MC = 16,
	C_MR,
	C_MS,
	C_MPLUS,
	C_CE,
	C_C,
	C_BS,
	C_SQR,
	C_1DIVX,
	C_DIV,
	C_MUL,
	C_SUB,
	C_ADD,
	C_EQ,
	C_DOT,
	C_NEG,
	C_CONV,
	C_COPY,
	C_PAST
};

class TFracEditor
{
private:
	std::string _string;
	static const std::string _stringNull;
	static const std::string separator;
	bool mode;
public:
	TFracEditor();
	~TFracEditor();

	bool IsZero();
	std::string ToString();
	std::string setSign();
	std::string addNum(int);

	void changeMode(bool);

	std::string erase();
	std::string clear();
	bool getMode();
	string Set_S(string new_s);
	string Edit(int i);
	bool IsBEmpty();
};
