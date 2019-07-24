#include "Window.h"
#include "MainForm.h"

#include "CheckBox.h"
#include "Button.h"

using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace MAM_FormEditor;

CWindow::CWindow() {
	Width = 400;
	Height = 200;
	position = Point(10, 10);

	widgets = gcnew ArrayList();
	
	top = Image::FromFile("res\\TopCenter_s.bmp");
	bottom = Image::FromFile("res\\BottomCenter.bmp");
	left = Image::FromFile("res\\Left.bmp");
	right = Image::FromFile("res\\Right.bmp");
	topLeft = Image::FromFile("res\\TopLeft_s.bmp");
	topRight = Image::FromFile("res\\TopRight_s.bmp");
	bottomLeft = Image::FromFile("res\\BottomLeft.bmp");
	bottomRight = Image::FromFile("res\\BottomRight.bmp");
	close = Image::FromFile("res\\Close.bmp");
}

void CWindow::Draw(PictureBox ^drawable) {
	Rectangle drawRect;

	//image should be min size of panel, but expand to max size of form plus buffer

	if (drawable->Image) delete drawable->Image;
	drawable->Image = gcnew Bitmap(drawable->Width, drawable->Height);

	Graphics^ gr = Graphics::FromImage(drawable->Image);

	unsigned int uiColor = 0x3A5121;
	SolidBrush ^bgColor = gcnew SolidBrush(Color::FromArgb(uiColor & 0xFF, (uiColor & 0xFF00) >> 8, (uiColor & 0xFF0000) >> 16));
	gr->FillRectangle(bgColor, Rectangle(position.X, position.Y, Width, Height));

	RectangleF topRect = RectangleF(position.X, position.Y, Width < top->Width ? Width : top->Width, top->Height);
	gr->DrawImage(top, topRect);
	MIN_TOP = top->Height + 2;

	RectangleF bottomRect = RectangleF( position.X, position.Y + (Height - bottom->Height), Width < bottom->Width ? Width : bottom->Width, bottom->Height);
	gr->DrawImage(bottom, bottomRect);
	MAX_BOTTOM = Height - (bottom->Height + 2);

	RectangleF leftRect = RectangleF(position.X, position.Y, left->Width, Height < left->Height ? Height : left->Height);
	gr->DrawImage(left, leftRect);
	MIN_LEFT = left->Width + 2;

	RectangleF rightRect = RectangleF(position.X + (Width - right->Width), position.Y, right->Width, Height < right->Height ? Height : right->Height);
	gr->DrawImage(right, rightRect);
	MAX_RIGHT = Width - (right->Width + 2);

	RectangleF topLeftRect = RectangleF(position.X, position.Y, topLeft->Width, topLeft->Height);
	gr->DrawImage(topLeft, topLeftRect);

	RectangleF topRightRect = RectangleF(position.X + (Width - topRight->Width), position.Y, topRight->Width, topRight->Height);
	gr->DrawImage(topRight, topRightRect);

	RectangleF bottomLeftRect = RectangleF(position.X, position.Y + (Height - bottomLeft->Height), bottomLeft->Width, bottomLeft->Height);
	gr->DrawImage(bottomLeft, bottomLeftRect);

	RectangleF bottomRightRect = RectangleF(position.X + (Width - bottomRight->Width), position.Y + (Height - bottomRight->Height), bottomRight->Width, bottomRight->Height);
	gr->DrawImage(bottomRight, bottomRightRect);

	StringFormat^ format = gcnew StringFormat;
	format->Alignment = StringAlignment::Center;
	format->LineAlignment = StringAlignment::Center;
	gr->DrawString(Title, gcnew Font("Verdana", 8), gcnew SolidBrush(Color::FromArgb(0xAD, 0xE9, 0xCD)), Point(position.X + (Width / 2), position.Y + 16), format);

	if (CloseButton) {
		RectangleF closeRect = RectangleF(position.X + (Width - close->Width - 9), position.Y + 9, close->Width, close->Height);
		gr->DrawImage(close, closeRect);
	}

	//draw widgets
	for each(CWidget^ w in widgets) {
		w->Draw(gr, position);
	}

	if (focus) {
		SolidBrush ^bgColor = gcnew SolidBrush(Color::FromArgb(50, 255, 255, 153));
		gr->FillRectangle(bgColor, Rectangle(position.X + focus->X, position.Y + focus->Y, focus->Width, focus->Height));
	}
}

