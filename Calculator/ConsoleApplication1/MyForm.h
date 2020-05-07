#pragma once
#include "TCtrl.h"
#include <msclr\marshal_cppstd.h>

namespace ConsoleApplication1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	TCtrl tctrl;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{







	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel2;
	private: System::Windows::Forms::Label^  funcTxt;







	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  настройкиToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  помощьToolStripMenuItem;
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel1;
	private: System::Windows::Forms::Label^  cNum1;
	private: System::Windows::Forms::ToolStripMenuItem^  режимToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  комплексноеЧислоToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  действительноеЧислоToolStripMenuItem;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button6;

	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::ToolStripMenuItem^  историяToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  показатьToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  очиститьToolStripMenuItem;




	private: System::Windows::Forms::Panel^  panel2;
	public:
		MyForm(void)
		{
			InitializeComponent();
			btns[0] = b0;
			btns[1] = b1;
			btns[2] = b2;
			btns[3] = b3;
			btns[4] = b4;
			btns[5] = b5;
			btns[6] = b6;
			btns[7] = b7;
			btns[8] = b8;
			btns[9] = b9;

			for(int i = 0 ; i < 10; i++)
				btns[i]->Click += gcnew System::EventHandler(this, &MyForm::digit_click);
			button22->Click += gcnew System::EventHandler(this, &MyForm::digit_click);

			cNum1->Text = gcnew String(tctrl.editor.ToString().c_str());
			Memory_Change(0);
			consoleLight = button3->BackColor;
			SwitchMode();
			SwitchMode();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	bool IsNumber = false;
	private: System::Windows::Forms::Button^  button21;
	private: System::Windows::Forms::Button^  button22;
	private: System::Windows::Forms::Button^  b0;

	private: System::Windows::Forms::Button^  button24;
	private: System::Windows::Forms::Button^  button17;
	private: System::Windows::Forms::Button^  b3;

	private: System::Windows::Forms::Button^  b2;

	private: System::Windows::Forms::Button^  b1;

	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  b6;

	private: System::Windows::Forms::Button^  b5;

	private: System::Windows::Forms::Button^  b4;

	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  b9;

	private: System::Windows::Forms::Button^  b8;

	private: System::Windows::Forms::Button^  b7;

	private: System::Windows::Forms::Button^  button13;

	private: System::Windows::Forms::Button^  button15;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::Button^  button10;
	private: System::Windows::Forms::Button^  button11;
	private: System::Windows::Forms::Button^  button12;


	private: System::Windows::Forms::Button^  button29;

	private: System::Windows::Forms::Button^  button27;
	private: System::Windows::Forms::Button^  button26;
	private: System::Windows::Forms::Button^  button25;
	private: System::Windows::Forms::Panel^  panel1;
	protected:
		cli::array<Button^>^ btns = gcnew cli::array<Button^>(16);
protected:




private: System::ComponentModel::IContainer^  components;

protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		//TFracEditor TFrac();
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->button21 = (gcnew System::Windows::Forms::Button());
			this->button22 = (gcnew System::Windows::Forms::Button());
			this->b0 = (gcnew System::Windows::Forms::Button());
			this->button24 = (gcnew System::Windows::Forms::Button());
			this->button17 = (gcnew System::Windows::Forms::Button());
			this->b3 = (gcnew System::Windows::Forms::Button());
			this->b2 = (gcnew System::Windows::Forms::Button());
			this->b1 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->b6 = (gcnew System::Windows::Forms::Button());
			this->b5 = (gcnew System::Windows::Forms::Button());
			this->b4 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->b9 = (gcnew System::Windows::Forms::Button());
			this->b8 = (gcnew System::Windows::Forms::Button());
			this->b7 = (gcnew System::Windows::Forms::Button());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->button15 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->button29 = (gcnew System::Windows::Forms::Button());
			this->button27 = (gcnew System::Windows::Forms::Button());
			this->button26 = (gcnew System::Windows::Forms::Button());
			this->button25 = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->cNum1 = (gcnew System::Windows::Forms::Label());
			this->flowLayoutPanel2 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->funcTxt = (gcnew System::Windows::Forms::Label());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->историяToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->показатьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->очиститьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->настройкиToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->режимToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->комплексноеЧислоToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->действительноеЧислоToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->помощьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->flowLayoutPanel1->SuspendLayout();
			this->flowLayoutPanel2->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// button21
			// 
			this->button21->BackColor = System::Drawing::SystemColors::ControlLight;
			this->button21->FlatAppearance->BorderColor = System::Drawing::SystemColors::ControlLight;
			this->button21->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->button21->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(160)),
				static_cast<System::Int32>(static_cast<System::Byte>(216)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->button21->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(120)),
				static_cast<System::Int32>(static_cast<System::Byte>(180)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			resources->ApplyResources(this->button21, L"button21");
			this->button21->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button21->Name = L"button21";
			this->button21->TabStop = false;
			this->button21->UseVisualStyleBackColor = false;
			this->button21->Click += gcnew System::EventHandler(this, &MyForm::button21_Click);
			// 
			// button22
			// 
			this->button22->BackColor = System::Drawing::SystemColors::ControlLight;
			resources->ApplyResources(this->button22, L"button22");
			this->button22->FlatAppearance->BorderColor = System::Drawing::SystemColors::ControlLight;
			this->button22->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->button22->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Gainsboro;
			this->button22->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button22->Name = L"button22";
			this->button22->TabStop = false;
			this->button22->UseVisualStyleBackColor = false;
			this->button22->Click += gcnew System::EventHandler(this, &MyForm::button22_Click);
			// 
			// b0
			// 
			this->b0->BackColor = System::Drawing::SystemColors::ControlLight;
			this->b0->FlatAppearance->BorderColor = System::Drawing::SystemColors::ControlLight;
			this->b0->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->b0->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Gainsboro;
			resources->ApplyResources(this->b0, L"b0");
			this->b0->ForeColor = System::Drawing::SystemColors::ControlText;
			this->b0->Name = L"b0";
			this->b0->TabStop = false;
			this->b0->UseVisualStyleBackColor = false;
			// 
			// button24
			// 
			this->button24->BackColor = System::Drawing::SystemColors::ControlLight;
			this->button24->FlatAppearance->BorderColor = System::Drawing::SystemColors::ControlLight;
			this->button24->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->button24->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Gainsboro;
			resources->ApplyResources(this->button24, L"button24");
			this->button24->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button24->Name = L"button24";
			this->button24->TabStop = false;
			this->button24->UseVisualStyleBackColor = false;
			this->button24->Click += gcnew System::EventHandler(this, &MyForm::button24_Click);
			// 
			// button17
			// 
			this->button17->BackColor = System::Drawing::SystemColors::ControlLight;
			this->button17->FlatAppearance->BorderColor = System::Drawing::SystemColors::ControlLight;
			this->button17->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->button17->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(160)),
				static_cast<System::Int32>(static_cast<System::Byte>(216)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->button17->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(120)),
				static_cast<System::Int32>(static_cast<System::Byte>(180)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			resources->ApplyResources(this->button17, L"button17");
			this->button17->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button17->Name = L"button17";
			this->button17->TabStop = false;
			this->button17->UseVisualStyleBackColor = false;
			this->button17->Click += gcnew System::EventHandler(this, &MyForm::button17_Click);
			// 
			// b3
			// 
			this->b3->BackColor = System::Drawing::SystemColors::ControlLight;
			this->b3->FlatAppearance->BorderColor = System::Drawing::SystemColors::ControlLight;
			this->b3->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->b3->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Gainsboro;
			resources->ApplyResources(this->b3, L"b3");
			this->b3->ForeColor = System::Drawing::SystemColors::ControlText;
			this->b3->Name = L"b3";
			this->b3->TabStop = false;
			this->b3->UseVisualStyleBackColor = false;
			// 
			// b2
			// 
			this->b2->BackColor = System::Drawing::SystemColors::ControlLight;
			this->b2->FlatAppearance->BorderColor = System::Drawing::SystemColors::ControlLight;
			this->b2->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->b2->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Gainsboro;
			resources->ApplyResources(this->b2, L"b2");
			this->b2->ForeColor = System::Drawing::SystemColors::ControlText;
			this->b2->Name = L"b2";
			this->b2->TabStop = false;
			this->b2->UseVisualStyleBackColor = false;
			// 
			// b1
			// 
			this->b1->BackColor = System::Drawing::SystemColors::ControlLight;
			this->b1->FlatAppearance->BorderColor = System::Drawing::SystemColors::ControlLight;
			this->b1->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->b1->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Gainsboro;
			resources->ApplyResources(this->b1, L"b1");
			this->b1->ForeColor = System::Drawing::SystemColors::ControlText;
			this->b1->Name = L"b1";
			this->b1->TabStop = false;
			this->b1->UseVisualStyleBackColor = false;
			// 
			// button5
			// 
			this->button5->BackColor = System::Drawing::SystemColors::ControlLight;
			this->button5->FlatAppearance->BorderColor = System::Drawing::SystemColors::ControlLight;
			this->button5->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->button5->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(160)),
				static_cast<System::Int32>(static_cast<System::Byte>(216)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->button5->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(120)),
				static_cast<System::Int32>(static_cast<System::Byte>(180)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			resources->ApplyResources(this->button5, L"button5");
			this->button5->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button5->Name = L"button5";
			this->button5->TabStop = false;
			this->button5->UseVisualStyleBackColor = false;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// b6
			// 
			this->b6->BackColor = System::Drawing::SystemColors::ControlLight;
			this->b6->FlatAppearance->BorderColor = System::Drawing::SystemColors::ControlLight;
			this->b6->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->b6->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Gainsboro;
			resources->ApplyResources(this->b6, L"b6");
			this->b6->ForeColor = System::Drawing::SystemColors::ControlText;
			this->b6->Name = L"b6";
			this->b6->TabStop = false;
			this->b6->UseVisualStyleBackColor = false;
			this->b6->Click += gcnew System::EventHandler(this, &MyForm::b6_Click);
			// 
			// b5
			// 
			this->b5->BackColor = System::Drawing::SystemColors::ControlLight;
			this->b5->FlatAppearance->BorderColor = System::Drawing::SystemColors::ControlLight;
			this->b5->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->b5->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Gainsboro;
			resources->ApplyResources(this->b5, L"b5");
			this->b5->ForeColor = System::Drawing::SystemColors::ControlText;
			this->b5->Name = L"b5";
			this->b5->TabStop = false;
			this->b5->UseVisualStyleBackColor = false;
			// 
			// b4
			// 
			this->b4->BackColor = System::Drawing::SystemColors::ControlLight;
			this->b4->FlatAppearance->BorderColor = System::Drawing::SystemColors::ControlLight;
			this->b4->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->b4->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Gainsboro;
			resources->ApplyResources(this->b4, L"b4");
			this->b4->ForeColor = System::Drawing::SystemColors::ControlText;
			this->b4->Name = L"b4";
			this->b4->TabStop = false;
			this->b4->UseVisualStyleBackColor = false;
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::SystemColors::ControlLight;
			this->button4->FlatAppearance->BorderColor = System::Drawing::SystemColors::ControlLight;
			this->button4->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->button4->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(160)),
				static_cast<System::Int32>(static_cast<System::Byte>(216)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->button4->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(120)),
				static_cast<System::Int32>(static_cast<System::Byte>(180)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			resources->ApplyResources(this->button4, L"button4");
			this->button4->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button4->Name = L"button4";
			this->button4->TabStop = false;
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// b9
			// 
			this->b9->BackColor = System::Drawing::SystemColors::ControlLight;
			this->b9->FlatAppearance->BorderColor = System::Drawing::SystemColors::ControlLight;
			this->b9->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->b9->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Gainsboro;
			resources->ApplyResources(this->b9, L"b9");
			this->b9->ForeColor = System::Drawing::SystemColors::ControlText;
			this->b9->Name = L"b9";
			this->b9->TabStop = false;
			this->b9->UseVisualStyleBackColor = false;
			// 
			// b8
			// 
			this->b8->BackColor = System::Drawing::SystemColors::ControlLight;
			this->b8->FlatAppearance->BorderColor = System::Drawing::SystemColors::ControlLight;
			this->b8->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->b8->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Gainsboro;
			resources->ApplyResources(this->b8, L"b8");
			this->b8->ForeColor = System::Drawing::SystemColors::ControlText;
			this->b8->Name = L"b8";
			this->b8->TabStop = false;
			this->b8->UseVisualStyleBackColor = false;
			// 
			// b7
			// 
			this->b7->BackColor = System::Drawing::SystemColors::ControlLight;
			this->b7->FlatAppearance->BorderColor = System::Drawing::SystemColors::ControlLight;
			this->b7->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->b7->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Gainsboro;
			resources->ApplyResources(this->b7, L"b7");
			this->b7->ForeColor = System::Drawing::SystemColors::ControlText;
			this->b7->Name = L"b7";
			this->b7->TabStop = false;
			this->b7->UseVisualStyleBackColor = false;
			// 
			// button13
			// 
			this->button13->BackColor = System::Drawing::SystemColors::ControlLight;
			this->button13->FlatAppearance->BorderColor = System::Drawing::SystemColors::ControlLight;
			this->button13->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->button13->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Gainsboro;
			resources->ApplyResources(this->button13, L"button13");
			this->button13->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button13->Name = L"button13";
			this->button13->TabStop = false;
			this->button13->UseVisualStyleBackColor = false;
			this->button13->Click += gcnew System::EventHandler(this, &MyForm::button13_Click);
			// 
			// button15
			// 
			this->button15->BackColor = System::Drawing::SystemColors::ControlLight;
			this->button15->FlatAppearance->BorderColor = System::Drawing::SystemColors::ControlLight;
			this->button15->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->button15->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Gainsboro;
			resources->ApplyResources(this->button15, L"button15");
			this->button15->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button15->Name = L"button15";
			this->button15->TabStop = false;
			this->button15->UseVisualStyleBackColor = false;
			this->button15->Click += gcnew System::EventHandler(this, &MyForm::button15_Click);
			// 
			// button9
			// 
			this->button9->BackColor = System::Drawing::SystemColors::ControlLight;
			this->button9->FlatAppearance->BorderColor = System::Drawing::SystemColors::ControlLight;
			this->button9->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->button9->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(160)),
				static_cast<System::Int32>(static_cast<System::Byte>(216)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->button9->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(120)),
				static_cast<System::Int32>(static_cast<System::Byte>(180)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			resources->ApplyResources(this->button9, L"button9");
			this->button9->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button9->Name = L"button9";
			this->button9->TabStop = false;
			this->button9->UseVisualStyleBackColor = false;
			this->button9->Click += gcnew System::EventHandler(this, &MyForm::button9_Click);
			// 
			// button10
			// 
			this->button10->BackColor = System::Drawing::SystemColors::ControlLight;
			this->button10->FlatAppearance->BorderColor = System::Drawing::SystemColors::ControlLight;
			this->button10->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->button10->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Gainsboro;
			resources->ApplyResources(this->button10, L"button10");
			this->button10->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button10->Name = L"button10";
			this->button10->TabStop = false;
			this->button10->UseVisualStyleBackColor = false;
			this->button10->Click += gcnew System::EventHandler(this, &MyForm::button10_Click);
			// 
			// button11
			// 
			this->button11->BackColor = System::Drawing::SystemColors::ControlLight;
			this->button11->FlatAppearance->BorderColor = System::Drawing::SystemColors::ControlLight;
			this->button11->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->button11->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Gainsboro;
			resources->ApplyResources(this->button11, L"button11");
			this->button11->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button11->Name = L"button11";
			this->button11->TabStop = false;
			this->button11->UseVisualStyleBackColor = false;
			this->button11->Click += gcnew System::EventHandler(this, &MyForm::button11_Click);
			// 
			// button12
			// 
			this->button12->BackColor = System::Drawing::SystemColors::ControlLight;
			this->button12->FlatAppearance->BorderColor = System::Drawing::SystemColors::ControlLight;
			this->button12->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->button12->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Gainsboro;
			resources->ApplyResources(this->button12, L"button12");
			this->button12->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button12->Name = L"button12";
			this->button12->TabStop = false;
			this->button12->UseVisualStyleBackColor = false;
			this->button12->Click += gcnew System::EventHandler(this, &MyForm::button12_Click);
			// 
			// button29
			// 
			this->button29->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->button29->FlatAppearance->BorderColor = System::Drawing::Color::Silver;
			this->button29->FlatAppearance->BorderSize = 0;
			this->button29->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Gainsboro;
			resources->ApplyResources(this->button29, L"button29");
			this->button29->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button29->Name = L"button29";
			this->button29->TabStop = false;
			this->button29->UseVisualStyleBackColor = false;
			this->button29->Click += gcnew System::EventHandler(this, &MyForm::button29_Click);
			// 
			// button27
			// 
			this->button27->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->button27->FlatAppearance->BorderColor = System::Drawing::Color::Silver;
			this->button27->FlatAppearance->BorderSize = 0;
			this->button27->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Gainsboro;
			resources->ApplyResources(this->button27, L"button27");
			this->button27->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button27->Name = L"button27";
			this->button27->TabStop = false;
			this->button27->UseVisualStyleBackColor = false;
			this->button27->Click += gcnew System::EventHandler(this, &MyForm::button27_Click);
			// 
			// button26
			// 
			this->button26->BackColor = System::Drawing::SystemColors::InactiveCaption;
			resources->ApplyResources(this->button26, L"button26");
			this->button26->FlatAppearance->BorderColor = System::Drawing::Color::Silver;
			this->button26->FlatAppearance->BorderSize = 0;
			this->button26->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Gainsboro;
			this->button26->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button26->Name = L"button26";
			this->button26->TabStop = false;
			this->button26->UseVisualStyleBackColor = false;
			this->button26->Click += gcnew System::EventHandler(this, &MyForm::button26_Click);
			// 
			// button25
			// 
			this->button25->BackColor = System::Drawing::SystemColors::InactiveCaption;
			resources->ApplyResources(this->button25, L"button25");
			this->button25->FlatAppearance->BorderColor = System::Drawing::Color::Silver;
			this->button25->FlatAppearance->BorderSize = 0;
			this->button25->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Gainsboro;
			this->button25->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button25->Name = L"button25";
			this->button25->TabStop = false;
			this->button25->UseVisualStyleBackColor = false;
			this->button25->Click += gcnew System::EventHandler(this, &MyForm::button25_Click);
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->button3);
			this->panel1->Controls->Add(this->button6);
			this->panel1->Controls->Add(this->button1);
			this->panel1->Controls->Add(this->panel2);
			this->panel1->Controls->Add(this->button25);
			this->panel1->Controls->Add(this->button21);
			this->panel1->Controls->Add(this->button26);
			this->panel1->Controls->Add(this->button22);
			this->panel1->Controls->Add(this->button27);
			this->panel1->Controls->Add(this->b0);
			this->panel1->Controls->Add(this->button24);
			this->panel1->Controls->Add(this->button29);
			this->panel1->Controls->Add(this->button17);
			this->panel1->Controls->Add(this->b3);
			this->panel1->Controls->Add(this->b2);
			this->panel1->Controls->Add(this->button12);
			this->panel1->Controls->Add(this->b1);
			this->panel1->Controls->Add(this->button11);
			this->panel1->Controls->Add(this->button5);
			this->panel1->Controls->Add(this->button10);
			this->panel1->Controls->Add(this->b6);
			this->panel1->Controls->Add(this->button9);
			this->panel1->Controls->Add(this->b5);
			this->panel1->Controls->Add(this->button15);
			this->panel1->Controls->Add(this->b4);
			this->panel1->Controls->Add(this->button4);
			this->panel1->Controls->Add(this->button13);
			this->panel1->Controls->Add(this->b9);
			this->panel1->Controls->Add(this->b7);
			this->panel1->Controls->Add(this->b8);
			resources->ApplyResources(this->panel1, L"panel1");
			this->panel1->Name = L"panel1";
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::SystemColors::ControlLight;
			this->button3->FlatAppearance->BorderColor = System::Drawing::SystemColors::ControlLight;
			this->button3->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->button3->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(160)),
				static_cast<System::Int32>(static_cast<System::Byte>(216)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->button3->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(120)),
				static_cast<System::Int32>(static_cast<System::Byte>(180)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			resources->ApplyResources(this->button3, L"button3");
			this->button3->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button3->Name = L"button3";
			this->button3->TabStop = false;
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click_1);
			// 
			// button6
			// 
			this->button6->BackColor = System::Drawing::SystemColors::ControlLight;
			this->button6->FlatAppearance->BorderColor = System::Drawing::SystemColors::ControlLight;
			this->button6->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->button6->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(160)),
				static_cast<System::Int32>(static_cast<System::Byte>(216)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->button6->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(120)),
				static_cast<System::Int32>(static_cast<System::Byte>(180)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			resources->ApplyResources(this->button6, L"button6");
			this->button6->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button6->Name = L"button6";
			this->button6->TabStop = false;
			this->button6->UseVisualStyleBackColor = false;
			this->button6->Click += gcnew System::EventHandler(this, &MyForm::button6_Click);
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::SystemColors::InactiveCaption;
			resources->ApplyResources(this->button1, L"button1");
			this->button1->FlatAppearance->BorderColor = System::Drawing::Color::Silver;
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Gainsboro;
			this->button1->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button1->Name = L"button1";
			this->button1->TabStop = false;
			this->button1->UseVisualStyleBackColor = false;
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->tableLayoutPanel1);
			resources->ApplyResources(this->panel2, L"panel2");
			this->panel2->Name = L"panel2";
			// 
			// tableLayoutPanel1
			// 
			resources->ApplyResources(this->tableLayoutPanel1, L"tableLayoutPanel1");
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel1, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel2, 0, 0);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Controls->Add(this->cNum1);
			resources->ApplyResources(this->flowLayoutPanel1, L"flowLayoutPanel1");
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			// 
			// cNum1
			// 
			resources->ApplyResources(this->cNum1, L"cNum1");
			this->cNum1->Name = L"cNum1";
			// 
			// flowLayoutPanel2
			// 
			this->flowLayoutPanel2->Controls->Add(this->funcTxt);
			resources->ApplyResources(this->flowLayoutPanel2, L"flowLayoutPanel2");
			this->flowLayoutPanel2->Name = L"flowLayoutPanel2";
			// 
			// funcTxt
			// 
			resources->ApplyResources(this->funcTxt, L"funcTxt");
			this->funcTxt->Name = L"funcTxt";
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->историяToolStripMenuItem,
					this->настройкиToolStripMenuItem, this->помощьToolStripMenuItem
			});
			resources->ApplyResources(this->menuStrip1, L"menuStrip1");
			this->menuStrip1->Name = L"menuStrip1";
			// 
			// историяToolStripMenuItem
			// 
			this->историяToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->показатьToolStripMenuItem,
					this->очиститьToolStripMenuItem
			});
			this->историяToolStripMenuItem->Name = L"историяToolStripMenuItem";
			resources->ApplyResources(this->историяToolStripMenuItem, L"историяToolStripMenuItem");
			this->историяToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::историяToolStripMenuItem_Click);
			// 
			// показатьToolStripMenuItem
			// 
			this->показатьToolStripMenuItem->Name = L"показатьToolStripMenuItem";
			resources->ApplyResources(this->показатьToolStripMenuItem, L"показатьToolStripMenuItem");
			this->показатьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::показатьToolStripMenuItem_Click);
			// 
			// очиститьToolStripMenuItem
			// 
			this->очиститьToolStripMenuItem->Name = L"очиститьToolStripMenuItem";
			resources->ApplyResources(this->очиститьToolStripMenuItem, L"очиститьToolStripMenuItem");
			this->очиститьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::очиститьToolStripMenuItem_Click);
			// 
			// настройкиToolStripMenuItem
			// 
			this->настройкиToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->режимToolStripMenuItem });
			this->настройкиToolStripMenuItem->Name = L"настройкиToolStripMenuItem";
			resources->ApplyResources(this->настройкиToolStripMenuItem, L"настройкиToolStripMenuItem");
			// 
			// режимToolStripMenuItem
			// 
			this->режимToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->комплексноеЧислоToolStripMenuItem,
					this->действительноеЧислоToolStripMenuItem
			});
			this->режимToolStripMenuItem->Name = L"режимToolStripMenuItem";
			resources->ApplyResources(this->режимToolStripMenuItem, L"режимToolStripMenuItem");
			// 
			// комплексноеЧислоToolStripMenuItem
			// 
			this->комплексноеЧислоToolStripMenuItem->Checked = true;
			this->комплексноеЧислоToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->комплексноеЧислоToolStripMenuItem->Name = L"комплексноеЧислоToolStripMenuItem";
			resources->ApplyResources(this->комплексноеЧислоToolStripMenuItem, L"комплексноеЧислоToolStripMenuItem");
			this->комплексноеЧислоToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::комплексноеЧислоToolStripMenuItem_Click);
			// 
			// действительноеЧислоToolStripMenuItem
			// 
			this->действительноеЧислоToolStripMenuItem->Name = L"действительноеЧислоToolStripMenuItem";
			resources->ApplyResources(this->действительноеЧислоToolStripMenuItem, L"действительноеЧислоToolStripMenuItem");
			this->действительноеЧислоToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::действительноеЧислоToolStripMenuItem_Click);
			// 
			// помощьToolStripMenuItem
			// 
			this->помощьToolStripMenuItem->Name = L"помощьToolStripMenuItem";
			resources->ApplyResources(this->помощьToolStripMenuItem, L"помощьToolStripMenuItem");
			this->помощьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::помощьToolStripMenuItem_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::SystemColors::MenuHighlight;
			resources->ApplyResources(this->button2, L"button2");
			this->button2->FlatAppearance->BorderSize = 0;
			this->button2->Name = L"button2";
			this->button2->TabStop = false;
			this->button2->UseVisualStyleBackColor = false;
			// 
			// MyForm
			// 
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->Controls->Add(this->button2);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->KeyPreview = true;
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"MyForm";
			this->Opacity = 0.97;
			this->ShowIcon = false;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Show;
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::MyForm_KeyPress_1);
			this->panel1->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel1->PerformLayout();
			this->flowLayoutPanel2->ResumeLayout(false);
			this->flowLayoutPanel2->PerformLayout();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
		Do_cmd(Command::C_MUL);
	}

