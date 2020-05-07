#pragma once

#include <iostream>
#include <string>
#include <regex>

using namespace std;

class TFrac
{
private:
	int a, b;
	void Normalize();
public:
	TFrac();
	TFrac(int, int);
	TFrac(string);
	int getA();
	int getB();

	string AtoString();
	string BtoString();
	string ToString();

	TFrac copy();
	TFrac sqr();
	TFrac reverse();
	~TFrac();

	void reset();

	TFrac operator*(const TFrac &);
	TFrac operator+(const TFrac &);
	TFrac operator-(const TFrac &);
	TFrac operator/(const TFrac &);

	TFrac operator-();

	bool operator>(const TFrac &) const;
	bool operator<(const TFrac &) const;
	bool operator>=(const TFrac &) const;
	bool operator<=(const TFrac &) const;
	bool operator==(const TFrac &) const;

	static int TFrac_comparator(TFrac, TFrac);
};

