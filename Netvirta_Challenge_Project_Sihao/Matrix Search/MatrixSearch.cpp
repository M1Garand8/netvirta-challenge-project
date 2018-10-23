#include "MatrixSearch.h"
#include "..\Netvirta_Challenge_Project_Sihao\StringUtils.h"
#include "SearchResult.h"
#include <iostream>
#include <chrono>

void MatrixSearch::SearchSequence(const EncryptedMatrix mat, const std::string inputSeq)
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

void MatrixSearch::SearchUnordered(const EncryptedMatrix mat, const std::vector<int> inputSeq)
{
	std::vector<int> foundRows;

	auto start = std::chrono::system_clock::now();
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
		SearchResult res;
		std::string rowStr = mat.GetRowString(i);
		std::vector<int> rowData = mat.GetRowData(i);
		for (unsigned j = 0; j < inputSeq.size(); ++j)
		{
			int currSearchInt = inputSeq[i];
			for (unsigned c = 0; c < rowData.size(); ++c)
			{
				int currInt = rowData[c];
				if (currInt == currSearchInt && res.Has(currSearchInt, c) == false)
				{
					res.Add(currSearchInt, c);
				}
			}
		}

		// SearchResult size and input size matches, means all numbers have been found
		if (res.MatchSize(inputSeq.size()))
		{
			foundRows.push_back(i + 1);
		}
	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << "SearchUnordered finished at: " << elapsed_seconds.count() << "\n";
	std::cout << "Sequence found in row(s): " << StringUtils::StringList(foundRows, ", ") << "\n";
}

void MatrixSearch::SearchBestMatch(const EncryptedMatrix mat, const std::vector<int> inputSeq)
{

}

bool MatrixSearch::CheckTrue(const std::vector<bool> foundList)
{
	for (unsigned i = 0; i < foundList.size(); ++i)
	{
		if (foundList[i] == false)
		{
			return false;
		}
	}

	return true;
}