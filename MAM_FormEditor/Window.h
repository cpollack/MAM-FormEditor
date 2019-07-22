#pragma once

public ref class CWindow {
public:
	property int Width;
	property int Height;
	property System::String^ Name;
	property System::String^ Caption;
	property bool CloseButton;

	CWindow();
	void CWindow::Draw(System::Windows::Forms::PictureBox^ drawable);

private:
	System::Drawing::Point position;

	System::Drawing::Image ^top, ^bottom, ^left, ^right;
	System::Drawing::Image ^topLeft, ^topRight, ^bottomLeft, ^bottomRight;
	System::Drawing::Image ^close;
};