#include "stdafx.h"

#include "History.h"

History::History()
{
}

History::~History()
{
}

void History::AddRecord(int op, string num1, string num2, string res)
{
	string temp;
	if (op == Command::C_1DIVX || op == (int)Command::C_SQR)
		temp += get_op(op) + " " + num2 + " = " + res + "\n";
	temp += num1 + " " + get_op(op) + " " + num2 + " = " + res + "\n";
	_str += temp;
}
string History::get_op(int op)
{
	string r = "";

	switch (op)
	{
	case Command::C_ADD:
		r = "+";
		break;
	case Command::C_SUB:
		r = "-";
		break;
	case Command::C_MUL:
		r = "*";
		break;
	case Command::C_DIV:
		r = "/";
		break;
	case Command::C_SQR:
		r = "sqr";
		break;
	case Command::C_1DIVX:
		r = "rev";
		break;
	}

	return r;
}

void History::clear()
{
	_str.clear();
}