private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void button12_Click(System::Object^  sender, System::EventArgs^  e) {
	Do_cmd(Command::C_CE);

}
private: System::Void button11_Click(System::Object^  sender, System::EventArgs^  e) {
	Do_cmd(Command::C_C);
}

private: System::Void button10_Click(System::Object^  sender, System::EventArgs^  e) {
	Do_cmd(Command::C_BS);
}

private: System::Void MyForm_KeyPress_1(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	int i = -1;
	if (e->KeyChar >= '0' && e->KeyChar <= '9')
		btns[(int)e->KeyChar - '0']->PerformClick();

	if (e->KeyChar == 13)
		i = (int)Command::C_EQ;

	if (i >= 0)
		Do_cmd(i);
}
private: System::Void digit_click(System::Object^  sender, System::EventArgs^  e) {
	unsigned int num = 0;
	try
	{
		num = int::Parse(((System::Windows::Forms::Button^)sender)->Text);
		Do_cmd(num);
	}
	catch (...)
	{
	}
}

private: System::Void Memory_Change(int i)
{
	if (i == 1)
	{
		button25->Enabled = true;
		button26->Enabled = true;
		button27->Enabled = true;
	}
	else
	{
		button25->Enabled = false;
		button26->Enabled = false;
		button27->Enabled = false;
	}

}

