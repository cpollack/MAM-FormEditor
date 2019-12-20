#pragma once

namespace MAM_FormEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ListForm
	/// </summary>
	public ref class ListForm : public System::Windows::Forms::Form
	{
	public:
		ListForm(Form^ form, String^ widgetName, List<String^> ^strings)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			parent = form;
			parent->Enabled = false;
			lblWidget->Text = widgetName;
			returnStrings = strings;
			lStrings = gcnew List<String^>(strings);
			fillList(lStrings);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ListForm()
		{
			parent->Enabled = true;
			if (components)
			{
				delete components;
			}
		}

		Form^ parent;
		List<String^> ^lStrings, ^returnStrings;
		void fillList(List<String^> ^strings);
		void listMoveUp();
		void listMoveDown();
		void listDelete();
		void listAdd(String^ s);
		void listSave();

	private: System::Windows::Forms::ListBox^  listBoxItems;
	private: System::Windows::Forms::Label^  labelFor;
	protected:

	private: System::Windows::Forms::Label^  lblWidget;
	private: System::Windows::Forms::Button^  buttonAdd;
	private: System::Windows::Forms::TextBox^  textBoxItem;
	private: System::Windows::Forms::Button^  buttonUp;
	private: System::Windows::Forms::Button^  buttonDelete;
	private: System::Windows::Forms::Button^  buttonDown;
	private: System::Windows::Forms::Button^  buttonSave;

	protected:

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
			this->listBoxItems = (gcnew System::Windows::Forms::ListBox());
			this->labelFor = (gcnew System::Windows::Forms::Label());
			this->lblWidget = (gcnew System::Windows::Forms::Label());
			this->buttonAdd = (gcnew System::Windows::Forms::Button());
			this->textBoxItem = (gcnew System::Windows::Forms::TextBox());
			this->buttonUp = (gcnew System::Windows::Forms::Button());
			this->buttonDelete = (gcnew System::Windows::Forms::Button());
			this->buttonDown = (gcnew System::Windows::Forms::Button());
			this->buttonSave = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// listBoxItems
			// 
			this->listBoxItems->FormattingEnabled = true;
			this->listBoxItems->Location = System::Drawing::Point(15, 25);
			this->listBoxItems->Name = L"listBoxItems";
			this->listBoxItems->Size = System::Drawing::Size(128, 160);
			this->listBoxItems->TabIndex = 0;
			// 
			// labelFor
			// 
			this->labelFor->AutoSize = true;
			this->labelFor->Location = System::Drawing::Point(12, 9);
			this->labelFor->Name = L"labelFor";
			this->labelFor->Size = System::Drawing::Size(81, 13);
			this->labelFor->TabIndex = 1;
			this->labelFor->Text = L"List of Items for:";
			// 
			// lblWidget
			// 
			this->lblWidget->AutoSize = true;
			this->lblWidget->Location = System::Drawing::Point(99, 9);
			this->lblWidget->Name = L"lblWidget";
			this->lblWidget->Size = System::Drawing::Size(44, 13);
			this->lblWidget->TabIndex = 2;
			this->lblWidget->Text = L"[widget]";
			// 
			// buttonAdd
			// 
			this->buttonAdd->Location = System::Drawing::Point(149, 189);
			this->buttonAdd->Name = L"buttonAdd";
			this->buttonAdd->Size = System::Drawing::Size(75, 23);
			this->buttonAdd->TabIndex = 3;
			this->buttonAdd->Text = L"Add";
			this->buttonAdd->UseVisualStyleBackColor = true;
			this->buttonAdd->Click += gcnew System::EventHandler(this, &ListForm::buttonAdd_Click);
			// 
			// textBoxItem
			// 
			this->textBoxItem->Location = System::Drawing::Point(15, 191);
			this->textBoxItem->Name = L"textBoxItem";
			this->textBoxItem->Size = System::Drawing::Size(128, 20);
			this->textBoxItem->TabIndex = 4;
			// 
			// buttonUp
			// 
			this->buttonUp->Location = System::Drawing::Point(164, 38);
			this->buttonUp->Name = L"buttonUp";
			this->buttonUp->Size = System::Drawing::Size(60, 23);
			this->buttonUp->TabIndex = 5;
			this->buttonUp->Text = L"Up";
			this->buttonUp->UseVisualStyleBackColor = true;
			this->buttonUp->Click += gcnew System::EventHandler(this, &ListForm::buttonUp_Click);
			// 
			// buttonDelete
			// 
			this->buttonDelete->Location = System::Drawing::Point(164, 122);
			this->buttonDelete->Name = L"buttonDelete";
			this->buttonDelete->Size = System::Drawing::Size(60, 23);
			this->buttonDelete->TabIndex = 6;
			this->buttonDelete->Text = L"Delete";
			this->buttonDelete->UseVisualStyleBackColor = true;
			this->buttonDelete->Click += gcnew System::EventHandler(this, &ListForm::buttonDelete_Click);
			// 
			// buttonDown
			// 
			this->buttonDown->Location = System::Drawing::Point(164, 67);
			this->buttonDown->Name = L"buttonDown";
			this->buttonDown->Size = System::Drawing::Size(60, 23);
			this->buttonDown->TabIndex = 7;
			this->buttonDown->Text = L"Down";
			this->buttonDown->UseVisualStyleBackColor = true;
			this->buttonDown->Click += gcnew System::EventHandler(this, &ListForm::buttonDown_Click);
			// 
			// buttonSave
			// 
			this->buttonSave->Location = System::Drawing::Point(83, 226);
			this->buttonSave->Name = L"buttonSave";
			this->buttonSave->Size = System::Drawing::Size(75, 23);
			this->buttonSave->TabIndex = 8;
			this->buttonSave->Text = L"Save";
			this->buttonSave->UseVisualStyleBackColor = true;
			this->buttonSave->Click += gcnew System::EventHandler(this, &ListForm::buttonSave_Click);
			// 
			// ListForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(238, 261);
			this->Controls->Add(this->buttonSave);
			this->Controls->Add(this->buttonDown);
			this->Controls->Add(this->buttonDelete);
			this->Controls->Add(this->buttonUp);
			this->Controls->Add(this->textBoxItem);
			this->Controls->Add(this->buttonAdd);
			this->Controls->Add(this->lblWidget);
			this->Controls->Add(this->labelFor);
			this->Controls->Add(this->listBoxItems);
			this->Name = L"ListForm";
			this->Text = L"Item List";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void buttonUp_Click(System::Object^  sender, System::EventArgs^  e) {
		listMoveUp();
	}
private: System::Void buttonDown_Click(System::Object^  sender, System::EventArgs^  e) {
	listMoveDown();
}
private: System::Void buttonDelete_Click(System::Object^  sender, System::EventArgs^  e) {
	listDelete();
}
private: System::Void buttonAdd_Click(System::Object^  sender, System::EventArgs^  e) {
	listAdd(textBoxItem->Text);
}
private: System::Void buttonSave_Click(System::Object^  sender, System::EventArgs^  e) {
	listSave();
	this->Close();
}
};
}
