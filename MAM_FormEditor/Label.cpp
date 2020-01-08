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
	loaded = true;
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

	if (vWidget->HasMember("Alignment")) Alignment = (LabelAlignment)((*vWidget)["Alignment"].GetInt());
	else Alignment = LabelAlignment::laLeft;
	if (vWidget->HasMember("VAlignment")) VAlignment = (LabelVAlignment)((*vWidget)["VAlignment"].GetInt());
	else VAlignment = LabelVAlignment::lvaTop;

	if (vWidget->HasMember("Underlined")) Underlined = (*vWidget)["Underlined"].GetBool();
	if (vWidget->HasMember("Multiline")) Multiline = (*vWidget)["Multiline"].GetBool();
	if (vWidget->HasMember("Text")) Text = gcnew System::String((*vWidget)["Text"].GetString());
	else Text = Name;
	CreateLabelTexture();
	loaded = true;
}

void CLabel::Save(rapidjson::Document* document, rapidjson::Value* vWidget) {
	CWidget::Save(document, vWidget);
	Document::AllocatorType& allocator = document->GetAllocator();

	Value vtext(kStringType);
	vtext.SetString(textToString(Text).c_str(), Text->Length, allocator);
	vWidget->AddMember("Text", vtext, allocator);

	Value vAlign(kNumberType);
	vAlign.SetInt((int)Alignment);
	vWidget->AddMember("Alignment", vAlign, allocator);
	Value vVAlign(kNumberType);
	vVAlign.SetInt((int)VAlignment);
	vWidget->AddMember("VAlignment", vVAlign, allocator);

	rapidjson::Value vUnderlined(Underlined);
	vWidget->AddMember("Underlined", vUnderlined, allocator);

	rapidjson::Value vMultiline(Multiline);
	vWidget->AddMember("Multiline", vMultiline, allocator);
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

	bool drawUnderline = false, drawUnderlineChar = false;
	System::String ^drawText = Text;

	//check text for ampersand and get position and size of character to underscore
	RectangleF underline, underlineChar;
	if (Text->Contains("&")) {
		int pos = Text->IndexOf("&");
		System::String^ prefix = Text->Substring(0, pos);
		System::String^ nextChar = Text->Substring(pos + 1, 1);
		SizeF prefixSize = gr->MeasureString(prefix, font, Point(0,0), textFormat);
		SizeF charSize = gr->MeasureString(nextChar, font, Point(0, 0), textFormat);
		underlineChar = RectangleF(prefixSize.Width, prefixSize.Height, charSize.Width, 1);
		drawUnderlineChar = true;

		drawText = drawText->Replace("&", "");
	}

	//Trim the end of the string and show ... if the whole string does not fit?
	//SizeF sizeF = gr->MeasureString(Text, font, Point(0, 0), textFormat);

	int hOffset, vOffset;
	SizeF txtSize = gr->MeasureString(drawText, font, Point(0, 0), textFormat);

	if (Underlined) {
		underline = RectangleF(0, txtSize.Height, txtSize.Width, 1);
		drawUnderline = true;
	}

	switch (alignment) {
	case LabelAlignment::laLeft:
		hOffset = 0;
		break;
	case LabelAlignment::laRight:
		hOffset = Width - txtSize.Width;
		break;
	case LabelAlignment::laCenter:
		hOffset = (Width / 2) - (txtSize.Width / 2);
		break;
	}

	vOffset = txtSize.Height / 2;
	switch (valignment) {
	case LabelVAlignment::lvaTop:
		vOffset += 0;
		break;
	case LabelVAlignment::lvaBottom:
		vOffset += Height - txtSize.Height;
		break;
	case LabelVAlignment::lvaCenter:
		vOffset += (Height / 2) - (txtSize.Height / 2);
		break;
	}

	gr->DrawString(drawText, font, fontBrush, Point(hOffset, vOffset), textFormat);
	if (drawUnderline) gr->DrawLine(underlinePen, underline.X, 13.0, underline.X + underline.Width, 13.0);
	if (drawUnderlineChar) gr->DrawLine(underlinePen, underlineChar.X, 13.0, underlineChar.X + underlineChar.Width, 13.0);
}