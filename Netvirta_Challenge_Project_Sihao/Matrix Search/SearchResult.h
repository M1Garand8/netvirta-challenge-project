#include <vector>

class SearchResult
{
public:
	SearchResult();
	void Add(const int num, const int pos);
	bool Has(const int num, const int pos);
	bool MatchSize(const unsigned size);

private:
	std::vector<int> foundNumsList;
	std::vector<int> foundNumPosList;
};