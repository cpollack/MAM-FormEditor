#include "Field.h"
#include "GlobalLib.h"

using namespace System::Drawing;
using namespace rapidjson;

CField::CField(System::String^ name, int x, int y) {
	widgetType = wtField;
	MIN_HEIGHT = 13;
	MIN_WIDTH = 20;

	Name = name;
	X = x;
	Y = y;
	Width = DEFAULT_WIDTH;
	Height = DEFAULT_HEIGHT;
	MaxLength = 0;
	ThickBorder = false;

	init();

	CreateFieldTexture();
	loaded = true;
}

CField::CField(rapidjson::Value* vWidget) : CWidget(vWidget) {
	if (!vWidget->IsObject()) return;

	widgetType = wtField;
	MIN_HEIGHT = 13;
	MIN_WIDTH = 20;

	init();

	if (vWidget->HasMember("Value")) Value = gcnew System::String((*vWidget)["Value"].GetString());
	if (vWidget->HasMember("IsPassword")) IsPassword = (*vWidget)["IsPassword"].GetBool();
	if (vWidget->HasMember("MaxLength")) MaxLength = (*vWidget)["MaxLength"].GetInt();
	if (vWidget->HasMember("ThickBorder")) ThickBorder = (*vWidget)["ThickBorder"].GetBool();
	CreateFieldTexture();
	loaded = true;
}

void CField::init() {
	textFormat = gcnew StringFormat(StringFormat::GenericTypographic);
	textFormat->Alignment = StringAlignment::Near;
	textFormat->LineAlignment = StringAlignment::Center;

	unsigned int uiColor = 0x3A5121;
	bgColor = gcnew SolidBrush(Color::FromArgb(uiColor & 0xFF, (uiColor & 0xFF00) >> 8, (uiColor & 0xFF0000) >> 16));
	whitePen = gcnew Pen(Color::FromArgb(0xFF, 0xFF, 0xFF, 0xFF));
	darkPen = gcnew Pen(Color::FromArgb(0xFF, 0xA0, 0xA0, 0xA0));

	IsPassword = false;
	Value = "";
}

void CField::Save(rapidjson::Document* document, rapidjson::Value* vWidget) {
	CWidget::Save(document, vWidget);
	Document::AllocatorType& allocator = document->GetAllocator();

	rapidjson::Value vValue(kStringType);
	vValue.SetString(textToString(Value).c_str(), Value->Length, allocator);
	vWidget->AddMember("Value", vValue, allocator);

	rapidjson::Value vIsPass(IsPassword);
	vWidget->AddMember("IsPassword", vIsPass, allocator);

	rapidjson::Value vMaxLength(kNumberType);
	vMaxLength.SetInt(MaxLength);
	vWidget->AddMember("MaxLength", vMaxLength, allocator);

	rapidjson::Value vBorder(ThickBorder);
	vWidget->AddMember("ThickBorder", vBorder, allocator);
}

void CField::Draw(Graphics^ gr, Point pos) {
	Point widgetPos(pos.X + X, pos.Y + Y);

	gr->DrawImage(fld, widgetPos);
	if (Value->Length > 0) gr->DrawString(Value, font, fontBrush, System::Drawing::Rectangle(widgetPos.X + 2, widgetPos.Y + 2, Width - 4, Height - 4), textFormat);
	//if (Value->Length > 0) gr->DrawString(Value, font, fontBrush, Point(0 + 2, Height / 2), textFormat);
}

void CField::CreateFieldTexture() {
	if (fld) delete fld;

	fld = gcnew Bitmap(Width, Height);
	Graphics ^gr = Graphics::FromImage(fld);
	gr->FillRectangle(bgColor, System::Drawing::Rectangle(0, 0, Width, Height));
	
	gr->DrawLine(darkPen, Point(0, 0), Point(width - 1, 0));
	gr->DrawLine(darkPen, Point(0, 0), Point(0, height - 1));

	gr->DrawLine(whitePen, Point(0, height - 1), Point(width - 1, height - 1));
	gr->DrawLine(whitePen, Point(width - 1, 0), Point(width - 1, height - 1));
}
