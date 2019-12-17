#include "TabControl.h"
#include "GlobalLib.h"

using namespace System::Drawing;
using namespace System::Collections;
using namespace rapidjson;

CTabControl::CTabControl(System::String^ name, int x, int y) {
	init();
	Name = name;
	X = x;
	Y = y;
	Width = DEFAULT_WIDTH;
	Height = DEFAULT_HEIGHT;
	Style = TabStyle::tsSimple;

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

	gr->DrawRectangle(pen, 0, TAB_HEADER_HEIGHT, Width - 1, Height - 1 - TAB_HEADER_HEIGHT);
}

void CTabControl::DrawDetailBorder(Graphics^ gr) {
	gr->DrawLine(whitePen, Point(0, TAB_HEADER_HEIGHT), Point(width - 1, TAB_HEADER_HEIGHT));
	gr->DrawLine(whitePen, Point(0, TAB_HEADER_HEIGHT), Point(0, height - 1));
	gr->DrawLine(lightPen, Point(1, TAB_HEADER_HEIGHT + 1), Point(width - 2, TAB_HEADER_HEIGHT + 1));
	gr->DrawLine(lightPen, Point(1, TAB_HEADER_HEIGHT + 1), Point(1, height - 2));

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
	//if (cpt) gr->DrawImage(cpt, Point(widgetPos.X + 5, widgetPos.Y));

	for each(CWidget^ w in widgets) {
		w->Draw(gr, pos);
	}
}

Point CTabControl::MouseDrag(Point dragPos, Point wPos, Point dragOffset, int dragMode) {
	int tWidth = Width;
	int tHeight = Height;

	Point rPoint = CWidget::MouseDrag(dragPos, wPos, dragOffset, dragMode);

	if (tWidth != Width || tHeight != Height) CreateTabControlImage();

	return rPoint;
}
