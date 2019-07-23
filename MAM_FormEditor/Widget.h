#pragma once

using namespace System::ComponentModel;

public ref class CWidget abstract {
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
	virtual void Draw(System::Drawing::Graphics^ gr, System::Drawing::Point pos) abstract;
};