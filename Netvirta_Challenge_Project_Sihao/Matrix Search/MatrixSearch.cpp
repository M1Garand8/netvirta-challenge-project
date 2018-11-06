#include "MatrixSearch.h"
#include "..\Netvirta_Challenge_Project_Sihao\StringUtils.h"
#include "SearchResult.h"
#include <iostream>
#include <chrono>

void MatrixSearch::SearchMatrix(std::string& searchFunc, const EncryptedMatrix& mat, const std::string& inputSeqStr, const std::vector<int>&  inputSeq)
{
	if (searchFunc == "searchSequence")
	{
		MatrixSearch::SearchSequence(mat, inputSeqStr);
	}
	else if (searchFunc == "searchUnordered")
	{
		MatrixSearch::SearchUnordered(mat, inputSeq);
	}
	else if (searchFunc == "searchBestMatch")
	{
		MatrixSearch::SearchBestMatch(mat, inputSeq);
	}
	else
	{
		std::cout << "No such search function exist! Valid functions: searchSequence, searchUnordered or searchBestMatch.\n";
	}
}

void MatrixSearch::SearchSequence(const EncryptedMatrix& mat, const std::string& inputSeq)
{
	std::vector<int> foundRows;

	auto start = std::chrono::system_clock::now();
	// Trivial rejection: if matrix columns are shorter than the sequence to search, then
	// it is impossible to match the sequence
	if (mat.Col() < inputSeq.size())
	{
		// To do: Wrap cout string in a function
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		std::cout << "SearchSequence finished at: " << elapsed_seconds.count() << "\n";
		std::cout << "Sequence found in row(s): " << StringUtils::StringList(foundRows, ", ") << "\n";

		return;
	}

	for (unsigned i = 0; i < mat.Row(); ++i)
	{
		std::string rowStr = mat.GetRowString(i);
		if (rowStr.find(inputSeq) != std::string::npos)
		{
			foundRows.push_back(i + 1);
		}
	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << "SearchSequence finished at: " << elapsed_seconds.count() << "\n";
	std::cout << "Sequence found in row(s): " << StringUtils::StringList(foundRows, ", ") << "\n";
}

void MatrixSearch::SearchSequenceOptimized(const EncryptedMatrix& mat, const std::string& inputSeq)
{
	std::vector<int> foundRows;

	auto start = std::chrono::system_clock::now();
	// Trivial rejection: if matrix columns are shorter than the sequence to search, then
	// it is impossible to match the sequence
	if (mat.Col() < inputSeq.size())
	{
		// To do: Wrap cout string in a function
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		std::cout << "SearchSequence finished at: " << elapsed_seconds.count() << "\n";
		std::cout << "Sequence found in row(s): " << StringUtils::StringList(foundRows, ", ") << "\n";

		return;
	}

	/*for (unsigned i = 0; i < mat.Row(); ++i)
	{
		std::string rowStr = mat.GetRowString(i);
		if (rowStr.find(inputSeq) != std::string::npos)
		{
			foundRows.push_back(i + 1);
		}
	}*/
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << "SearchSequence finished at: " << elapsed_seconds.count() << "\n";
	std::cout << "Sequence found in row(s): " << StringUtils::StringList(foundRows, ", ") << "\n";
}

void MatrixSearch::SearchUnordered(const EncryptedMatrix& mat, const std::vector<int>& inputSeq)
{
	std::vector<int> foundRows;

	auto start = std::chrono::system_clock::now();
	// Trivial rejection: if matrix columns are shorter than the sequence to search, then
	// it is impossible to match the sequence
	if (mat.Col() < inputSeq.size())
	{
		// To do: Wrap cout string in a function
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		std::cout << "SearchSequence finished at: " << elapsed_seconds.count() << "\n";
		std::cout << "Sequence found in row(s): " << StringUtils::StringList(foundRows, ", ") << "\n";

		return;
	}
	
	for (unsigned i = 0; i < mat.Row(); ++i)
	{
		int row = i + 1;
		SearchResult res(row);
		std::string rowStr = mat.GetRowString(i);
		std::vector<int> rowData = mat.GetRowData(i);
		for (unsigned j = 0; j < inputSeq.size(); ++j)
		{
			int currSearchInt = inputSeq[i];
			for (unsigned c = 0; c < rowData.size(); ++c)
			{
				int currInt = rowData[c];
				if (currInt == currSearchInt && res.Has(currSearchInt, c) == false && res.InSequence(c) == true)
				{
					res.Add(currSearchInt, c);
				}
			}
		}

		// SearchResult size and input size matches, means all numbers have been found
		if (res.MatchSize(inputSeq.size() && res.InASequence()))
		{
			foundRows.push_back(row);
		}
	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << "SearchUnordered finished at: " << elapsed_seconds.count() << "\n";
	std::cout << "Sequence found in row(s): " << StringUtils::StringList(foundRows, ", ") << "\n";
}

void MatrixSearch::SearchUnorderedOptimized(const EncryptedMatrix& mat, const std::vector<int>& inputSeq)
{
	std::vector<int> foundRows;

	auto start = std::chrono::system_clock::now();
	// Trivial rejection: if matrix columns are shorter than the sequence to search, then
	// it is impossible to match the sequence
	if (mat.Col() < inputSeq.size())
	{
		// To do: Wrap cout string in a function
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		std::cout << "SearchSequence finished at: " << elapsed_seconds.count() << "\n";
		std::cout << "Sequence found in row(s): " << StringUtils::StringList(foundRows, ", ") << "\n";

		return;
	}

	//for (unsigned i = 0; i < mat.Row(); ++i)
	//{
	//	int row = i + 1;
	//	SearchResult res(row);
	//	std::string rowStr = mat.GetRowString(i);
	//	std::vector<int> rowData = mat.GetRowData(i);
	//	for (unsigned j = 0; j < inputSeq.size(); ++j)
	//	{
	//		int currSearchInt = inputSeq[i];
	//		for (unsigned c = 0; c < rowData.size(); ++c)
	//		{
	//			int currInt = rowData[c];
	//			if (currInt == currSearchInt && res.Has(currSearchInt, c) == false && res.InSequence(c) == true)
	//			{
	//				res.Add(currSearchInt, c);
	//			}
	//		}
	//	}

	//	// SearchResult size and input size matches, means all numbers have been found
	//	if (res.MatchSize(inputSeq.size() && res.InASequence()))
	//	{
	//		foundRows.push_back(row);
	//	}
	//}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << "SearchUnordered finished at: " << elapsed_seconds.count() << "\n";
	std::cout << "Sequence found in row(s): " << StringUtils::StringList(foundRows, ", ") << "\n";
}

void MatrixSearch::SearchBestMatch(const EncryptedMatrix& mat, const std::vector<int>& inputSeq)
{
	SearchResult bestRow;

	auto start = std::chrono::system_clock::now();
	for (unsigned i = 0; i < mat.Row(); ++i)
	{
		int row = i + 1;
		SearchResult res(row);
		std::string rowStr = mat.GetRowString(i);
		std::vector<int> rowData = mat.GetRowData(i);

		for (unsigned j = 0; j < inputSeq.size(); ++j)
		{
			int currSearchInt = inputSeq[i];
			for (unsigned c = 0; c < rowData.size(); ++c)
			{
				int currInt = rowData[c];
				if (currInt == currSearchInt && res.Has(currSearchInt, c) == false && res.InSequence(c) == true)
				{
					res.Add(currSearchInt, c);
				}
			}
		}

		if (bestRow.MatchSize(inputSeq) < res.MatchSize(inputSeq))
		{
			bestRow = res;
		}
	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << "SearchBestMatch finished at: " << elapsed_seconds.count() << "\n";
	std::cout << "Sequence found in row: " << bestRow.Row() << "\n";
}

void MatrixSearch::SearchBestMatchOptimized(const EncryptedMatrix& mat, const std::vector<int>& inputSeq)
{
	SearchResult bestRow;

	auto start = std::chrono::system_clock::now();
	/*for (unsigned i = 0; i < mat.Row(); ++i)
	{
		int row = i + 1;
		SearchResult res(row);
		std::string rowStr = mat.GetRowString(i);
		std::vector<int> rowData = mat.GetRowData(i);

		for (unsigned j = 0; j < inputSeq.size(); ++j)
		{
			int currSearchInt = inputSeq[i];
			for (unsigned c = 0; c < rowData.size(); ++c)
			{
				int currInt = rowData[c];
				if (currInt == currSearchInt && res.Has(currSearchInt, c) == false && res.InSequence(c) == true)
				{
					res.Add(currSearchInt, c);
				}
			}
		}

		if (bestRow.MatchSize(inputSeq) < res.MatchSize(inputSeq))
		{
			bestRow = res;
		}
	}*/
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << "SearchBestMatch finished at: " << elapsed_seconds.count() << "\n";
	std::cout << "Sequence found in row: " << bestRow.Row() << "\n";
}

int MatrixSearch::BinarySearch(const std::vector<ElemData>& data, int l, int r, int x)
{
	if (r >= l)
	{
		int mid = l + (r - l) / 2;

		if (data[mid].Num() == x)
		{
			return mid;
		}

		if (data[mid].Num() > x)
		{
			return BinarySearch(data, l, mid - 1, x);
		}

		return BinarySearch(data, mid + 1, r, x);
	}

	return -1;
}

int MatrixSearch::BinarySearchLowerBound(const std::vector<ElemData>& data, int l, int r, int x)
{
	if (l > r)
	{
		return l;
	}

	int mid = l + (r - l) / 2;

	if (data[mid].Num() >= x)
	{
		return BinarySearchLowerBound(data, l, mid - 1, x);
	}
	else
	{
		return BinarySearchLowerBound(data, mid + 1, r, x);
	}
}

int MatrixSearch::BinarySearchUpperBound(const std::vector<ElemData>& data, int l, int r, int x)
{
	if (l > r)
	{
		return l;
	}

	int mid = l + (r - l) / 2;

	if (data[mid].Num() > x)
	{
		return BinarySearchUpperBound(data, l, mid - 1, x);
	}
	else
	{
		return BinarySearchUpperBound(data, mid + 1, r, x);
	}
}