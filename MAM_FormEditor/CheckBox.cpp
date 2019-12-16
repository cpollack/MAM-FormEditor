#include "CheckBox.h"
#include "GlobalLib.h"

using namespace System::Drawing;
using namespace rapidjson;

CCheckBox::CCheckBox(System::String^ name, int x, int y) {
	widgetType = wtCheckBox;
	MIN_HEIGHT = 13;
	MIN_WIDTH = 20;

	Name = name;
	Text = name;
	X = x;
	Y = y;
	Width = DEFAULT_WIDTH;
	Height = DEFAULT_HEIGHT;

	cb = Image::FromFile("ico\\cb.bmp");

	textFormat = gcnew StringFormat;
	textFormat->Alignment = StringAlignment::Near;
	textFormat->LineAlignment = StringAlignment::Center;

	dashedPen = gcnew Pen(Color::FromArgb(0, 0, 0));
	dashedPen->DashStyle = Drawing2D::DashStyle::Dash;
	dashedPen->DashPattern = gcnew array<float>(2) {2.0f, 3.0f};
}

CCheckBox::CCheckBox(rapidjson::Value* vWidget) : CWidget(vWidget) {
	widgetType = wtCheckBox;
	MIN_HEIGHT = 13;
	MIN_WIDTH = 20;

	if (Width == 0) Width = DEFAULT_WIDTH;
	if (Height == 0) Height = DEFAULT_HEIGHT;

	cb = Image::FromFile("ico\\cb.bmp");

	textFormat = gcnew StringFormat;
	textFormat->Alignment = StringAlignment::Near;
	textFormat->LineAlignment = StringAlignment::Center;

	dashedPen = gcnew Pen(Color::FromArgb(0, 0, 0));
	dashedPen->DashStyle = Drawing2D::DashStyle::Dash;
	dashedPen->DashPattern = gcnew array<float>(2) { 2.0f, 3.0f };

	if (vWidget->HasMember("Text")) Text = gcnew System::String((*vWidget)["Text"].GetString());
	else Text = Name;
}

void CCheckBox::Save(rapidjson::Document* document, rapidjson::Value* vWidget) {
	CWidget::Save(document, vWidget);
	Document::AllocatorType& allocator = document->GetAllocator();

	Value vtext(kStringType);
	vtext.SetString(textToString(Text).c_str(), Text->Length, allocator);
	vWidget->AddMember("Text", vtext, allocator);
}

void CCheckBox::Draw(Graphics^ gr, Point pos) {
	Point widgetPos(pos.X + X, pos.Y + Y);

	gr->DrawImage(cb, widgetPos);
	gr->DrawString(Text, font, fontBrush, Point(widgetPos.X + 15, widgetPos.Y + (cb->Height / 2)), textFormat);

	if (!previewMode) gr->DrawRectangle(dashedPen, System::Drawing::Rectangle(widgetPos.X, widgetPos.Y, Width, Height));
}