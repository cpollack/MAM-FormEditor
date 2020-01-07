#include "ImageBox.h"
#include "GlobalLib.h"

using namespace System::Drawing;
using namespace rapidjson;

CImageBox::CImageBox(System::String^ name, int x, int y) {
	Name = name;
	X = x;
	Y = y;
	Width = DEFAULT_WIDTH;
	Height = DEFAULT_HEIGHT;

	init();
	CreateImageTexture();
	loaded = true;
}

CImageBox::CImageBox(rapidjson::Value* vWidget) : CWidget(vWidget) {
	if (!vWidget->IsObject()) return;

	if (vWidget->HasMember("SkinImage")) SkinImage = gcnew System::String((*vWidget)["SkinImage"].GetString());
	else SkinImage = "";

	if (vWidget->HasMember("Bordered")) Bordered = (*vWidget)["Bordered"].GetBool();
	if (vWidget->HasMember("BlackBackground")) BlackBackground = (*vWidget)["BlackBackground"].GetBool();

	if (vWidget->HasMember("Anchor")) Anchor = (ImageAnchor)((*vWidget)["Anchor"].GetInt());
	else Anchor = ImageAnchor::iaTopLeft;

	init();
	CreateImageTexture();
	loaded = true;
}

void CImageBox::init() {
	widgetType = wtImageBox;
	MIN_HEIGHT = 10;
	MIN_WIDTH = 10;
	if (!SkinImage) SkinImage = "";

	blackBrush = gcnew SolidBrush(Color::FromArgb(0xFF, 0x00, 0x00, 0x00));
	whitePen = gcnew Pen(Color::FromArgb(0xFF, 0xFF, 0xFF, 0xFF));
	darkPen = gcnew Pen(Color::FromArgb(0xFF, 0xA0, 0xA0, 0xA0));

	dashedPen = gcnew Pen(Color::FromArgb(0, 0, 0));
	dashedPen->DashStyle = Drawing2D::DashStyle::Dash;
	dashedPen->DashPattern = gcnew array<float>(2) { 2.0f, 3.0f };
}

void CImageBox::Save(rapidjson::Document* document, rapidjson::Value* vWidget) {
	CWidget::Save(document, vWidget);
	Document::AllocatorType& allocator = document->GetAllocator();

	Value vSkinImg(kStringType);
	vSkinImg.SetString(textToString(SkinImage).c_str(), SkinImage->Length, allocator);
	vWidget->AddMember("SkinImage", vSkinImg, allocator);

	Value vBordered(Bordered);
	vWidget->AddMember("Bordered", Bordered, allocator);

	Value vBlackBackground(BlackBackground);
	vWidget->AddMember("BlackBackground", vBlackBackground, allocator);

	Value vAnchor(kNumberType);
	vAnchor.SetInt((int)Anchor);
	vWidget->AddMember("Anchor", vAnchor, allocator);
}

void CImageBox::CreateImageTexture() {
	if (img) {
		delete img;
		img = nullptr;
	}
	if (SkinImage->Length == 0) return;

	System::String^ filePath = "res\\" + SkinImage;

	if (!System::IO::File::Exists(filePath)) return;
	img = Image::FromFile(filePath);
	Width = img->Width;
	Height = img->Height;
}


void CImageBox::Draw(Graphics^ gr, Point pos) {
	Point widgetPos(pos.X + X, pos.Y + Y);

	if (BlackBackground) gr->FillRectangle(blackBrush, System::Drawing::Rectangle(widgetPos.X, widgetPos.Y, Width, Height));

	if (Bordered) {
		gr->DrawLine(darkPen, Point(widgetPos.X, widgetPos.Y), Point(widgetPos.X + width - 1, widgetPos.Y));
		gr->DrawLine(darkPen, Point(widgetPos.X, widgetPos.Y), Point(widgetPos.X, widgetPos.Y + height - 1));

		gr->DrawLine(whitePen, Point(widgetPos.X, widgetPos.Y + height - 1), Point(widgetPos.X + width - 1, widgetPos.Y + height - 1));
		gr->DrawLine(whitePen, Point(widgetPos.X + width - 1, widgetPos.Y), Point(widgetPos.X + width - 1, widgetPos.Y + height - 1));

		if (img) gr->DrawImage(img, System::Drawing::Rectangle(widgetPos.X + 1, widgetPos.Y + 1, Width - 2, Height - 2));
	}
	else {
		if (img) gr->DrawImage(img, System::Drawing::Rectangle(widgetPos.X, widgetPos.Y, img->Width, img->Height));
		if (!previewMode) gr->DrawRectangle(dashedPen, System::Drawing::Rectangle(widgetPos.X, widgetPos.Y, Width, Height));
	}
}
