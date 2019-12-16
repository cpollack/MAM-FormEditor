#pragma once

#include "Widget.h"

public ref class CDropDown : public CWidget {
public:
	[Category("Main"), Description("Text of the Button")]
	property System::String^ Value {
		System::String^ get() {
			return value;
		}
		void set(System::String^ v) {
			value = v;
			//if (loaded) CreateValueTexture();
		}
	}

	property int Width {
		virtual int get() override {
			return width;
		}
		virtual void set(int value) override {
			width = value;
			//if (loaded) CreateValueTexture();
		}
	}
	property int Height {
		virtual int get() override {
			return height;
		}
		virtual void set(int value) override {
			height = value;
			//if (loaded) CreateValueTexture();
		}
	}

	[Category("Appearance"), DisplayName("Detailed"), Description("Render the dropdown with a detailed appearance.")]
	property bool Detailed;

public:
	CDropDown(System::String^ name, int x, int y);
	CDropDown(rapidjson::Value* vWidget);
	virtual void Save(rapidjson::Document* document, rapidjson::Value* vWidget) override;
	virtual void Draw(System::Drawing::Graphics^ gr, System::Drawing::Point pos) override;

private:
	const int DEFAULT_WIDTH = 72;
	const int DEFAULT_HEIGHT = 24;
	bool loaded = false;
	void init();

	System::Drawing::Image^ dd = nullptr;
	System::Drawing::Pen ^borderColor;
	System::Drawing::Pen ^buttonColor;
	void CreateButtonImage();

	System::String^ value;
	System::Drawing::Image^ lbl = nullptr;
	System::Drawing::StringFormat^ textFormat;
	//void CreateValueTexture();

	System::Drawing::Pen ^whitePen, ^light2Pen, ^dark1Pen, ^dark2Pen, ^blackPen;
	System::Drawing::SolidBrush ^light1Brush;
};