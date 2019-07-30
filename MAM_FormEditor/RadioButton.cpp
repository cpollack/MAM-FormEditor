#include "RadioButton.h"
#include "GlobalLib.h"

using namespace System::Drawing;
using namespace rapidjson;

CRadioButton::CRadioButton(System::String^ name, int x, int y) {
	widgetType = wtRadioButton;
	MIN_HEIGHT = 13;
	MIN_WIDTH = 20;

	Name = name;
	Text = name;
	X = x;
	Y = y;
	Width = DEFAULT_WIDTH;
	Height = DEFAULT_HEIGHT;

	rb = Image::FromFile("ico\\rb.png");

	textFormat = gcnew StringFormat;
	textFormat->Alignment = StringAlignment::Near;
	textFormat->LineAlignment = StringAlignment::Center;

	dashedPen = gcnew Pen(Color::FromArgb(0, 0, 0));
	dashedPen->DashStyle = Drawing2D::DashStyle::Dash;
	dashedPen->DashPattern = gcnew array<float>(2) { 2.0f, 3.0f };
}

void CRadioButton::Save(rapidjson::Document* document, rapidjson::Value* vWidget) {
	CWidget::Save(document, vWidget);
	Document::AllocatorType& allocator = document->GetAllocator();

	Value vtext(kStringType);
	vtext.SetString(textToString(Text).c_str(), Text->Length, allocator);
	vWidget->AddMember("Text", vtext, allocator);
}

void CRadioButton::Draw(Graphics^ gr, Point pos) {
	Point widgetPos(pos.X + X, pos.Y + Y);

	gr->DrawImage(rb, Point(widgetPos.X, widgetPos.Y+1));
	gr->DrawString(Text, font, fontBrush, Point(widgetPos.X + 15, widgetPos.Y + 1 + (rb->Height / 2)), textFormat);

	if (!previewMode) gr->DrawRectangle(dashedPen, System::Drawing::Rectangle(widgetPos.X, widgetPos.Y, Width, Height));
}