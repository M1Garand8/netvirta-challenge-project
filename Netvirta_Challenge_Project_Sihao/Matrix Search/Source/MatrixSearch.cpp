#include "../Header/MatrixSearch.h"
#include "../../Netvirta_Challenge_Project_Sihao/Header/StringUtils.h"
#include "../Header/SearchResult.h"
#include <iostream>
#include <chrono>
#include <map>

int MatrixSearch::SearchMatrix(std::string& searchFunc, const EncryptedMatrix& mat, SearchInput& searchInput, bool naive, bool printMessages)
{
	if (searchFunc == "searchSequence")
	{
		return naive == false ? MatrixSearch::SearchSequenceOptimized(mat, searchInput, printMessages) : MatrixSearch::SearchSequence(mat, searchInput, printMessages);
	}
	else if (searchFunc == "searchUnordered")
	{
		return  naive == false ? MatrixSearch::SearchUnorderedOptimized(mat, searchInput, printMessages) : MatrixSearch::SearchUnordered(mat, searchInput, printMessages);
	}
	else if (searchFunc == "searchBestMatch")
	{
		return  naive == false ? MatrixSearch::SearchBestMatchOptimized(mat, searchInput, printMessages) : MatrixSearch::SearchBestMatch(mat, searchInput, printMessages);
	}
	else
	{
		std::cout << "No such search function exist! Valid functions: searchSequence, searchUnordered or searchBestMatch." << std::endl;

		return 0;
	}
}

int MatrixSearch::SearchSequence(const EncryptedMatrix& mat, SearchInput& inputSeq, bool printMessages)
{
	std::vector<int> foundRows;

	auto start = std::chrono::system_clock::now();
	// Trivial rejection: stop searching immediately if input sequence is empty
	if (inputSeq.Size() == 0)
	{
		// To do: Wrap cout string in a function
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		int elapsed_microseconds = StringUtils::ConvertToMicroseconds(elapsed_seconds.count());

		if (printMessages == true)
		{
			std::cout << "SearchSequence finished at: " << elapsed_microseconds << " microseconds." << std::endl;
			std::cout << "Sequence found in row(s): none." << std::endl;
		}

		return elapsed_microseconds;
	}

	// Trivial rejection: if matrix columns are shorter than the sequence to search, then
	// it is impossible to match the sequence
	if (mat.Col() < inputSeq.Size())
	{
		// To do: Wrap cout string in a function
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		int elapsed_microseconds = StringUtils::ConvertToMicroseconds(elapsed_seconds.count());

		if (printMessages == true)
		{
			std::cout << "SearchSequence finished at: " << elapsed_microseconds << " microseconds." << std::endl;
			std::cout << "Sequence found in row(s): none." << std::endl;
		}

		return elapsed_microseconds;
	}

	std::vector<ElemData> foundElems;
	for (unsigned i = 0; i < mat.Row(); ++i)
	{
		int row = i + 1;
		std::vector<int> rowData = mat.GetRowData(i);
		for (unsigned j = 0; j < inputSeq.Size(); ++j)
		{
			int currSearchInt = inputSeq[j];
			for (unsigned c = 0; c < rowData.size(); ++c)
			{
				int currInt = rowData[c];
				if (currInt == currSearchInt)
				{
					int pos = StringUtils::SafeConvertUnsigned((i * mat.Col()) + c);
					ElemData newData{ currInt, pos };

					foundElems.push_back(newData);
				}
			}
		}
	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	int elapsed_microseconds = StringUtils::ConvertToMicroseconds(elapsed_seconds.count());

	if (printMessages == true)
	{
		std::cout << "SearchSequence finished at: " << elapsed_microseconds << " microseconds." << std::endl;
		std::cout << "Sequence found in row(s): " << GetSearchResult(SearchType::SEQUENCE, foundElems, inputSeq, mat.Col()) << std::endl;
	}

	return elapsed_microseconds;
}

int MatrixSearch::SearchSequenceOptimized(const EncryptedMatrix& mat, SearchInput& inputSeq, bool printMessages)
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

		int elapsed_microseconds = StringUtils::ConvertToMicroseconds(elapsed_seconds.count());

		if (printMessages == true)
		{
			std::cout << "SearchSequence finished at: " << elapsed_microseconds << " microseconds." << std::endl;
			std::cout << "Sequence found in row(s): none." << std::endl;
		}

		return elapsed_microseconds;
	}

	// Trivial rejection: if matrix columns are shorter than the sequence to search, then
	// it is impossible to match the sequence
	if (mat.Col() < inputSeq.Size())
	{
		// To do: Wrap cout string in a function
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		int elapsed_microseconds = StringUtils::ConvertToMicroseconds(elapsed_seconds.count());

		if (printMessages == true)
		{
			std::cout << "SearchSequence finished at: " << elapsed_microseconds << " microseconds." << std::endl;
			std::cout << "Sequence found in row(s): none." << std::endl;
		}

		return elapsed_microseconds;
	}

	std::vector<ElemData> foundElems;
	for (auto inputSeqEntry : inputSeq.GetSequenceCount())
	{
		int matSize = StringUtils::SafeConvertUnsigned(matData.size());
		int lastElem = matSize - 1;

		int currSearchInt = inputSeqEntry.first;
		int numExist = BinarySearch(matData, 0, matSize, currSearchInt);
		if (numExist != -1)
		{
			int lowerNumPos = BinarySearchLowerBound(matData, 0, lastElem, currSearchInt);
			int upperNumPos = BinarySearchUpperBound(matData, 0, lastElem, currSearchInt) - 1;

			int prevRow = 0;
			bool numAdded = false;
			for (int r = lowerNumPos; r <= upperNumPos; ++r)
			{
				foundElems.push_back(matData[r]);
			}
		}
		// Stop searching if one of the input number cannot be found.
		else
		{
			break;
		}
	}

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	int elapsed_microseconds = StringUtils::ConvertToMicroseconds(elapsed_seconds.count());

	if (printMessages == true)
	{
		std::cout << "SearchSequence finished at: " << elapsed_microseconds << " microseconds." << std::endl;
		std::cout << "Sequence found in row(s): " << GetSearchResult(SearchType::SEQUENCE, foundElems, inputSeq, mat.Col()) << std::endl;
	}

	return elapsed_microseconds;
}

