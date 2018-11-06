#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>
#include <vector>

class StringUtils
{
public:
	static bool TryParse(const std::string str, int& result);
	static bool TryParse(const std::string str, unsigned& result);
	static std::vector<std::string> Split(const std::string& str, char delimiter);
	static const std::vector<int> IntParseSearchSequence(int argc, char *argv[]);
	static const std::string StrParseSearchSequence(int argc, char *argv[]);
	static const std::vector<int> IntParseSearchSequence(std::vector<std::string>& searchFuncSeq);
	static const std::string StrParseSearchSequence(std::vector<std::string>& searchFuncSeq);
	static const std::string StringList(const std::vector<int>& list, const std::string separator);

private:
	StringUtils() { }
};

#endif