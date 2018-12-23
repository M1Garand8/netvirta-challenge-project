#include "../Header/SearchResult.h"
#include "../../Netvirta_Challenge_Project_Sihao/Header/StringUtils.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>

const SearchInput SearchUtils::GenerateSearchInput(int count, int range_max)
{
	std::vector<std::string> searchStrList = StringUtils::GenerateInputSequenceString(count, range_max);
	SearchInput searchInput{ searchStrList, false };

	return searchInput;
}

SearchInput::SearchInput(std::vector<std::string>& searchFuncSeq, const bool hasSearchFunc)
{
	Set(searchFuncSeq, hasSearchFunc);
}

void SearchInput::Update(std::vector<std::string>& searchFuncSeq, const bool hasSearchFunc)
{
	_inputSequence.clear();
	_sequenceCount.clear();

	Set(searchFuncSeq, hasSearchFunc);
}

const int& SearchInput::operator[](unsigned i)
{
	unsigned size = _inputSequence.size();
	if (i >= size)
	{
		std::cout << "Index out of bounds." << std::endl;
		unsigned end = size - 1;
		return _inputSequence[end];
	}

	return _inputSequence[i];
}

const unsigned SearchInput::Size() const
{
	return _inputSequence.size();
}

const int SearchInput::GetCount(int num) const
{
	auto findRes = _sequenceCount.find(num);

	if (findRes != _sequenceCount.end())
	{
		return findRes->second;
	}

	return -1;
}

const std::vector<int>& SearchInput::GetInputSequence() const
{
	return _inputSequence;
}

const std::unordered_map<int, int>& SearchInput::GetSequenceCount() const
{
	return _sequenceCount;
}

void SearchInput::Set(std::vector<std::string>& searchFuncSeq, const bool hasSearchFunc)
{
	_inputSequence = StringUtils::IntParseSearchSequence(searchFuncSeq, hasSearchFunc);

	for (unsigned i = 0; i < _inputSequence.size(); ++i)
	{
		int currNum = _inputSequence[i];
		++_sequenceCount[currNum];
	}
}

SearchResult::SearchResult() { }

SearchResult::SearchResult(const unsigned row, const unsigned expectedSize) : _row(row), _expectedSize(expectedSize) { }

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

void SearchResult::Add(const ElemData data)
{
	_foundNumsList.push_back(data);

	_foundNumsListSorted.push_back(data);
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

bool SearchResult::MatchSize()
{
	return _expectedSize == _foundNumsList.size();
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

	return newPos > lastElemPos;
}

// Checks if new position to be added is directly after the last found position
bool SearchResult::InDirectSequence(const int newPos)
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

// Checks if new position to be added is within the range expected by the leftmost position
bool SearchResult::WithinASequence(const int newPos)
{
	unsigned seqSize = _foundNumsListSorted.size();
	// First in sequence, always in "sequence"
	if (seqSize == 0)
	{
		return true;
	}

	for (unsigned i = 0; i < seqSize; ++i)
	{
		int currElemPos = _foundNumsListSorted[i].Pos();
		unsigned diff = abs(currElemPos - newPos);

		if (diff > seqSize)
		{
			return false;
		}
	}

	return true;
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

//bool SearchResultList::Add(const int currSrchSeq, const int searchSize, const ElemData data, bool isOrdered)
//{
//	int row = data.Row();
//	int listSize = StringUtils::SafeConvertUnsigned(_searchResList.size());
//	int lastData = listSize - 1;
//
//	// First ever result found
//	if (listSize == 0 && currSrchSeq == 1)
//	{
//		SearchResult res(data.Row(), searchSize);
//		res.Add(data);
//		_searchResList.push_back(res);
//
//		return true;
//	}
//
//	int rowExist = BinarySearchRow(_searchResList, 0, lastData, row);
//	if (rowExist != -1)
//	{
//		SearchResult& res = _searchResList[rowExist];
//		// Skip adding if data already added
//		if (res.Has(data.Num(), data.Pos()))
//		{
//			return false;
//		}
//
//		// Skip adding if it fails in sequence requirement
//		if (isOrdered == true && res.InSequence(data.Pos()) == false)
//		{
//			return false;
//		}
//
//		res.Add(data);
//
//		return true;
//	}
//	// Add new result only if matched number is first one found
//	else if (rowExist == -1 && currSrchSeq == 1)
//	{
//		SearchResult res(data.Row(), searchSize);
//		res.Add(data);
//		_searchResList.push_back(res);
//		Sort();
//
//		return true;
//	}
//
//	// Nothing added if it reaches here, so return "failed".
//	return false;
//}

void SearchResultList::Add(const int currRow, const ElemData data)
{
	if (_searchResMap.find(currRow) == _searchResMap.end())
	{
		SearchResult res;
		_searchResMap[currRow] = res;
	}

	_searchResMap[currRow].Add(data);
}

bool SearchResultList::Has(const int currRow, const ElemData data)
{
	if (_searchResMap.find(currRow) == _searchResMap.end())
	{
		return false;
	}

	SearchResult res = _searchResMap[currRow];

	return res.Has(data.Num(), data.Pos());
}

bool SearchResultList::InSequence(const int currRow, const int newPos)
{
	auto rowExist = _searchResMap.find(currRow);

	// First in the sequence, always true
	if (rowExist == _searchResMap.end())
	{
		return true;
	}

	return rowExist->second.InSequence(newPos);
}

std::vector<int> SearchResultList::GetFoundList(const int searchSize)
{
	std::vector<int> foundRows;
	/*for (unsigned i = 0; i < _searchResList.size(); ++i)
	{
		SearchResult currRes = _searchResList[i];
		if (currRes.Size() == searchSize)
		{
			foundRows.push_back(currRes.Row());
		}
	}*/

	for (auto resEntry : _searchResMap)
	{
		if (resEntry.second.Size() == searchSize)
		{
			foundRows.push_back(resEntry.first);
		}
	}

	return foundRows;
}

void SearchResultList::Sort()
{
	std::sort(_searchResList.begin(), _searchResList.end(), [](const SearchResult& res1, const SearchResult& res2) {
		return res1.Row() < res2.Row();
	});
}

int SearchResultList::BinarySearchRow(const std::vector<SearchResult>& data, int l, int r, const int row)
{
	if (r >= l)
	{
		int mid = l + (r - l) / 2;

		if (data[mid].Row() == row)
		{
			return mid;
		}

		if (data[mid].Row() > row)
		{
			return BinarySearchRow(data, l, mid - 1, row);
		}

		return BinarySearchRow(data, mid + 1, r, row);
	}

	return -1;
}
