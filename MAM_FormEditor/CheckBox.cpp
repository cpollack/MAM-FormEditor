#include "CheckBox.h"

using namespace System::Drawing;

CCheckBox::CCheckBox(System::String^ name, int x, int y) {
	widgetType = wtCheckBox;
	MIN_HEIGHT = 13;
	MIN_WIDTH = 20;

	Name = name;
	X = x;
	Y = y;
	Width = DEFAULT_WIDTH;
	Height = DEFAULT_HEIGHT;

	cb = Image::FromFile("ico\\cb.bmp");

	textFont = gcnew Font("Verdana", 8);
	textFormat = gcnew StringFormat;
	textFormat->Alignment = StringAlignment::Near;
	textFormat->LineAlignment = StringAlignment::Center;
	textBrush = gcnew  SolidBrush(Color::FromArgb(0, 0, 0));
	
}

void CCheckBox::Draw(Graphics^ gr, Point pos) {
	Point widgetPos(pos.X + X, pos.Y + Y);

	gr->DrawImage(cb, widgetPos);
	gr->DrawString(Text, textFont, textBrush, Point(widgetPos.X + 15, widgetPos.Y + (cb->Height / 2)), textFormat);
}