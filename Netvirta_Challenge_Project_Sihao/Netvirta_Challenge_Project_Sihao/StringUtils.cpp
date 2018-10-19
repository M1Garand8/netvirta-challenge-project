#include "StringUtils.h"
#include <sstream>

bool StringUtils::TryParse(const std::string str, int& result)
{
	std::stringstream inputStr{ str };
	inputStr >> result;

	return !inputStr.fail();
}

std::vector<std::string> StringUtils::Split(const std::string str, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream{ str };

	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}

	return tokens;
}