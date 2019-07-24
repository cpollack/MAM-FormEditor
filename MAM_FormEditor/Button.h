#pragma once

#include "Widget.h"

public ref class CButton : public CWidget {
public:
	[Category("Main"), Description("Text of the Button")]
	property System::String^ Text;

public:
	CButton(System::String^ name, int x, int y);
	virtual void Draw(System::Drawing::Graphics^ gr, System::Drawing::Point pos) override;

	System::Drawing::Point MouseDrag(System::Drawing::Point dragPos, System::Drawing::Point wPos, System::Drawing::Point dragOffset, int dragMode) override;

private:
	const int DEFAULT_WIDTH = 72;
	const int DEFAULT_HEIGHT = 24;

	System::Drawing::Image^ btn = nullptr;
	System::Drawing::Pen ^borderColor;
	System::Drawing::SolidBrush ^buttonColor;
	void CreateButtonImage();

	System::Drawing::StringFormat^ textFormat;
};