#pragma once

#include "Widget.h"

public ref class CRadioButton : public CWidget {
public:
	[Category("Main"), Description("Descriptive label of the checkbox")]
	property System::String^ Text;

public:
	CRadioButton(System::String^ name, int x, int y);
	virtual void Save(rapidjson::Document* document, rapidjson::Value* vWidget) override;
	virtual void Draw(System::Drawing::Graphics^ gr, System::Drawing::Point pos) override;

private:
	const int DEFAULT_WIDTH = 50;
	const int DEFAULT_HEIGHT = 14;
	System::Drawing::Image^ rb;

	System::Drawing::StringFormat^ textFormat;
	System::Drawing::Pen^ dashedPen;
};