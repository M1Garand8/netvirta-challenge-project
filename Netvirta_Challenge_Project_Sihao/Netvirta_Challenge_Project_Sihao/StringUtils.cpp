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

const std::vector<int> StringUtils::IntParseSearchSequence(int argc, char *argv[])
{
	std::vector<int> inputSeq;

	for (int i = 3; i < argc; ++i)
	{
		int currInt = 0;
		if (StringUtils::TryParse(argv[i], currInt) == true)
		{
			inputSeq.push_back(currInt);
		}
	}

	return inputSeq;
}

const std::string StringUtils::StrParseSearchSequence(int argc, char *argv[])
{
	std::string strSeq;

	for (int i = 3; i < argc; ++i)
	{
		int currInt = 0;
		if (StringUtils::TryParse(argv[i], currInt) == true)
		{
			strSeq += std::to_string(currInt);
		}

		if (i < (argc - 1))
		{
			strSeq += " ";
		}
	}

	return strSeq;
}

// Given a list of integers, string up the list using given separator
const std::string StringUtils::StringList(const std::vector<int> list, const std::string separator)
{
	std::string strungList;

	for (unsigned i = 0; i < list.size(); ++i)
	{
		strungList += std::to_string(list[i]);

		if (i < (list.size() - 1))
		{
			strungList += separator;
		}
	}

	return strungList;
}