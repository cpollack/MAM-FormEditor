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

	textFormat = gcnew StringFormat;
	textFormat->Alignment = StringAlignment::Center;
	textFormat->LineAlignment = StringAlignment::Center;

	CreateButtonImage();
}

void CButton::CreateButtonImage() {
	if (btn) delete btn;
	btn = gcnew Bitmap(Width, Height);
	Graphics^ gr = Graphics::FromImage(btn);
	gr->FillRectangle(buttonColor, System::Drawing::Rectangle(0, 0, Width, Height));
	gr->DrawRectangle(borderColor, System::Drawing::Rectangle(0, 0, Width-1, Height-1));
}

void CButton::Save(rapidjson::Document* document, rapidjson::Value* vWidget) {
	CWidget::Save(document, vWidget);
	Document::AllocatorType& allocator = document->GetAllocator();

	Value vtext(kStringType);
	vtext.SetString(textToString(Text).c_str(), Text->Length, allocator);
	vWidget->AddMember("Text", vtext, allocator);
}

void CButton::Draw(Graphics^ gr, Point pos) {
	Point widgetPos(pos.X + X, pos.Y + Y);

	gr->DrawImage(btn, widgetPos);
	gr->DrawString(Text, font, fontBrush, Point(widgetPos.X + (btn->Width / 2), widgetPos.Y + (btn->Height / 2)), textFormat);
}

Point CButton::MouseDrag(Point dragPos, Point wPos, Point dragOffset, int dragMode) {
	int tWidth = Width;
	int tHeight = Height;

	Point rPoint = CWidget::MouseDrag(dragPos, wPos, dragOffset, dragMode);

	if (tWidth != Width || tHeight != Height) CreateButtonImage();

	return rPoint;
}