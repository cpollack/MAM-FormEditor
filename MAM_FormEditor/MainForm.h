#pragma once

#include "Window.h"
#include "CheckBox.h"

namespace MAM_FormEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//


			//propertyGrid

			window = gcnew CWindow();
			CCheckBox^ cb1 = gcnew CCheckBox(10, 12);
			propertyGrid->SelectedObject = window;
		}
	private: System::Windows::Forms::SplitContainer^  splitContainerEditor;
	public:

	public:
	private: System::Windows::Forms::PictureBox^  addLabel;
	private: System::Windows::Forms::PictureBox^  addRadioButton;
	private: System::Windows::Forms::PictureBox^  addCheckbox;

		CWindow^ window;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::SplitContainer^  splitContainer;
	protected:
	private: System::Windows::Forms::PropertyGrid^  propertyGrid;
	private: System::Windows::Forms::Label^  labelWidgetName;
	private: System::Windows::Forms::PictureBox^  pbDrawWindow;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->splitContainer = (gcnew System::Windows::Forms::SplitContainer());
			this->propertyGrid = (gcnew System::Windows::Forms::PropertyGrid());
			this->labelWidgetName = (gcnew System::Windows::Forms::Label());
			this->splitContainerEditor = (gcnew System::Windows::Forms::SplitContainer());
			this->addLabel = (gcnew System::Windows::Forms::PictureBox());
			this->addRadioButton = (gcnew System::Windows::Forms::PictureBox());
			this->addCheckbox = (gcnew System::Windows::Forms::PictureBox());
			this->pbDrawWindow = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer))->BeginInit();
			this->splitContainer->Panel1->SuspendLayout();
			this->splitContainer->Panel2->SuspendLayout();
			this->splitContainer->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainerEditor))->BeginInit();
			this->splitContainerEditor->Panel1->SuspendLayout();
			this->splitContainerEditor->Panel2->SuspendLayout();
			this->splitContainerEditor->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->addLabel))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->addRadioButton))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->addCheckbox))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbDrawWindow))->BeginInit();
			this->SuspendLayout();
			// 
			// splitContainer
			// 
			this->splitContainer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer->FixedPanel = System::Windows::Forms::FixedPanel::Panel1;
			this->splitContainer->IsSplitterFixed = true;
			this->splitContainer->Location = System::Drawing::Point(0, 0);
			this->splitContainer->Name = L"splitContainer";
			// 
			// splitContainer.Panel1
			// 
			this->splitContainer->Panel1->BackColor = System::Drawing::SystemColors::ControlLight;
			this->splitContainer->Panel1->Controls->Add(this->propertyGrid);
			this->splitContainer->Panel1->Controls->Add(this->labelWidgetName);
			// 
			// splitContainer.Panel2
			// 
			this->splitContainer->Panel2->AutoScroll = true;
			this->splitContainer->Panel2->BackColor = System::Drawing::SystemColors::Control;
			this->splitContainer->Panel2->Controls->Add(this->splitContainerEditor);
			this->splitContainer->Size = System::Drawing::Size(684, 361);
			this->splitContainer->SplitterDistance = 211;
			this->splitContainer->TabIndex = 0;
			// 
			// propertyGrid
			// 
			this->propertyGrid->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->propertyGrid->BackColor = System::Drawing::SystemColors::Control;
			this->propertyGrid->Location = System::Drawing::Point(3, 25);
			this->propertyGrid->Name = L"propertyGrid";
			this->propertyGrid->Size = System::Drawing::Size(205, 283);
			this->propertyGrid->TabIndex = 1;
			// 
			// labelWidgetName
			// 
			this->labelWidgetName->AutoSize = true;
			this->labelWidgetName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->labelWidgetName->Location = System::Drawing::Point(3, 9);
			this->labelWidgetName->Name = L"labelWidgetName";
			this->labelWidgetName->Size = System::Drawing::Size(91, 13);
			this->labelWidgetName->TabIndex = 0;
			this->labelWidgetName->Text = L"[Widget Name]";
			// 
			// splitContainerEditor
			// 
			this->splitContainerEditor->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->splitContainerEditor->FixedPanel = System::Windows::Forms::FixedPanel::Panel1;
			this->splitContainerEditor->IsSplitterFixed = true;
			this->splitContainerEditor->Location = System::Drawing::Point(-1, 0);
			this->splitContainerEditor->Name = L"splitContainerEditor";
			// 
			// splitContainerEditor.Panel1
			// 
			this->splitContainerEditor->Panel1->BackColor = System::Drawing::SystemColors::Control;
			this->splitContainerEditor->Panel1->Controls->Add(this->addLabel);
			this->splitContainerEditor->Panel1->Controls->Add(this->addRadioButton);
			this->splitContainerEditor->Panel1->Controls->Add(this->addCheckbox);
			// 
			// splitContainerEditor.Panel2
			// 
			this->splitContainerEditor->Panel2->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->splitContainerEditor->Panel2->Controls->Add(this->pbDrawWindow);
			this->splitContainerEditor->Size = System::Drawing::Size(470, 361);
			this->splitContainerEditor->SplitterDistance = 25;
			this->splitContainerEditor->SplitterWidth = 1;
			this->splitContainerEditor->TabIndex = 1;
			// 
			// addLabel
			// 
			this->addLabel->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"addLabel.Image")));
			this->addLabel->Location = System::Drawing::Point(3, 13);
			this->addLabel->Name = L"addLabel";
			this->addLabel->Size = System::Drawing::Size(16, 16);
			this->addLabel->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->addLabel->TabIndex = 2;
			this->addLabel->TabStop = false;
			// 
			// addRadioButton
			// 
			this->addRadioButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"addRadioButton.Image")));
			this->addRadioButton->Location = System::Drawing::Point(3, 57);
			this->addRadioButton->Name = L"addRadioButton";
			this->addRadioButton->Size = System::Drawing::Size(16, 16);
			this->addRadioButton->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->addRadioButton->TabIndex = 1;
			this->addRadioButton->TabStop = false;
			// 
			// addCheckbox
			// 
			this->addCheckbox->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"addCheckbox.Image")));
			this->addCheckbox->Location = System::Drawing::Point(3, 35);
			this->addCheckbox->Name = L"addCheckbox";
			this->addCheckbox->Size = System::Drawing::Size(16, 16);
			this->addCheckbox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->addCheckbox->TabIndex = 0;
			this->addCheckbox->TabStop = false;
			// 
			// pbDrawWindow
			// 
			this->pbDrawWindow->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->pbDrawWindow->Location = System::Drawing::Point(0, 0);
			this->pbDrawWindow->Name = L"pbDrawWindow";
			this->pbDrawWindow->Size = System::Drawing::Size(448, 361);
			this->pbDrawWindow->TabIndex = 0;
			this->pbDrawWindow->TabStop = false;
			this->pbDrawWindow->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::pbDrawWindow_Paint);
			this->pbDrawWindow->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::pbDrawWindow_MouseDown);
			this->pbDrawWindow->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::pbDrawWindow_MouseMove);
			this->pbDrawWindow->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::pbDrawWindow_MouseUp);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(684, 361);
			this->Controls->Add(this->splitContainer);
			this->MinimumSize = System::Drawing::Size(700, 400);
			this->Name = L"MainForm";
			this->Text = L"MAM Form Editor";
			this->splitContainer->Panel1->ResumeLayout(false);
			this->splitContainer->Panel1->PerformLayout();
			this->splitContainer->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer))->EndInit();
			this->splitContainer->ResumeLayout(false);
			this->splitContainerEditor->Panel1->ResumeLayout(false);
			this->splitContainerEditor->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainerEditor))->EndInit();
			this->splitContainerEditor->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->addLabel))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->addRadioButton))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->addCheckbox))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbDrawWindow))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

		public:
		System::Windows::Forms::Control^ getDrawableControl() {
			return splitContainer->Panel2;
		}
	private: System::Void pbDrawWindow_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		window->Draw(pbDrawWindow);
	}
private: System::Void pbDrawWindow_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	Cursor = window->MouseMove(e);
}
private: System::Void pbDrawWindow_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	window->MouseUp(e);
	propertyGrid->Refresh();
}
private: System::Void pbDrawWindow_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	window->MouseDown(e);
}
};
}