private: System::Void Do_cmd(int i)
{
	try
	{
		string t = tctrl.Do_Cmd(i);
		if (i == (int)Command::C_MS)
			Memory_Change(1);
		if (i == (int)Command::C_MC)
			Memory_Change(0);
		ReloadText();
	}
	catch (...)
	{
		tctrl.Reset();
		cNum1->Text = "Incorrect input number!";
	}
}

private: System::Void ReloadText()
{
	string temp = tctrl.editor.ToString();
	if (tctrl.editor.IsBEmpty() && !settingsMode)
		temp.erase(temp.end() - 2, temp.end());
	cNum1->Text = gcnew String(temp.c_str());
}

private: System::Void button24_Click(System::Object^  sender, System::EventArgs^  e) {
	Do_cmd(Command::C_NEG);
}

private: System::Void MyForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	int i = -1;
	switch (e->KeyCode)
	{
	case Keys::Back:
		i = (int)Command::C_BS;
		break;
	case Keys::Delete:
		i = (int)Command::C_CE;
		break;
	case Keys::Oemplus:
		i = (int)Command::C_EQ;
		break;
	case Keys::Divide:
		i = (int)Command::C_DIV;
		break;
	case Keys::Multiply:
		i = (int)Command::C_MUL;
		break;
	case Keys::Subtract:
		i = (int)Command::C_SUB;
		break;
	case Keys::Add:
		i = (int)Command::C_ADD;
		break;
	case Keys::Tab:
		SwitchMode();
	}

	if (i > 0)
		Do_cmd(i);
}

