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
	std::string formatMessage{ "Format: Matrix Search.exe <dat file> <search file> OR Matrix Search.exe <dat file> <search function> <seq 1 ... seq n> OR Matrix Search.exe MatrixSearchTest\n" };

	if (argc < 2)
	{
		std::cout << formatMessage;

		return 0;
	}
	else if (argc == 2)
	{
		// Check if first and second parameters are numbers
		int arg1;
		if (StringUtils::TryParse(argv[1], arg1) == true)
		{
			std::cout << formatMessage;

			return 0;
		}

		std::string testSearchFunc{ argv[1] };

		if (testSearchFunc == "MatrixSearchTest")
		{
			isTestRun = true;
		}
		else
		{
			std::cout << formatMessage;

			return 0;
		}
	}
	else if (argc == 3)
	{
		// Check if first and second parameters are numbers
		int arg1, arg2;
		if (StringUtils::TryParse(argv[1], arg1) == true || StringUtils::TryParse(argv[2], arg2) == true)
		{
			std::cout << formatMessage;

			return 0;
		}

		std::string testSearchFunc{ argv[2] };

		if (StringUtils::CheckFileName(testSearchFunc, ".txt") == true)
		{
			isUseSearchFile = true;
		}
		else
		{
			std::cout << formatMessage;

			return 0;
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
		std::vector<std::string> inputSeqStrList = StringUtils::Split(inputSeqStr, ' ');

		MatrixSearch::SearchMatrix(searchfunc, mat, inputSeqStrList, inputSeqStr, inputSeq);
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
				std::vector<std::string> inputSeqStrList = StringUtils::Split(inputSeqStr, ' ');

				MatrixSearch::SearchMatrix(searchStrList[i], mat, inputSeqStrList, inputSeqStr, inputSeq);
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
		//std::string testEvenDataPath{ "even_test_10_10.dat" };
		std::string testEvenDataPath{ "even_test_10_10_plain.dat" };

		const EncryptedMatrix mat_10_10(testEvenDataPath, false);

		std::string evenSearchSeqStr{ "35 28 20 19 42 63" };
		std::vector<std::string> evenSearchStrList = StringUtils::Split(evenSearchSeqStr, ' ');
		std::vector<int> evenInputSeq = StringUtils::IntParseSearchSequence(evenSearchStrList, false);
		std::string evenInputSeqStr = StringUtils::StrParseSearchSequence(evenSearchStrList, false);

		std::cout << "Test #1a: Correctness test, Square Matrix, Matching Non-full Row" << std::endl;
		std::cout << "Search string: " << evenSearchSeqStr << std::endl;
		std::cout << "SearchSequence search row(s) expected: 7" << std::endl;
		MatrixSearch::SearchMatrix(searchSeq, mat_10_10, evenSearchStrList, evenInputSeqStr, evenInputSeq);
		std::cout << "SearchUnordered search row(s) expected: 7" << std::endl;
		MatrixSearch::SearchMatrix(searchUnOrd, mat_10_10, evenSearchStrList, evenInputSeqStr, evenInputSeq);
		std::cout << "SearchBestMatch search row(s) expected: 7" << std::endl;
		MatrixSearch::SearchMatrix(searchBM, mat_10_10, evenSearchStrList, evenInputSeqStr, evenInputSeq);

		evenSearchSeqStr = "20 42 35 63 28 19";
		evenSearchStrList = StringUtils::Split(evenSearchSeqStr, ' ');
		evenInputSeq = StringUtils::IntParseSearchSequence(evenSearchStrList, false);
		evenInputSeqStr = StringUtils::StrParseSearchSequence(evenSearchStrList, false);

		std::cout << "Test #1b: Correctness test, Square Matrix, Matching Non-Full Row, Swapped Order" << std::endl;
		std::cout << "Search string: " << evenSearchSeqStr << std::endl;
		std::cout << "SearchSequence search row(s) expected: none." << std::endl;
		MatrixSearch::SearchMatrix(searchSeq, mat_10_10, evenSearchStrList, evenInputSeqStr, evenInputSeq);
		std::cout << "SearchUnordered search row(s) expected: 7" << std::endl;
		MatrixSearch::SearchMatrix(searchUnOrd, mat_10_10, evenSearchStrList, evenInputSeqStr, evenInputSeq);
		std::cout << "SearchBestMatch search row(s) expected: 7" << std::endl;
		MatrixSearch::SearchMatrix(searchBM, mat_10_10, evenSearchStrList, evenInputSeqStr, evenInputSeq);
		
		evenSearchSeqStr = "41 37 85 33 79 63 8 60 100 17" ;
		evenSearchStrList = StringUtils::Split(evenSearchSeqStr, ' ');
		evenInputSeq = StringUtils::IntParseSearchSequence(evenSearchStrList, false);
		evenInputSeqStr = StringUtils::StrParseSearchSequence(evenSearchStrList, false);

		std::cout << "Test #1c: Correctness test, Square Matrix, Matching Full Row" << std::endl;
		std::cout << "Search string: " << evenSearchSeqStr << std::endl;
		std::cout << "SearchSequence search row(s) expected: 8" << std::endl;
		MatrixSearch::SearchMatrix(searchSeq, mat_10_10, evenSearchStrList, evenInputSeqStr, evenInputSeq);
		std::cout << "SearchUnordered search row(s) expected: 8" << std::endl;
		MatrixSearch::SearchMatrix(searchUnOrd, mat_10_10, evenSearchStrList, evenInputSeqStr, evenInputSeq);
		std::cout << "SearchBestMatch search row(s) expected: 8" << std::endl;
		MatrixSearch::SearchMatrix(searchBM, mat_10_10, evenSearchStrList, evenInputSeqStr, evenInputSeq);

		evenSearchSeqStr = "33";
		evenSearchStrList = StringUtils::Split(evenSearchSeqStr, ' ');
		evenInputSeq = StringUtils::IntParseSearchSequence(evenSearchStrList, false);
		evenInputSeqStr = StringUtils::StrParseSearchSequence(evenSearchStrList, false);

		std::cout << "Test #1d: Correctness test, Square Matrix, Matching Single Digit" << std::endl;
		std::cout << "Search string: " << evenSearchSeqStr << std::endl;
		std::cout << "SearchSequence search row(s) expected: 1, 2, 3, 8, 9" << std::endl;
		MatrixSearch::SearchMatrix(searchSeq, mat_10_10, evenSearchStrList, evenInputSeqStr, evenInputSeq);
		std::cout << "SearchUnordered search row(s) expected: 1, 2, 3, 8, 9" << std::endl;
		MatrixSearch::SearchMatrix(searchUnOrd, mat_10_10, evenSearchStrList, evenInputSeqStr, evenInputSeq);
		std::cout << "SearchBestMatch search row(s) expected: 1, 2, 3, 8, 9" << std::endl;
		MatrixSearch::SearchMatrix(searchBM, mat_10_10, evenSearchStrList, evenInputSeqStr, evenInputSeq);

		// Test #2: Correctness test, Non-Square Matrix (Row != Col)
		//std::string testUnevenDataPath{ "even_test_10_50.dat" };
		std::string testUnevenDataPath{ "even_test_10_50_plain.dat" };

		const EncryptedMatrix mat_10_50(testUnevenDataPath, false);

		std::string unevenSearchSeqStr{ "56 92 86 26 10 41 39 92 87 10 2 5 17 19 77 76 69 100" };
		std::vector<std::string> unevenSearchStrList = StringUtils::Split(unevenSearchSeqStr, ' ');
		std::vector<int> unevenInputSeq = StringUtils::IntParseSearchSequence(unevenSearchStrList, false);
		std::string unevenInputSeqStr = StringUtils::StrParseSearchSequence(unevenSearchStrList, false);

		std::cout << "Test #2a: Correctness test, Non-Square Matrix, Matching Non-full Row" << std::endl;
		std::cout << "Search string: " << unevenInputSeqStr << std::endl;
		std::cout << "SearchSequence search row(s) expected: 5" << std::endl;
		MatrixSearch::SearchMatrix(searchSeq, mat_10_50, unevenSearchStrList, unevenInputSeqStr, unevenInputSeq);
		std::cout << "SearchUnordered search row(s) expected: 5" << std::endl;
		MatrixSearch::SearchMatrix(searchUnOrd, mat_10_50, unevenSearchStrList, unevenInputSeqStr, unevenInputSeq);
		std::cout << "SearchBestMatch search row(s) expected: 5" << std::endl;
		MatrixSearch::SearchMatrix(searchBM, mat_10_50, unevenSearchStrList, unevenInputSeqStr, unevenInputSeq);

		unevenSearchSeqStr = "15 16 99 81 69 39 24 73 62 50 26 15 20 67 22 58 58 50 25 14 67 34 98 96 27 87 49 83 45 97 87 20 12 92 74 33 81 96 34 9 4 55 25 7 55 73 71 56 27 59" ;
		unevenSearchStrList = StringUtils::Split(unevenSearchSeqStr, ' ');
		unevenInputSeq = StringUtils::IntParseSearchSequence(unevenSearchStrList, false);
		unevenInputSeqStr = StringUtils::StrParseSearchSequence(unevenSearchStrList, false);

		std::cout << "Test #2b: Correctness test, Non-Square Matrix, Matching Full Row" << std::endl;
		std::cout << "Search string: " << unevenInputSeqStr << std::endl;
		std::cout << "SearchSequence search row(s) expected: 10" << std::endl;
		MatrixSearch::SearchMatrix(searchSeq, mat_10_50, unevenSearchStrList, unevenInputSeqStr, unevenInputSeq);
		std::cout << "SearchUnordered search row(s) expected: 10" << std::endl;
		MatrixSearch::SearchMatrix(searchUnOrd, mat_10_50, unevenSearchStrList, unevenInputSeqStr, unevenInputSeq);
		std::cout << "SearchBestMatch search row(s) expected: 10" << std::endl;
		MatrixSearch::SearchMatrix(searchBM, mat_10_50, unevenSearchStrList, unevenInputSeqStr, unevenInputSeq);

		unevenSearchSeqStr = "90";
		unevenSearchStrList = StringUtils::Split(unevenSearchSeqStr, ' ');
		unevenInputSeq = StringUtils::IntParseSearchSequence(unevenSearchStrList, false);
		unevenInputSeqStr = StringUtils::StrParseSearchSequence(unevenSearchStrList, false);

		std::cout << "Test #2c: Correctness test, Non-Square Matrix, Matching Single Digit, Repeated" << std::endl;
		std::cout << "Search string: " << unevenInputSeqStr << std::endl;
		std::cout << "SearchSequence search row(s) expected: 3, 4, 6, 8" << std::endl;
		MatrixSearch::SearchMatrix(searchSeq, mat_10_50, unevenSearchStrList, unevenInputSeqStr, unevenInputSeq);
		std::cout << "SearchUnordered search row(s) expected: 3, 4, 6, 8" << std::endl;
		MatrixSearch::SearchMatrix(searchUnOrd, mat_10_50, unevenSearchStrList, unevenInputSeqStr, unevenInputSeq);
		std::cout << "SearchBestMatch search row(s) expected: 3, 4, 6, 8" << std::endl;
		MatrixSearch::SearchMatrix(searchBM, mat_10_50, unevenSearchStrList, unevenInputSeqStr, unevenInputSeq);

		// Test #3: Performance test (1000 x 1000 matrix)
		//std::string perf1000_1000TestDataPath{ "perf_test_1000_1000.dat" };
		std::string perf1000_1000TestDataPath{ "perf_test_1000_1000_plain.dat" };

		const EncryptedMatrix mat_1000_1000(perf1000_1000TestDataPath, false);

		std::string perf1000_1000SearchSeqStr{ "42 47 31 8 52 99 32 22 72 90 73 2 97 27 66 84 40 89 8 100 84 40 20 19 8 29 25 91 80 98 60 40 74 53 5 40 76 68 85 72 9 53 14 35 60 67 31 50 57 20 45 57 99 48 17 38 8 95 6 15 39 86 5 76 40 76 95 13 11 42 12 65 30 63 38 40 48 46 55 62 26 56 51 24 25 87 95 34 64 55 10 22 31" };
		std::vector<std::string> perf1000_1000SearchStrList = StringUtils::Split(perf1000_1000SearchSeqStr, ' ');
		const std::vector<int> perf1000_1000InputSeq = StringUtils::IntParseSearchSequence(perf1000_1000SearchStrList, false);
		const std::string perf1000_1000InputSeqStr = StringUtils::StrParseSearchSequence(perf1000_1000SearchStrList, false);

		std::cout << "Test #3: Performance test (1000 x 1000 matrix)" << std::endl;
		std::cout << "Search string: " << perf1000_1000InputSeqStr << std::endl;
		std::cout << "SearchSequence search row(s) expected: 16" << std::endl;
		MatrixSearch::SearchMatrix(searchSeq, mat_1000_1000, perf1000_1000SearchStrList, perf1000_1000InputSeqStr, perf1000_1000InputSeq);
		std::cout << "SearchUnordered search row(s) expected: Entire matrix" << std::endl;
		MatrixSearch::SearchMatrix(searchUnOrd, mat_1000_1000, perf1000_1000SearchStrList, perf1000_1000InputSeqStr, perf1000_1000InputSeq);
		std::cout << "SearchBestMatch search row(s) expected: 16" << std::endl;
		MatrixSearch::SearchMatrix(searchBM, mat_1000_1000, perf1000_1000SearchStrList, perf1000_1000InputSeqStr, perf1000_1000InputSeq);

		// Test #4: Performance test (10000 x 10000 matrix) *Not enough memory to generate
		//std::cout << "Test #4: Performance test (10000 x 10000 matrix)" << std::endl;
		//std::string perf10000_10000TestDataPath{ "perf_test_10000_10000.dat" };
		//std::string perf10000_10000SearchSeqStr{ "1 54 23 4 17 78" }; // To be changed
		//std::vector<std::string> perf10000_10000SearchStrList = StringUtils::Split(perf10000_10000SearchSeqStr, ' ');

		//const EncryptedMatrix mat_10000_10000(perf10000_10000TestDataPath);
		//const std::vector<int> perf10000_10000InputSeq = StringUtils::IntParseSearchSequence(perf10000_10000SearchStrList, false);
		//const std::string perf10000_10000InputSeqStr = StringUtils::StrParseSearchSequence(perf10000_10000SearchStrList, false);

		//MatrixSearch::SearchMatrix(searchSeq, mat_10000_10000, perf10000_10000SearchStrList, perf10000_10000InputSeqStr, perf10000_10000InputSeq);
		//MatrixSearch::SearchMatrix(searchUnOrd, mat_10000_10000, perf10000_10000SearchStrList, perf10000_10000InputSeqStr, perf10000_10000InputSeq);
		//MatrixSearch::SearchMatrix(searchBM, mat_10000_10000, perf10000_10000SearchStrList, perf10000_10000InputSeqStr, perf10000_10000InputSeq);
	}

	return 0;
}