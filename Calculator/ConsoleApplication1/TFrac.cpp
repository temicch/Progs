#include "stdafx.h"

#include "TFrac.h"

int gcd(int a, int b) {
	if (!a)
		return b;
	while (a != b)
		if (a > b) a -= b; else b -= a;
	return a;
}

TFrac::TFrac(int a, int b)
{
	this->a = a;
	this->b = b;
	Normalize();
}

TFrac::TFrac()
{
	this->a = 0;
	this->b = 1;
	Normalize();
}

TFrac::TFrac(string f)
{
	if (!regex_match(f, regex("(-?)(\\d+)/?(\\d+)")))
		throw("Неверное представление дроби");
	sscanf_s(f.c_str(), "%d/%d", &a, &b);
	Normalize();
}

int TFrac::getA()
{
	return a;
}

int TFrac::getB()
{
	return b;
}

void TFrac::Normalize()
{
	if (b == 0) 
		throw std::logic_error("Division by zero.");
	int _gcd = gcd(std::abs(a), std::abs(b));
	a /= _gcd;
	b /= _gcd;
	if (b < 0)
	{
		a *= -1;
		b *= -1;
	}
}

string TFrac::AtoString()
{
	return to_string(a);
}

string TFrac::BtoString()
{
	return to_string(b);
}

string TFrac::ToString()
{
	return to_string(a) + "/" + to_string(b);
}

TFrac TFrac::copy()
{
	return TFrac(a, b);
}

TFrac TFrac::sqr()
{
	return TFrac(a*a, b*b);
}

TFrac TFrac::reverse()
{
	return TFrac(b, a);
}

TFrac TFrac::operator/(const TFrac &other)
{
	return TFrac(a*other.b, b*other.a);
}

TFrac TFrac::operator*(const TFrac &other)
{
	return TFrac(a*other.a, b*other.b);
}

TFrac TFrac::operator+(const TFrac &other)
{
	return TFrac(a*(other.b) + other.a*(b), b*other.b);
}

TFrac TFrac::operator-(const TFrac &other)
{
	return TFrac(a*(other.b) - other.a*(b), b*other.b);
}

TFrac TFrac::operator-()
{
	return TFrac(-a, b);
}

int TFrac::TFrac_comparator(TFrac a, TFrac b)
{
	TFrac c = a - b;
	return c.a;
}

bool TFrac::operator>(const TFrac &other) const { return TFrac_comparator(*this, other) > 0; }
bool TFrac::operator<(const TFrac &other) const { return TFrac_comparator(*this, other) < 0; }
bool TFrac::operator>=(const TFrac &other) const { return TFrac_comparator(*this, other) >= 0; }
bool TFrac::operator<=(const TFrac &other) const { return TFrac_comparator(*this, other) <= 0; }
bool TFrac::operator==(const TFrac &other) const { return TFrac_comparator(*this, other) == 0; }

TFrac::~TFrac()
{
}

void TFrac::reset()
{
	this->a = 0;
	this->b = 1;
	Normalize();
}