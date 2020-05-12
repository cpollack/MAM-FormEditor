#include "GlobalLib.h"
#include "Window.h"

#include "Widget.h"
#include "Button.h"
#include "Label.h"
#include "CheckBox.h"
#include "DropDown.h"
#include "Field.h"
#include "Gauge.h"
#include "ImageBox.h"
#include "Panel.h"
#include "RadioButton.h"
#include "TabControl.h"
#include "ListBox.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace rapidjson;

std::string textToString(System::String^ text) {
	msclr::interop::marshal_context context;
	return context.marshal_as<std::string>(text);
}

CWidget^ LoadWidgetByType(rapidjson::Value* vWidget) {
	if (!vWidget->IsObject()) return nullptr;
	Value widget = vWidget->GetObject();

	int type;
	if (!widget.HasMember("Type")) return nullptr;
	type = widget["Type"].GetInt();

	CWidget ^addWidget = nullptr;
	switch (type) {
	case wtLabel:
		addWidget = gcnew CLabel(&widget);
		break;
	case wtCheckBox:
		addWidget = gcnew CCheckBox(&widget);
		break;
	case wtRadioButton:
		addWidget = gcnew CRadioButton(&widget);
		break;
	case wtButton:
		addWidget = gcnew CButton(&widget);
		break;
	case wtPanel:
		addWidget = gcnew CPanel(&widget);
		break;
	case wtField:
		addWidget = gcnew CField(&widget);
		break;
	case wtDropDown:
		addWidget = gcnew CDropDown(&widget);
		break;
	case wtImageBox:
		addWidget = gcnew CImageBox(&widget);
		break;
	case wtTabControl:
		addWidget = gcnew CTabControl(&widget);
		break;
	case wtGauge:
		addWidget = gcnew CGauge(&widget);
		break;
	case wtListBox:
		addWidget = gcnew CListBox(&widget);
		break;
	}

	return addWidget;
}

void doMessageBoxError(std::string title, std::string message) {
	System::String^ mbTitle = gcnew String(title.c_str());
	System::String^ mbMessage = gcnew String(message.c_str());
	MessageBox::Show(mbMessage, mbTitle, MessageBoxButtons::OK, MessageBoxIcon::Error);
}