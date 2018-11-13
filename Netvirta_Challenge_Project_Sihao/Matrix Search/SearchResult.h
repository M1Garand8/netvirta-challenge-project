#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include "..\Netvirta_Challenge_Project_Sihao\MatrixUtils.h"
#include <vector>

class SearchResult
{
public:
	SearchResult();
	SearchResult(const unsigned row);
	SearchResult(const SearchResult& res);
	const int Row() const;
	SearchResult& operator=(const SearchResult& res);
	void Add(const int num, const int pos);
	void AddSwap(const int num, const int pos);
	void Swap(const int old_num, const int old_pos, const int new_num, const int new_pos);
	bool IsCloser(const int num, const int pos);
	bool Has(const int num);
	bool Has(const int num, const int pos);
	int Find(const std::vector<ElemData>& data, const int num);
	const unsigned Size() const;
	bool MatchSize(const unsigned size);
	const int MatchSize(const std::vector<int>& inputSeq) const;
	bool InASequence();
	bool InSequence(const int newPos);

	const std::string PrintSequence();

private:
	bool IsSmaller(const ElemData& data1, const ElemData& data2) const;
	void Sort();
	unsigned _row;
	std::vector<ElemData> _foundNumsList;
	std::vector<ElemData> _foundNumsListSorted;
};

#endif // !SEARCHRESULT_H