#pragma once

#include "include/rapidjson/document.h"

enum DragMode {
	dmNone,
	dmDrag,
	dmW,
	dmE,
	dmN,
	dmS,
	dmNW,
	dmNE,
	dmSW,
	dmSE
};

ref class CWidget;

public ref class CWindow {
public: //Properties
	property int Width;
	property int Height;
	property System::String^ Name;
	property System::String^ Title;
	property bool CloseButton;

public:
	CWindow();
	void CWindow::Draw(System::Windows::Forms::PictureBox^ drawable);
	rapidjson::Document* CWindow::Save(rapidjson::Document* document);
	void CWindow::Load(rapidjson::Document* document);
	//void CWindow::LoadWidgetByType(rapidjson::Value* vWidget);

	//Events
	System::Windows::Forms::Cursor^ CWindow::MouseMove(System::Windows::Forms::MouseEventArgs^ e);
	void CWindow::MouseDown(System::Windows::Forms::MouseEventArgs^ e);
	void CWindow::MouseUp(System::Windows::Forms::MouseEventArgs^ e);
	System::Object^ CWindow::Click(System::Windows::Forms::MouseEventArgs^ e, int addMode);

	System::Collections::ArrayList ^widgets;
	CWidget^ focus;

private:
	System::Drawing::Point position;
	bool dragging = false;
	bool draggingWidget = false;
	int dragMode = dmNone;
	System::Drawing::Point dragOffset;

	System::Drawing::Image ^top, ^bottom, ^left, ^right;
	System::Drawing::Image ^topLeft, ^topRight, ^bottomLeft, ^bottomRight;
	System::Drawing::Image ^close;
	int MIN_LEFT, MAX_RIGHT, MIN_TOP, MAX_BOTTOM;

	CWidget^ getWidgetAtPoint(System::Collections::ArrayList ^widgets, System::Drawing::Point p);
};