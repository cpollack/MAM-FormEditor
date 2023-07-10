#include "MainForm.h"
#include "GlobalLib.h"
#include <cstdio>

using namespace MAM_FormEditor;

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/filereadstream.h"


void MainForm::SetFormTitle(bool edited) {
	String^ title = "MAM Form Editor";
	if (fileNameShort) title += " - " + fileNameShort;
	else title += " - Untitled";
	if (edited) title += "*";
	this->Text = title;
}


void MainForm::NewFile() {
	if (document) delete document;
	document = new Document;

	if (window) delete window;
	window = gcnew CWindow();

	if (fileNameShort) {
		delete fileNameShort; 
		fileNameShort = nullptr;
	}
	if (fileName) {
		delete fileName;
		fileName = nullptr;
	}
	if (filePath) {
		delete filePath;
		filePath = nullptr;
	}

	SetFormTitle(true);
	pbDrawWindow->Refresh(); //Required to get the pb to draw the image
	propertyGrid->SelectedObject = window;
}


void MainForm::SaveToFile() {
	if (!window) return;
	if (!fileNameShort || fileNameShort->Length == 0) {
		SaveAsFile();
		return;
	}

	//prompt to overwrite?

	if (document) delete document;
	document = new Document;
	document = window->Save(document);

	FILE* fp = fopen(textToString(filePath + fileName).c_str(), "w+b");
	char writeBuffer[65536];
	FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> writer(os);
	document->Accept(writer);
	fclose(fp);

	SetFormTitle(false);
}


void MainForm::SaveAsFile() {
	if (!window) return;
	if (saveFileDialog->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		String ^fullFileName = saveFileDialog->FileName;
		array<System::String ^> ^splitFile = fullFileName->Split('\\');
		String ^nameExt = splitFile[splitFile->Length - 1];
		array<System::String ^> ^splitName = nameExt->Split('.');

		filePath = gcnew String("");
		for (int i = 0; i < splitFile->Length - 1; i++) filePath += splitFile[i] + "\\";
		fileName = splitFile[splitFile->Length - 1];
		fileNameShort = splitName[0];

		if (document) delete document;
		document = new Document;
		document = window->Save(document);

		FILE* fp = fopen(textToString(filePath + fileName).c_str(), "w+b");
		char writeBuffer[65536];
		FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
		Writer<FileWriteStream> writer(os);
		document->Accept(writer);
		fclose(fp);

		SetFormTitle(false);
		propertyGrid->SelectedObject = window;
	}
}


void MainForm::LoadFromFile() {
	if (openFileDialog->ShowDialog(this) == System::Windows::Forms::DialogResult::OK) {
		String ^fullFileName = openFileDialog->FileName;
		array<System::String ^> ^splitFile = fullFileName->Split('\\');
		String ^nameExt = splitFile[splitFile->Length - 1];
		array<System::String ^> ^splitName = nameExt->Split('.');

		filePath = gcnew String("");
		for (int i = 0; i < splitFile->Length - 1; i++) filePath += splitFile[i] + "\\";
		fileName = splitFile[splitFile->Length - 1];
		fileNameShort = splitName[0];

		//load document from file
		FILE* fp = fopen(textToString(filePath + fileName).c_str(), "rb");
		char readBuffer[65536];
		FileReadStream is(fp, readBuffer, sizeof(readBuffer));
		
		if (document) delete document;
		document = new Document;
		document->ParseStream<0, UTF8<>, FileReadStream>(is);
		fclose(fp);

		if (window) delete window;
		window = gcnew CWindow();
		window->Load(document);

		propertyGrid->SelectedObject = window;
		SetFormTitle(false);
		pbDrawWindow->Refresh(); //Required to get the pb to draw the image
	}
}


void MainForm::ViewPreviewMode() {
	previewMode = previewModeToolStripMenuItem->Checked;
}

void MainForm::ToggleAddSelection(RadioButton ^rb) {
	if (addSelection == rb) {
		rb->Checked = false;
		addSelection = nullptr;
	}
	else addSelection = rb;
}
