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

	textFormat = gcnew StringFormat(StringFormat::GenericTypographic);
	textFormat->Alignment = StringAlignment::Center;
	textFormat->LineAlignment = StringAlignment::Center;

	if (!Value) Value = "";
}

void CDropDown::Save(rapidjson::Document* document, rapidjson::Value* vWidget) {
	CWidget::Save(document, vWidget);
	Document::AllocatorType& allocator = document->GetAllocator();

	//Value vtext(kStringType);
	//vtext.SetString(textToString(Text).c_str(), Text->Length, allocator);
	//vWidget->AddMember("Text", vtext, allocator);
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

	gr->DrawRectangle(borderColor, System::Drawing::Rectangle(widgetPos.X, widgetPos.Y, width, height));
	gr->DrawRectangle(borderColor, System::Drawing::Rectangle(widgetPos.X + width - 13, widgetPos.Y, 13, height));

	Point buttonCenter(widgetPos.X + width - 7, widgetPos.Y + (height / 2));
	gr->DrawLine(buttonColor, buttonCenter.X - 2, buttonCenter.Y - 1, buttonCenter.X + 2, buttonCenter.Y - 1);
	gr->DrawLine(buttonColor, buttonCenter.X - 1, buttonCenter.Y, buttonCenter.X + 1, buttonCenter.Y);
	gr->DrawLine(buttonColor, buttonCenter.X, buttonCenter.Y - 1, buttonCenter.X, buttonCenter.Y + 1);

	
	//gr->DrawImage(btn, widgetPos);
	//gr->DrawImage(lbl, widgetPos);
}
