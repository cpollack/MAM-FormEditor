#pragma once

#include "Widget.h"

public ref class CField : public CWidget {
public:
	[Category("Main"), DisplayName("Default Value"), Description("Content of the field")]
	property System::String^ Value {
		System::String^ get() {
			return value;
		}
		void set(System::String^ v) {
			value = v;
			if (loaded) CreateFieldTexture();
		}
	}

	property int Width {
		virtual int get() override {
			return width;
		}
		virtual void set(int value) override {
			width = value;
			if (loaded) CreateFieldTexture();
		}
	}
	property int Height {
		virtual int get() override {
			return height;
		}
		virtual void set(int value) override {
			height = value;
			if (loaded) CreateFieldTexture();
		}
	}

	[Category("Behavior"), DisplayName("Is Password"), Description("Treat field as a password and mask its value.")]
	property bool IsPassword;

public:
	CField(System::String^ name, int x, int y);
	CField(rapidjson::Value* vWidget);
	virtual void Save(rapidjson::Document* document, rapidjson::Value* vWidget) override;
	virtual void Draw(System::Drawing::Graphics^ gr, System::Drawing::Point pos) override;

private:
	const int DEFAULT_WIDTH = 50;
	const int DEFAULT_HEIGHT = 14;
	bool loaded = false;

	System::Drawing::Image^ fld = nullptr;
	System::Drawing::Image^ val = nullptr;
	System::String^ value;

	System::Drawing::StringFormat^ textFormat;
	System::Drawing::SolidBrush ^bgColor;
	System::Drawing::Pen ^whitePen, ^darkPen;

	void init();
	void CreateFieldTexture();
};