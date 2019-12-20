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
	Style = TabStyle::tsSimple;
	tabs = gcnew System::Collections::Generic::List<String^>;

	//Testing
	tabs->Add(gcnew String("Default"));

	tabControl = gcnew Bitmap(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	Graphics^ gr = Graphics::FromImage(tabControl);
	Width = GetControlWidth(gr);
	Height = DEFAULT_HEIGHT;
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

	if (vWidget->HasMember("TabsOnBottom")) TabsOnBottom = (*vWidget)["TabsOnBottom"].GetBool();

	//if (vWidget->HasMember("Caption")) Caption = gcnew System::String((*vWidget)["Caption"].GetString());
	//else Caption = "";

	tabs = gcnew List<String^>;
	if (vWidget->HasMember("Tabs")) {
		Value vTabs = (*vWidget)["Tabs"].GetArray();
		if (vTabs.IsArray() && vTabs.Size()) {
			for (rapidjson::SizeType i = 0; i < vTabs.Size(); i++) {
				tabs->Add(gcnew String(vTabs[i].GetString()));
			}
		}
	}

	if (vWidget->HasMember("Widgets")) {
		Value vWidgets = (*vWidget)["Widgets"].GetArray();
		if (vWidgets.IsArray() && vWidgets.Size()) {
			for (rapidjson::SizeType i = 0; i < vWidgets.Size(); i++) {
				Value vWidget = vWidgets[i].GetObject();
				CWidget ^addWidget = LoadWidgetByType(&vWidget);
				if (addWidget) {
					widgets->Add(addWidget);
					addWidget->containedBy = this;
				}
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

	Value vTabs(kArrayType);
	for each (String^ s in tabs) {
		Value* vTab = new Value(kStringType);
		vTab->SetString(textToString(s).c_str(), s->Length, allocator);
		vTabs.PushBack(*vTab, allocator);
		delete vTab;
	}
	vWidget->AddMember("Tabs", vTabs, allocator);

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

int CTabControl::GetTabWidth(Graphics^ gr, int tabIdx) {
	SizeF strSize = gr->MeasureString(tabs[tabIdx], font, Point(0, 0), textFormat);
	
	if (strSize.Width <= TAB_MIN_WIDTH) {
		return TAB_MIN_WIDTH;
	}
	else {
		return tabIdx == VisibleTab ? strSize.Width + TAB_SPACER2*2 : strSize.Width + TAB_SPACER2;
	}
}

int CTabControl::GetControlWidth(Graphics^ gr) {
	int w = 0;
	for (int i = 0; i < tabs->Count; ++i) {
		w += GetTabWidth(gr, i) + TAB_SPACER;
	}

	return w + TAB_SPACER;
}

void CTabControl::DrawSimpleTab(Graphics^ gr, Point &pos, int index) {
	SizeF strSize = gr->MeasureString(tabs[index], font, Point(0, 0), textFormat);
	const int tabWidth = GetTabWidth(gr, index);

	Image ^iTab;
	Graphics^ gr2;
	if (VisibleTab == index) {
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
	//
}

void CTabControl::DrawButtonTab(Graphics^ gr, Point &pos, int index) {
	SolidBrush^ buttonColor = gcnew SolidBrush(Color::FromArgb(00, 56, 55));
	SolidBrush^ fontBrush = gcnew SolidBrush(Color::FromArgb(0xAA, 0xD5, 0xFF));
	Pen^ borderColor = gcnew Pen(Color::FromArgb(0, 0, 0));

	SizeF strSize = gr->MeasureString(tabs[index], font, Point(0, 0), textFormat);
	const int tabWidth = GetTabWidth(gr, index) + 16;
	Image ^iTab;
	Graphics^ gr2;
	if (VisibleTab == index) {
		iTab = gcnew Bitmap(tabWidth, TAB_BUTTON_HEIGHT);
		gr2 = Graphics::FromImage(iTab);
		Point strPoint = Point((iTab->Width / 2) - (strSize.Width / 2), (iTab->Height / 2) - (strSize.Height / 2));

		gr2->FillRectangle(buttonColor, System::Drawing::Rectangle(0, 0, Width, TAB_BUTTON_HEIGHT));
		gr2->DrawLine(borderColor, Point(0, 0), Point(0, TAB_BUTTON_HEIGHT -1));
		if (!TabsOnBottom) gr2->DrawLine(borderColor, Point(0, 0), Point(tabWidth - 1, 0));
		gr2->DrawLine(borderColor, Point(tabWidth - 1, 0), Point(tabWidth - 1, TAB_BUTTON_HEIGHT - 1));
		if (TabsOnBottom) gr2->DrawLine(borderColor, Point(0, TAB_BUTTON_HEIGHT - 1), Point(tabWidth - 1, TAB_BUTTON_HEIGHT - 1));

		gr2->DrawString(tabs[index], font, fontBrush, strPoint, textFormat);
		
		Point p = pos;
		if (TabsOnBottom) p.Y += Height - TAB_BUTTON_HEIGHT;
		gr->DrawImage(iTab, p);
		pos.X += tabWidth + TAB_SPACER;
	}
	else {
		iTab = gcnew Bitmap(tabWidth, TAB_BUTTON_HEIGHT);
		gr2 = Graphics::FromImage(iTab);
		Point strPoint = Point((iTab->Width / 2) - (strSize.Width / 2), (iTab->Height / 2) - (strSize.Height / 2));

		gr2->FillRectangle(buttonColor, System::Drawing::Rectangle(0, 0, tabWidth - 1, TAB_BUTTON_HEIGHT - 1));
		gr2->DrawRectangle(borderColor, System::Drawing::Rectangle(0, 0, tabWidth - 1, TAB_BUTTON_HEIGHT - 1));

		gr2->DrawString(tabs[index], font, fontBrush, strPoint, textFormat);

		Point p = pos;
		if (TabsOnBottom) p.Y += Height - TAB_BUTTON_HEIGHT;
		gr->DrawImage(iTab, p);
		pos.X += tabWidth + TAB_SPACER;
	}
}

void CTabControl::UpdateVisibleTab(Point onFormMousePos)
{
	if (onFormMousePos.Y >= Y && onFormMousePos.Y <= Y + TAB_HEADER_HEIGHT) {
		if (!tabControl) doMessageBoxError("CTabControl::MouseDrag", "tabControl is null!");
		Graphics^ gr = Graphics::FromImage(tabControl);

		int x = X;
		for (int i = 0; i < tabs->Count; ++i) {
			int tabWidth = GetTabWidth(gr, i);

			if (onFormMousePos.X >= x && onFormMousePos.X <= x + tabWidth) {
				VisibleTab = i;
				break;
			}

			x += tabWidth;
		}
	}
}

Point CTabControl::MouseDrag(Point dragPos, Point wPos, Point dragOffset, int dragMode) {
	int tWidth = Width;
	int tHeight = Height;

	Point rPoint = CWidget::MouseDrag(dragPos, wPos, dragOffset, dragMode);

	if (tWidth != Width || tHeight != Height) CreateTabControlImage();

	UpdateVisibleTab(Point(dragPos.X - wPos.X, dragPos.Y - wPos.Y));

	return rPoint;
}
