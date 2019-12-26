#include "Widget.h"
#include "Window.h"
#include "GlobalLib.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace rapidjson;

CWidget::CWidget() {
	font = gcnew Font("Verdana", 12, GraphicsUnit::Pixel);
	fontBrush = gcnew SolidBrush(Color::FromArgb(0xAD, 0xE9, 0xCD));
	TabItem = 0;
}

CWidget::CWidget(rapidjson::Value* vWidget) {
	if (!vWidget->IsObject()) return;
	//Value widget = vWidget->GetObject();

	if (vWidget->HasMember("Name")) Name = gcnew String((*vWidget)["Name"].GetString());
	if (vWidget->HasMember("X")) X = (*vWidget)["X"].GetInt();
	if (vWidget->HasMember("Y")) Y = (*vWidget)["Y"].GetInt();
	if (vWidget->HasMember("Width")) Width = (*vWidget)["Width"].GetInt();
	else Width = 0;
	if (vWidget->HasMember("Height")) Height = (*vWidget)["Height"].GetInt();
	else Height = 0;
	if (vWidget->HasMember("TabItem")) TabItem = (*vWidget)["TabItem"].GetInt();
	else TabItem = 0;

	font = gcnew Font("Verdana", 12, GraphicsUnit::Pixel);
	fontBrush = gcnew SolidBrush(Color::FromArgb(0xAD, 0xE9, 0xCD));
}

void CWidget::Save(rapidjson::Document* document, rapidjson::Value* vWidget) {
	Document::AllocatorType& allocator = document->GetAllocator();

	Value vType(kNumberType);
	vType.SetInt(widgetType);
	vWidget->AddMember("Type", vType, allocator);

	Value vName(kStringType);
	vName.SetString(textToString(Name).c_str(), Name->Length, allocator);
	vWidget->AddMember("Name", vName, allocator);

	Value vWidth(kNumberType);
	vWidth.SetInt(Width);
	vWidget->AddMember("Width", vWidth, allocator);

	Value vHeight(kNumberType);
	vHeight.SetInt(Height);
	vWidget->AddMember("Height", vHeight, allocator);

	Value vX(kNumberType);
	vX.SetInt(X);
	vWidget->AddMember("X", vX, allocator);

	Value vY(kNumberType);
	vY.SetInt(Y);
	vWidget->AddMember("Y", vY, allocator);

	Value vTabItem(kNumberType);
	vTabItem.SetInt(TabItem);
	vWidget->AddMember("TabItem", vTabItem, allocator);
}

bool CWidget::DoesPointIntersect(Point point) {
	if (point.X >= X && point.X <= X + Width && point.Y >= Y && point.Y <= Y + Height) return true;
	return false;
}

int CWidget::MouseDown(System::Windows::Forms::MouseEventArgs^ e, System::Drawing::Point wPos) {
	int dragMode = dmNone;
	Point position(wPos.X + X, wPos.Y + Y);

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

	return cursor;
}

Point CWidget::MouseDrag(Point dragPos, Point wPos, Point dragOffset, int dragMode) {
	Point position(wPos.X + X, wPos.Y + Y);
	Point offset(dragPos.X - dragOffset.X, dragPos.Y - dragOffset.Y);

	int origX = X;
	int origY = Y;
	int adjustHeight, adjustWidth;

	switch (dragMode) {
	case dmDrag:
		X = dragPos.X - dragOffset.X - wPos.X;
		Y = dragPos.Y - dragOffset.Y - wPos.Y;
		break;
	case dmN:
		adjustHeight = dragPos.Y - dragOffset.Y - position.Y;
		if (Height - adjustHeight < MIN_HEIGHT) adjustHeight = Height - MIN_HEIGHT;
		Y = Y + adjustHeight;
		Height -= adjustHeight;
		break;
	case dmS:
		adjustHeight = dragPos.Y - dragOffset.Y - position.Y;
		if (Height + adjustHeight < MIN_HEIGHT) adjustHeight = MIN_HEIGHT - Height;
		Height += adjustHeight;
		dragOffset.Y += adjustHeight;
		break;
	case dmW:
		adjustWidth = dragPos.X - dragOffset.X - position.X;
		if (Width - adjustWidth < MIN_WIDTH) adjustWidth = Width - MIN_WIDTH;
		X = X + adjustWidth;
		Width -= adjustWidth;
		break;
	case dmE:
		adjustWidth = dragPos.X - dragOffset.X - position.X;
		if (Width + adjustWidth < MIN_WIDTH) adjustWidth = MIN_WIDTH - Width;
		Width += adjustWidth;
		dragOffset.X += adjustWidth;
		break;
	case dmNW:
		adjustWidth = dragPos.X - dragOffset.X - position.X;
		adjustHeight = dragPos.Y - dragOffset.Y - position.Y;
		if (Width - adjustWidth < MIN_WIDTH) adjustWidth = Width - MIN_WIDTH;
		if (Height - adjustHeight < MIN_HEIGHT) adjustHeight = Height - MIN_HEIGHT;
		X = X + adjustWidth;
		Y = Y + adjustHeight;
		Width -= adjustWidth;
		Height -= adjustHeight;
		break;
	case dmNE:
		adjustWidth = dragPos.X - dragOffset.X - position.X;
		adjustHeight = dragPos.Y - dragOffset.Y - position.Y;
		if (Width + adjustWidth < MIN_WIDTH) adjustWidth = MIN_WIDTH - Width;
		if (Height - adjustHeight < MIN_HEIGHT) adjustHeight = Height - MIN_HEIGHT;
		Y = Y + adjustHeight;
		Width += adjustWidth;
		Height -= adjustHeight;
		dragOffset.X += adjustWidth;
		break;
	case dmSW:
		adjustWidth = dragPos.X - dragOffset.X - position.X;
		adjustHeight = dragPos.Y - dragOffset.Y - position.Y;
		if (Width - adjustWidth < MIN_WIDTH) adjustWidth = Width - MIN_WIDTH;
		if (Height + adjustHeight < MIN_HEIGHT) adjustHeight = MIN_HEIGHT - Height;
		Width -= adjustWidth;
		Height += adjustHeight;
		X = X + adjustWidth;
		dragOffset.Y += adjustHeight;
		break;
	case dmSE:
		adjustWidth = dragPos.X - dragOffset.X - position.X;
		adjustHeight = dragPos.Y - dragOffset.Y - position.Y;
		if (Width + adjustWidth < MIN_WIDTH) adjustWidth = MIN_WIDTH - Width;
		if (Height + adjustHeight < MIN_HEIGHT) adjustHeight = MIN_HEIGHT - Height;
		Width += adjustWidth;
		Height += adjustHeight;
		dragOffset.X += adjustWidth;
		dragOffset.Y += adjustHeight;
		break;
	}

	if (X != origX || Y != origY) dragSubwidgets(X - origX, Y - origY);
	return dragOffset;
}

void CWidget::dragSubwidgets(int adjustX, int adjustY) {
	if (!container) return;

	for each (CWidget^ w in widgets) {
		if (w->container) w->dragSubwidgets(adjustX, adjustY);
		w->X += adjustX;
		w->Y += adjustY;
	}
}
