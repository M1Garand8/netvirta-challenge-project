#include "MatrixSearch.h"
#include "..\Netvirta_Challenge_Project_Sihao\StringUtils.h"
#include "SearchResult.h"
#include <iostream>
#include <chrono>

void MatrixSearch::SearchMatrix(std::string& searchFunc, const EncryptedMatrix& mat, const std::vector<std::string>& inputSeqStrList, const std::string& inputSeqStr, const std::vector<int>&  inputSeq)
{
	if (searchFunc == "searchSequence")
	{
		//MatrixSearch::SearchSequence(mat, inputSeqStrList, inputSeqStr);
		MatrixSearch::SearchSequenceOptimized(mat, inputSeq);
	}
	else if (searchFunc == "searchUnordered")
	{
		//MatrixSearch::SearchUnordered(mat, inputSeq);
		MatrixSearch::SearchUnorderedOptimized(mat, inputSeq);
	}
	else if (searchFunc == "searchBestMatch")
	{
		MatrixSearch::SearchBestMatchOptimized(mat, inputSeq);
	}
	else
	{
		std::cout << "No such search function exist! Valid functions: searchSequence, searchUnordered or searchBestMatch." << std::endl;
	}
}

void MatrixSearch::SearchSequence(const EncryptedMatrix& mat, const std::vector<std::string>& inputSeqStrList, const std::string& inputSeq)
{
	std::vector<int> foundRows;

	auto start = std::chrono::system_clock::now();
	// Trivial rejection: stop searching immediately if input sequence is empty
	if (inputSeqStrList.size() == 0)
	{
		// To do: Wrap cout string in a function
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		std::cout << "SearchSequence finished at: " << StringUtils::ConvertToMicroseconds(elapsed_seconds.count()) << " microseconds." << std::endl;
		std::cout << "Sequence found in row(s): none." << std::endl;

		return;
	}

	// Trivial rejection: if matrix columns are shorter than the sequence to search, then
	// it is impossible to match the sequence
	if (mat.Col() < inputSeqStrList.size())
	{
		// To do: Wrap cout string in a function
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		std::cout << "SearchSequence finished at: " << StringUtils::ConvertToMicroseconds(elapsed_seconds.count()) << " microseconds." << std::endl;
		std::cout << "Sequence found in row(s): none." << std::endl;

		return;
	}

	for (unsigned i = 0; i < mat.Row(); ++i)
	{
		int row = i + 1;
		SearchResult res(row, inputSeq.size());
		std::string rowStr = mat.GetRowString(i);
		std::vector<int> rowData = mat.GetRowData(i);
		for (unsigned j = 0; j < inputSeq.size(); ++j)
		{
			int currSearchInt = inputSeq[j];
			for (unsigned c = 0; c < rowData.size(); ++c)
			{
				int currInt = rowData[c];
				if (currInt == currSearchInt && res.Has(currSearchInt, c) == false && res.InSequence(c))
				{
					res.Add(currSearchInt, c);
				}
			}

			int currSize = j + 1;
			if (res.MatchSize(currSize) == false)
			{
				// If size fails to match after searching through the row with a particular number,
				// then it means that it won't find the full string, therefore can stop further searching
				break;
			}
		}

		// SearchResult size and input size matches, means all numbers have been found
		if (res.MatchSize(inputSeq.size()))
		{
			// Comment when not testing
			//std::cout << "Sequence String found for row " << row << ": " << res.PrintSequence() << std::endl;
			foundRows.push_back(row);
		}
	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << "SearchSequence finished at: " << StringUtils::ConvertToMicroseconds(elapsed_seconds.count()) << " microseconds." << std::endl;
	std::cout << "Sequence found in row(s): " << StringUtils::StringList(foundRows, ", ") << std::endl;
}

void MatrixSearch::SearchSequenceOptimized(const EncryptedMatrix& mat, const std::vector<int>& inputSeq)
{
	std::vector<int> foundRows;

	auto start = std::chrono::system_clock::now();
	// Trivial rejection: stop searching immediately if input sequence is empty
	if (inputSeq.size() == 0)
	{
		// To do: Wrap cout string in a function
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		std::cout << "SearchSequence finished at: " << StringUtils::ConvertToMicroseconds(elapsed_seconds.count()) << " microseconds." << std::endl;
		std::cout << "Sequence found in row(s): none." << std::endl;

		return;
	}

	// Trivial rejection: if matrix columns are shorter than the sequence to search, then
	// it is impossible to match the sequence
	if (mat.Col() < inputSeq.size())
	{
		// To do: Wrap cout string in a function
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		std::cout << "SearchSequence finished at: " << StringUtils::ConvertToMicroseconds(elapsed_seconds.count()) << " microseconds." << std::endl;
		std::cout << "Sequence found in row(s): none." << std::endl;

		return;
	}

	for (unsigned i = 0; i < mat.Row(); ++i)
	{
		int row = i + 1;
		SearchResult res(row, inputSeq.size());
		std::string rowStr = mat.GetRowString(i);
		std::vector<ElemData> rowData = mat.GetSortedRowData(i);
		for (unsigned j = 0; j < inputSeq.size(); ++j)
		{
			int currSearchInt = inputSeq[j];
			/*for (unsigned c = 0; c < rowData.size(); ++c)
			{
				int currInt = rowData[c];
				if (currInt == currSearchInt && res.Has(currSearchInt, c) == false && res.InSequence(c))
				{
					res.Add(currSearchInt, c);
				}
			}*/
			int lastPos = StringUtils::SafeConvertUnsigned(rowData.size() - 1);
			int numExist = BinarySearch(rowData, 0, lastPos, currSearchInt);
			if (numExist != -1)
			{
				int lowerNumPos = BinarySearchLowerBound(rowData, 0, lastPos, currSearchInt);
				int upperNumPos = BinarySearchUpperBound(rowData, 0, lastPos, currSearchInt);

				// If only 1 number found, just check its relative position
				if (lowerNumPos == upperNumPos)
				{
					ElemData num = rowData[lowerNumPos];
					if (res.InSequence(num.Pos()) == true)
					{
						res.Add(num.Num(), num.Pos());
					}
				}
				// Multiple numbers found, have to check position for all
				else
				{
					for (int i = lowerNumPos; i <= upperNumPos; ++i)
					{
						ElemData currNum = rowData[i];
						if (res.InSequence(currNum.Pos()) == true)
						{
							res.Add(currNum.Num(), currNum.Pos());
							break;
						}
					}
				}
			}
			// If one number not found means sequence not in the row
			else
			{
				break;
			}

			int currSize = j + 1;
			if (res.MatchSize(currSize) == false)
			{
				// If size fails to match after searching through the row with a particular number,
				// then it means that it won't find the full string, therefore can stop further searching
				break;
			}
		}

		// SearchResult size and input size matches, means all numbers have been found
		//if (res.MatchSize(inputSeq.size()))
		//{
		//	// Comment when not testing
		//	//std::cout << "Sequence String found for row " << row << ": " << res.PrintSequence() << std::endl;
		//	foundRows.push_back(row);
		//}
	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << "SearchSequence finished at: " << StringUtils::ConvertToMicroseconds(elapsed_seconds.count()) << " microseconds." << std::endl;
	std::cout << "Sequence found in row(s): " << StringUtils::StringList(foundRows, ", ") << std::endl;
}

void MatrixSearch::SearchUnordered(const EncryptedMatrix& mat, const std::vector<int>& inputSeq)
{
	std::vector<int> foundRows;

	auto start = std::chrono::system_clock::now();
	// Trivial rejection: stop searching immediately if input sequence is empty
	if (inputSeq.size() == 0)
	{
		// To do: Wrap cout string in a function
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		std::cout << "SearchUnordered finished at: " << StringUtils::ConvertToMicroseconds(elapsed_seconds.count()) << " microseconds." << std::endl;
		std::cout << "Sequence found in row(s): none." << std::endl;

		return;
	}

	// Trivial rejection: if matrix columns are shorter than the sequence to search, then
	// it is impossible to match the sequence
	if (mat.Col() < inputSeq.size())
	{
		// To do: Wrap cout string in a function
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		std::cout << "SearchUnordered finished at: " << StringUtils::ConvertToMicroseconds(elapsed_seconds.count()) << " microseconds." << std::endl;
		std::cout << "Sequence found in row(s): none."  << std::endl;

		return;
	}
	
	for (unsigned i = 0; i < mat.Row(); ++i)
	{
		int row = i + 1;
		SearchResult res(row, inputSeq.size());
		std::string rowStr = mat.GetRowString(i);
		std::vector<int> rowData = mat.GetRowData(i);
		for (unsigned j = 0; j < inputSeq.size(); ++j)
		{
			int currSearchInt = inputSeq[j];
			for (unsigned c = 0; c < rowData.size(); ++c)
			{
				int currInt = rowData[c];
				if (currInt == currSearchInt && res.Has(currSearchInt, c) == false)
				{
					res.Add(currSearchInt, c);
				}
			}

			int currSize = j + 1;
			if (res.MatchSize(currSize) == false)
			{
				// If size fails to match after searching through the row with a particular number,
				// then it means that it won't find the full string, therefore can stop further searching
				break;
			}
		}

		// SearchResult size and input size matches, means all numbers have been found
		if (res.MatchSize(inputSeq.size()))
		{
			// Comment when not testing
			//std::cout << "Sequence String found for row " << row << ": " << res.PrintSequence() << std::endl;
			foundRows.push_back(row);
		}
	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << "SearchUnordered finished at: " << StringUtils::ConvertToMicroseconds(elapsed_seconds.count()) << " microseconds." << std::endl;
	std::cout << "Sequence found in row(s): " << StringUtils::StringList(foundRows, ", ") << std::endl;
}

void MatrixSearch::SearchUnorderedOptimized(const EncryptedMatrix& mat, const std::vector<int>& inputSeq)
{
	std::vector<int> foundRows;

	auto start = std::chrono::system_clock::now();
	// Trivial rejection: stop searching immediately if input sequence is empty
	if (inputSeq.size() == 0)
	{
		// To do: Wrap cout string in a function
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		std::cout << "SearchUnordered finished at: " << StringUtils::ConvertToMicroseconds(elapsed_seconds.count()) << " microseconds." << std::endl;
		std::cout << "Sequence found in row(s): none." << std::endl;

		return;
	}

	// Trivial rejection: if matrix columns are shorter than the sequence to search, then
	// it is impossible to match the sequence
	if (mat.Col() < inputSeq.size())
	{
		// To do: Wrap cout string in a function
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		std::cout << "SearchUnordered finished at: " << StringUtils::ConvertToMicroseconds(elapsed_seconds.count()) << " microseconds." << std::endl;
		std::cout << "Sequence found in row(s): none." << std::endl;

		return;
	}

	for (unsigned i = 0; i < mat.Row(); ++i)
	{
		int row = i + 1;
		SearchResult res(row, inputSeq.size());
		std::string rowStr = mat.GetRowString(i);
		std::vector<ElemData> rowData = mat.GetSortedRowData(i);
		for (unsigned j = 0; j < inputSeq.size(); ++j)
		{
			int currSearchInt = inputSeq[j];
			int lastPos = StringUtils::SafeConvertUnsigned(rowData.size() - 1);
			int numExist = BinarySearch(rowData, 0, lastPos, currSearchInt);
			if (numExist != -1)
			{
				ElemData num = rowData[numExist];
				res.Add(num.Num(), num.Pos());
			}
			// If one number not found means sequence not in the row
			else
			{
				break;
			}

			//int currSize = j + 1;
			//if (res.MatchSize(currSize) == false)
			//{
			//	// If size fails to match after searching through the row with a particular number,
			//	// then it means that it won't find the full string, therefore can stop further searching
			//	break;
			//}
		}

		// SearchResult size and input size matches, means all numbers have been found
		if (res.MatchSize())
		{
			// Comment when not testing
			//std::cout << "Sequence String found for row " << row << ": " << res.PrintSequence() << std::endl;
			foundRows.push_back(row);
		}
	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << "SearchUnordered finished at: " << StringUtils::ConvertToMicroseconds(elapsed_seconds.count()) << " microseconds." << std::endl;
	std::cout << "Sequence found in row(s): " << StringUtils::StringList(foundRows, ", ") << std::endl;
}

void MatrixSearch::SearchBestMatch(const EncryptedMatrix& mat, const std::vector<int>& inputSeq)
{
	SearchResult bestRow;

	auto start = std::chrono::system_clock::now();
	// Trivial rejection: stop searching immediately if input sequence is empty
	if (inputSeq.size() == 0)
	{
		// To do: Wrap cout string in a function
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		std::cout << "SearchBestMatch finished at: " << StringUtils::ConvertToMicroseconds(elapsed_seconds.count()) << " microseconds." << std::endl;
		std::cout << "Sequence found in row(s): none." << std::endl;

		return;
	}

	for (unsigned i = 0; i < mat.Row(); ++i)
	{
		int row = i + 1;
		SearchResult res(row, inputSeq.size());
		std::string rowStr = mat.GetRowString(i);
		std::vector<int> rowData = mat.GetRowData(i);

		for (unsigned j = 0; j < inputSeq.size(); ++j)
		{
			int currSearchInt = inputSeq[j];
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
			// Comment when not testing
			//std::cout << "Current best sequence found: " << res.PrintSequence() << std::endl;
			bestRow = res;
		}
	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << "SearchBestMatch finished at: " << StringUtils::ConvertToMicroseconds(elapsed_seconds.count()) << " microseconds." << std::endl;
	std::cout << "Sequence found in row: " << bestRow.Row() << std::endl;
}

void MatrixSearch::SearchBestMatchOptimized(const EncryptedMatrix& mat, const std::vector<int>& inputSeq)
{
	SearchResult bestRow;

	auto start = std::chrono::system_clock::now();
	// Trivial rejection: stop searching immediately if input sequence is empty
	if (inputSeq.size() == 0)
	{
		// To do: Wrap cout string in a function
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		std::cout << "SearchBestMatch finished at: " << StringUtils::ConvertToMicroseconds(elapsed_seconds.count()) << " microseconds." << std::endl;
		std::cout << "Sequence found in row(s): none." << std::endl;

		return;
	}

	for (unsigned i = 0; i < mat.Row(); ++i)
	{
		int row = i + 1;
		SearchResult res(row, inputSeq.size());
		std::string rowStr = mat.GetRowString(i);
		std::vector<ElemData> rowData = mat.GetSortedRowData(i);
		for (unsigned j = 0; j < inputSeq.size(); ++j)
		{
			int currSearchInt = inputSeq[j];
			int lastPos = StringUtils::SafeConvertUnsigned(rowData.size() - 1);
			int numExist = BinarySearch(rowData, 0, lastPos, currSearchInt);
			if (numExist != -1)
			{
				ElemData num = rowData[numExist];
				res.Add(num.Num(), num.Pos());
			}
			// If one number not found means sequence not in the row
			else
			{
				break;
			}

			//int currSize = j + 1;
			//if (res.MatchSize(currSize) == false)
			//{
			//	// If size fails to match after searching through the row with a particular number,
			//	// then it means that it won't find the full string, therefore can stop further searching
			//	break;
			//}
		}

		if (bestRow.MatchSize(inputSeq) < res.MatchSize(inputSeq))
		{
			// Comment when not testing
			//std::cout << "Current best sequence found: " << res.PrintSequence() << std::endl;
			bestRow = res;
		}
	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << "SearchBestMatch finished at: " << StringUtils::ConvertToMicroseconds(elapsed_seconds.count()) << " microseconds." << std::endl;
	std::cout << "Sequence found in row: " << bestRow.Row() << std::endl;
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
	if (l >= r)
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