#pragma once

//#include "TFracEditor.h"
#include "TProc.h"
#include "History.h"
#include "TMemory.h"

class TCtrl
{
	enum Ctrl_State 
	{ 
		Start, 
		Editing, 
		FunDone, 
		OpChange 
	};

	Ctrl_State state;
	TProc <TFrac> processor;
	TMemory <TFrac> memory;
	TFrac number;

	int notation, not_copy, not_paste;

public:
	History history;
	TFracEditor editor;
	void Reset();
	TCtrl();
	~TCtrl();
	Ctrl_State TCtrl::Get_State();
	void Set_State(Ctrl_State st);
	string TCtrl::Do_Cmd(int i);
	string Do_Edit(int i);
	string Do_Operation(int i);
	string Do_Func(int i);
	string Do_Calculation(int i);
	string Do_Memory(int i);
	string Do_Clipboard(int i);
};
