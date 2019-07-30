#pragma once

#include "Widget.h"

public ref class CButton : public CWidget {
public:
	[Category("Main"), Description("Text of the Button")]
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
	CButton(System::String^ name, int x, int y);
	CButton(rapidjson::Value* vWidget);
	virtual void Save(rapidjson::Document* document, rapidjson::Value* vWidget) override;
	virtual void Draw(System::Drawing::Graphics^ gr, System::Drawing::Point pos) override;

	System::Drawing::Point MouseDrag(System::Drawing::Point dragPos, System::Drawing::Point wPos, System::Drawing::Point dragOffset, int dragMode) override;

private:
	const int DEFAULT_WIDTH = 72;
	const int DEFAULT_HEIGHT = 24;
	bool loaded = false;

	System::Drawing::Image^ btn = nullptr;
	System::Drawing::Pen ^borderColor;
	System::Drawing::SolidBrush ^buttonColor;
	void CreateButtonImage();

	System::String^ text;
	System::Drawing::Image^ lbl = nullptr;
	System::Drawing::StringFormat^ textFormat;
	System::Drawing::Pen^ underlinePen;
	void CButton::CreateLabelTexture();
};