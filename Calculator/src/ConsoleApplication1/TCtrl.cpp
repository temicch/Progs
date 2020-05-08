#include "stdafx.h"

#include "TCtrl.h"

TCtrl::TCtrl()
{
	state = Ctrl_State::Start;
}

TCtrl::~TCtrl()
{
}

void TCtrl::Reset()
{
	state = Ctrl_State::Start;
	editor.clear();
	processor.ReSet();
	memory.clear();
	number.reset();
}

TCtrl::Ctrl_State TCtrl::Get_State()
{
	return state;
}

void TCtrl::Set_State(Ctrl_State st)
{
	state = st;
}

string TCtrl::Do_Cmd(int i)
{
	if (i == (int)Command::C_C)
	{
		Reset();
		return number.ToString();
	}

	if (i >= 0 && i <= 9 ||
		i == (int)Command::C_DOT ||
		i == (int)Command::C_NEG ||
		i == (int)Command::C_CE ||
		i == (int)Command::C_BS)
		return Do_Edit(i);

	if (i >= (int)Command::C_MC && i <= (int)Command::C_MPLUS)
		return Do_Memory(i);

	if (i == (int)Command::C_SQR || i == (int)Command::C_1DIVX)
		return Do_Func(i);

	if (i >= (int)Command::C_DIV && i <= (int)Command::C_ADD)
		return Do_Operation(i);

	if (i == (int)Command::C_EQ)
		return Do_Calculation(i);


	if (i == (int)Command::C_COPY || i == (int)Command::C_PAST)
		return Do_Clipboard(i);

	throw 0;
}

string TCtrl::Do_Edit(int i)
{
	if (state == Ctrl_State::FunDone)
		return editor.ToString();

	if (state == Ctrl_State::OpChange)
		editor.clear();

	state = Ctrl_State::Editing;
	return editor.Edit(i);
}

string TCtrl::Do_Operation(int i)
{
	string res = editor.ToString();
	string num1, num2;
	int op;
	switch (state)
	{
	case Ctrl_State::Editing:

		if (processor.OprtnGet() != TOprtn::None)
		{
			processor.Rop_Set(TFrac(res));

			op = (int)processor.OprtnGet();
			num1 = processor.Lop_Res_Get().ToString();
			num2 = processor.Rop_Get().ToString();

			res = processor.OprtnRun();

			history.AddRecord(op, num1, num2, res);
			processor.OprtnSet((TOprtn)i);
		}
		else
		{
			processor.Lop_Res_Set(TFrac(res));
			processor.Rop_Set(TFrac(res));
			processor.OprtnSet((TOprtn)i);
		}

		break;

	case Ctrl_State::OpChange:

		processor.OprtnSet((TOprtn)i);
		break;

	case Ctrl_State::FunDone:

		if (processor.OprtnGet() != TOprtn::None)
		{
			op = (int)processor.OprtnGet();
			num1 = processor.Lop_Res_Get().ToString();
			num2 = processor.Rop_Get().ToString();

			res = processor.OprtnRun();

			history.AddRecord(op, num1, num2, res);
			processor.OprtnSet((TOprtn)i);
		}
		else
		{
			processor.Lop_Res_Set(TFrac(res));
			processor.OprtnSet((TOprtn)i);
		}

		break;
	}

	state = Ctrl_State::OpChange;
	editor.Set_S(res);

	return res;
}

string TCtrl::Do_Func(int i)
{
	string res = editor.ToString();
	string num1, num2;
	int op;

	switch (state)
	{
	case Ctrl_State::Editing:
		state = Ctrl_State::FunDone;
		processor.Rop_Set(TFrac(res));
		processor.FuncSet((TFunc)i);

		op = (int)processor.FuncGet();
		num1 = processor.Lop_Res_Get().ToString();
		num2 = processor.Rop_Get().ToString();

		res = processor.FuncRun();
		history.AddRecord(op, num1, num2, res);

		break;

	case Ctrl_State::FunDone:
		processor.FuncSet((TFunc)i);

		op = (int)processor.FuncGet();
		num1 = processor.Lop_Res_Get().ToString();
		num2 = processor.Rop_Get().ToString();

		res = processor.FuncRun();
		history.AddRecord(op, num1, num2, res);

		break;
	}

	editor.Set_S(res);
	return res;
}

string TCtrl::Do_Calculation(int i)
{
	string res = editor.ToString();
	string num1, num2;
	int op;

	switch (state)
	{
	case Ctrl_State::OpChange:

		op = (int)processor.OprtnGet();
		num1 = processor.Lop_Res_Get().ToString();
		num2 = processor.Rop_Get().ToString();

		res = processor.OprtnRun();
		history.AddRecord(op, num1, num2, res);

		break;

	case Ctrl_State::FunDone:

		if (processor.OprtnGet() != TOprtn::None)
		{
			op = (int)processor.OprtnGet();
			num1 = processor.Lop_Res_Get().ToString();
			num2 = processor.Rop_Get().ToString();

			res = processor.OprtnRun();
			history.AddRecord(op, num1, num2, res);
		}
		else
		{
			op = (int)processor.FuncGet();
			num1 = processor.Lop_Res_Get().ToString();
			num2 = processor.Rop_Get().ToString();

			res = processor.FuncRun();
			history.AddRecord(op, num1, num2, res);
		}

		break;
	case Ctrl_State::Editing:

		processor.Rop_Set(TFrac(res));
		op = (int)processor.OprtnGet();
		num1 = processor.Lop_Res_Get().ToString();
		num2 = processor.Rop_Get().ToString();

		res = processor.OprtnRun();
		history.AddRecord(op, num1, num2, res);

		state = Ctrl_State::OpChange;
		break;
	}

	editor.Set_S(res);

	return res;
}

string TCtrl::Do_Memory(int i)
{
	string res = editor.ToString();

	switch ((Command)i)
	{
	case Command::C_MC:
		memory.clear();
		break;

	case Command::C_MS:
		memory.write(TFrac(res));
		break;

	case Command::C_MPLUS:
		memory += TFrac(res);
		break;

	case Command::C_MR:
		if (state != Ctrl_State::FunDone)
		{
			state = Ctrl_State::Editing;
			res = memory.get().ToString();
			editor.Set_S(res);
		}

		break;
	}

	return res;
}

string TCtrl::Do_Clipboard(int i)
{
	string res = editor.ToString();
	return res;
}