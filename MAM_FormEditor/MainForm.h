#pragma once

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/filereadstream.h"

#include "Window.h"
#include "CheckBox.h"

namespace MAM_FormEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace rapidjson;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();

			//document = new rapidjson::Document();
			//window = gcnew CWindow();
			//CCheckBox^ cb1 = gcnew CCheckBox(10, 12);

			//propertyGrid->SelectedObject = window;

			//SetFormTitle(true);
		}
	
	public:
		CWindow^ window;
		rapidjson::Document* document;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog;
	private: System::Windows::Forms::ToolStripMenuItem^  saveAsToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	public:
		String^ fileNameShort = nullptr;
		String^ fileName = nullptr;
		String^ filePath = nullptr;

		void SetFormTitle(bool edited);
		void NewFile();
		void SaveToFile();
		void SaveAsFile();
		void LoadFromFile();
		void ViewPreviewMode();

	private: System::Windows::Forms::MenuStrip^  menuStripMain;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  newToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  loadToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  viewToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  previewModeToolStripMenuItem;

	private: System::Windows::Forms::RadioButton^  addRadioButton;
	private: System::Windows::Forms::RadioButton^  addCheckbox;
	private: System::Windows::Forms::RadioButton^  addLabel;
	private: System::Windows::Forms::RadioButton^  addButton;
	private: System::Windows::Forms::SplitContainer^  splitContainerEditor;

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
			this->addButton = (gcnew System::Windows::Forms::RadioButton());
			this->addRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->addCheckbox = (gcnew System::Windows::Forms::RadioButton());
			this->addLabel = (gcnew System::Windows::Forms::RadioButton());
			this->pbDrawWindow = (gcnew System::Windows::Forms::PictureBox());
			this->menuStripMain = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->viewToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->previewModeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer))->BeginInit();
			this->splitContainer->Panel1->SuspendLayout();
			this->splitContainer->Panel2->SuspendLayout();
			this->splitContainer->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainerEditor))->BeginInit();
			this->splitContainerEditor->Panel1->SuspendLayout();
			this->splitContainerEditor->Panel2->SuspendLayout();
			this->splitContainerEditor->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbDrawWindow))->BeginInit();
			this->menuStripMain->SuspendLayout();
			this->SuspendLayout();
			// 
			// splitContainer
			// 
			this->splitContainer->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->splitContainer->FixedPanel = System::Windows::Forms::FixedPanel::Panel1;
			this->splitContainer->IsSplitterFixed = true;
			this->splitContainer->Location = System::Drawing::Point(0, 27);
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
			this->splitContainer->Size = System::Drawing::Size(684, 334);
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
			this->propertyGrid->Size = System::Drawing::Size(205, 306);
			this->propertyGrid->TabIndex = 1;
			this->propertyGrid->SelectedObjectsChanged += gcnew System::EventHandler(this, &MainForm::propertyGrid_SelectedObjectsChanged);
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
			this->splitContainerEditor->Panel1->Controls->Add(this->addButton);
			this->splitContainerEditor->Panel1->Controls->Add(this->addRadioButton);
			this->splitContainerEditor->Panel1->Controls->Add(this->addCheckbox);
			this->splitContainerEditor->Panel1->Controls->Add(this->addLabel);
			// 
			// splitContainerEditor.Panel2
			// 
			this->splitContainerEditor->Panel2->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->splitContainerEditor->Panel2->Controls->Add(this->pbDrawWindow);
			this->splitContainerEditor->Size = System::Drawing::Size(470, 334);
			this->splitContainerEditor->SplitterDistance = 25;
			this->splitContainerEditor->SplitterWidth = 1;
			this->splitContainerEditor->TabIndex = 1;
			// 
			// addButton
			// 
			this->addButton->Appearance = System::Windows::Forms::Appearance::Button;
			this->addButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->addButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"addButton.Image")));
			this->addButton->Location = System::Drawing::Point(0, 99);
			this->addButton->Name = L"addButton";
			this->addButton->Size = System::Drawing::Size(23, 24);
			this->addButton->TabIndex = 10;
			this->addButton->TabStop = true;
			this->addButton->UseVisualStyleBackColor = true;
			// 
			// addRadioButton
			// 
			this->addRadioButton->Appearance = System::Windows::Forms::Appearance::Button;
			this->addRadioButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"addRadioButton.Image")));
			this->addRadioButton->Location = System::Drawing::Point(0, 69);
			this->addRadioButton->Name = L"addRadioButton";
			this->addRadioButton->Size = System::Drawing::Size(23, 24);
			this->addRadioButton->TabIndex = 9;
			this->addRadioButton->TabStop = true;
			this->addRadioButton->UseVisualStyleBackColor = true;
			// 
			// addCheckbox
			// 
			this->addCheckbox->Appearance = System::Windows::Forms::Appearance::Button;
			this->addCheckbox->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"addCheckbox.Image")));
			this->addCheckbox->Location = System::Drawing::Point(0, 39);
			this->addCheckbox->Name = L"addCheckbox";
			this->addCheckbox->Size = System::Drawing::Size(23, 24);
			this->addCheckbox->TabIndex = 8;
			this->addCheckbox->TabStop = true;
			this->addCheckbox->UseVisualStyleBackColor = true;
			// 
			// addLabel
			// 
			this->addLabel->Appearance = System::Windows::Forms::Appearance::Button;
			this->addLabel->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"addLabel.Image")));
			this->addLabel->Location = System::Drawing::Point(0, 9);
			this->addLabel->Name = L"addLabel";
			this->addLabel->Size = System::Drawing::Size(23, 24);
			this->addLabel->TabIndex = 7;
			this->addLabel->TabStop = true;
			this->addLabel->UseVisualStyleBackColor = true;
			// 
			// pbDrawWindow
			// 
			this->pbDrawWindow->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->pbDrawWindow->Location = System::Drawing::Point(0, 0);
			this->pbDrawWindow->Name = L"pbDrawWindow";
			this->pbDrawWindow->Size = System::Drawing::Size(477, 334);
			this->pbDrawWindow->TabIndex = 0;
			this->pbDrawWindow->TabStop = false;
			this->pbDrawWindow->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::pbDrawWindow_Paint);
			this->pbDrawWindow->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::pbDrawWindow_MouseClick);
			this->pbDrawWindow->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::pbDrawWindow_MouseDown);
			this->pbDrawWindow->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::pbDrawWindow_MouseMove);
			this->pbDrawWindow->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::pbDrawWindow_MouseUp);
			// 
			// menuStripMain
			// 
			this->menuStripMain->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->fileToolStripMenuItem,
					this->viewToolStripMenuItem
			});
			this->menuStripMain->Location = System::Drawing::Point(0, 0);
			this->menuStripMain->Name = L"menuStripMain";
			this->menuStripMain->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
			this->menuStripMain->Size = System::Drawing::Size(684, 24);
			this->menuStripMain->TabIndex = 1;
			this->menuStripMain->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->newToolStripMenuItem,
					this->loadToolStripMenuItem, this->saveToolStripMenuItem, this->saveAsToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// newToolStripMenuItem
			// 
			this->newToolStripMenuItem->Name = L"newToolStripMenuItem";
			this->newToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->newToolStripMenuItem->Text = L"New";
			this->newToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::newToolStripMenuItem_Click);
			// 
			// loadToolStripMenuItem
			// 
			this->loadToolStripMenuItem->Name = L"loadToolStripMenuItem";
			this->loadToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->loadToolStripMenuItem->Text = L"Load";
			this->loadToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::loadToolStripMenuItem_Click);
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->saveToolStripMenuItem->Text = L"Save";
			this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveToolStripMenuItem_Click);
			// 
			// saveAsToolStripMenuItem
			// 
			this->saveAsToolStripMenuItem->Name = L"saveAsToolStripMenuItem";
			this->saveAsToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->saveAsToolStripMenuItem->Text = L"Save As";
			this->saveAsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveAsToolStripMenuItem_Click);
			// 
			// viewToolStripMenuItem
			// 
			this->viewToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->previewModeToolStripMenuItem });
			this->viewToolStripMenuItem->Name = L"viewToolStripMenuItem";
			this->viewToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->viewToolStripMenuItem->Text = L"View";
			// 
			// previewModeToolStripMenuItem
			// 
			this->previewModeToolStripMenuItem->CheckOnClick = true;
			this->previewModeToolStripMenuItem->Name = L"previewModeToolStripMenuItem";
			this->previewModeToolStripMenuItem->Size = System::Drawing::Size(149, 22);
			this->previewModeToolStripMenuItem->Text = L"Preview Mode";
			this->previewModeToolStripMenuItem->CheckedChanged += gcnew System::EventHandler(this, &MainForm::previewModeToolStripMenuItem_CheckedChanged);
			// 
			// saveFileDialog
			// 
			this->saveFileDialog->DefaultExt = L"JSON";
			this->saveFileDialog->Filter = L"JSON Files|*.JSON";
			this->saveFileDialog->Title = L"Save Form";
			// 
			// openFileDialog
			// 
			this->openFileDialog->DefaultExt = L"JSON";
			this->openFileDialog->Filter = L"JSON File|*.JSON";
			this->openFileDialog->Title = L"Load Form";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(684, 362);
			this->Controls->Add(this->menuStripMain);
			this->Controls->Add(this->splitContainer);
			this->MainMenuStrip = this->menuStripMain;
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbDrawWindow))->EndInit();
			this->menuStripMain->ResumeLayout(false);
			this->menuStripMain->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	public:
	System::Windows::Forms::Control^ getDrawableControl() {
		return splitContainer->Panel2;
	}
