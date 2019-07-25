#include "MainForm.h"
#include "GlobalLib.h"

using namespace MAM_FormEditor;

void MainForm::SaveToFile() {
	document = window->Save(document);
	filename = "test";

	String^ fullFileName = filename + ".json";
	FILE* fp = fopen(textToString(fullFileName).c_str(), "wb");
	char writeBuffer[65536];
	FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> writer(os);
	document->Accept(writer);
	fclose(fp);
}

