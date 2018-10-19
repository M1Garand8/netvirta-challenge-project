#include <string>
#include <vector>

class StringUtils
{
public:
	static bool TryParse(const std::string str, int& result);
	static std::vector<std::string> Split(const std::string str, char delimiter);

private:
	StringUtils() { }
};