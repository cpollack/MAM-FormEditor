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
}

void CCheckBox::Draw(Graphics^ gr, Point pos) {
	Point widgetPos(pos.X + X, pos.Y + Y);
	gr->DrawImage(Image::FromFile("ico\\cb.bmp"), widgetPos);
	StringFormat^ format = gcnew StringFormat;
	gr->DrawString(Text, gcnew Font("Verdana", 8), gcnew SolidBrush(Color::FromArgb(0, 0, 0)), Point(widgetPos.X + 15, widgetPos.Y), format);
}