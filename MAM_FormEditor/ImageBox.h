#pragma once

#include "Widget.h"

public ref class CImageBox : public CWidget {
public:
	property int Width {
		virtual int get() override {
			return width;
		}
		virtual void set(int value) override {
			width = value;
			//if (loaded) CreateFieldTexture();
		}
	}
	property int Height {
		virtual int get() override {
			return height;
		}
		virtual void set(int value) override {
			height = value;
			//if (loaded) CreateFieldTexture();
		}
	}

	[Category("Appearance"), DisplayName("Skin Image"), Description("Specify the name and extensive of an image from the current skin to use.")]
	property System::String^ SkinImage {
		System::String^ get() {
			return skinImage;
		}
		void set(System::String^ value) {
			skinImage = value;
			if (loaded) CreateImageTexture();
		}
	}
	[Category("Appearance"), DisplayName("Black Background"), Description("Draw the image on a solid black background.")]
	property bool BlackBackground;
	[Category("Appearance"), Description("Encase the image in a 1 pixel border.")]
	property bool Bordered;

public:
	CImageBox(System::String^ name, int x, int y);
	CImageBox(rapidjson::Value* vWidget);
	virtual void Save(rapidjson::Document* document, rapidjson::Value* vWidget) override;
	virtual void Draw(System::Drawing::Graphics^ gr, System::Drawing::Point pos) override;

private:
	const int DEFAULT_WIDTH = 40;
	const int DEFAULT_HEIGHT = 40;
	bool loaded = false;

	//System::Drawing::Image^ bx = nullptr;
	System::String ^skinImage;
	System::Drawing::Image^ img = nullptr;

	System::Drawing::SolidBrush ^bgColor, ^blackBrush;
	System::Drawing::Pen ^whitePen, ^darkPen;
	System::Drawing::Pen^ dashedPen;

	void init();
	void CreateImageTexture();
};