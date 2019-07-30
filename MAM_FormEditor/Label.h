#pragma once

#include "Widget.h"

public ref class CLabel : public CWidget {
public:
	[Category("Main"), Description("Descriptive label of the checkbox")]
	property System::String^ Text {
		System::String^ get() {
			return text;
		}
		void set(System::String^ value) {
			text = value;
			if (loaded) CreateLabelTexture();
		}
	}

	property int Width {
		virtual int get() override {
			return width;
		}
		virtual void set(int value) override {
			width = value;
			if (loaded) CreateLabelTexture();
		}
	}
	property int Height {
		virtual int get() override {
			return height;
		}
		virtual void set(int value) override {
			height = value;
			if (loaded) CreateLabelTexture();
		}
	}

public:
	CLabel(System::String^ name, int x, int y);
	CLabel(rapidjson::Value* vWidget);
	virtual void Save(rapidjson::Document* document, rapidjson::Value* vWidget) override;
	virtual void Draw(System::Drawing::Graphics^ gr, System::Drawing::Point pos) override;

private:
	const int DEFAULT_WIDTH = 50;
	const int DEFAULT_HEIGHT = 14;
	bool loaded = false;

	System::Drawing::Image^ lbl = nullptr;
	System::String^ text;

	System::Drawing::StringFormat^ textFormat;
	System::Drawing::Pen^ dashedPen;
	System::Drawing::Pen^ underlinePen;

	void CLabel::CreateLabelTexture();
};