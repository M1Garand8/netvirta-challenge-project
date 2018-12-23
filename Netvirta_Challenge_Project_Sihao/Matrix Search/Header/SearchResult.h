#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include "../../Netvirta_Challenge_Project_Sihao/Header/MatrixUtils.h"
#include <vector>
#include <unordered_map>

class SearchInput
{
public:
	SearchInput(std::vector<std::string>& searchFuncSeq, const bool hasSearchFunc = true);
	void Update(std::vector<std::string>& searchFuncSeq, const bool hasSearchFunc = true);
	const int& operator[](unsigned i);
	const unsigned Size() const;
	const int GetCount(int num) const;
	const std::vector<int>& GetInputSequence() const;
	const std::unordered_map<int, int>& GetSequenceCount() const;

private:
	void Set(std::vector<std::string>& searchFuncSeq, const bool hasSearchFunc = true);
	std::vector<int> _inputSequence;
	std::unordered_map<int, int> _sequenceCount;
};

class SearchResult
{
public:
	SearchResult();
	SearchResult(const unsigned row, const unsigned expectedSize);
	SearchResult(const SearchResult& res);
	const int Row() const;
	SearchResult& operator=(const SearchResult& res);
	void Add(const int num, const int pos);
	void Add(const ElemData data);
	void AddSwap(const int num, const int pos);
	void Swap(const int old_num, const int old_pos, const int new_num, const int new_pos);
	bool IsCloser(const int num, const int pos);
	bool Has(const int num);
	bool Has(const int num, const int pos);
	int Find(const std::vector<ElemData>& data, const int num);
	const unsigned Size() const;
	bool MatchSize();
	bool MatchSize(const unsigned size);
	const int MatchSize(const std::vector<int>& inputSeq) const;
	bool InASequence();
	bool InSequence(const int newPos);
	bool InDirectSequence(const int newPos);
	bool WithinASequence(const int newPos);

	const std::string PrintSequence();

private:
	bool IsSmaller(const ElemData& data1, const ElemData& data2) const;
	void Sort();
	unsigned _row;
	unsigned _expectedSize;
	std::vector<ElemData> _foundNumsList;
	std::vector<ElemData> _foundNumsListSorted;
};

class SearchResultList
{
public:
	//bool Add(const int currSrchSeq, const int searchSize, const ElemData data, bool isOrdered = true);
	void Add(const int currRow, const ElemData data);
	bool Has(const int currRow, const ElemData data);
	bool InSequence(const int currRow, const int newPos);
	std::vector<int> GetFoundList(const int searchSize);

private:
	void Sort();
	int BinarySearchRow(const std::vector<SearchResult>& data, int l, int r, const int row);
	std::vector<SearchResult> _searchResList;
	std::unordered_map<int, SearchResult> _searchResMap;
};

class SearchUtils
{
public:
	static const SearchInput GenerateSearchInput(int count, int range_max);

private:
	SearchUtils() { }
};

#endif // !SEARCHRESULT_H