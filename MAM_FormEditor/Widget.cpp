#include "Widget.h"

using namespace System::Drawing;

bool CWidget::DoesPointIntersect(Point point) {
	if (point.X >= X && point.X <= X + Width && point.Y >= Y && point.Y <= Y + Height) return true;
	return false;
}