#pragma once

#include "include/rapidjson/document.h"

using namespace System::ComponentModel;

enum WidgetType {
	wtLabel,
	wtCheckBox,
	wtRadioButton,
	wtButton
};

public ref class CWidget {
public: //Properties
	[Category("Main"), Description("The indentifying name of the widget")]
	property System::String^ Name;
	[Category("Main"), Description("X coordinate of widget on form")]
	property int X;
	[Category("Main"), Description("Y coordinate of widget on form")]
	property int Y;
	[Category("Main"), Description("Width of the widget in pixels")]
	property int Width;
	[Category("Main"), Description("Height of the widget in pixels")]
	property int Height;
	//[DisplayName("Test Property")]

public:
	int widgetType;

	CWidget();
	CWidget(rapidjson::Value* vWidget);
	virtual void Draw(System::Drawing::Graphics^ gr, System::Drawing::Point pos) abstract;
	virtual void Save(rapidjson::Document* document, rapidjson::Value* vWidget);

	virtual bool DoesPointIntersect(System::Drawing::Point point);
	int MouseDown(System::Windows::Forms::MouseEventArgs^ e, System::Drawing::Point wPos);
	System::Windows::Forms::Cursor^ MouseMove(System::Windows::Forms::MouseEventArgs^ e, System::Drawing::Point wPos);
	virtual System::Drawing::Point MouseDrag(System::Drawing::Point dragPos, System::Drawing::Point wPos, System::Drawing::Point dragOffset, int dragMode);

protected:
	int MIN_HEIGHT = 2;
	int MIN_WIDTH = 5;

	System::Drawing::Font ^font;
	System::Drawing::SolidBrush ^fontBrush;
};