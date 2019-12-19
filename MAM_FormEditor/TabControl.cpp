#include "TabControl.h"
#include "GlobalLib.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace rapidjson;

CTabControl::CTabControl(System::String^ name, int x, int y) {
	init();
	Name = name;
	X = x;
	Y = y;
	Width = DEFAULT_WIDTH;
	Height = DEFAULT_HEIGHT;
	Style = TabStyle::tsSimple;
	tabs = gcnew System::Collections::Generic::List<String^>;

	//Testing
	tabs->Add(gcnew String("Test"));
	tabs->Add(gcnew String("Testing Long Tab Just because"));
	tabs->Add(gcnew String("Tab 3 Neato"));
	//Testing

	VisibleTab = 0;

	CreateTabControlImage();
	//CreateCaptionTexture();
	loaded = true;
}

CTabControl::CTabControl(rapidjson::Value* vWidget) : CWidget(vWidget) {
	init();
	if (!vWidget->IsObject()) return;

	VisibleTab = 0;

	if (vWidget->HasMember("Style")) Style = (TabStyle)(*vWidget)["Style"].GetInt();
	else Style = TabStyle::tsSimple;

	//if (vWidget->HasMember("Caption")) Caption = gcnew System::String((*vWidget)["Caption"].GetString());
	//else Caption = "";

	if (vWidget->HasMember("Tabs")) {
		Value vTabs = (*vWidget)["Tabs"].GetArray();
		if (vTabs.IsArray()) {
			for (rapidjson::SizeType i = 0; i < vTabs.Size(); i++) {
				Value vTab = vTabs[i].GetObject();
				vTab.GetString();
				tabs->Add(gcnew String(vTab.GetString()));
			}
		}
	}

	if (vWidget->HasMember("Widgets")) {
		Value vWidgets = (*vWidget)["Widgets"].GetArray();
		if (vWidgets.IsArray()) {
			for (rapidjson::SizeType i = 0; i < vWidgets.Size(); i++) {
				Value vWidget = vWidgets[i].GetObject();
				CWidget ^addWidget = LoadWidgetByType(&vWidget);
				if (addWidget) widgets->Add(addWidget);
			}
		}
	}

	CreateTabControlImage();
	//CreateCaptionTexture();
	loaded = true;
}

void CTabControl::init() {
	widgetType = wtTabControl;
	MIN_HEIGHT = 30;
	MIN_WIDTH = 20;

	container = true;
	widgets = gcnew ArrayList;

	unsigned int uiColor = 0x3A5121;
	bgColor = gcnew SolidBrush(Color::FromArgb(uiColor & 0xFF, (uiColor & 0xFF00) >> 8, (uiColor & 0xFF0000) >> 16));
	whitePen = gcnew Pen(Color::FromArgb(0xFF, 0xFF, 0xFF, 0xFF));
	lightPen = gcnew Pen(Color::FromArgb(0xFF, 0xE3, 0xE3, 0xE3));
	darkPen1 = gcnew Pen(Color::FromArgb(0xFF, 0xA0, 0xA0, 0xA0));
	darkPen2 = gcnew Pen(Color::FromArgb(0xFF, 0x69, 0x69, 0x69));

	textFormat = gcnew StringFormat(StringFormat::GenericTypographic);
	textFormat->Alignment = StringAlignment::Near;
	textFormat->LineAlignment = StringAlignment::Near;
}

void CTabControl::Save(rapidjson::Document* document, rapidjson::Value* vWidget) {
	CWidget::Save(document, vWidget);
	Document::AllocatorType& allocator = document->GetAllocator();

	//if (Caption->Length > 0) {
	//	Value vtext(kStringType);
	//	vtext.SetString(textToString(Caption).c_str(), Caption->Length, allocator);
	//	vWidget->AddMember("Caption", vtext, allocator);
	//}

	rapidjson::Value vBottom(TabsOnBottom);
	vWidget->AddMember("TabsOnBottom", vBottom, allocator);

	Value vStyle(kNumberType);
	vStyle.SetInt((int)Style);
	vWidget->AddMember("Style", vStyle, allocator);

	Value vWidgets(kArrayType);
	for each (CWidget^ w in widgets) {
		Value* vWidget = new Value(kObjectType);
		w->Save(document, vWidget);
		vWidgets.PushBack(*vWidget, allocator);
		delete vWidget;
	}
	vWidget->AddMember("Widgets", vWidgets, allocator);
}

