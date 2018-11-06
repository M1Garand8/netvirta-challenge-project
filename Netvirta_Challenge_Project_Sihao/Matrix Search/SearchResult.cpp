#include "SearchResult.h"
#include <cmath>
#include <algorithm>

SearchResult::SearchResult() { }

SearchResult::SearchResult(const unsigned row) : _row(row) { }

SearchResult::SearchResult(const SearchResult& res)
{
	_row = res._row;

	_foundNumsList = res._foundNumsList;
	_foundNumsListSorted = res._foundNumsListSorted;
}

const int SearchResult::Row() const
{
	return _row;
}

SearchResult& SearchResult::operator=(const SearchResult& res)
{
	_row = res._row;

	_foundNumsList = res._foundNumsList;
	_foundNumsListSorted = res._foundNumsListSorted;

	return *this;
}

void SearchResult::Add(const int num, const int pos)
{
	ElemData foundNum(num, pos);
	_foundNumsList.push_back(foundNum);

	_foundNumsListSorted.push_back(foundNum);
	std::sort(_foundNumsListSorted.begin(), _foundNumsListSorted.end(), [](const ElemData& data1, const ElemData& data2) {
		return data1.Pos() < data2.Pos();
	});
}

bool SearchResult::Has(const int num, const int pos)
{
	for (unsigned i = 0; i < _foundNumsList.size(); ++i)
	{
		ElemData foundNum = _foundNumsList[i];

		if (foundNum.Num() == num && foundNum.Pos() == pos)
		{
			return true;
		}
	}

	return false;
}

const unsigned SearchResult::Size() const
{
	return _foundNumsList.size();
}

bool SearchResult::MatchSize(const unsigned size)
{
	return size == _foundNumsList.size();
}

const int SearchResult::MatchSize(const std::vector<int>& inputSeq) const
{
	int numsMatched = 0;
	for (unsigned i = 0; i < inputSeq.size(); ++i)
	{
		int numToMatch = inputSeq[i];
		int currNum = _foundNumsList[i].Num();

		if (numToMatch == currNum)
		{
			++numsMatched;
		}
	}

	return numsMatched;
}

// Checks if the found numbers list is in sequence, not necessary in order
bool SearchResult::InASequence()
{
	unsigned listSize = _foundNumsList.size();

	// 0 length list is not a sequence!
	if (listSize == 0)
	{
		return false;
	}

	// Sequence of 1 number
	if (listSize == 1)
	{
		return true;
	}

	// Even if numbers matched are not in sequence (in the case of SearchUnordered),
	// the position of the numbers must be still in sequence, since it is a sequence
	for (unsigned i = 0, j = i + 1; j < _foundNumsListSorted.size(); ++i, ++j)
	{
		ElemData first = _foundNumsListSorted[i];
		ElemData second = _foundNumsListSorted[j];

		int diff = std::abs(first.Pos() - second.Pos());

		if (diff > 1)
		{
			return false;
		}
	}

	return true;
}

// Checks if new position to be added is directly after the last found position
bool SearchResult::InSequence(const int newPos)
{
	unsigned lastElem = _foundNumsListSorted.size() - 1;
	int lastElemPos = _foundNumsListSorted[lastElem].Pos();
	int diff = abs(lastElemPos - newPos);

	return newPos > lastElemPos && diff == 1;
}

bool SearchResult::IsSmaller(const ElemData& data1, const ElemData& data2) const
{
	return data1.Pos() < data2.Pos();
}