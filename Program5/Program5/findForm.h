#pragma once

namespace Program5 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for findForm
	/// </summary>
	public ref class findForm : public System::Windows::Forms::Form
	{
	public:
		findForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			buttFind->DialogResult = System::Windows::Forms::DialogResult::OK;
			buttReplace->DialogResult = System::Windows::Forms::DialogResult::OK;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~findForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  tbFind;
	private: System::Windows::Forms::TextBox^  tbReplace;
	protected: 

	protected: 

	private: System::Windows::Forms::Button^  buttReplace;
	private: System::Windows::Forms::Button^  buttFind;
	private: System::Windows::Forms::Label^  lbFind;



	private: System::Windows::Forms::Label^  lbReplace;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->tbFind = (gcnew System::Windows::Forms::TextBox());
			this->tbReplace = (gcnew System::Windows::Forms::TextBox());
			this->buttReplace = (gcnew System::Windows::Forms::Button());
			this->buttFind = (gcnew System::Windows::Forms::Button());
			this->lbFind = (gcnew System::Windows::Forms::Label());
			this->lbReplace = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// tbFind
			// 
			this->tbFind->Location = System::Drawing::Point(15, 25);
			this->tbFind->Name = L"tbFind";
			this->tbFind->Size = System::Drawing::Size(258, 20);
			this->tbFind->TabIndex = 0;
			// 
			// tbReplace
			// 
			this->tbReplace->Location = System::Drawing::Point(12, 92);
			this->tbReplace->Name = L"tbReplace";
			this->tbReplace->Size = System::Drawing::Size(258, 20);
			this->tbReplace->TabIndex = 1;
			// 
			// buttReplace
			// 
			this->buttReplace->Location = System::Drawing::Point(195, 118);
			this->buttReplace->Name = L"buttReplace";
			this->buttReplace->Size = System::Drawing::Size(75, 23);
			this->buttReplace->TabIndex = 2;
			this->buttReplace->Text = L"REPLACE";
			this->buttReplace->UseVisualStyleBackColor = true;
			this->buttReplace->Click += gcnew System::EventHandler(this, &findForm::buttReplace_Click);
			// 
			// buttFind
			// 
			this->buttFind->Location = System::Drawing::Point(198, 51);
			this->buttFind->Name = L"buttFind";
			this->buttFind->Size = System::Drawing::Size(75, 23);
			this->buttFind->TabIndex = 3;
			this->buttFind->Text = L"FIND";
			this->buttFind->UseVisualStyleBackColor = true;
			this->buttFind->Click += gcnew System::EventHandler(this, &findForm::buttFind_Click);
			// 
			// lbFind
			// 
			this->lbFind->AutoSize = true;
			this->lbFind->Location = System::Drawing::Point(12, 9);
			this->lbFind->Name = L"lbFind";
			this->lbFind->Size = System::Drawing::Size(27, 13);
			this->lbFind->TabIndex = 4;
			this->lbFind->Text = L"Find";
			this->lbFind->Click += gcnew System::EventHandler(this, &findForm::label1_Click);
			// 
			// lbReplace
			// 
			this->lbReplace->AutoSize = true;
			this->lbReplace->Location = System::Drawing::Point(12, 76);
			this->lbReplace->Name = L"lbReplace";
			this->lbReplace->Size = System::Drawing::Size(47, 13);
			this->lbReplace->TabIndex = 5;
			this->lbReplace->Text = L"Replace";
			// 
			// findForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(282, 154);
			this->Controls->Add(this->lbReplace);
			this->Controls->Add(this->lbFind);
			this->Controls->Add(this->buttFind);
			this->Controls->Add(this->buttReplace);
			this->Controls->Add(this->tbReplace);
			this->Controls->Add(this->tbFind);
			this->Name = L"findForm";
			this->Text = L"findForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void buttFind_Click(System::Object^  sender, System::EventArgs^  e) {
			 Close();
		 }
private: System::Void buttReplace_Click(System::Object^  sender, System::EventArgs^  e) {
			 Close();
		 }

public: String^ getFindText()
	{
		return tbFind->Text;
	}
public: String^ getReplaceText()
	{
		return tbReplace->Text;
	}
public: void setFind()
		{
			lbReplace->Visible = false;
			tbReplace->Visible = false;
			buttReplace->Visible = false;
		}
public: void setReplace()
		{
			lbReplace->Visible = true;
			tbReplace->Visible = true;
			buttReplace->Visible = true;
		}

};
}
