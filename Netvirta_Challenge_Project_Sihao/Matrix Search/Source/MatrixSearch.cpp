#include "..\Header\MatrixSearch.h"
#include "..\..\Netvirta_Challenge_Project_Sihao\Header\StringUtils.h"
#include "..\Header\SearchResult.h"
#include <iostream>
#include <chrono>

void MatrixSearch::SearchMatrix(std::string& searchFunc, const EncryptedMatrix& mat, const std::vector<std::string>& inputSeqStrList, const std::string& inputSeqStr, const std::vector<int>&  inputSeq, SearchInput searchInput)
{
	if (searchFunc == "searchSequence")
	{
		//MatrixSearch::SearchSequence(mat, inputSeqStrList, inputSeqStr);
		MatrixSearch::SearchSequenceOptimized(mat, /*inputSeq*/searchInput);
	}
	else if (searchFunc == "searchUnordered")
	{
		//MatrixSearch::SearchUnordered(mat, inputSeq);
		MatrixSearch::SearchUnorderedOptimized(mat, /*inputSeq*/searchInput);
	}
	else if (searchFunc == "searchBestMatch")
	{
		//MatrixSearch::SearchBestMatch(mat, inputSeq);
		MatrixSearch::SearchBestMatchOptimized(mat, /*inputSeq*/searchInput);
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

void MatrixSearch::SearchSequenceOptimized(const EncryptedMatrix& mat, /*const std::vector<int>& inputSeq*/SearchInput inputSeq)
{
	std::vector<int> foundRows;
	std::vector<ElemData> matData = mat.GetSortedMatrixData();

	auto start = std::chrono::system_clock::now();
	// Trivial rejection: stop searching immediately if input sequence is empty
	if (inputSeq.Size() == 0)
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
	if (mat.Col() < inputSeq.Size())
	{
		// To do: Wrap cout string in a function
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		std::cout << "SearchSequence finished at: " << StringUtils::ConvertToMicroseconds(elapsed_seconds.count()) << " microseconds." << std::endl;
		std::cout << "Sequence found in row(s): none." << std::endl;

		return;
	}

	//int elemsSearchedOld = 0;
	//for (unsigned i = 0; i < mat.Row(); ++i)
	//{
	//	int row = i + 1;
	//	SearchResult res(row, inputSeq.Size());
	//	//std::vector<ElemData> rowData = mat.GetSortedMatrixData();
	//	int rowStart = StringUtils::SafeConvertUnsigned(i * mat.Col());
	//	int rowEnd = rowStart + StringUtils::SafeConvertUnsigned(mat.Col()) - 1;
	//	for (unsigned j = 0; j < inputSeq.Size(); ++j)
	//	{
	//		//++elemsSearchedOld;
	//		int currSearchInt = inputSeq[j];
	//		int numCount = inputSeq.GetCount(currSearchInt);
	//		int numExist = BinarySearch(mat.GetOldSortedMatrixData(), rowStart, rowEnd, currSearchInt);
	//		if (numExist != -1)
	//		{
	//			int lowerNumPos = BinarySearchLowerBound(mat.GetOldSortedMatrixData(), rowStart, rowEnd, currSearchInt);
	//			int upperNumPos = BinarySearchUpperBound(mat.GetOldSortedMatrixData(), rowStart, rowEnd, currSearchInt) - 1;

	//			int rowNumCount = (upperNumPos - lowerNumPos) + 1; // + 1 because count is inclusive
	//			// Trivial Rejection: No more need to search further if input sequence contains more repeating
	//			// numbers than exists in the row
	//			if (numCount > rowNumCount)
	//			{
	//				break;
	//			}

	//			for (int i = lowerNumPos; i <= upperNumPos; ++i)
	//			{
	//				//++elemsSearchedOld;
	//				ElemData currNum = mat.GetElemOld(i);
	//				if (res.Has(currNum.Num(), currNum.Pos()) == false && res.InSequence(currNum.Pos()) == true)
	//				{
	//					res.Add(currNum.Num(), currNum.Pos());
	//					break;
	//				}
	//			}
	//		}
	//		// If one number not found means sequence not in the row
	//		else
	//		{
	//			break;
	//		}

	//		int currSize = j + 1;
	//		if (res.MatchSize(currSize) == false)
	//		{
	//			// If size fails to match after searching through the row with a particular number,
	//			// then it means that it won't find the full string, therefore can stop further searching
	//			break;
	//		}
	//	}

	//	// SearchResult size and input size matches, means all numbers have been found
	//	if (res.MatchSize(inputSeq.Size()))
	//	{
	//		// Comment when not testing
	//		//std::cout << "Sequence String found for row " << row << ": " << res.PrintSequence() << std::endl;
	//		foundRows.push_back(row);
	//	}
	//}

	SearchResultList foundList;
	// For debugging
	//int elemsSearched = 0;
	for (unsigned i = 0; i < inputSeq.Size(); ++i)
	{
		//++elemsSearched;
		int matSize = StringUtils::SafeConvertUnsigned(matData.size());
		int lastElem = matSize - 1;

		int currSearchInt = inputSeq[i];
		int numCount = inputSeq.GetCount(currSearchInt);
		int numExist = BinarySearch(matData, 0, matSize, currSearchInt);
		if (numExist != -1)
		{
			int lowerNumPos = BinarySearchLowerBound(matData, 0, lastElem, currSearchInt);
			int upperNumPos = BinarySearchUpperBound(matData, 0, lastElem, currSearchInt) - 1;

			int prevRow = 0;
			bool numAdded = false;
			//for (int r = lowerNumPos; r <= upperNumPos; ++r)
			//{
			//	//++elemsSearched;
			//	ElemData currNum = matData[r];
			//	int currRow = currNum.Row();
			//	// Reset isAdded flag on new row
			//	if (currRow != prevRow)
			//	{
			//		numAdded = false;
			//	}

			//	// Add number only once
			//	if (currNum.Num() == currSearchInt && numAdded == false)
			//	{
			//		numAdded = foundList.Add(i + 1, inputSeq.Size(), currNum);
			//	}

			//	prevRow = currRow;
			//}

			std::vector<std::vector<OrderedElemData>> orderedData = GetOrderedDataByRows(matData, lowerNumPos, upperNumPos);
			std::vector<int> toRemoveList;
			for (unsigned o = 0; o < orderedData.size(); ++o)
			{
				numAdded = false;

				/*int rowNumSize = StringUtils::SafeConvertUnsigned(orderedData[o].size());
				if (rowNumSize < numCount)
				{
					continue;
				}*/

				for (unsigned d = 0; d < orderedData[o].size(); ++d)
				{
					OrderedElemData& currNum = orderedData[o][d];

					// Add number only once
					if (currNum.Data().Num() == currSearchInt && numAdded == false)
					{
						numAdded = foundList.Add(i + 1, inputSeq.Size(), currNum.Data());
						if (numAdded == true)
						{
							toRemoveList.push_back(currNum.Pos());
						}
					}
				}
			}

			int removeStart = toRemoveList.size() - 1;
			if (removeStart > 0)
			{
				for (int r = removeStart; r >= 0; --r)
				{
					matData.erase(matData.begin() + toRemoveList[r]);
				}
			}
		}
		// Trivial Rejection: No matching number in all rows
		else
		{
			break;
		}
	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	//std::cout << "Elements searched (Old): " << elemsSearchedOld << std::endl;
	//std::cout << "Elements searched (New): " << elemsSearched << std::endl;
	std::cout << "SearchSequence finished at: " << StringUtils::ConvertToMicroseconds(elapsed_seconds.count()) << " microseconds." << std::endl;
	//std::cout << "Sequence found in row(s): " << StringUtils::StringList(foundRows, ", ") << std::endl;
	std::cout << "Sequence found in row(s): " << StringUtils::StringList(foundList.GetFoundList(inputSeq.Size()), ", ") << std::endl;
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

void MatrixSearch::SearchUnorderedOptimized(const EncryptedMatrix& mat, /*const std::vector<int>& inputSeq*/SearchInput inputSeq)
{
	std::vector<int> foundRows;

	auto start = std::chrono::system_clock::now();
	// Trivial rejection: stop searching immediately if input sequence is empty
	if (inputSeq.Size() == 0)
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
	if (mat.Col() < inputSeq.Size())
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
		SearchResult res(row, inputSeq.Size());
		//std::vector<ElemData> rowData = mat.GetSortedRowData(i);
		int rowStart = StringUtils::SafeConvertUnsigned(i * mat.Col());
		int rowEnd = rowStart + StringUtils::SafeConvertUnsigned(mat.Col()) - 1;
		for (unsigned j = 0; j < inputSeq.Size(); ++j)
		{
			int currSearchInt = inputSeq[j];
			int numCount = inputSeq.GetCount(currSearchInt);
			//int lastPos = StringUtils::SafeConvertUnsigned(rowData.size() - 1);
			int numExist = BinarySearch(mat.GetOldSortedMatrixData(), rowStart, rowEnd, currSearchInt);
			if (numExist != -1)
			{
				int lowerNumPos = BinarySearchLowerBound(mat.GetOldSortedMatrixData(), rowStart, rowEnd, currSearchInt);
				int upperNumPos = BinarySearchUpperBound(mat.GetOldSortedMatrixData(), rowStart, rowEnd, currSearchInt) - 1;
				int rowNumCount = (upperNumPos - lowerNumPos) + 1; // + 1 because count is inclusive

				// Trivial Rejection: No more need to search further if input sequence contains more repeating
				// numbers than exists in the row
				if (numCount > rowNumCount)
				{
					break;
				}

				for (int i = lowerNumPos; i <= upperNumPos; ++i)
				{
					ElemData currNum = mat.GetElemOld(i);
					if (res.Has(currNum.Num(), currNum.Pos()) == false)
					{
						res.Add(currNum.Num(), currNum.Pos());
						break;
					}
				}
			}
			// If one number not found means sequence not in the row
			else
			{
				break;
			}
		}

		// SearchResult size and input size matches, means all numbers have been found
		if (res.MatchSize())
		{
			// Comment when not testing
			//std::cout << "Sequence String found for row " << row << ": " << res.PrintSequence() << std::endl;
			foundRows.push_back(row);
		}
	}

	//SearchResultList foundList;
	//int matSize = StringUtils::SafeConvertUnsigned(mat.GetSortedMatrixData().size());
	//int lastElem = matSize - 1;
	//for (unsigned i = 0; i < inputSeq.Size(); ++i)
	//{
	//	int currSearchInt = inputSeq[i];
	//	int numCount = inputSeq.GetCount(currSearchInt);
	//	int numExist = BinarySearch(mat.GetSortedMatrixData(), 0, matSize, currSearchInt);
	//	if (numExist != -1)
	//	{
	//		int lowerNumPos = BinarySearchLowerBound(mat.GetSortedMatrixData(), 0, lastElem, currSearchInt);
	//		int upperNumPos = BinarySearchUpperBound(mat.GetSortedMatrixData(), 0, lastElem, currSearchInt) - 1;

	//		int prevRow = 0;
	//		bool numAdded = false;
	//		for (int r = lowerNumPos; r <= upperNumPos; ++r)
	//		{
	//			ElemData currNum = mat[r];
	//			int currRow = currNum.Row();
	//			// Reset isAdded flag on new row
	//			if (currRow != prevRow)
	//			{
	//				numAdded = false;
	//			}

	//			// Add number only once
	//			if (currNum.Num() == currSearchInt && numAdded == false)
	//			{
	//				numAdded = foundList.Add(i + 1, inputSeq.Size(), currNum, false);
	//			}

	//			prevRow = currRow;
	//		}
	//	}
	//	// Trivial Rejection: No matching number in all rows
	//	else
	//	{
	//		break;
	//	}
	//}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << "SearchUnordered finished at: " << StringUtils::ConvertToMicroseconds(elapsed_seconds.count()) << " microseconds." << std::endl;
	std::cout << "Sequence found in row(s): " << StringUtils::StringList(foundRows, ", ") << std::endl;
	//std::cout << "Sequence found in row(s): " << StringUtils::StringList(foundList.GetFoundList(inputSeq.Size()), ", ") << std::endl;
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
		}

		if (bestRow.Size() < res.Size())
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

void MatrixSearch::SearchBestMatchOptimized(const EncryptedMatrix& mat, /*const std::vector<int>& inputSeq*/SearchInput inputSeq)
{
	SearchResult bestRow;

	auto start = std::chrono::system_clock::now();
	// Trivial rejection: stop searching immediately if input sequence is empty
	if (inputSeq.Size() == 0)
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
		SearchResult res(row, inputSeq.Size());
		//std::vector<ElemData> rowData = mat.GetSortedRowData(i);
		int rowStart = StringUtils::SafeConvertUnsigned(i * mat.Col());
		int rowEnd = rowStart + StringUtils::SafeConvertUnsigned(mat.Col()) - 1;
		for (unsigned j = 0; j < inputSeq.Size(); ++j)
		{
			int currSearchInt = inputSeq[j];
			int numCount = inputSeq.GetCount(currSearchInt);
			//int lastPos = StringUtils::SafeConvertUnsigned(rowData.size() - 1);
			int numExist = BinarySearch(mat.GetOldSortedMatrixData(), rowStart, rowEnd, currSearchInt);
			if (numExist != -1)
			{
				int lowerNumPos = BinarySearchLowerBound(mat.GetOldSortedMatrixData(), rowStart, rowEnd, currSearchInt);
				int upperNumPos = BinarySearchUpperBound(mat.GetOldSortedMatrixData(), rowStart, rowEnd, currSearchInt) - 1;
				int rowNumCount = (upperNumPos - lowerNumPos) + 1; // + 1 because count is inclusive

				// Trivial Rejection: No more need to search further if input sequence contains more repeating
				// numbers than exists in the row
				if (numCount > rowNumCount)
				{
					break;
				}

				for (int i = lowerNumPos; i <= upperNumPos; ++i)
				{
					ElemData currNum = mat[i];
					if (res.Has(currNum.Num(), currNum.Pos()) == false)
					{
						res.Add(currNum.Num(), currNum.Pos());
						break;
					}
				}
			}
		}

		if (bestRow.Size() < res.Size())
		{
			// Comment when not testing
			//std::cout << "Current best sequence found: " << res.PrintSequence() << std::endl;
			bestRow = res;
		}

		// Trivial Acceptance: if the best row found is already the entire row, no need to search the other rows anymore
		if (bestRow.Size() == mat.Col())
		{
			break;
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
		int mid = l + ((r - l) >> 1);

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

	int mid = l + ((r - l) >> 1);

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

	int mid = l + ((r - l) >> 1);

	if (data[mid].Num() > x)
	{
		return BinarySearchUpperBound(data, l, mid - 1, x);
	}
	else
	{
		return BinarySearchUpperBound(data, mid + 1, r, x);
	}
}

std::vector<std::vector<OrderedElemData>> MatrixSearch::GetOrderedDataByRows(const std::vector<ElemData>& data, int start, int end)
{
	std::vector<std::vector<OrderedElemData>> orderedData;

	int prevRow = -1;
	for (int i = start; i <= end; ++i)
	{
		//++elemsSearched;
		ElemData currNum = data[i];
		OrderedElemData currData{ i, currNum };
		int currRow = currNum.Row();
		// Reset isAdded flag on new row
		if (currRow != prevRow)
		{
			std::vector<OrderedElemData> rowData;
			orderedData.push_back(rowData);
		}

		if (orderedData.size() == 0)
		{
			break;
		}

		unsigned lastPos = orderedData.size() - 1;
		orderedData[lastPos].push_back(currData);

		prevRow = currRow;
	}

	return orderedData;
}