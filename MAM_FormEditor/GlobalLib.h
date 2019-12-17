#pragma once

#include <string>
#include <msclr\marshal_cppstd.h>
#include "include/rapidjson/document.h"

ref class CWidget;

std::string textToString(System::String^ text);
CWidget^ LoadWidgetByType(rapidjson::Value* vWidget);
void doMessageBoxError(std::string title, std::string message);

extern bool previewMode;