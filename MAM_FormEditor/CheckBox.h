#pragma once

#include "Widget.h"

public ref class CCheckBox : public CWidget {
public: 
	/*[Category("Test"), Description("X coordinate of widget on form")]
	//[DisplayName("Test Property")]
	property int X;
	[Category("Test"), Description("Y coordinate of widget on form")]
	property int Y;
	property int Width;
	property int Height;*/

	[Category("Main"), Description("Descriptive label of the checkbox")]
	property System::String^ Text;

public:
	CCheckBox(System::String^ name, int x, int y);
	virtual void Draw(System::Drawing::Graphics^ gr, System::Drawing::Point pos) override;

private:
	const int DEFAULT_WIDTH = 50;
	const int DEFAULT_HEIGHT = 14;
};