private: System::Void flowLayoutPanel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
}
private: System::Void button20_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void button19_Click(System::Object^  sender, System::EventArgs^  e) {
}

private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e) {
	Do_cmd(Command::C_DIV);
	if (tctrl.editor.getMode() == MODE_B)
		SwitchMode();
}
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
	Do_cmd(Command::C_SUB);
	if (tctrl.editor.getMode() == MODE_B)
		SwitchMode();
}
private: System::Void button17_Click(System::Object^  sender, System::EventArgs^  e) {
	Do_cmd(Command::C_ADD);
	if (tctrl.editor.getMode() == MODE_B)
		SwitchMode();
}
private: System::Void button21_Click(System::Object^  sender, System::EventArgs^  e) {
	Do_cmd(Command::C_EQ);	
	if (tctrl.editor.getMode() == MODE_B)
		SwitchMode();
}
private: System::Void button13_Click(System::Object^  sender, System::EventArgs^  e) {
	Do_cmd(Command::C_1DIVX);
}

Color consoleLight;

private: System::Void SwitchMode()
{
	if (tctrl.editor.getMode() == MODE_A)
	{
		tctrl.editor.changeMode(MODE_B);
		button3->BackColor = button2->BackColor;
		button6->BackColor = consoleLight;
	}
	else
	{
		button6->BackColor = button2->BackColor;
		button3->BackColor = consoleLight;
		tctrl.editor.changeMode(MODE_A);
	}
}

