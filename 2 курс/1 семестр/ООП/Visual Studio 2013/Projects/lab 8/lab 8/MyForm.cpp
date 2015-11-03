#include "MyForm.h"
#include "MyForm1.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	lab8::MyForm form;
	lab8::MyForm1 form1;
	Application::Run(%form);
	Application::Run(%form1);
}
