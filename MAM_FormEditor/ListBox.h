#pragma once

#include "Widget.h"

public ref class CListBox : public CWidget {
public:
	[Category("Main"), Description("Header caption of the ListBox")]
	property System::String^ Caption {
		System::String^ get() {
			return caption;
		}
		void set(System::String^ value) {
			caption = value;
			if (loaded) {
				CreateListBoxImage();
				CreateCaptionTexture();
			}
		}
	}

	property int Width {
		virtual int get() override {
			return width;
		}
		virtual void set(int value) override {
			width = value;
			if (loaded) CreateListBoxImage();
		}
	}
	property int Height {
		virtual int get() override {
			return height;
		}
		virtual void set(int value) override {
			height = value;
			if (loaded) CreateListBoxImage();
		}
	}

public:
	CListBox(System::String^ name, int x, int y);
	CListBox(rapidjson::Value* vWidget);
	void init();
	virtual void Save(rapidjson::Document* document, rapidjson::Value* vWidget) override;
	virtual void Draw(System::Drawing::Graphics^ gr, System::Drawing::Point pos) override;
	
	System::Drawing::Point MouseDrag(System::Drawing::Point dragPos, System::Drawing::Point wPos, System::Drawing::Point dragOffset, int dragMode) override;

private:
	const int DEFAULT_WIDTH = 50;
	const int DEFAULT_HEIGHT = 50;
	bool loaded = false;

	System::Drawing::Image^ pnl = nullptr;
	System::Drawing::Image^ cpt = nullptr;
	System::String^ caption;

	System::Drawing::StringFormat^ textFormat;
	System::Drawing::SolidBrush ^bgColor;
	System::Drawing::Pen ^whitePen, ^darkPen;

	void CreateListBoxImage();
	void CreateCaptionTexture();
};