#include "Widget.h"
#include "Window.h"

using namespace System::Drawing;
using namespace System::Windows::Forms;

bool CWidget::DoesPointIntersect(Point point) {
	if (point.X >= X && point.X <= X + Width && point.Y >= Y && point.Y <= Y + Height) return true;
	return false;
}

int CWidget::MouseDown(System::Windows::Forms::MouseEventArgs^ e, System::Drawing::Point wPos) {
	int dragMode = dmNone;
	Point position(wPos.X + X, wPos.Y + Y);

	if (e->X >= position.X && e->X <= position.X + 2) {
		dragMode = dmW;
	}
	else if (e->X >= position.X + Width - 2 && e->X <= position.X + Width) {
		dragMode = dmE;
	}
	else if (e->Y >= position.Y && e->Y <= position.Y + 2) {
		dragMode = dmN;
	}
	else if (e->Y >= position.Y + Height - 2 && e->Y <= position.Y + Height) {
		dragMode = dmS;
	}
	else {
		dragMode = dmDrag;
	}

	return dragMode;
}


Cursor^ CWidget::MouseMove(MouseEventArgs^ e, Point wPos) {
	Cursor^ cursor = Cursors::Default;
	Point position(wPos.X + X, wPos.Y + Y);

	if (e->X >= position.X && e->X <= position.X + Width
		&& e->Y >= position.Y && e->Y <= position.Y + Height) {

		if (e->X >= position.X && e->X <= position.X + 2
			|| e->X >= position.X + Width - 2 && e->X <= position.X + Width) {
			cursor = Cursors::SizeWE;
		}
		else if (e->Y >= position.Y && e->Y <= position.Y + 2
			|| e->Y >= position.Y + Height - 2 && e->Y <= position.Y + Height) {
			cursor = Cursors::SizeNS;
		}
	}

	return cursor;
}

Point CWidget::MouseDrag(MouseEventArgs^ e, Point wPos, Point dragOffset, int dragMode) {
	Point position(wPos.X + X, wPos.Y + Y);
	Point offset(e->X - dragOffset.X, e->Y - dragOffset.Y);

	int adjustHeight, adjustWidth;

	switch (dragMode) {
	case dmDrag:
		X = e->X - dragOffset.X - wPos.X;
		Y = e->Y - dragOffset.Y - wPos.Y;
		break;
	case dmN:
		adjustHeight = e->Y - dragOffset.Y - position.Y;
		if (Height - adjustHeight < MIN_HEIGHT) adjustHeight = Height - MIN_HEIGHT;
		Y = Y + adjustHeight;
		Height -= adjustHeight;
		break;
	case dmS:
		adjustHeight = e->Y - dragOffset.Y - position.Y;
		if (Height + adjustHeight < MIN_HEIGHT) adjustHeight = MIN_HEIGHT - Height;
		Height += adjustHeight;
		dragOffset.Y += adjustHeight;
		break;
	case dmW:
		adjustWidth = e->X - dragOffset.X - position.X;
		if (Width - adjustWidth < MIN_WIDTH) adjustWidth = Width - MIN_WIDTH;
		X = X + adjustWidth;
		Width -= adjustWidth;
		break;
	case dmE:
		adjustWidth = e->X - dragOffset.X - position.X;
		if (Width + adjustWidth < MIN_WIDTH) adjustWidth = MIN_WIDTH - Width;
		Width += adjustWidth;
		dragOffset.X += adjustWidth;
		break;
	}
	return dragOffset;
}