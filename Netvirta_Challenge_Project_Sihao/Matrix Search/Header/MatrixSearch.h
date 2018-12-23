#ifndef MATRIXSEARCH_H
#define MATRIXSEARCH_H

#include "../../Netvirta_Challenge_Project_Sihao/Header/EncryptedMatrix.h"
#include "SearchResult.h"
#include <string>

enum SearchType
{
	SEQUENCE,
	UNORDERED,
	BEST_MATCH
};

class MatrixSearch
{
public:
	static int SearchMatrix(std::string& searchFunc, const EncryptedMatrix& mat, SearchInput& searchInput, bool printMessages = true);

private:
	static int SearchSequenceOptimized(const EncryptedMatrix& mat, SearchInput& inputSeq, bool printMessages);
	static int SearchUnorderedOptimized(const EncryptedMatrix& mat, SearchInput& inputSeq, bool printMessages);
	static int SearchBestMatchOptimized(const EncryptedMatrix& mat, SearchInput& inputSeq, bool printMessages);
	static int BinarySearch(const std::vector<ElemData>& data, int l, int r, int x);
	static int BinarySearchLowerBound(const std::vector<ElemData>& data, int l, int r, int x);
	static int BinarySearchUpperBound(const std::vector<ElemData>& data, int l, int r, int x);
	static std::string GetSearchResult(SearchType searchType, const std::vector<ElemData>& data, SearchInput& searchInput, const unsigned rowSize);

	MatrixSearch() { }
};

#endif