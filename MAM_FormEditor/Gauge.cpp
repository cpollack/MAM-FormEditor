#include "Gauge.h"
#include "GlobalLib.h"

using namespace System::Drawing;
using namespace rapidjson;

CGauge::CGauge(System::String^ name, int x, int y) {
	widgetType = wtGauge;
	MIN_HEIGHT = 13;
	MIN_WIDTH = 20;

	Name = name;
	X = x;
	Y = y;
	Width = DEFAULT_WIDTH;
	Height = DEFAULT_HEIGHT;

	init();

	CreateTexture();
	loaded = true;
}

CGauge::CGauge(rapidjson::Value* vWidget) : CWidget(vWidget) {
	if (!vWidget->IsObject()) return;

	widgetType = wtGauge;
	MIN_HEIGHT = 13;
	MIN_WIDTH = 20;

	init();

	if (vWidget->HasMember("Value")) Value =(*vWidget)["Value"].GetInt();
	CreateTexture();
	loaded = true;
}

void CGauge::init() {
	textFormat = gcnew StringFormat(StringFormat::GenericTypographic);
	textFormat->Alignment = StringAlignment::Center;
	textFormat->LineAlignment = StringAlignment::Center;

	unsigned int uiColor = 0x3A5121;
	bgColor = gcnew SolidBrush(Color::FromArgb(uiColor & 0xFF, (uiColor & 0xFF00) >> 8, (uiColor & 0xFF0000) >> 16));
	fillBrush = gcnew SolidBrush(Color::FromArgb(0xFF, 0x33, 0x66, 0x99));
	borderPen = gcnew Pen(Color::FromArgb(0xFF, 0x00, 0x40, 0x80));

	ShowLabel = true;
	Value = 0;
	Max = 0;
}

void CGauge::Save(rapidjson::Document* document, rapidjson::Value* vWidget) {
	CWidget::Save(document, vWidget);
	Document::AllocatorType& allocator = document->GetAllocator();

	rapidjson::Value vValue(kNumberType);
	vValue.SetInt(Value);
	vWidget->AddMember("Value", vValue, allocator);

	rapidjson::Value vMax(kNumberType);
	vMax.SetInt(Value);
	vWidget->AddMember("Max", vMax, allocator);

	rapidjson::Value vShowLbl(ShowLabel);
	vShowLbl.SetBool(ShowLabel);
	vWidget->AddMember("ShowLabel", vShowLbl, allocator);
}

void CGauge::Draw(Graphics^ gr, Point pos) {
	Point widgetPos(pos.X + X, pos.Y + Y);

	gr->DrawImage(gge, widgetPos);
}

void CGauge::CreateTexture() {
	if (gge) delete gge;

	gge = gcnew Bitmap(Width, Height);
	Graphics ^gr = Graphics::FromImage(gge);
	gr->FillRectangle(bgColor, System::Drawing::Rectangle(0, 0, Width, Height));

	gr->DrawRectangle(borderPen, System::Drawing::Rectangle(0, 0, Width-1, Height-1));
	
	float fillWidth;
	if (Max > 0) fillWidth = (Width - 2) * ((float)Value / (float)Max);
	else fillWidth = 0;
	gr->FillRectangle(fillBrush, System::Drawing::RectangleF(1, 1, fillWidth, Height - 2));

	if (ShowLabel) {
		System::String^ label = Value.ToString() + "/" + Max.ToString();
		gr->DrawString(label, font, fontBrush, RectangleF(1, 1, Width - 2, Height - 2), textFormat);
	}
}
