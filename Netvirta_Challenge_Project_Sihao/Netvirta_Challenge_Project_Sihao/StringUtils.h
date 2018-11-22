#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>
#include <vector>
#include "..\Matrix Search\SearchResult.h"

class StringUtils
{
public:
	static bool TryParse(const std::string str, int& result);
	static bool TryParse(const std::string str, unsigned& result);

	static std::vector<std::string> Split(const std::string& str, char delimiter);

	static const std::vector<int> IntParseSearchSequence(int argc, char *argv[]);
	static const std::string StrParseSearchSequence(int argc, char *argv[]);
	static const std::vector<int> IntParseSearchSequence(std::vector<std::string>& searchFuncSeq, const bool hasSearchFunc = true);
	static const std::string StrParseSearchSequence(std::vector<std::string>& searchFuncSeq, const bool hasSearchFunc = true);

	static const std::string StringList(const std::vector<int>& list, const std::string separator);

	static bool CheckFileName(const std::string& str, const std::string& fileType);

	static int ConvertToMiliseconds(double seconds);
	static int ConvertToMicroseconds(double seconds);

	static int SafeConvertUnsigned(const unsigned num, const int returnDefault = -1);

private:
	StringUtils() { }
};

#endif