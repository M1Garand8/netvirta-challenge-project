#include "IntParse.h"
#include <sstream>

IntParse::IntParse() {}

bool IntParse::TryParse(const std::string str, int& result)
{
	std::stringstream inputStr{ str };
	inputStr >> result;

	return !inputStr.fail();
}