private: System::Void pbDrawWindow_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
	if (window) window->Draw(pbDrawWindow);
}
private: System::Void pbDrawWindow_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (window) Cursor = window->MouseMove(e);
}
private: System::Void pbDrawWindow_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (window) window->MouseUp(e);
	propertyGrid->Refresh();
}
private: System::Void pbDrawWindow_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (window) window->MouseDown(e);
}

private: System::Void pbDrawWindow_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (!window) return;
	Object^ focus;
	int addMode = 0;

	if (addLabel->Checked) addMode = amLabel;
	else if (addCheckbox->Checked) addMode = amCheckbox;
	else if (addRadioButton->Checked) addMode = amRadio;
	else if (addButton->Checked) addMode = amButton;

	focus = window->Click(e, addMode);
	if (focus) propertyGrid->SelectedObject = focus;

	//Uncheck all radio buttons to prevent accidental multi-add
	for each (RadioButton^ rb in splitContainerEditor->Panel1->Controls) {
		rb->Checked = false;
	}
}

private: System::Void saveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	SaveToFile();
}
private: System::Void saveAsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	SaveAsFile();
}
private: System::Void loadToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	LoadFromFile();
}
private: System::Void previewModeToolStripMenuItem_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	ViewPreviewMode();
}
private: System::Void propertyGrid_SelectedObjectsChanged(System::Object^  sender, System::EventArgs^  e) {
	if (propertyGrid->SelectedObject == window) labelWidgetName->Text = "Window";
	else labelWidgetName->Text = ((CWidget^)propertyGrid->SelectedObject)->Name;
}
private: System::Void newToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	NewFile();
}
};
}