void CTabControl::CreateTabControlImage() {
	if (tabControl) delete tabControl;
	tabControl = gcnew Bitmap(Width, Height);
	Graphics^ gr = Graphics::FromImage(tabControl);

	//Fill with BG color first
	gr->FillRectangle(bgColor, System::Drawing::Rectangle(0, 0, Width, Height));

	switch (Style) {
	case TabStyle::tsSimple:
		DrawSimpleBorder(gr);
		break;
	case TabStyle::tsDetail:
		DrawDetailBorder(gr);
		break;
	case TabStyle::tsButton:
		DrawButtonBorder(gr);
		break;
	}

	//Style
	//TabsOnBottom

	/*if (Caption->Length > 0) {
		//Header, draw complex border
		int captionOffset = 7;
		gr->DrawRectangle(whitePen, System::Drawing::Rectangle(1, captionOffset + 1, width - 2, height - captionOffset - 2));
		gr->DrawRectangle(darkPen, System::Drawing::Rectangle(0, captionOffset, width - 2, height - captionOffset - 2));
	}
	else {
		//No header, draw simple border
		gr->DrawLine(whitePen, Point(0, 0), Point(width - 1, 0));
		gr->DrawLine(whitePen, Point(0, 0), Point(0, height - 1));

		gr->DrawLine(darkPen, Point(0, height - 1), Point(width - 1, height - 1));
		gr->DrawLine(darkPen, Point(width - 1, 0), Point(width - 1, height - 1));
	}*/
}

void CTabControl::DrawSimpleBorder(Graphics^ gr) {
	Pen^ pen = gcnew Pen(Color::FromArgb(0xFF, 0xA0, 0x96, 0x83));

	gr->DrawRectangle(pen, 0, TAB_HEADER_HEIGHT - 1, Width - 1, Height - 2 - TAB_HEADER_HEIGHT);
}

void CTabControl::DrawDetailBorder(Graphics^ gr) {
	gr->DrawLine(whitePen, Point(0, TAB_HEADER_HEIGHT - 1), Point(width - 1, TAB_HEADER_HEIGHT - 1));
	gr->DrawLine(whitePen, Point(0, TAB_HEADER_HEIGHT - 1), Point(0, height - 1));
	gr->DrawLine(lightPen, Point(1, TAB_HEADER_HEIGHT), Point(width - 2, TAB_HEADER_HEIGHT));
	gr->DrawLine(lightPen, Point(1, TAB_HEADER_HEIGHT), Point(1, height - 2));

	gr->DrawLine(darkPen2, Point(0, height - 1), Point(width - 1, height - 1));
	gr->DrawLine(darkPen2, Point(width - 1, TAB_HEADER_HEIGHT), Point(width - 1, height - 1));
	gr->DrawLine(darkPen1, Point(1, height - 2), Point(width - 2, height - 2));
	gr->DrawLine(darkPen1, Point(width - 2, TAB_HEADER_HEIGHT + 1), Point(width - 2, height - 2));
}

void CTabControl::DrawButtonBorder(Graphics^ gr) {
	//no border
}

/*void CPanel::CreateCaptionTexture() {
	if (cpt) {
		delete cpt;
		cpt = nullptr;
	}
	if (Caption->Length == 0) return;

	Graphics ^gr = Graphics::FromImage(pnl);
	gr->TextRenderingHint = System::Drawing::Text::TextRenderingHint::AntiAlias;

	SizeF prefixSize = gr->MeasureString(Caption, font, Point(0, 0), textFormat);
	cpt = gcnew Bitmap(prefixSize.Width + 4, prefixSize.Height + 2);

	gr = Graphics::FromImage(cpt);
	gr->FillRectangle(bgColor, System::Drawing::Rectangle(0, 0, width, height));
	gr->DrawString(Caption, font, fontBrush, Point(2, 1), textFormat);
}*/

