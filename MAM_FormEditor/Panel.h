#pragma once

#include "Widget.h"

public ref class CPanel : public CWidget {
public:
	[Category("Main"), Description("Header caption of the panel")]
	property System::String^ Caption {
		System::String^ get() {
			return caption;
		}
		void set(System::String^ value) {
			caption = value;
			if (loaded) {
				CreatePanelImage();
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
			if (loaded) CreatePanelImage();
		}
	}
	property int Height {
		virtual int get() override {
			return height;
		}
		virtual void set(int value) override {
			height = value;
			if (loaded) CreatePanelImage();
		}
	}

public:
	CPanel(System::String^ name, int x, int y);
	CPanel(rapidjson::Value* vWidget);
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

	void CreatePanelImage();
	void CreateCaptionTexture();
};