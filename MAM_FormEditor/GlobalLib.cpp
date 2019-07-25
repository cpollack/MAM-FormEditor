#include "GlobalLib.h"

std::string textToString(System::String^ text) {
	msclr::interop::marshal_context context;
	return context.marshal_as<std::string>(text);
}