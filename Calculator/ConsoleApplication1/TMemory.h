#pragma once

#include<string>

using namespace std;

template <class Type>
class TMemory
{
	bool FState;
	Type *FNumber;
public:
	enum
	{
		_On = true,
		_Off = false
	};
	void write(Type);
	Type get();

	void clear();
	string getState();

	TMemory();
	TMemory(string);
	TMemory(Type);
	~TMemory();

	void operator+=(Type);
	void operator-=(Type);
};

template <class Type>
TMemory<Type>::TMemory(string str) : FState(_Off)
{
	this->FNumber = new Type(str);
}

template <class Type>
TMemory<Type>::TMemory(Type typ) : FState(_Off)
{
	this->FNumber = typ.copy();
}

template <class Type>
TMemory<Type>::TMemory() : FState(_Off)
{
	this->FNumber = new Type;
}

template <class Type>
TMemory<Type>::~TMemory()
{
	delete this->FNumber;
}

template <class Type>
void TMemory<Type>::write(Type E)
{
	*FNumber = E.copy();
	FState = _On;
}

template <class Type>
Type TMemory<Type>::get()
{
	return FNumber->copy();
}

template <class Type>
void TMemory<Type>::operator+=(Type other)
{
	*this->FNumber = FNumber->copy() + other;
	FState = _On;
}

template <class Type>
void TMemory<Type>::operator-=(Type other)
{
	*this->FNumber = FNumber->copy() - other;
	FState = _On;
}

template <class Type>
void TMemory<Type>::clear()
{
	delete FNumber;
	FNumber = new Type;
	FState = _Off;
}

template <class Type>
string TMemory<Type>::getState()
{
	string _FState = FState ? "On" : "Off";
	return _FState;
}