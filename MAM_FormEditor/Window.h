#pragma once

public ref class CWindow {
public: //Properties
	property int Width;
	property int Height;
	property System::String^ Name;
	property System::String^ Caption;
	property bool CloseButton;

public:
	CWindow();
	void CWindow::Draw(System::Windows::Forms::PictureBox^ drawable);

	//Events
	System::Windows::Forms::Cursor^ CWindow::MouseMove(System::Windows::Forms::MouseEventArgs^ e);
	void CWindow::MouseDown(System::Windows::Forms::MouseEventArgs^ e);
	void CWindow::MouseUp(System::Windows::Forms::MouseEventArgs^ e);

private:
	System::Drawing::Point position;
	bool dragging = false;
	System::Drawing::Point dragOffset;

	System::Drawing::Image ^top, ^bottom, ^left, ^right;
	System::Drawing::Image ^topLeft, ^topRight, ^bottomLeft, ^bottomRight;
	System::Drawing::Image ^close;
};