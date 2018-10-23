#include "SearchResult.h"

SearchResult::SearchResult() { }

void SearchResult::Add(const int num, const int pos)
{
	foundNumsList.push_back(num);
	foundNumPosList.push_back(pos);
}

bool SearchResult::Has(const int num, const int pos)
{
	for (unsigned i = 0; i < foundNumsList.size(); ++i)
	{
		int currNum = foundNumsList[i];
		int currPos = foundNumPosList[i];

		if (currNum == num && currPos == pos)
		{
			return true;
		}
	}

	return false;
}

bool SearchResult::MatchSize(const unsigned size)
{
	return size == foundNumsList.size();
}