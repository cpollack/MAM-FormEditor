#pragma once

#include "Widget.h"

public ref class CGauge : public CWidget {
public:
	[Category("Main"), DisplayName("Current Value"), Description("Current value of the gauge.")]
	property int Value {
		int get() {
			return value;
		}
		void set(int v) {
			value = v;
			if (loaded) CreateTexture();
		}
	}
	[Category("Main"), DisplayName("Max Value"), Description("Max value of the gauge.")]
	property int Max {
		int get() {
			return max;
		}
		void set(int v) {
			max = v;
			if (loaded) CreateTexture();
		}
	}

	property int Width {
		virtual int get() override {
			return width;
		}
		virtual void set(int value) override {
			width = value;
			if (loaded) CreateTexture();
		}
	}
	property int Height {
		virtual int get() override {
			return height;
		}
		virtual void set(int value) override {
			height = value;
			if (loaded) CreateTexture();
		}
	}

	[Category("Behavior"), DisplayName("Show Label"), Description("Display Value/Total in the gauge area.")]
	property bool ShowLabel {
		bool get() {
			return showLabel;
		}
		void set(bool v) {
			showLabel = v;
			if (loaded) CreateTexture();
		}
	}


public:
	CGauge(System::String^ name, int x, int y);
	CGauge(rapidjson::Value* vWidget);
	virtual void Save(rapidjson::Document* document, rapidjson::Value* vWidget) override;
	virtual void Draw(System::Drawing::Graphics^ gr, System::Drawing::Point pos) override;

private:
	const int DEFAULT_WIDTH = 50;
	const int DEFAULT_HEIGHT = 14;
	bool loaded = false;

	System::Drawing::Image^ gge = nullptr;
	System::Drawing::Image^ val = nullptr;
	int value, max;
	bool showLabel = true;

	System::Drawing::StringFormat^ textFormat;
	System::Drawing::SolidBrush ^bgColor, ^fillBrush;
	System::Drawing::Pen ^borderPen;

	void init();
	void CreateTexture();
};