int MatrixSearch::SearchUnordered(const EncryptedMatrix& mat, SearchInput& inputSeq, bool printMessages)
{
	std::vector<int> foundRows;

	auto start = std::chrono::system_clock::now();
	// Trivial rejection: stop searching immediately if input sequence is empty
	if (inputSeq.Size() == 0)
	{
		// To do: Wrap cout string in a function
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		int elapsed_microseconds = StringUtils::ConvertToMicroseconds(elapsed_seconds.count());

		if (printMessages == true)
		{
			std::cout << "SearchUnordered finished at: " << elapsed_microseconds << " microseconds." << std::endl;
			std::cout << "Sequence found in row(s): none." << std::endl;
		}

		return elapsed_microseconds;
	}

	// Trivial rejection: if matrix columns are shorter than the sequence to search, then
	// it is impossible to match the sequence
	if (mat.Col() < inputSeq.Size())
	{
		// To do: Wrap cout string in a function
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		int elapsed_microseconds = StringUtils::ConvertToMicroseconds(elapsed_seconds.count());

		if (printMessages == true)
		{
			std::cout << "SearchUnordered finished at: " << elapsed_microseconds << " microseconds." << std::endl;
			std::cout << "Sequence found in row(s): none." << std::endl;
		}

		return elapsed_microseconds;
	}

	std::vector<ElemData> foundElems;
	for (unsigned i = 0; i < mat.Row(); ++i)
	{
		int row = i + 1;
		std::vector<int> rowData = mat.GetRowData(i);
		for (unsigned j = 0; j < inputSeq.Size(); ++j)
		{
			int currSearchInt = inputSeq[j];
			for (unsigned c = 0; c < rowData.size(); ++c)
			{
				int currInt = rowData[c];
				if (currInt == currSearchInt)
				{
					int pos = StringUtils::SafeConvertUnsigned((i * mat.Col()) + c);
					ElemData newData{ currInt, pos };

					foundElems.push_back(newData);
				}
			}
		}
	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	int elapsed_microseconds = StringUtils::ConvertToMicroseconds(elapsed_seconds.count());

	if (printMessages == true)
	{
		std::cout << "SearchUnordered finished at: " << elapsed_microseconds << " microseconds." << std::endl;
		std::cout << "Sequence found in row(s): " << GetSearchResult(SearchType::UNORDERED, foundElems, inputSeq, mat.Col()) << std::endl;
	}

	return elapsed_microseconds;
}

int MatrixSearch::SearchUnorderedOptimized(const EncryptedMatrix& mat, SearchInput& inputSeq, bool printMessages)
{
	//std::vector<int> foundRows;
	std::vector<ElemData> matData = mat.GetSortedMatrixData();
	const std::unordered_map<int, int>& inputSequenceCount = inputSeq.GetSequenceCount();

	auto start = std::chrono::system_clock::now();
	// Trivial rejection: stop searching immediately if input sequence is empty
	if (inputSeq.Size() == 0)
	{
		// To do: Wrap cout string in a function
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		int elapsed_microseconds = StringUtils::ConvertToMicroseconds(elapsed_seconds.count());

		if (printMessages == true)
		{
			std::cout << "SearchUnordered finished at: " << elapsed_microseconds << " microseconds." << std::endl;
			std::cout << "Sequence found in row(s): none." << std::endl;
		}

		return elapsed_microseconds;
	}

	// Trivial rejection: if matrix columns are shorter than the sequence to search, then
	// it is impossible to match the sequence
	if (mat.Col() < inputSeq.Size())
	{
		// To do: Wrap cout string in a function
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		int elapsed_microseconds = StringUtils::ConvertToMicroseconds(elapsed_seconds.count());

		if (printMessages == true)
		{
			std::cout << "SearchUnordered finished at: " << elapsed_microseconds << " microseconds." << std::endl;
			std::cout << "Sequence found in row(s): none." << std::endl;
		}

		return elapsed_microseconds;
	}

	std::vector<ElemData> foundElems;
	for (auto inputSeqEntry : inputSeq.GetSequenceCount())
	{
		int matSize = StringUtils::SafeConvertUnsigned(matData.size());
		int lastElem = matSize - 1;

		int currSearchInt = inputSeqEntry.first;
		int numExist = BinarySearch(matData, 0, matSize, currSearchInt);
		if (numExist != -1)
		{
			int lowerNumPos = BinarySearchLowerBound(matData, 0, lastElem, currSearchInt);
			int upperNumPos = BinarySearchUpperBound(matData, 0, lastElem, currSearchInt) - 1;

			int prevRow = 0;
			bool numAdded = false;
			for (int r = lowerNumPos; r <= upperNumPos; ++r)
			{
				foundElems.push_back(matData[r]);
			}
		}
		// Stop searching if one of the input number cannot be found.
		else
		{
			break;
		}
	}

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	int elapsed_microseconds = StringUtils::ConvertToMicroseconds(elapsed_seconds.count());

	if (printMessages == true)
	{
		std::cout << "SearchUnordered finished at: " << elapsed_microseconds << " microseconds." << std::endl;
		std::cout << "Sequence found in row(s): " << GetSearchResult(SearchType::UNORDERED, foundElems, inputSeq, mat.Col()) << std::endl;
	}

	return elapsed_microseconds;
}

int MatrixSearch::SearchBestMatch(const EncryptedMatrix& mat, SearchInput& inputSeq, bool printMessages)
{
	SearchResult bestRow;

	auto start = std::chrono::system_clock::now();
	// Trivial rejection: stop searching immediately if input sequence is empty
	if (inputSeq.Size() == 0)
	{
		// To do: Wrap cout string in a function
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		int elapsed_microseconds = StringUtils::ConvertToMicroseconds(elapsed_seconds.count());

		if (printMessages == true)
		{
			std::cout << "SearchBestMatch finished at: " << elapsed_microseconds << " microseconds." << std::endl;
			std::cout << "Sequence found in row(s): none." << std::endl;
		}

		return elapsed_microseconds;
	}

	std::vector<ElemData> foundElems;
	for (unsigned i = 0; i < mat.Row(); ++i)
	{
		int row = i + 1;
		std::vector<int> rowData = mat.GetRowData(i);

		for (unsigned j = 0; j < inputSeq.Size(); ++j)
		{
			int currSearchInt = inputSeq[j];
			for (unsigned c = 0; c < rowData.size(); ++c)
			{
				int currInt = rowData[c];
				if (currInt == currSearchInt)
				{
					int pos = StringUtils::SafeConvertUnsigned((i * mat.Col()) + c);
					ElemData newData{ currInt, pos };

					foundElems.push_back(newData);
				}
			}
		}
	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	int elapsed_microseconds = StringUtils::ConvertToMicroseconds(elapsed_seconds.count());

	if (printMessages == true)
	{
		std::cout << "SearchBestMatch finished at: " << elapsed_microseconds << " microseconds." << std::endl;
		std::cout << "Sequence found in row(s): " << GetSearchResult(SearchType::BEST_MATCH, foundElems, inputSeq, mat.Col()) << std::endl;
	}

	return elapsed_microseconds;
}

int MatrixSearch::SearchBestMatchOptimized(const EncryptedMatrix& mat, SearchInput& inputSeq, bool printMessages)
{
	SearchResult bestRow;
	std::vector<ElemData> matData = mat.GetSortedMatrixData();

	auto start = std::chrono::system_clock::now();
	// Trivial rejection: stop searching immediately if input sequence is empty
	if (inputSeq.Size() == 0)
	{
		// To do: Wrap cout string in a function
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		int elapsed_microseconds = StringUtils::ConvertToMicroseconds(elapsed_seconds.count());

		if (printMessages == true)
		{
			std::cout << "SearchBestMatch finished at: " << elapsed_microseconds << " microseconds." << std::endl;
			std::cout << "Sequence found in row(s): none." << std::endl;
		}

		return elapsed_microseconds;
	}
		
	std::vector<ElemData> foundElems;
	for (auto inputSeqEntry : inputSeq.GetSequenceCount())
	{
		int matSize = StringUtils::SafeConvertUnsigned(matData.size());
		int lastElem = matSize - 1;

		int currSearchInt = inputSeqEntry.first;
		int numExist = BinarySearch(matData, 0, matSize, currSearchInt);
		if (numExist != -1)
		{
			int lowerNumPos = BinarySearchLowerBound(matData, 0, lastElem, currSearchInt);
			int upperNumPos = BinarySearchUpperBound(matData, 0, lastElem, currSearchInt) - 1;

			int prevRow = 0;
			bool numAdded = false;
			for (int r = lowerNumPos; r <= upperNumPos; ++r)
			{
				foundElems.push_back(matData[r]);
			}
		}
	}

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	int elapsed_microseconds = StringUtils::ConvertToMicroseconds(elapsed_seconds.count());

	if (printMessages == true)
	{
		std::cout << "SearchBestMatch finished at: " << elapsed_microseconds << " microseconds." << std::endl;
		//std::cout << "Sequence found in row: " << bestRow.Row() << std::endl;
		std::cout << "Sequence found in row: " << GetSearchResult(SearchType::BEST_MATCH, foundElems, inputSeq, mat.Col()) << std::endl;
	}

	return elapsed_microseconds;
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

std::string MatrixSearch::GetSearchResult(SearchType searchType, const std::vector<ElemData>& data, SearchInput& searchInput, const unsigned rowSize)
{
	std::map<int, std::map<int, std::vector<ElemData>>> resultMap;

	for (unsigned i = 0; i < data.size(); ++i)
	{
		ElemData currData = data[i];
		int row = (currData.Pos() / rowSize) + 1;
		if (resultMap.find(row) == resultMap.end())
		{
			std::map<int, std::vector<ElemData>> newResNumMap;
			resultMap.insert(std::pair<int, std::map<int, std::vector<ElemData>>>(row, newResNumMap));
		}

		if (resultMap[row].find(currData.Num()) == resultMap[row].end())
		{
			std::vector<ElemData> newResList;
			resultMap[row].insert(std::pair<int, std::vector<ElemData>>(currData.Num(), newResList));
		}

		resultMap[row][currData.Num()].push_back(currData);
	}

	std::vector<int> foundRows;
	std::vector<SearchResult> bestRowRes;
	switch (searchType)
	{
	case SEQUENCE:
		for (auto entry : resultMap)
		{
			SearchResult res;
			for (unsigned i = 0; i < searchInput.Size(); ++i)
			{
				int currSearchInt = searchInput[i];
				if (entry.second.find(currSearchInt) != entry.second.end())
				{
					for (unsigned p = 0; p < entry.second[currSearchInt].size(); ++p)
					{
						ElemData currData = entry.second[currSearchInt][p];
						if (res.Has(currData.Num(), currData.Pos()) == false && res.InSequence(currData.Pos()))
						{
							res.Add(currData);
							break;
						}
					}
				}
				// Go to next entry if one number not found
				else
				{
					break;
				}
			}

			// SearchResult size and input size matches, means all numbers have been found
			if (res.MatchSize(searchInput.Size()) == true)
			{
				foundRows.push_back(entry.first);
			}
		}
		break;
	case UNORDERED:
		for (auto entry : resultMap)
		{
			SearchResult res;
			for (unsigned i = 0; i < searchInput.Size(); ++i)
			{
				int currSearchInt = searchInput[i];
				if (entry.second.find(currSearchInt) != entry.second.end())
				{
					for (unsigned p = 0; p < entry.second[currSearchInt].size(); ++p)
					{
						ElemData currData = entry.second[currSearchInt][p];
						if (res.Has(currData.Num(), currData.Pos()) == false)
						{
							res.Add(currData);
							break;
						}
					}
				}
				// Go to next entry if one number not found
				else
				{
					break;
				}
			}

			// SearchResult size and input size matches, means all numbers have been found
			if (res.MatchSize(searchInput.Size()) == true)
			{
				foundRows.push_back(entry.first);
			}
		}
		break;
	case BEST_MATCH:
		for (auto entry : resultMap)
		{
			SearchResult res;
			for (unsigned i = 0; i < searchInput.Size(); ++i)
			{
				int currSearchInt = searchInput[i];
				if (entry.second.find(currSearchInt) != entry.second.end())
				{
					for (unsigned p = 0; p < entry.second[currSearchInt].size(); ++p)
					{
						ElemData currData = entry.second[currSearchInt][p];
						if (res.Has(currData.Num(), currData.Pos()) == false)
						{
							res.Add(currData);
							break;
						}
					}
				}
			}

			// If first best match found
			if (bestRowRes.size() == 0)
			{
				foundRows.push_back(entry.first);
				bestRowRes.push_back(res);
			}
			// Update the current best match entry if better match found
			else
			{
				if (bestRowRes[0].Size() < res.Size())
				{
					foundRows[0] = entry.first;
					bestRowRes[0] = res;
				}
			}
		}
		break;
	}

	return StringUtils::StringList(foundRows, ", ");
}