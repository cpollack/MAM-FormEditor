#pragma once

#include "Widget.h"

using System::ComponentModel::DescriptionAttribute;
using System::ComponentModel::BrowsableAttribute;

public enum class TabStyle
{
	tsSimple,
	tsDetail,
	tsButton
};

public ref class CTabControl : public CWidget {
public:
	/*[Category("Main"), Description("Header caption of the panel")]
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
	}*/

	property int Width {
		virtual int get() override {
			return width;
		}
		virtual void set(int value) override {
			width = value;
			if (loaded) CreateTabControlImage();
		}
	}
	property int Height {
		virtual int get() override {
			return height;
		}
		virtual void set(int value) override {
			height = value;
			if (loaded) CreateTabControlImage();
		}
	}

	[Category("Appearance"), Description("Select a tab styling of simple, detailed, or buttoned")]
	property TabStyle Style {
		TabStyle get() {
			return style;
		}
		void set(TabStyle value) {
			style = value;
			if (loaded) CreateTabControlImage();
		}
	}
	[Category("Appearance"), Description("Show the Tab Header on the bottom.")]
	property bool TabsOnBottom;
	[Category("Appearance"), Description("The current visible tab")]
	property int VisibleTab;

	
	[Browsable(false)]
	property int TabItem;

	//[ReadOnly(true)]
	property System::String^ Tabs {
		System::String^ get() {
			System::String ^string;
			string = tabs->Count.ToString() + " tabs.";
			return string;
		}
		void set(System::String ^s) {}
	}

public:
	CTabControl(System::String^ name, int x, int y);
	CTabControl(rapidjson::Value* vWidget);
	void init();
	virtual void Save(rapidjson::Document* document, rapidjson::Value* vWidget) override;
	virtual void Draw(System::Drawing::Graphics^ gr, System::Drawing::Point pos) override;

	System::Drawing::Point MouseDrag(System::Drawing::Point dragPos, System::Drawing::Point wPos, System::Drawing::Point dragOffset, int dragMode) override;
	
	void UpdateVisibleTab(System::Drawing::Point onFormMousePos);

	System::Collections::Generic::List<System::String^> ^tabs;

private:
	const int DEFAULT_WIDTH = 100;
	const int DEFAULT_HEIGHT = 100;
	const int TAB_MIN_WIDTH = 44;
	const int TAB_SPACER = 4;
	const int TAB_SPACER2 = 8;
	const int TAB_HEADER_HEIGHT = 16;
	bool loaded = false;

	System::Drawing::Image^ tabControl = nullptr;
	//System::Drawing::Image^ cpt = nullptr;
	//System::String^ caption;

	System::Drawing::StringFormat^ textFormat;
	System::Drawing::SolidBrush ^bgColor;
	System::Drawing::Pen ^whitePen, ^lightPen, ^darkPen1, ^darkPen2;

	TabStyle style;
	void CreateTabControlImage();
	void DrawSimpleBorder(System::Drawing::Graphics^ gr);
	void DrawDetailBorder(System::Drawing::Graphics^ gr);
	void DrawButtonBorder(System::Drawing::Graphics^ gr);

	void DrawTabs(System::Drawing::Graphics^ gr, System::Drawing::Point pos);
	void DrawSimpleTab(System::Drawing::Graphics^ gr, System::Drawing::Point &pos, int index);
	void DrawDetailTab(System::Drawing::Graphics^ gr, System::Drawing::Point &pos, int index);
	void DrawButtonTab(System::Drawing::Graphics^ gr, System::Drawing::Point &pos, int index);
	//void CreateTabImages();

	int getTabWidth(System::Drawing::Graphics^ gr, int tabidx);
	int getControlWidth(System::Drawing::Graphics^ gr);
};
