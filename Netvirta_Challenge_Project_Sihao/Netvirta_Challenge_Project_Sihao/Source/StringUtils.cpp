#include "../Header/StringUtils.h"
#include <sstream>

bool StringUtils::TryParse(const std::string str, int& result)
{
	std::stringstream inputStr{ str };
	inputStr >> result;

	return !inputStr.fail();
}

bool StringUtils::TryParse(const std::string str, unsigned& result)
{
	std::stringstream inputStr{ str };
	inputStr >> result;

	return !inputStr.fail();
}

std::vector<std::string> StringUtils::Split(const std::string& str, char delimiter)
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

const std::vector<int> StringUtils::IntParseSearchSequence(std::vector<std::string>& searchFuncSeq, const bool hasSearchFunc)
{
	std::vector<int> strSeq;
	unsigned seqSize = searchFuncSeq.size();

	if (hasSearchFunc == true && seqSize <= 1)
	{
		return strSeq;
	}

	unsigned start = hasSearchFunc == true ? 1 : 0;

	for (unsigned i = start; i < seqSize; ++i)
	{
		int currInt = 0;
		if (StringUtils::TryParse(searchFuncSeq[i], currInt) == true)
		{
			strSeq.push_back(currInt);
		}
	}

	return strSeq;
}

const std::string StringUtils::StrParseSearchSequence(std::vector<std::string>& searchFuncSeq, const bool hasSearchFunc)
{
	std::string strSeq = "";

	unsigned seqSize = searchFuncSeq.size();

	if (hasSearchFunc == true && seqSize <= 1)
	{
		return strSeq;
	}

	unsigned start = hasSearchFunc == true ? 1 : 0;

	for (unsigned i = start; i < seqSize; ++i)
	{
		int currInt = 0;
		if (StringUtils::TryParse(searchFuncSeq[i], currInt) == true)
		{
			strSeq += searchFuncSeq[i];
		}

		if (i < (seqSize - 1))
		{
			strSeq += " ";
		}
	}

	return strSeq;
}

// Given a list of integers, string up the list using given separator
const std::string StringUtils::StringList(const std::vector<int>& list, const std::string separator)
{
	if (list.empty() == true)
	{
		return "none.";
	}

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

bool StringUtils::CheckFileName(const std::string& str, const std::string& fileType)
{
	int pos = str.find(fileType);

	// File type not found, either missing or wrong file type
	if (pos == std::string::npos)
	{
		return false;
	}

	// File name + file type shouldn't be less than the length of file type
	if (fileType.size() >= str.size())
	{
		return false;
	}

	int realStart = str.size() - fileType.size();

	// Found file type position is not at supposed location, either duplicate file type in the string or in the wrong place
	if (pos != realStart)
	{
		return false;
	}

	return true;
}

int StringUtils::ConvertToMiliseconds(double seconds)
{
	return int(seconds * 1000.0);
}

int StringUtils::ConvertToMicroseconds(double seconds)
{
	return int(seconds * 1000000.0);
}

int StringUtils::SafeConvertUnsigned(const unsigned num, const int returnDefault)
{
	if (num < static_cast<unsigned>(std::numeric_limits<int>::max()))
	{
		return int(num);
	}
	else
	{
		return returnDefault;
	}
}