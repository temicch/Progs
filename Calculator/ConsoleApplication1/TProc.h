#pragma once

#include<string>
#include "TFracEditor.h"

using namespace std;

enum TOprtn
{
	None,
	Add = Command::C_ADD,
	Sub = Command::C_SUB,
	Mul = Command::C_MUL,
	Dvd = Command::C_DIV
};

enum TFunc
{
	Rev = Command::C_1DIVX,
	Sqr = Command::C_SQR
};

template <class Type>
class TProc
{
	Type *Lop_Res, *Rop;
public:
	TOprtn Operation;
	TFunc Function;
	TProc();
	~TProc();
	void ReSet();

	void OprtnClear();
	string OprtnRun();
	TOprtn OprtnGet();
	void OprtnSet(TOprtn);

	TFunc FuncGet();
	void FuncSet(TFunc);
	string FuncRun();
	
	void Lop_Res_Set(Type);
	void Rop_Set(Type);

	Type Lop_Res_Get();
	Type Rop_Get();
};


template <class Type>
TProc<Type>::TProc()
{
	this->Lop_Res = new Type;
	this->Rop = new Type;
	this->Operation = TOprtn::None;
}

template <class Type>
TProc<Type>::~TProc()
{
	delete this->Lop_Res;
	delete this->Rop;
}

template <class Type>
void TProc<Type>::ReSet()
{
	delete this->Lop_Res;
	delete this->Rop;
	this->Lop_Res = new Type;
	this->Rop = new Type;
	OprtnClear();
}

template <class Type>
void TProc<Type>::OprtnClear()
{
	Operation = TOprtn::None;
}

template <class Type>
string TProc<Type>::OprtnRun()
{
	switch (Operation)
	{
	case TOprtn::Add: *Lop_Res = *Lop_Res + *Rop; break;
	case TOprtn::Sub: *Lop_Res = *Lop_Res - *Rop; break;
	case TOprtn::Mul: *Lop_Res = *Lop_Res * *Rop; break;
	case TOprtn::Dvd: *Lop_Res = *Lop_Res / *Rop; break;
	default: break;
	}
	return this->Lop_Res_Get().ToString();
}

template <class Type>
void TProc<Type>::Lop_Res_Set(Type Operand)
{
	*Lop_Res = Operand.copy();
}

template <class Type>
void TProc<Type>::Rop_Set(Type Operand)
{
	*Rop = Operand.copy();
}

template <class Type>
Type TProc<Type>::Lop_Res_Get()
{
	return this->Lop_Res->copy();
}

template <class Type>
Type TProc<Type>::Rop_Get()
{
	return this->Rop->copy();
}

template <class Type>
TOprtn TProc<Type>::OprtnGet()
{
	return this->Operation;
}

template <class Type>
void TProc<Type>::OprtnSet(TOprtn oprtn)
{
	this->Operation = oprtn;
}

template <class Type>
string TProc<Type>::FuncRun()
{
	switch (this->Function)
	{
	case TFunc::Rev:	*Rop = this->Rop->reverse();	break;
	case TFunc::Sqr:	*Rop = this->Rop->sqr();		break;
	}
	return this->Rop->ToString();
}

template <class Type>
void TProc<Type>::FuncSet(TFunc f)
{
	this->Function = f;
}

template <class Type>
TFunc TProc<Type>::FuncGet()
{
	return this->Function;
}