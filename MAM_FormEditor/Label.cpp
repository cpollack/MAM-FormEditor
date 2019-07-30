#include "Label.h"
#include "GlobalLib.h"

using namespace System::Drawing;
using namespace rapidjson;

CLabel::CLabel(System::String^ name, int x, int y) {
	widgetType = wtLabel;
	MIN_HEIGHT = 13;
	MIN_WIDTH = 20;

	Name = name;
	X = x;
	Y = y;
	Width = DEFAULT_WIDTH;
	Height = DEFAULT_HEIGHT;

	//textFormat = gcnew StringFormat();
	textFormat = gcnew StringFormat(StringFormat::GenericTypographic);
	textFormat->Alignment = StringAlignment::Near;
	textFormat->LineAlignment = StringAlignment::Center;

	dashedPen = gcnew Pen(Color::FromArgb(0, 0, 0));
	dashedPen->DashStyle = Drawing2D::DashStyle::Dash;
	dashedPen->DashPattern = gcnew array<float>(2) { 2.0f, 3.0f };

	underlinePen = gcnew Pen(fontBrush->Color);

	Text = name;
	CreateLabelTexture();
}

CLabel::CLabel(rapidjson::Value* vWidget) : CWidget(vWidget) {
	if (!vWidget->IsObject()) return;

	widgetType = wtLabel;
	MIN_HEIGHT = 13;
	MIN_WIDTH = 20;

	textFormat = gcnew StringFormat(StringFormat::GenericTypographic);
	textFormat->Alignment = StringAlignment::Near;
	textFormat->LineAlignment = StringAlignment::Center;

	dashedPen = gcnew Pen(Color::FromArgb(0, 0, 0));
	dashedPen->DashStyle = Drawing2D::DashStyle::Dash;
	dashedPen->DashPattern = gcnew array<float>(2) { 2.0f, 3.0f };

	underlinePen = gcnew Pen(fontBrush->Color);

	if (vWidget->HasMember("Text")) Text = gcnew System::String((*vWidget)["Text"].GetString());
	else Text = Name;
	CreateLabelTexture();
}

void CLabel::Save(rapidjson::Document* document, rapidjson::Value* vWidget) {
	CWidget::Save(document, vWidget);
	Document::AllocatorType& allocator = document->GetAllocator();

	Value vtext(kStringType);
	vtext.SetString(textToString(Text).c_str(), Text->Length, allocator);
	vWidget->AddMember("Text", vtext, allocator);
}

void CLabel::Draw(Graphics^ gr, Point pos) {
	Point widgetPos(pos.X + X, pos.Y + Y);

	gr->DrawImage(lbl, widgetPos);

	if (!previewMode) gr->DrawRectangle(dashedPen, System::Drawing::Rectangle(widgetPos.X, widgetPos.Y, Width, Height));
}

void CLabel::CreateLabelTexture() {
	if (lbl) delete lbl;

	lbl = gcnew Bitmap(Width, Height);
	Graphics ^gr = Graphics::FromImage(lbl);
	//gr->PageUnit = GraphicsUnit::Pixel;
	gr->TextRenderingHint = System::Drawing::Text::TextRenderingHint::AntiAlias;

	bool drawUnderline = false;
	System::String ^drawText = Text;

	//check text for ampersand and get position and size of character to underscore
	RectangleF underline;
	if (Text->Contains("&")) {
		int pos = Text->IndexOf("&");
		System::String^ prefix = Text->Substring(0, pos);
		System::String^ nextChar = Text->Substring(pos + 1, 1);
		SizeF prefixSize = gr->MeasureString(prefix, font, Point(0,0), textFormat);
		SizeF charSize = gr->MeasureString(nextChar, font, Point(0, 0), textFormat);
		underline = RectangleF(prefixSize.Width, prefixSize.Height, charSize.Width, 1);
		drawUnderline = true;

		/* Experimental WIN32 GDI measuring gave string measures too wide
		//include library: Gdi32.lib
		HDC hdc = (HDC)gr->GetHdc().ToPointer();
		HGDIOBJ hgdiobj = (void*)font->ToHfont().ToPointer();
		System::IntPtr h_OldFont = (System::IntPtr)WIN32::SelectObject(hdc, hgdiobj);

		WIN32::SIZE prefixSize, charSize;		
		char c = Text[pos+1];
		WIN32::GetTextExtentPoint32(hdc, (LPCWSTR)&c, 1, &charSize);
		std::string strPrefix = textToString(prefix);
		WIN32::GetTextExtentPoint32(hdc, (LPCWSTR)strPrefix.c_str(), strPrefix.length(), &prefixSize);
		
		WIN32::SelectObject(hdc, (HGDIOBJ)h_OldFont);
		gr->ReleaseHdc();
		underline = RectangleF(prefixSize.cx + 1, prefixSize.cy, charSize.cx - 1, 1);*/

		drawText = drawText->Replace("&", "");
	}

	//Trim the end of the string and show ... if the whole string does not fit?
	//SizeF sizeF = gr->MeasureString(Text, font, Point(0, 0), textFormat);

	gr->DrawString(drawText, font, fontBrush, Point(0, Height / 2), textFormat);
	if (drawUnderline) gr->DrawLine(underlinePen, underline.X, 13.0, underline.X + underline.Width, 13.0);
}