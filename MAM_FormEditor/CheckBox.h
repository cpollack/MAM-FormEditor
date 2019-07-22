#pragma once

using namespace System::ComponentModel;

public ref class CCheckBox {
public: 
	[Category("Test"), Description("X coordinate of widget on form")]
	//[DisplayName("Test Property")]
	property int X;
	[Category("Test"), Description("Y coordinate of widget on form")]
	property int Y;
	property int Width;
	property int Height;

public:
	CCheckBox(int x, int y);
	void CCheckBox::Draw();

private:
	const int DEFAULT_WIDTH = 20;
	const int DEFAULT_HEIGHT = 8;
};