void CTabControl::Draw(Graphics^ gr, Point pos) {
	Point widgetPos(pos.X + X, pos.Y + Y);

	gr->DrawImage(tabControl, widgetPos);
	DrawTabs(gr, widgetPos);

	for each(CWidget^ w in widgets) {
		if (VisibleTab == w->TabItem) w->Draw(gr, pos);
	}
}

void CTabControl::DrawTabs(Graphics^ gr, Point pos) {
	int xOffset = 0;

	for (int i = 0; i < tabs->Count; i++) {
		switch (Style) {
		case TabStyle::tsSimple:
			DrawSimpleTab(gr, pos, i);
			break;
		case TabStyle::tsDetail:
			DrawDetailTab(gr, pos, i);
			break;
		case TabStyle::tsButton:
			DrawButtonTab(gr, pos, i);
			break;
		}
	}
}

void CTabControl::DrawSimpleTab(Graphics^ gr, Point &pos, int index) {
	SizeF strSize = gr->MeasureString(tabs[index], font, Point(0, 0), textFormat);
	int tabWidth = strSize.Width;
	if (tabWidth < TAB_MIN_WIDTH) tabWidth = TAB_MIN_WIDTH;

	Image ^iTab;
	Graphics^ gr2;
	if (VisibleTab == index) {
		if (tabWidth > TAB_MIN_WIDTH) tabWidth = strSize.Width + 16;
		iTab = gcnew Bitmap(tabWidth, TAB_HEADER_HEIGHT);
		Point strPoint = Point((iTab->Width / 2) - (strSize.Width / 2), (iTab->Height / 2) - (strSize.Height / 2));

		gr2 = Graphics::FromImage(iTab);
		gr2->FillRectangle(bgColor, System::Drawing::Rectangle(0, 0, iTab->Width, iTab->Height));

		Pen^ pen = gcnew Pen(Color::FromArgb(0xFF, 0xA0, 0x96, 0x83));
		gr2->DrawLine(pen, Point(0, 0), Point(0, TAB_HEADER_HEIGHT - 1));
		gr2->DrawLine(pen, Point(tabWidth - 1, 0), Point(tabWidth - 1, TAB_HEADER_HEIGHT - 1));
		gr2->DrawLine(pen, Point(0, 0), Point(strPoint.X, 0));
		gr2->DrawLine(pen, Point(strPoint.X + strSize.Width, 0), Point(tabWidth - 1, 0));

		gr2->DrawString(tabs[index], font, fontBrush, strPoint, textFormat);

		gr->DrawImage(iTab, pos);
		pos.X += tabWidth + TAB_SPACER;
	}
	else {
		if (tabWidth > TAB_MIN_WIDTH) tabWidth = strSize.Width + 8;

		iTab = gcnew Bitmap(tabWidth, TAB_HEADER_HEIGHT - 1);
		Point strPoint = Point((iTab->Width / 2) - (strSize.Width / 2), (iTab->Height / 2) - (strSize.Height / 2));
		gr2 = Graphics::FromImage(iTab);

		SolidBrush ^blueBrush = gcnew SolidBrush(Color::FromArgb(255, 0x30, 0x60, 0x90));
		gr2->FillRectangle(blueBrush, System::Drawing::Rectangle(0, 0, iTab->Width, iTab->Height));

		gr2->DrawString(tabs[index], font, bgColor, strPoint, textFormat);

		gr->DrawImage(iTab, pos);
		pos.X += tabWidth + TAB_SPACER;
	}
}

void CTabControl::DrawDetailTab(Graphics^ gr, Point &pos, int index) {
}

void CTabControl::DrawButtonTab(Graphics^ gr, Point &pos, int index) {
}

Point CTabControl::MouseDrag(Point dragPos, Point wPos, Point dragOffset, int dragMode) {
	int tWidth = Width;
	int tHeight = Height;

	Point rPoint = CWidget::MouseDrag(dragPos, wPos, dragOffset, dragMode);

	if (tWidth != Width || tHeight != Height) CreateTabControlImage();

	return rPoint;
}
