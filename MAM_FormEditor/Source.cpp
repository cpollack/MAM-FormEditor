#include "MainForm.h"
#include "GlobalLib.h"

using namespace MAM_FormEditor;

using namespace System;
using namespace System::Windows::Forms; 

bool previewMode;

[STAThread]
void Main(array<String^>^ args)
{
	previewMode = false;

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	MAM_FormEditor::MainForm form;
	Application::Run(%form);
}