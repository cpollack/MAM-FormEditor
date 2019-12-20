#include "Window.h"
#include "GlobalLib.h"
#include "MainForm.h"

#include "Label.h"
#include "CheckBox.h"
#include "RadioButton.h"
#include "Button.h"
#include "Panel.h"
#include "Field.h"
#include "ImageBox.h"
#include "DropDown.h"
#include "Gauge.h"
#include "TabControl.h"

using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace MAM_FormEditor;

CWindow::CWindow() {
	Width = 400;
	Height = 200;
	position = Point(10, 10);

	widgets = gcnew ArrayList();
	Title = "New Form";
	Name = "newForm";
	
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

rapidjson::Document* CWindow::Save(rapidjson::Document* document) {
	document->SetObject();
	Document::AllocatorType& allocator = document->GetAllocator();

	Value vWin(kObjectType); {
		Value vWidth(kNumberType);
		vWidth.SetInt(Width);
		vWin.AddMember("Width", vWidth, allocator);

		Value vHeight(kNumberType);
		vHeight.SetInt(Height);
		vWin.AddMember("Height", vHeight, allocator);

		Value vName(kStringType);
		std::string strName = textToString(Name);
		vName.SetString(strName.c_str(), strName.length(), allocator);
		vWin.AddMember("Name", vName, allocator);

		Value vTitle(kStringType);
		std::string strTitle = textToString(Title);
		vTitle.SetString(strTitle.c_str(), strTitle.length(), allocator);
		vWin.AddMember("Title", vTitle, allocator);

		Value vClose(CloseButton);
		vWin.AddMember("CloseButton", vClose, allocator);

		Value vWidgets(kArrayType);
		for each (CWidget^ w in widgets) {
			Value* vWidget = new Value(kObjectType);
			w->Save(document, vWidget);
			vWidgets.PushBack(*vWidget, allocator);
			delete vWidget;
		}
		vWin.AddMember("Widgets", vWidgets, allocator);
	}
	document->AddMember("Window", vWin, allocator);

	return document;
}


void CWindow::Load(rapidjson::Document* document) {
	if (!document->IsObject()) return;

	if (!document->HasMember("Window")) return;
	Value vDocObject = document->GetObject();
	Value vWindow = vDocObject["Window"].GetObject();

	if (vWindow.HasMember("Width")) Width = vWindow["Width"].GetInt();
	if (vWindow.HasMember("Height")) Height = vWindow["Height"].GetInt();
	if (vWindow.HasMember("Name")) Name = gcnew String(vWindow["Name"].GetString());
	if (vWindow.HasMember("Title")) Title = gcnew String(vWindow["Title"].GetString());
	if (vWindow.HasMember("CloseButton")) CloseButton = vWindow["CloseButton"].GetBool();

	if (vWindow.HasMember("Widgets")) {
		Value vWidgets = vWindow["Widgets"].GetArray();
		if (vWidgets.IsArray()) {
			for (rapidjson::SizeType i = 0; i < vWidgets.Size(); i++) {
				Value vWidget = vWidgets[i].GetObject();
				CWidget ^addWidget = LoadWidgetByType(&vWidget);
				if (addWidget) widgets->Add(addWidget);
			}
		}
	}

	return;
}

void CWindow::DeleteWidget(CWidget^ widget) {
	CWidget ^container = widget->containedBy;
	if (container) {
		container->widgets->Remove(widget);
	}
	delete widget;
}


/*void CWindow::LoadWidgetByType(rapidjson::Value* vWidget) {
	if (!vWidget->IsObject()) return;
	Value widget = vWidget->GetObject();

	int type;
	if (!widget.HasMember("Type")) return;
	type = widget["Type"].GetInt();

	CWidget ^addWidget = nullptr;
	switch (type) {
	case wtLabel:
		addWidget = gcnew CLabel(&widget);
		break;
	case wtCheckBox:
		addWidget = gcnew CCheckBox(&widget);
		break;
	case wtRadioButton:
		addWidget = gcnew CRadioButton(&widget);
		break;
	case wtButton:
		addWidget = gcnew CButton(&widget);
		break;
	case wtPanel:
		addWidget = gcnew CPanel(&widget);
		break;
	case wtField:
		addWidget = gcnew CField(&widget);
		break;
	case wtDropDown:
		addWidget = gcnew CDropDown(&widget);
		break;
	case wtImageBox:
		addWidget = gcnew CImageBox(&widget);
		break;
	case wtGauge:
		addWidget = gcnew CGauge(&widget);
		break;
	}
	if (addWidget) widgets->Add(addWidget);
}*/


void CWindow::Draw(PictureBox ^drawable) {
	System::Drawing::Rectangle drawRect;

	//image should be min size of panel, but expand to max size of form plus buffer

	if (drawable->Image) delete drawable->Image;
	drawable->Image = gcnew Bitmap(drawable->Width, drawable->Height);

	Graphics^ gr = Graphics::FromImage(drawable->Image);

	unsigned int uiColor = 0x3A5121;
	SolidBrush ^bgColor = gcnew SolidBrush(Color::FromArgb(uiColor & 0xFF, (uiColor & 0xFF00) >> 8, (uiColor & 0xFF0000) >> 16));
	gr->FillRectangle(bgColor, System::Drawing::Rectangle(position.X, position.Y, Width, Height));

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
		gr->FillRectangle(bgColor, System::Drawing::Rectangle(position.X + focus->X, position.Y + focus->Y, focus->Width, focus->Height));
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

			if (e->X >= position.X && e->X <= position.X + 4) {
				if (e->Y >= position.Y && e->Y <= position.Y + 4) cursor = Cursors::SizeNWSE;
				else if (e->Y >= position.Y + Height - 4 && e->Y <= position.Y + Height) cursor = Cursors::SizeNESW;
				else cursor = Cursors::SizeWE;
			}
			else if (e->X >= position.X + Width - 4 && e->X <= position.X + Width) {
				if (e->Y >= position.Y && e->Y <= position.Y + 4) cursor = Cursors::SizeNESW;
				else if (e->Y >= position.Y + Height - 4 && e->Y <= position.Y + Height) cursor = Cursors::SizeNWSE;
				else cursor = Cursors::SizeWE;
			} 
			else if (e->Y >= position.Y && e->Y <= position.Y + 4
				|| e->Y >= position.Y + Height - 4 && e->Y <= position.Y + Height) {
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
			case dmNW:
				adjustHeight = e->Y - position.Y - dragOffset.Y;
				adjustWidth = e->X - position.X - dragOffset.X;
				position = Point(position.X + adjustWidth, position.Y + adjustHeight);
				Width -= adjustWidth;
				Height -= adjustHeight;
				dragOffset.Y = e->Y - position.Y;
				dragOffset.X = e->X - position.X;
				break;
			case dmNE:
				adjustWidth = e->X - position.X - dragOffset.X;
				adjustHeight = e->Y - position.Y - dragOffset.Y;
				position = Point(position.X, position.Y + adjustHeight);
				Width += adjustWidth;
				Height -= adjustHeight;
				dragOffset.X += adjustWidth;
				dragOffset.Y = e->Y - position.Y;
				break;
			case dmSW:
				adjustWidth = e->X - position.X - dragOffset.X;
				adjustHeight = e->Y - position.Y - dragOffset.Y;
				position = Point(position.X + adjustWidth, position.Y);
				Width -= adjustWidth;
				Height += adjustHeight;
				dragOffset.X = e->X - position.X;
				dragOffset.Y += adjustHeight;
				break;
			case dmSE:
				adjustWidth = e->X - position.X - dragOffset.X;
				adjustHeight = e->Y - position.Y - dragOffset.Y;
				Width += adjustWidth;
				Height += adjustHeight;
				dragOffset.X += adjustWidth;
				dragOffset.Y += adjustHeight;
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
	if (e->X >= position.X && e->X <= position.X + 4) {
		if (e->Y >= position.Y && e->Y <= position.Y + 4) dragMode = dmNW;
		else if (e->Y >= position.Y + Height - 4 && e->Y <= position.Y + Height) dragMode = dmSW;
		else dragMode = dmW;
	} 
	else if (e->X >= position.X + Width - 4 && e->X <= position.X + Width) {
		if (e->Y >= position.Y && e->Y <= position.Y + 4) dragMode = dmNE;
		else if (e->Y >= position.Y + Height - 4 && e->Y <= position.Y + Height) dragMode = dmSE;
		else dragMode = dmE;
	}
	else if (e->Y >= position.Y && e->Y <= position.Y + 4) {
		dragMode = dmN;
	}
	else if (e->Y >= position.Y + Height - 4 && e->Y <= position.Y + Height) {
		dragMode = dmS;
	}
	else if (e->Y > position.Y + 4 && e->Y <= position.Y + top->Height) {
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
	CWidget^ container = nullptr;
	CWidget^ selectedWidget = getWidgetAtPoint(widgets, click);
	if (selectedWidget) {
		if (!selectedWidget->container || (selectedWidget->container && addMode == wtWidget)) {
			focus = selectedWidget;
			return selectedWidget;
		}
		container = selectedWidget;
	}

	//If no widget was clicked, check if in add mode
	if (addMode != wtWidget) {
		CWidget^ addWidget = nullptr;
		switch (addMode) {
		case wtLabel:
			addWidget = gcnew CLabel("lbl1", click.X, click.Y);
			break;
		case wtCheckBox:
			addWidget = gcnew CCheckBox("cb1", click.X, click.Y);
			break;
		case wtRadioButton:
			addWidget = gcnew CRadioButton("rb1", click.X, click.Y);
			break;
		case wtButton:
			addWidget = gcnew CButton("btn1", click.X, click.Y);
			break;
		case wtPanel:
			addWidget = gcnew CPanel("pnl1", click.X, click.Y);
			break;
		case wtField:
			addWidget = gcnew CField("fld1", click.X, click.Y);
			break;
		case wtDropDown:
			addWidget = gcnew CDropDown("dd1", click.X, click.Y);
			break;
		case wtImageBox:
			addWidget = gcnew CImageBox("img1", click.X, click.Y);
			break;
		case wtTabControl:
			addWidget = gcnew CTabControl("tab1", click.X, click.Y);
			break;
		case wtGauge:
			addWidget = gcnew CGauge("gauge1", click.X, click.Y);
			break;
		}
		
		if (addWidget) {
			if (container) {
				container->widgets->Add(addWidget);
				addWidget->containedBy = container;
				if (container->widgetType == wtTabControl) {
					addWidget->TabItem = ((CTabControl^)container)->VisibleTab;
				}
			}
			else widgets->Add(addWidget);
			focus = addWidget;
			return addWidget;
		}
		
	}

	return this;
}

CWidget^ CWindow::getWidgetAtPoint(ArrayList ^widgets, Point p) {
	CWidget^ selectedWidget = nullptr;
	for each (CWidget^ w in widgets) {
		if (w->DoesPointIntersect(p)) {
			if (w->container) {
				selectedWidget = getWidgetAtPoint(w->widgets, p);
				if (!selectedWidget) selectedWidget = w;
				break;
			}
			else {
				return w;
			}
		}
	}

	return selectedWidget;
}