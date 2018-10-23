#include "MatrixSearch.h"
#include "..\Netvirta_Challenge_Project_Sihao\StringUtils.h"
#include <iostream>
#include <chrono>

void MatrixSearch::SearchSequence(const EncryptedMatrix mat, const std::string inputSeq)
{
	std::vector<int> foundRows;

	auto start = std::chrono::system_clock::now();
	for (int i = 0; i < mat.Row(); ++i)
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
	for (int i = 0; i < mat.Row(); ++i)
	{
		std::vector<bool> seqFound;
		std::string rowStr = mat.GetRowString(i);
		for (unsigned j = 0; j < inputSeq.size(); ++j)
		{
			// Incomplete, to be finished
			std::string currInt = std::to_string(inputSeq[i]);
			if (rowStr.find(currInt) != std::string::npos)
			{
				seqFound.push_back(true);
			}
			else
			{
				seqFound.push_back(false);
			}
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