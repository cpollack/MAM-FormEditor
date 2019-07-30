#include "Button.h"
#include "GlobalLib.h"

using namespace System::Drawing;
using namespace rapidjson;

CButton::CButton(System::String^ name, int x, int y) {
	widgetType = wtButton;
	MIN_HEIGHT = 13;
	MIN_WIDTH = 20;

	Name = name;
	Text = name;
	X = x;
	Y = y;
	Width = DEFAULT_WIDTH;
	Height = DEFAULT_HEIGHT;

	borderColor = gcnew Pen(Color::FromArgb(0, 0, 0));
	buttonColor = gcnew SolidBrush(Color::FromArgb(00, 56, 55));
	fontBrush = gcnew SolidBrush(Color::FromArgb(0xAA, 0xD5, 0xFF));

	textFormat = gcnew StringFormat(StringFormat::GenericTypographic);
	textFormat->Alignment = StringAlignment::Center;
	textFormat->LineAlignment = StringAlignment::Center;

	underlinePen = gcnew Pen(fontBrush->Color);

	CreateButtonImage();
	CreateLabelTexture();
	loaded = true;
}

CButton::CButton(rapidjson::Value* vWidget) : CWidget(vWidget) {
	if (!vWidget->IsObject()) return;

	widgetType = wtButton;
	MIN_HEIGHT = 13;
	MIN_WIDTH = 20;

	borderColor = gcnew Pen(Color::FromArgb(0, 0, 0));
	buttonColor = gcnew SolidBrush(Color::FromArgb(00, 56, 55));
	fontBrush = gcnew SolidBrush(Color::FromArgb(0xAA, 0xD5, 0xFF));

	textFormat = gcnew StringFormat(StringFormat::GenericTypographic);
	textFormat->Alignment = StringAlignment::Center;
	textFormat->LineAlignment = StringAlignment::Center;

	underlinePen = gcnew Pen(fontBrush->Color);

	if (vWidget->HasMember("Text")) Text = gcnew System::String((*vWidget)["Text"].GetString());
	else Text = Name;

	CreateButtonImage();
	CreateLabelTexture();
	loaded = true;
}

void CButton::Save(rapidjson::Document* document, rapidjson::Value* vWidget) {
	CWidget::Save(document, vWidget);
	Document::AllocatorType& allocator = document->GetAllocator();

	Value vtext(kStringType);
	vtext.SetString(textToString(Text).c_str(), Text->Length, allocator);
	vWidget->AddMember("Text", vtext, allocator);
}

void CButton::CreateButtonImage() {
	if (btn) delete btn;
	btn = gcnew Bitmap(Width, Height);
	Graphics^ gr = Graphics::FromImage(btn);
	gr->FillRectangle(buttonColor, System::Drawing::Rectangle(0, 0, Width, Height));
	gr->DrawRectangle(borderColor, System::Drawing::Rectangle(0, 0, Width-1, Height-1));
}

void CButton::CreateLabelTexture() {
	if (lbl) delete lbl;

	lbl = gcnew Bitmap(Width, Height);
	Graphics ^gr = Graphics::FromImage(lbl);
	gr->TextRenderingHint = System::Drawing::Text::TextRenderingHint::AntiAlias;

	bool drawUnderline = false;
	System::String ^drawText = Text;

	//check text for ampersand and get position and size of character to underscore
	RectangleF underline;
	if (Text->Contains("&")) {
		int pos = Text->IndexOf("&");
		System::String^ prefix = Text->Substring(0, pos);
		System::String^ nextChar = Text->Substring(pos + 1, 1);
		SizeF prefixSize = gr->MeasureString(prefix, font, Point(0, 0), textFormat);
		SizeF charSize = gr->MeasureString(nextChar, font, Point(0, 0), textFormat);
		underline = RectangleF(prefixSize.Width, prefixSize.Height, charSize.Width, 1);
		drawUnderline = true;

		drawText = drawText->Replace("&", "");
	}

	SizeF textSize = gr->MeasureString(drawText, font, Point(0, 0), textFormat);
	gr->DrawString(drawText, font, fontBrush, Point(Width / 2, Height / 2), textFormat);
	float xPos = (Width / 2) - (textSize.Width / 2) + underline.X;
	float yPos = (Height / 2) + (textSize.Height / 2) - 0.5;
	if (drawUnderline) gr->DrawLine(underlinePen, xPos, yPos, xPos + underline.Width, yPos);
}

void CButton::Draw(Graphics^ gr, Point pos) {
	Point widgetPos(pos.X + X, pos.Y + Y);

	gr->DrawImage(btn, widgetPos);
	gr->DrawImage(lbl, widgetPos);
}

Point CButton::MouseDrag(Point dragPos, Point wPos, Point dragOffset, int dragMode) {
	int tWidth = Width;
	int tHeight = Height;

	Point rPoint = CWidget::MouseDrag(dragPos, wPos, dragOffset, dragMode);

	if (tWidth != Width || tHeight != Height) CreateButtonImage();

	return rPoint;
}