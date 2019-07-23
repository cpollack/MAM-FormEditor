#include "Window.h"
#include "MainForm.h"

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

	RectangleF bottomRect = RectangleF( position.X, position.Y + (Height - bottom->Height), Width < bottom->Width ? Width : bottom->Width, bottom->Height);
	gr->DrawImage(bottom, bottomRect);

	RectangleF leftRect = RectangleF(position.X, position.Y, left->Width, Height < left->Height ? Height : left->Height);
	gr->DrawImage(left, leftRect);

	RectangleF rightRect = RectangleF(position.X + (Width - right->Width), position.Y, right->Width, Height < right->Height ? Height : right->Height);
	gr->DrawImage(right, rightRect);

	RectangleF topLeftRect = RectangleF(position.X, position.Y, topLeft->Width, topLeft->Height);
	gr->DrawImage(topLeft, topLeftRect);

	RectangleF topRightRect = RectangleF(position.X + (Width - topRight->Width), position.Y, topRight->Width, topRight->Height);
	gr->DrawImage(topRight, topRightRect);

	RectangleF bottomLeftRect = RectangleF(position.X, position.Y + (Height - bottomLeft->Height), bottomLeft->Width, bottomLeft->Height);
	gr->DrawImage(bottomLeft, bottomLeftRect);

	RectangleF bottomRightRect = RectangleF(position.X + (Width - bottomRight->Width), position.Y + (Height - bottomRight->Height), bottomRight->Width, bottomRight->Height);
	gr->DrawImage(bottomRight, bottomRightRect);
}

Cursor^ CWindow::MouseMove(System::Windows::Forms::MouseEventArgs^ e) {
	Cursor^ cursor = Cursors::Default;

	if (e->X >= position.X && e->X <= position.X + Width 
		&& e->Y >= position.Y && e->Y <= position.Y + Height) {

		if (e->X >= position.X && e->X <= position.X + 2
			|| e->X >= position.X + Width - 2 && e->X <= position.X + Width) {
			cursor = Cursors::SizeWE;
		} else if (e->Y >= position.Y && e->Y <= position.Y + 2
			|| e->Y >= position.Y + Height - 2 && e->Y <= position.Y + Height) {
			cursor = Cursors::SizeNS;
		}
	}

	if (dragging) {
		int adjustWidth, adjustHeight;
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

	return cursor;
}

void CWindow::MouseDown(System::Windows::Forms::MouseEventArgs^ e) {
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

	if (dragMode != dmNone) {
		dragOffset = Point(e->X - position.X, e->Y - position.Y);
		dragging = true;
	}
}

void CWindow::MouseUp(System::Windows::Forms::MouseEventArgs^ e) {
	dragging = false;
	dragMode = dmNone;
}

Object^ CWindow::Click(System::Windows::Forms::MouseEventArgs^ e, int addMode) {
	if (dragging) return nullptr;
	if (e->X < position.X || e->X > position.X + Width || e->Y < position.Y || e->Y > position.Y + Height) return nullptr;

	//Iterate widgets and see if one was clicked.
	/*for each (Widget^ w in widgets) {
		//return w;
	}*/

	//If no widget was clicked, check if in add mode
	if (addMode != amNone) {
		//add the new widget at pos;
		//return newWidget;
	}

	return this;
}