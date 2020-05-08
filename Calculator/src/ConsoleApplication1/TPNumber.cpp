#include "stdafx.h"
#include "TPNumber.h"

void _reverse(string &str)
{
	char temp[1];
	for (int i = 0, size = str.length(); i < size / 2; i++)
	{
		temp[0] = str[i];
		str[i] = str[str.length() - i - 1];
		str[str.length() - i - 1] = temp[0];
	}
}

double new_strtof(string ostr, unsigned char base)
{
	string comp[] = { "A", "B", "C", "D", "E", "F" };
	string _regex = "(-?)([0-" + (base <= 10 ? to_string(base - 1) : "9A-" + comp[base - 11]) + "]*)(\\,?)([0-" + (base <= 10 ? to_string(base - 1) : "9A-" + comp[base - 11]) + "]*)";
	if (!std::regex_match(ostr, regex(_regex)))
		throw("Неверное представление P числа");

	char *str = (char*)malloc(ostr.length() + 1);
	strcpy(str, ostr.c_str());
	const char* dot = ",";
	char *cbefore_the_dot = strtok(str, dot);
	char *cafter_the_dot = strtok(NULL, dot);
	double f = (double)strtol(cbefore_the_dot, 0, base);
	int i, sign = (str[0] == '-' ? -1 : 1);
	char n[2] = { 0 };

	if(cafter_the_dot)
		for (i = 0; cafter_the_dot[i]; i++)
		{
			n[0] = cafter_the_dot[i];
			f += strtol(n, 0, base) * pow(base, -(i + 1))*sign;
		}
	free(str);
	//printf("result: %f\n", f);
	return f;
}

string TPNumber::toString()
{
	string str("");
	char temp[1];
	strcpy(temp, "");
	double result = 0;
	bool isPlus = n > 0 ? true : false;
	int extra = (int)_CMATH_::abs(n);
	//printf("---n: %d b:%d---\n", extra, b);
	if (extra)
	{
		int i;
		while (extra >= b)
		{
			i = extra % b;
			//printf("\ni[%d]\n", i);
			temp[0] = i < 10 ? '0' + (char)(i) : 'A' + (char)(i - 10);
			temp[1] = '\0';
			str += temp;
			extra /= b;
		}
		if (extra)
		{
			temp[0] = extra < 10 ? '0' + (char)(extra) : 'A' + (char)(extra - 10);
			temp[1] = '\0';
			str += temp;
		}
		if (!isPlus)
		{
			temp[0] = '-';
			temp[1] = '\0';
			str += temp;
		}
		std::reverse(str.begin(), str.end());
	}
	else
	{
		temp[0] = '0';
		temp[1] = '\0';
		str += temp;
	}
	double f2 = _CMATH_::fabs(n) - (int)_CMATH_::abs(n);
	//printf("f2: %f\n", f2);
	if (f2 > 0)
	{
		temp[0] = ',';
		temp[1] = '\0';
		str += temp;
		for (int i = 0; i < c; i++)
		{
			f2 *= b;
			//printf("--f2: %lf %d\n", f2, (int)f2);
			temp[0] = f2 < 10 ? '0' + (char)((int)f2) : 'A' + (char)((int)f2 - 10);
			str += temp;
			f2 = f2 - (int)f2;
			if (f2 == 0.0)break;
		}
	}
	return str;
}

TPNumber::TPNumber(double n, int b, int c)
{
	this->b = b;
	if (this->b < 2 || this->b > 16)
		throw("Недопустимое основание числа");
	this->n = n;
	this->c = c;
	if (this->c < 0)
		throw("Недопустимая точность числа");
}

TPNumber::TPNumber()
{
	this->b = 10;
	this->n = 0;
	this->c = 2;
}

TPNumber::TPNumber(string n, string b, string c)
{
	this->b = stoi(b);
	if (this->b < 2 || this->b > 16)
		throw("Недопустимое основание числа");
	this->n = new_strtof(n, this->b);
	this->c = stoi(c);
	if (this->c < 0)
		throw("Недопустимая точность числа");
}

TPNumber TPNumber::operator+(TPNumber other)
{
	return TPNumber(n + other.n, b, c);
}

TPNumber TPNumber::operator-(TPNumber other)
{
	return TPNumber(n - other.n, b, c);
}

TPNumber TPNumber::operator*(TPNumber other)
{
	return TPNumber(n * other.n, b, c);
}

TPNumber TPNumber::operator/(TPNumber other)
{
	return TPNumber(n / other.n, b, c);
}

TPNumber TPNumber::copy()
{
	return TPNumber(n, b, c);
}

TPNumber TPNumber::reverse()
{
	return TPNumber(1 / n, b, c);
}

TPNumber TPNumber::sqr()
{
	return TPNumber(n * n, b, c);
}

double TPNumber::getN()
{
	return n;
}

int TPNumber::getB()
{
	return b;
}

int TPNumber::getC()
{
	return c;
}

string TPNumber::BtoString()
{
	return to_string(b);
}

string TPNumber::CtoString()
{
	return to_string(c);
}

bool TPNumber::setB(int _b)
{
	if (_b >= 2 && _b <= 16)
	{
		b = _b;
		return true;
	}
	return false;
}

bool TPNumber::setC(int _c)
{
	if (_c >= 0)
	{
		c = _c;
		return true;
	}
	return false;
}

bool TPNumber::setB(string _b)
{
	int temp = stoi(_b);
	if (temp >= 2 && temp <= 16)
	{
		b = temp;
		return true;
	}
	return false;
}

bool TPNumber::setC(string _c)
{
	int temp = stoi(_c);
	if (temp >= 0)
	{
		c = temp;
		return true;
	}
	return false;
}

TPNumber::~TPNumber()
{
}
