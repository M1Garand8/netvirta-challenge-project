#include <string>
#include <vector>

class StringUtils
{
public:
	static bool TryParse(const std::string str, int& result);
	static std::vector<std::string> Split(const std::string str, char delimiter);
	static const std::vector<int> IntParseSearchSequence(int argc, char *argv[]);
	static const std::string StrParseSearchSequence(int argc, char *argv[]);
	static const std::string StringList(const std::vector<int> list, const std::string separator);

private:
	StringUtils() { }
};