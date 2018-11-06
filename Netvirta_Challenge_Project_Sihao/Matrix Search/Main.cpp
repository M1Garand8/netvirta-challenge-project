#include "..\Netvirta_Challenge_Project_Sihao\StringUtils.h"
//#include "..\Netvirta_Challenge_Project_Sihao\EncryptedMatrix.h"
#include "MatrixSearch.h"
#include <iostream>
#include <sstream>
#include <fstream>

int main(int argc, char *argv[])
{
	bool isUseSearchFile = false;
	bool isTestRun = false;
	if (argc < 3)
	{
		std::cout << "Format: Matrix Search.exe <dat file> <search file> OR Matrix Search.exe <dat file> <search function> <seq 1 ... seq n>\n";

		return 0;
	}
	else if (argc == 3)
	{
		// Check if first and second parameters are numbers
		int arg1, arg2;
		if (StringUtils::TryParse(argv[1], arg1) == true || StringUtils::TryParse(argv[2], arg2) == true)
		{
			std::cout << "Format: Matrix Search.exe <dat file> <search file> OR Matrix Search.exe <dat file> <search function> <seq 1 ... seq n>\n";

			return 0;
		}

		std::string testSearchFunc{ argv[2] };

		if (testSearchFunc != "MatrixSearchTest")
		{
			isUseSearchFile = true;
		}
		else
		{
			isTestRun = true;
		}
	}
	else if (argc > 3)
	{
		std::string testSearchFunc{ argv[2] };
		if (testSearchFunc != "searchSequence" && testSearchFunc != "searchUnordered" && testSearchFunc != "searchBestMatch")
		{
			std::cout << "No such search function exist! Valid functions: searchSequence, searchUnordered or searchBestMatch.\n";

			return 0;
		}

		isUseSearchFile = false;
	}

	int isNum = 0;
	if (isTestRun == false && isUseSearchFile == false && StringUtils::TryParse(argv[1], isNum) == false)
	{
		std::string filename{ argv[1] };
		if (StringUtils::CheckFileName(filename, ".dat") == false)
		{
			std::cout << "Matrix data file input is not a .dat file!" << std::endl;

			return 0;
		}
		std::string searchfunc{ argv[2] };

		const EncryptedMatrix mat(filename);
		const std::vector<int> inputSeq = StringUtils::IntParseSearchSequence(argc, argv);
		const std::string inputSeqStr = StringUtils::StrParseSearchSequence(argc, argv);

		MatrixSearch::SearchMatrix(searchfunc, mat, inputSeqStr, inputSeq);
	}
	else if (isTestRun == false && isUseSearchFile == true && StringUtils::TryParse(argv[1], isNum) == false)
	{
		std::string filename{ argv[1] };
		if (StringUtils::CheckFileName(filename, ".dat") == false)
		{
			std::cout << "Matrix data file input is not a .dat file!" << std::endl;

			return 0;
		}
		std::string searchFuncsPath{ argv[2] };
		if (StringUtils::CheckFileName(searchFuncsPath, ".txt") == false)
		{
			std::cout << "Search function file input is not a text file!" << std::endl;

			return 0;
		}

		std::ifstream file;

		file.open(searchFuncsPath, std::ios::in);

		if (file.is_open())
		{
			std::string currLine;
			int i = 0;
			while (std::getline(file, currLine))
			{
				std::vector<std::string> searchStrList = StringUtils::Split(currLine, ' ');

				const EncryptedMatrix mat(filename);
				const std::vector<int> inputSeq = StringUtils::IntParseSearchSequence(searchStrList);
				const std::string inputSeqStr = StringUtils::StrParseSearchSequence(searchStrList);

				MatrixSearch::SearchMatrix(searchStrList[i], mat, inputSeqStr, inputSeq);
			}
		}

		file.close();
	}
	else if (isTestRun == true && isUseSearchFile == false && StringUtils::TryParse(argv[1], isNum) == false)
	{
		std::string searchSeq = "searchSequence";
		std::string searchUnOrd = "searchUnordered";
		std::string searchBM = "searchBestMatch";

		// Test #1: Correctness test, Square Matrix (Row == Col)
		std::cout << "Test #1: Correctness test, Square Matrix (Row == Col)" << std::endl;
		std::string testEvenDataPath{ "even_test_10_10.dat" };
		std::string evenSearchSeqStr{ "1 54 23 4 17 78" }; // To be changed
		std::vector<std::string> evenSearchStrList = StringUtils::Split(evenSearchSeqStr, ' ');


		// Test #2: Correctness test, Non-Square Matrix (Row != Col)
		std::cout << "Test #2: Correctness test, Non-Square Matrix (Row != Col)" << std::endl;
		std::string testUnevenDataPath{ "even_test_10_50.dat" };
		std::string unevenSearchSeqStr{ "1 54 23 4 17 78" }; // To be changed
		std::vector<std::string> unSearchStrList = StringUtils::Split(unevenSearchSeqStr, ' ');


		// Test #3: Performance test (1000 x 1000 matrix)
		std::cout << "Test #3: Performance test (1000 x 1000 matrix)" << std::endl;
		std::string perfTestDataPath1{ "perf_test_100_100.dat" };
		std::string perf1000_1000SearchSeqStr{ "1 54 23 4 17 78" }; // To be changed
		std::vector<std::string> searchStrList = StringUtils::Split(perf1000_1000SearchSeqStr, ' ');

		const EncryptedMatrix mat_1000_1000(perfTestDataPath1);
		/*const std::vector<int> inputSeq = StringUtils::IntParseSearchSequence(searchStrList, false);
		const std::string inputSeqStr = StringUtils::StrParseSearchSequence(searchStrList, false);
		
		MatrixSearch::SearchMatrix(searchSeq, mat_1000_1000, inputSeqStr, inputSeq);
		MatrixSearch::SearchMatrix(searchUnOrd, mat_1000_1000, inputSeqStr, inputSeq);
		MatrixSearch::SearchMatrix(searchBM, mat_1000_1000, inputSeqStr, inputSeq);*/

		// Test #4: Performance test (10000 x 10000 matrix)
		std::cout << "Test #4: Performance test (10000 x 10000 matrix)" << std::endl;
		std::string perfTestDataPath2{ "perf_test_10000_10000.dat" };
		std::string perf10000_10000SearchSeqStr{ "1 54 23 4 17 78" }; // To be changed
		std::vector<std::string> searchStrList = StringUtils::Split(perf10000_10000SearchSeqStr, ' ');

		const EncryptedMatrix mat_10000_10000(perfTestDataPath2);
		/*const std::vector<int> inputSeq = StringUtils::IntParseSearchSequence(searchStrList, false);
		const std::string inputSeqStr = StringUtils::StrParseSearchSequence(searchStrList, false);

		MatrixSearch::SearchMatrix(searchSeq, mat_10000_10000, inputSeqStr, inputSeq);
		MatrixSearch::SearchMatrix(searchUnOrd, mat_10000_10000, inputSeqStr, inputSeq);
		MatrixSearch::SearchMatrix(searchBM, mat_10000_10000, inputSeqStr, inputSeq);*/

		// Test #5: Performance test (1000000 x 1000000 matrix)
		std::cout << "Test #5: Performance test (1000000 x 1000000 matrix)" << std::endl;
		std::string perfTestDataPath2{ "perf_test_1000000_1000000.dat" };
		std::string perf1000000_1000000SearchSeqStr{ "1 54 23 4 17 78" }; // To be changed
		std::vector<std::string> searchStrList = StringUtils::Split(perf1000000_1000000SearchSeqStr, ' ');

		const EncryptedMatrix mat_1000000_1000000(perfTestDataPath2);
		/*const std::vector<int> inputSeq = StringUtils::IntParseSearchSequence(searchStrList, false);
		const std::string inputSeqStr = StringUtils::StrParseSearchSequence(searchStrList, false);

		MatrixSearch::SearchMatrix(searchSeq, mat_1000000_1000000, inputSeqStr, inputSeq);
		MatrixSearch::SearchMatrix(searchUnOrd, mat_1000000_1000000, inputSeqStr, inputSeq);
		MatrixSearch::SearchMatrix(searchBM, mat_1000000_1000000, inputSeqStr, inputSeq);*/
	}

	return 0;
}