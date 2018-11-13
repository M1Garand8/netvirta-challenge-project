#include "SearchResult.h"
#include "..\Netvirta_Challenge_Project_Sihao\StringUtils.h"
#include <cmath>
#include <algorithm>
#include <string>

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
	Sort();
}

void SearchResult::AddSwap(const int num, const int pos)
{
	int numPosUnsorted = Find(_foundNumsList, num);
	int numPosSorted = Find(_foundNumsListSorted, num);

	// Both lists should have the number!
	if (numPosUnsorted != -1 && numPosSorted != -1)
	{
		_foundNumsList[numPosUnsorted].Set(num, pos);
		_foundNumsListSorted[numPosSorted].Set(num, pos);
	}
}

void SearchResult::Swap(const int old_num, const int old_pos, const int new_num, const int new_pos)
{
	int oldNumPosUnsorted = Find(_foundNumsList, old_num);
	int oldNumPosSorted = Find(_foundNumsListSorted, old_num);

	// Both lists should have the number!
	if (oldNumPosUnsorted != -1 && oldNumPosSorted != -1)
	{
		_foundNumsList[oldNumPosUnsorted].Set(new_num, new_pos);
		_foundNumsListSorted[oldNumPosSorted].Set(new_num, new_pos);
	}
}

bool SearchResult::IsCloser(const int num, const int pos)
{
	if (Has(num) == true)
	{
		int currNumPos = Find(_foundNumsListSorted, num);

		ElemData firstData = _foundNumsListSorted[0];
		ElemData currData = _foundNumsListSorted[currNumPos];

		int currDataDist = std::abs(firstData.Pos() - currData.Pos());
		int newDataDist = std::abs(firstData.Pos() - pos);

		return newDataDist < currDataDist;
	}

	return true;
}

bool SearchResult::Has(const int num)
{

	return Find(_foundNumsListSorted, num) != -1;
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

int SearchResult::Find(const std::vector<ElemData>& data, const int num)
{
	for (unsigned i = 0; i < data.size(); ++i)
	{
		ElemData foundData = _foundNumsList[i];
		if (foundData.Num() == num)
		{
			return StringUtils::SafeConvertUnsigned(i);
		}
	}

	return -1;
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
		for (unsigned j = 0; j < _foundNumsList.size(); ++j)
		{
			int currNum = _foundNumsList[j].Num();

			if (numToMatch == currNum)
			{
				++numsMatched;
			}
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
	unsigned seqSize = _foundNumsListSorted.size();
	// First in sequence, always in "sequence"
	if (seqSize == 0)
	{
		return true;
	}

	unsigned lastElem = _foundNumsListSorted.size() - 1;
	int lastElemPos = _foundNumsListSorted[lastElem].Pos();
	int diff = abs(lastElemPos - newPos);

	return newPos > lastElemPos && diff == 1;
}

const std::string SearchResult::PrintSequence()
{
	std::string seqStr;

	unsigned seqLength = _foundNumsList.size();
	for (unsigned i = 0; i < seqLength; ++i)
	{
		ElemData data = _foundNumsList[i];
		seqStr += std::to_string(data.Num());

		if (i < seqLength - 1)
		{
			seqStr += " ";
		}
	}

	return seqStr;
}

bool SearchResult::IsSmaller(const ElemData& data1, const ElemData& data2) const
{
	return data1.Pos() < data2.Pos();
}

void SearchResult::Sort()
{
	std::sort(_foundNumsListSorted.begin(), _foundNumsListSorted.end(), [](const ElemData& data1, const ElemData& data2) {
		return data1.Pos() < data2.Pos();
	});
}