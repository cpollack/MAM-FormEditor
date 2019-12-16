#include "DropDown.h"
#include "GlobalLib.h"

using namespace System::Drawing;
using namespace rapidjson;

CDropDown::CDropDown(System::String^ name, int x, int y) {
	Name = name;
	X = x;
	Y = y;
	Width = DEFAULT_WIDTH;
	Height = DEFAULT_HEIGHT;

	init();
	CreateButtonImage();
	loaded = true;
}

CDropDown::CDropDown(rapidjson::Value* vWidget) : CWidget(vWidget) {
	if (!vWidget->IsObject()) return;

	if (vWidget->HasMember("Value")) Value = gcnew System::String((*vWidget)["Value"].GetString());
	if (vWidget->HasMember("Detailed")) Detailed = (*vWidget)["Detailed"].GetBool();

	init();
	CreateButtonImage();
	loaded = true;
}

void CDropDown::init() {
	widgetType = wtDropDown;
	MIN_HEIGHT = 20;
	MIN_WIDTH = 40;

	borderColor = gcnew Pen(Color::FromArgb(0, 0, 0));
	buttonColor = gcnew Pen(Color::FromArgb(00, 56, 55));
	fontBrush = gcnew SolidBrush(Color::FromArgb(0xAA, 0xD5, 0xFF));

	whitePen = gcnew Pen(Color::FromArgb(0xFF, 0xFF, 0xFF, 0xFF));
	light2Pen = gcnew Pen(Color::FromArgb(0xFF, 0xF0, 0xF0, 0xF0));
	light1Brush = gcnew SolidBrush(Color::FromArgb(0xFF, 0xE3, 0xE3, 0xE3));
	dark1Pen = gcnew Pen(Color::FromArgb(0xFF, 0xA0, 0xA0, 0xA0));
	dark2Pen = gcnew Pen(Color::FromArgb(0xFF, 0x69, 0x69, 0x69));
	blackPen = gcnew Pen(Color::FromArgb(0xFF, 0x00, 0x00, 0x00));

	textFormat = gcnew StringFormat(StringFormat::GenericTypographic);
	textFormat->Alignment = StringAlignment::Center;
	textFormat->LineAlignment = StringAlignment::Center;

	if (!Value) Value = "";
}

void CDropDown::Save(rapidjson::Document* document, rapidjson::Value* vWidget) {
	CWidget::Save(document, vWidget);
	Document::AllocatorType& allocator = document->GetAllocator();

	rapidjson::Value vDetailed(Detailed);
	vWidget->AddMember("Detailed", vDetailed, allocator);
}

void CDropDown::CreateButtonImage() {
	/*if (btn) delete btn;
	btn = gcnew Bitmap(Width, Height);
	Graphics^ gr = Graphics::FromImage(btn);
	gr->FillRectangle(buttonColor, System::Drawing::Rectangle(0, 0, Width, Height));
	gr->DrawRectangle(borderColor, System::Drawing::Rectangle(0, 0, Width - 1, Height - 1));*/
}