Cursor^ CWindow::MouseMove(System::Windows::Forms::MouseEventArgs^ e) {
	Cursor^ cursor = Cursors::Default;

	if (focus) {
		cursor = focus->MouseMove(e, position);
	}

	if (cursor == Cursors::Default) {
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
	}

	if (dragging) {
		int adjustWidth, adjustHeight;
		if (draggingWidget) {
			Point mousePos(e->X, e->Y);
			if (e->X - dragOffset.X < MIN_LEFT + position.X) mousePos.X = MIN_LEFT + position.X + dragOffset.X;
			if (e->X - dragOffset.X + focus->Width > MAX_RIGHT + position.X) mousePos.X = MAX_RIGHT + position.X + dragOffset.X - focus->Width;
			if (e->Y - dragOffset.Y < MIN_TOP + position.Y) mousePos.Y = MIN_TOP + position.Y + dragOffset.Y;
			if (e->Y - dragOffset.Y + focus->Height > MAX_BOTTOM + position.Y) mousePos.Y = MAX_BOTTOM + position.Y + dragOffset.Y - focus->Height;

			dragOffset = focus->MouseDrag(mousePos, position, dragOffset, dragMode);
		}
		else {
			switch (dragMode) {
			case dmDrag:
				position = Point(e->X - dragOffset.X, e->Y - dragOffset.Y);
				break;
			case dmN:
				adjustHeight = e->Y - position.Y - dragOffset.Y;
				position = Point(position.X, position.Y + adjustHeight);
				Height -= adjustHeight;
				dragOffset.Y = e->Y - position.Y;
				break;
			case dmS:
				adjustHeight = e->Y - position.Y - dragOffset.Y;
				Height += adjustHeight;
				dragOffset.Y += adjustHeight;
				break;
			case dmW:
				adjustWidth = e->X - position.X - dragOffset.X;
				position = Point(position.X + adjustWidth, position.Y);
				Width -= adjustWidth;
				dragOffset.X = e->X - position.X;
				break;
			case dmE:
				adjustWidth = e->X - position.X - dragOffset.X;
				Width += adjustWidth;
				dragOffset.X += adjustWidth;
				break;
			}
		}
	}

	return cursor;
}

void CWindow::MouseDown(System::Windows::Forms::MouseEventArgs^ e) {
	//Verify if mouse down happened within a focused widget
	if (focus) {
		Point click(e->X - position.X, e->Y - position.Y);
		if (!focus->DoesPointIntersect(click)) {
			focus = nullptr;
		}
	}

	//Check for window drag conditions
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
	else if (e->Y > position.Y + 2 && e->Y <= position.Y + top->Height) {
		dragMode = dmDrag;
	}

	//Window is not being dragged, check if the focused widget is
	if (dragMode == dmNone && focus) {
		dragMode = focus->MouseDown(e, position);
		if (dragMode != dmNone) draggingWidget = true;
	}

	//Drag is occuring, record offset point
	if (dragMode != dmNone) {
		dragOffset = Point(e->X - position.X, e->Y - position.Y);
		if (draggingWidget) {
			dragOffset.X -= focus->X;
			dragOffset.Y -= focus->Y;
		}
		dragging = true;
	}
}

void CWindow::MouseUp(System::Windows::Forms::MouseEventArgs^ e) {
	//Cancel all dragging rules on mouseup
	dragging = false;
	draggingWidget = false;
	dragMode = dmNone;
}

Object^ CWindow::Click(System::Windows::Forms::MouseEventArgs^ e, int addMode) {
	if (dragging) return nullptr;
	if (e->X < position.X || e->X > position.X + Width || e->Y < position.Y || e->Y > position.Y + Height) return nullptr;

	Point click(e->X - position.X, e->Y - position.Y);
	focus = nullptr;

	//Iterate widgets and see if one was clicked.
	for each (CWidget^ w in widgets) {
		if (w->DoesPointIntersect(click)) {
			focus = w;
			return w;
		}
	}

	//If no widget was clicked, check if in add mode
	if (addMode != amNone) {
		CWidget^ addWidget = nullptr;
		switch (addMode) {
		case amCheckbox:
			addWidget = gcnew CCheckBox("cb1", click.X, click.Y);
			break;

		case amButton:
			addWidget = gcnew CButton("btn1", click.X, click.Y);
			break;
		}
		
		if (addWidget) {
			widgets->Add(addWidget);
			focus = addWidget;
			return addWidget;
		}
	}

	return this;
}