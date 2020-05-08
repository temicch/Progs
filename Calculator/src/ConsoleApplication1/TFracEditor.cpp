#include "stdafx.h"

#include "TFracEditor.h"

const std::string TFracEditor::separator = "/";
const std::string TFracEditor::_stringNull = "0" + TFracEditor::separator + "1";

TFracEditor::TFracEditor()
{
	_string = _stringNull;
	mode = MODE_A;
}

TFracEditor::~TFracEditor()
{
}

bool TFracEditor::IsZero()
{
	if (_string == _stringNull)
		return true;
	return false;
}

std::string TFracEditor::ToString()
{
	return _string;
}

std::string TFracEditor::addNum(int a)
{
	if (mode == MODE_A)
	{
		if (_string[0] == '0')
		{
			_string[0] = '0' + a;
		}
		else if (_string[0] == '-' && _string[1] == '0')
		{
			_string[1] = '0' + a;
		}
		else
			for (unsigned int i = 0; i < _string.length(); i++)
			{
				if (_string[i] == separator.c_str()[0])
				{
					_string.insert(i, 1, ('0' + a));
					break;
				}
			}
	}
	else
	{
		for (unsigned int i = 0; i < _string.length(); i++)
		{
			if (_string[i] == separator.c_str()[0])
			{
				if (_string[i + 1] == '0')
				{
					_string[i + 1] = '0' + a;
				}
				else
				{
					_string.insert(_string.end(), ('0' + a));
				}
				break;
			}
		}
	}
	return _string;
}

std::string TFracEditor::setSign()
{
	if (_string[0] == '-')
		_string.erase(_string.begin());
	else
		_string.insert(_string.begin(), '-');
	return _string;
}

void TFracEditor::changeMode(bool mode)
{
	if (mode != MODE_A && mode != MODE_B)
		return;
	this->mode = mode;
}

std::string TFracEditor::erase()
{
	if (this->mode == MODE_A)
	{
		_string.erase(_string.find('/') - 1, 1);
		if (_string[0] == '/')
			_string.insert(_string.begin(), '0');
	}
	else
	{
		_string.erase(_string.length() - 1, 1);
		if (_string[_string.length() - 1] == '/')
			_string.insert(_string.end(), '0');
	}
	return _string;
}

std::string TFracEditor::clear()
{
	_string = _stringNull;
	return _string;
}

bool TFracEditor::getMode()
{
	return mode;
}

string TFracEditor::Set_S(string new_s)
{
	return (_string = new_s);
}
string TFracEditor::Edit(int i)
{
	switch (i)
	{
	case (int)Command::C_DOT:
		this->addNum(16);
		break;
	case (int)Command::C_BS:
		this->erase();
		break;
	case (int)Command::C_CE:
		this->clear();
		break;
	case (int)Command::C_NEG:
		this->setSign();
		break;
	default:
		this->addNum(i);
		break;
	}
	return _string;
}
bool TFracEditor::IsBEmpty()
{
	try
	{
		int a, b;
		sscanf_s(_string.c_str(), "%d/%d", &a, &b);
		if (b == 1)
			return true;
	}
	catch (...) {}
	return false;
}