#include "Panel.h"
#include "GlobalLib.h"

using namespace System::Drawing;
using namespace rapidjson;

CPanel::CPanel(System::String^ name, int x, int y) {
	widgetType = wtPanel;
	MIN_HEIGHT = 30;
	MIN_WIDTH = 20;

	Name = name;
	Caption = "";
	X = x;
	Y = y;
	Width = DEFAULT_WIDTH;
	Height = DEFAULT_HEIGHT;

	unsigned int uiColor = 0x3A5121;
	bgColor = gcnew SolidBrush(Color::FromArgb(uiColor & 0xFF, (uiColor & 0xFF00) >> 8, (uiColor & 0xFF0000) >> 16));
	whitePen = gcnew Pen(Color::FromArgb(0xFF, 0xFF, 0xFF, 0xFF));
	darkPen = gcnew Pen(Color::FromArgb(0xFF, 0xA0, 0xA0, 0xA0));
	fontBrush = gcnew SolidBrush(Color::FromArgb(0xAA, 0xD5, 0xFF));

	textFormat = gcnew StringFormat(StringFormat::GenericTypographic);
	textFormat->Alignment = StringAlignment::Near;
	textFormat->LineAlignment = StringAlignment::Near;

	CreatePanelImage();
	CreateCaptionTexture();
	loaded = true;
}

CPanel::CPanel(rapidjson::Value* vWidget) : CWidget(vWidget) {
	if (!vWidget->IsObject()) return;

	widgetType = wtPanel;
	MIN_HEIGHT = 20;
	MIN_WIDTH = 20;

	unsigned int uiColor = 0x3A5121;
	bgColor = gcnew SolidBrush(Color::FromArgb(uiColor & 0xFF, (uiColor & 0xFF00) >> 8, (uiColor & 0xFF0000) >> 16));
	fontBrush = gcnew SolidBrush(Color::FromArgb(0xAA, 0xD5, 0xFF));

	textFormat = gcnew StringFormat(StringFormat::GenericTypographic);
	textFormat->Alignment = StringAlignment::Near;
	textFormat->LineAlignment = StringAlignment::Near;

	if (vWidget->HasMember("Caption")) Caption = gcnew System::String((*vWidget)["Caption"].GetString());
	else Caption = "";

	CreatePanelImage();
	CreateCaptionTexture();
	loaded = true;
}

void CPanel::Save(rapidjson::Document* document, rapidjson::Value* vWidget) {
	CWidget::Save(document, vWidget);
	Document::AllocatorType& allocator = document->GetAllocator();

	if (Caption->Length > 0) {
		Value vtext(kStringType);
		vtext.SetString(textToString(Caption).c_str(), Caption->Length, allocator);
		vWidget->AddMember("Caption", vtext, allocator);
	}
}

void CPanel::CreatePanelImage() {
	if (pnl) delete pnl;
	pnl = gcnew Bitmap(Width, Height);
	Graphics^ gr = Graphics::FromImage(pnl);

	//Fill with BG color first
	gr->FillRectangle(bgColor, System::Drawing::Rectangle(0, 0, Width, Height));

	if (Caption->Length > 0) {
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
	}
}

void CPanel::CreateCaptionTexture() {
	if (cpt) delete cpt;

	Graphics ^gr = Graphics::FromImage(pnl);
	gr->TextRenderingHint = System::Drawing::Text::TextRenderingHint::AntiAlias;

	SizeF prefixSize = gr->MeasureString(Caption, font, Point(0, 0), textFormat);
	cpt = gcnew Bitmap(prefixSize.Width + 4, prefixSize.Height + 2);

	gr = Graphics::FromImage(cpt);
	gr->FillRectangle(bgColor, System::Drawing::Rectangle(0, 0, width, height));
	gr->DrawString(Caption, font, fontBrush, Point(2,1), textFormat);
}

void CPanel::Draw(Graphics^ gr, Point pos) {
	Point widgetPos(pos.X + X, pos.Y + Y);

	gr->DrawImage(pnl, widgetPos);
	if (cpt) gr->DrawImage(cpt, Point(widgetPos.X + 5, widgetPos.Y));
}

Point CPanel::MouseDrag(Point dragPos, Point wPos, Point dragOffset, int dragMode) {
	int tWidth = Width;
	int tHeight = Height;

	Point rPoint = CWidget::MouseDrag(dragPos, wPos, dragOffset, dragMode);

	if (tWidth != Width || tHeight != Height) CreatePanelImage();

	return rPoint;
}