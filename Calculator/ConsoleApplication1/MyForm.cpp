#include "stdafx.h"

#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	ConsoleApplication1::MyForm form;
	Application::Run(%form);
}