void CDropDown::Draw(Graphics^ gr, Point pos) {
	Point widgetPos(pos.X + X, pos.Y + Y);

	if (!Detailed) {
		gr->DrawRectangle(borderColor, System::Drawing::Rectangle(widgetPos.X, widgetPos.Y, width, height));
		gr->DrawRectangle(borderColor, System::Drawing::Rectangle(widgetPos.X + width - 13, widgetPos.Y, 13, height));

		Point buttonCenter(widgetPos.X + width - 7, widgetPos.Y + (height / 2));
		gr->DrawLine(buttonColor, buttonCenter.X - 2, buttonCenter.Y - 1, buttonCenter.X + 2, buttonCenter.Y - 1);
		gr->DrawLine(buttonColor, buttonCenter.X - 1, buttonCenter.Y, buttonCenter.X + 1, buttonCenter.Y);
		gr->DrawLine(buttonColor, buttonCenter.X, buttonCenter.Y - 1, buttonCenter.X, buttonCenter.Y + 1);
	}
	else {
		gr->DrawLine(dark1Pen, widgetPos, Point(widgetPos.X + width, widgetPos.Y));
		gr->DrawLine(dark1Pen, widgetPos, Point(widgetPos.X, widgetPos.Y + height));
		gr->DrawLine(dark2Pen, Point(widgetPos.X + 1, widgetPos.Y + 1), Point(widgetPos.X + 1 + width - 2, widgetPos.Y + 1));
		gr->DrawLine(dark2Pen, Point(widgetPos.X + 1, widgetPos.Y + 1), Point(widgetPos.X + 1, widgetPos.Y + 1 + height - 2));
		gr->DrawLine(whitePen, Point(widgetPos.X, widgetPos.Y + height), Point(widgetPos.X + width, widgetPos.Y + height));
		gr->DrawLine(whitePen, Point(widgetPos.X + width, widgetPos.Y), Point(widgetPos.X + width, widgetPos.Y + height));
		gr->DrawLine(light2Pen, Point(widgetPos.X + 1, widgetPos.Y + height - 1), Point(widgetPos.X + 1 + width - 2, widgetPos.Y + height - 1));
		gr->DrawLine(light2Pen, Point(widgetPos.X + width - 1, widgetPos.Y + 1), Point(widgetPos.X + width - 1, widgetPos.Y + 1 + height - 2));

		int rectHeight = height - 4;
		Point rectPos = Point(widgetPos.X + width - 2 - rectHeight, widgetPos.Y + 2);
		gr->DrawLine(light2Pen, rectPos, Point(rectPos.X + rectHeight, rectPos.Y));
		gr->DrawLine(light2Pen, rectPos, Point(rectPos.X, rectPos.Y + rectHeight));
		gr->DrawLine(whitePen, Point(rectPos.X + 1, rectPos.Y + 1), Point(rectPos.X + 1 + rectHeight - 2, rectPos.Y + 1));
		gr->DrawLine(whitePen, Point(rectPos.X + 1, rectPos.Y + 1), Point(rectPos.X + 1, rectPos.Y + 1 + rectHeight - 2));
		gr->DrawLine(dark2Pen, Point(rectPos.X + rectHeight, rectPos.Y), Point(rectPos.X + rectHeight, rectPos.Y + rectHeight));
		gr->DrawLine(dark2Pen, Point(rectPos.X, rectPos.Y + rectHeight), Point(rectPos.X + rectHeight, rectPos.Y + rectHeight));
		gr->DrawLine(dark1Pen, Point(rectPos.X + rectHeight - 1, rectPos.Y + 1), Point(rectPos.X + rectHeight - 1, rectPos.Y + 1 + rectHeight - 2));
		gr->DrawLine(dark1Pen, Point(rectPos.X + 1, rectPos.Y + rectHeight - 1), Point(rectPos.X + 1 + rectHeight - 2, rectPos.Y + rectHeight - 1));
		gr->FillRectangle(light1Brush, rectPos.X + 2, rectPos.Y + 2, rectHeight - 3, rectHeight - 3);

		Point center = Point(rectPos.X + (rectHeight / 2), rectPos.Y + (rectHeight / 2));
		gr->DrawLine(blackPen, Point(center.X - 3, center.Y - 1), Point(center.X + 3, center.Y - 1));
		gr->DrawLine(blackPen, Point(center.X - 2, center.Y), Point(center.X + 2, center.Y));
		gr->DrawLine(blackPen, Point(center.X - 1, center.Y + 1), Point(center.X + 1, center.Y + 1));
		gr->DrawLine(blackPen, Point(center.X, center.Y + 1), Point(center.X, center.Y + 2));
	}

	
	//gr->DrawImage(btn, widgetPos);
	//gr->DrawImage(lbl, widgetPos);
}
