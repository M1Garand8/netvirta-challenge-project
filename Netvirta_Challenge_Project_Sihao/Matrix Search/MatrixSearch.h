#ifndef MATRIXSEARCH_H
#define MATRIXSEARCH_H

#include "..\Netvirta_Challenge_Project_Sihao\EncryptedMatrix.h"

class MatrixSearch
{
public:
	static void SearchMatrix(std::string& searchFunc, const EncryptedMatrix& mat, const std::vector<std::string>& inputSeqStrList, const std::string& inputSeqStr, const std::vector<int>&  inputSeq);

private:
	static void SearchSequence(const EncryptedMatrix& mat, const std::vector<std::string>& inputSeqStrList, const std::string& inputSeq);
	static void SearchSequenceOptimized(const EncryptedMatrix& mat, const std::vector<int>& inputSeq);
	static void SearchUnordered(const EncryptedMatrix& mat, const std::vector<int>&  inputSeq);
	static void SearchUnorderedOptimized(const EncryptedMatrix& mat, const std::vector<int>&  inputSeq);
	static void SearchBestMatch(const EncryptedMatrix& mat, const std::vector<int>&  inputSeq);
	static void SearchBestMatchOptimized(const EncryptedMatrix& mat, const std::vector<int>&  inputSeq);
	static int BinarySearch(const std::vector<ElemData>& data, int l, int r, int x);
	static int BinarySearchLowerBound(const std::vector<ElemData>& data, int l, int r, int x);
	static int BinarySearchUpperBound(const std::vector<ElemData>& data, int l, int r, int x);

	MatrixSearch() { }
};

#endif