#pragma once

#include "include/rapidjson/document.h"

using namespace System::ComponentModel;

enum WidgetType {
	wtWidget = 0,
	wtLabel,
	wtCheckBox,
	wtRadioButton,
	wtButton,
	wtPanel,
	wtField,
	wtDropDown,
	wtImageBox,
	wtTabControl,
	wtGauge,
	wtListBox,
	wtGridBox
};

ref class EnumUnderConvertor : public System::ComponentModel::EnumConverter
{
private:
	System::Type^ _enumType;
public:
	EnumUnderConvertor(System::Type^ type) : System::ComponentModel::EnumConverter(type)
	{
		_enumType = type;
	}

	bool CanConvertTo(System::ComponentModel::ITypeDescriptorContext^ context, System::Type^ destType)override
	{
		return destType == System::String::typeid;
	}

	System::Object^ ConvertTo(System::ComponentModel::ITypeDescriptorContext^ context, System::Globalization::CultureInfo^ culture, System::Object^ value, System::Type^ destType)override
	{
		return value->ToString()->Replace("_", " ");
	}

	bool CanConvertFrom(System::ComponentModel::ITypeDescriptorContext^ context, System::Type^ srcType)override
	{
		return srcType == System::String::typeid;
	}

	System::Object^ ConvertFrom(System::ComponentModel::ITypeDescriptorContext^ context, System::Globalization::CultureInfo^ culture, System::Object^ value)override
	{
		return System::Enum::Parse(_enumType, ((System::String^)value)->Replace(" ", "_")->Replace(",_", ", "));
	}
};

public ref class CWidget {
public: //Properties
	[Category("Main"), Description("The indentifying name of the widget")]
	property System::String^ Name;
	[Category("Main"), Description("X coordinate of widget on form")]
	property int X;
	[Category("Main"), Description("Y coordinate of widget on form")]
	property int Y;
	[Category("Main"), Description("Width of the widget in pixels")]
	property int Width
	{
		virtual int get() {
			return width;
		};
		virtual void set(int value) {
			width = value;
		};
	}
	[Category("Main"), Description("Height of the widget in pixels")]
	property int Height {
		virtual int get() {
			return height;
		};
		virtual void set(int value) {
			height = value;
		};
	}

	[Category("Main"), Description("Widget is assigned to this tab.")]
	property int TabItem;

	//[DisplayName("Test Property")]

public:
	int widgetType;
	int width, height;

	bool container = false;
	System::Collections::ArrayList ^widgets = nullptr;
	CWidget ^containedBy = nullptr;

	CWidget();
	CWidget(rapidjson::Value* vWidget);
	virtual void Draw(System::Drawing::Graphics^ gr, System::Drawing::Point pos) abstract;
	virtual void Save(rapidjson::Document* document, rapidjson::Value* vWidget);

	virtual bool DoesPointIntersect(System::Drawing::Point point);
	int MouseDown(System::Windows::Forms::MouseEventArgs^ e, System::Drawing::Point wPos);
	System::Windows::Forms::Cursor^ MouseMove(System::Windows::Forms::MouseEventArgs^ e, System::Drawing::Point wPos);
	virtual System::Drawing::Point MouseDrag(System::Drawing::Point dragPos, System::Drawing::Point wPos, System::Drawing::Point dragOffset, int dragMode);

private:
	void dragSubwidgets(int adjustX, int adjustY);

protected:
	int MIN_HEIGHT = 2;
	int MIN_WIDTH = 5;

	System::Drawing::Font ^font;
	System::Drawing::SolidBrush ^fontBrush;
};