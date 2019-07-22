#include "MainForm.h"

using namespace MAM_FormEditor;

using namespace System;
using namespace System::Windows::Forms; 

[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	MAM_FormEditor::MainForm form;
	Application::Run(%form);
}