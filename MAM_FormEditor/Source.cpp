#include "MainForm.h"
#include "GlobalLib.h"

using namespace MAM_FormEditor;

using namespace System;
using namespace System::Windows::Forms; 

bool previewMode;

/*[STAThread]
int Main(array<String^>^ args)
{
	previewMode = false;

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	MAM_FormEditor::MainForm form;
	Application::Run(%form);

	return 0;
}*/

[STAThread]
INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, INT nCmdShow)
{
	previewMode = false;

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	MAM_FormEditor::MainForm form;
	Application::Run(%form);

	return 0;
}