private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	SwitchMode();
}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
	SwitchMode();
}

private: System::Void button15_Click(System::Object^  sender, System::EventArgs^  e) {
	Do_cmd(Command::C_SQR);
}
private: System::Void button14_Click(System::Object^  sender, System::EventArgs^  e) {
}


private: System::Void button29_Click(System::Object^  sender, System::EventArgs^  e) {
	Do_cmd(Command::C_MS);
}
private: System::Void button28_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void button27_Click(System::Object^  sender, System::EventArgs^  e) {
	Do_cmd(Command::C_MPLUS);
}
private: System::Void button26_Click(System::Object^  sender, System::EventArgs^  e) {
	Do_cmd(Command::C_MR);
}
private: System::Void button25_Click(System::Object^  sender, System::EventArgs^  e) {
	Do_cmd(Command::C_MC);
}
private: System::Void помощьToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	MessageBox::Show(this, "Калькулятор простых дробей\nВыполнил студент группы ИП-412\nМаксимов А.С.", "Справка");
}
		 bool settingsMode = true;
private: System::Void комплексноеЧислоToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	комплексноеЧислоToolStripMenuItem->Checked = true;
	действительноеЧислоToolStripMenuItem->Checked = false;
	settingsMode = true;
	ReloadText();
}
private: System::Void действительноеЧислоToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	комплексноеЧислоToolStripMenuItem->Checked = false;
	действительноеЧислоToolStripMenuItem->Checked = true;
	settingsMode = false;
	ReloadText();
}
private: System::Void button22_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
	if (tctrl.editor.getMode() == MODE_B)
		SwitchMode();
}
private: System::Void button3_Click_1(System::Object^  sender, System::EventArgs^  e) {
	if (tctrl.editor.getMode() == MODE_A)
		SwitchMode();
}
private: System::Void историяToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void показатьToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	MessageBox::Show(this, gcnew String(tctrl.history._str.c_str()), "История");
}
private: System::Void очиститьToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	tctrl.history.clear();
	MessageBox::Show(this,"Очищено", "История");
}
private: System::Void b6_Click(System::Object^  sender, System::EventArgs^  e) {
}
};
}
