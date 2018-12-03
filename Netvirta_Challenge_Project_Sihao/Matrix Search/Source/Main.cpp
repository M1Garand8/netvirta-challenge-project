#include "../../Netvirta_Challenge_Project_Sihao/Header/StringUtils.h"
//#include "../../Netvirta_Challenge_Project_Sihao/Header/EncryptedMatrix.h"
#include "../Header/MatrixSearch.h"
#include "../Header/SearchResult.h"
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
		SearchInput searchInput{ inputSeqStrList };

		MatrixSearch::SearchMatrix(searchfunc, mat, inputSeqStrList, inputSeqStr, inputSeq, searchInput);
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
				SearchInput searchInput{ inputSeqStrList };

				MatrixSearch::SearchMatrix(searchStrList[i], mat, inputSeqStrList, inputSeqStr, inputSeq, searchInput);
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
		SearchInput evenSrcInput{ evenSearchStrList, false };

		std::cout << "Test #1a: Correctness test, Square Matrix, Matching Non-full Row" << std::endl;
		std::cout << "Search string: " << evenSearchSeqStr << std::endl;
		std::cout << "SearchSequence search row(s) expected: 7" << std::endl;
		MatrixSearch::SearchMatrix(searchSeq, mat_10_10, evenSearchStrList, evenInputSeqStr, evenInputSeq, evenSrcInput);
		std::cout << "SearchUnordered search row(s) expected: 7" << std::endl;
		MatrixSearch::SearchMatrix(searchUnOrd, mat_10_10, evenSearchStrList, evenInputSeqStr, evenInputSeq, evenSrcInput);
		std::cout << "SearchBestMatch search row expected: 7" << std::endl;
		MatrixSearch::SearchMatrix(searchBM, mat_10_10, evenSearchStrList, evenInputSeqStr, evenInputSeq, evenSrcInput);

		evenSearchSeqStr = "20 42 35 63 28 19";
		evenSearchStrList = StringUtils::Split(evenSearchSeqStr, ' ');
		evenInputSeq = StringUtils::IntParseSearchSequence(evenSearchStrList, false);
		evenInputSeqStr = StringUtils::StrParseSearchSequence(evenSearchStrList, false);
		evenSrcInput.Update(evenSearchStrList, false);

		std::cout << "Test #1b: Correctness test, Square Matrix, Matching Non-Full Row, Swapped Order" << std::endl;
		std::cout << "Search string: " << evenSearchSeqStr << std::endl;
		std::cout << "SearchSequence search row(s) expected: none." << std::endl;
		MatrixSearch::SearchMatrix(searchSeq, mat_10_10, evenSearchStrList, evenInputSeqStr, evenInputSeq, evenSrcInput);
		std::cout << "SearchUnordered search row(s) expected: 7" << std::endl;
		MatrixSearch::SearchMatrix(searchUnOrd, mat_10_10, evenSearchStrList, evenInputSeqStr, evenInputSeq, evenSrcInput);
		std::cout << "SearchBestMatch search row expected: 7" << std::endl;
		MatrixSearch::SearchMatrix(searchBM, mat_10_10, evenSearchStrList, evenInputSeqStr, evenInputSeq, evenSrcInput);
		
		evenSearchSeqStr = "41 37 85 33 79 63 8 60 100 17" ;
		evenSearchStrList = StringUtils::Split(evenSearchSeqStr, ' ');
		evenInputSeq = StringUtils::IntParseSearchSequence(evenSearchStrList, false);
		evenInputSeqStr = StringUtils::StrParseSearchSequence(evenSearchStrList, false);
		evenSrcInput.Update(evenSearchStrList, false);

		std::cout << "Test #1c: Correctness test, Square Matrix, Matching Full Row" << std::endl;
		std::cout << "Search string: " << evenSearchSeqStr << std::endl;
		std::cout << "SearchSequence search row(s) expected: 8" << std::endl;
		MatrixSearch::SearchMatrix(searchSeq, mat_10_10, evenSearchStrList, evenInputSeqStr, evenInputSeq, evenSrcInput);
		std::cout << "SearchUnordered search row(s) expected: 8" << std::endl;
		MatrixSearch::SearchMatrix(searchUnOrd, mat_10_10, evenSearchStrList, evenInputSeqStr, evenInputSeq, evenSrcInput);
		std::cout << "SearchBestMatch search row expected: 8" << std::endl;
		MatrixSearch::SearchMatrix(searchBM, mat_10_10, evenSearchStrList, evenInputSeqStr, evenInputSeq, evenSrcInput);

		evenSearchSeqStr = "33";
		evenSearchStrList = StringUtils::Split(evenSearchSeqStr, ' ');
		evenInputSeq = StringUtils::IntParseSearchSequence(evenSearchStrList, false);
		evenInputSeqStr = StringUtils::StrParseSearchSequence(evenSearchStrList, false);
		evenSrcInput.Update(evenSearchStrList, false);

		std::cout << "Test #1d: Correctness test, Square Matrix, Matching Single Digit" << std::endl;
		std::cout << "Search string: " << evenSearchSeqStr << std::endl;
		std::cout << "SearchSequence search row(s) expected: 1, 2, 3, 8, 9" << std::endl;
		MatrixSearch::SearchMatrix(searchSeq, mat_10_10, evenSearchStrList, evenInputSeqStr, evenInputSeq, evenSrcInput);
		std::cout << "SearchUnordered search row(s) expected: 1, 2, 3, 8, 9" << std::endl;
		MatrixSearch::SearchMatrix(searchUnOrd, mat_10_10, evenSearchStrList, evenInputSeqStr, evenInputSeq, evenSrcInput);
		std::cout << "SearchBestMatch search row expected: 1" << std::endl;
		MatrixSearch::SearchMatrix(searchBM, mat_10_10, evenSearchStrList, evenInputSeqStr, evenInputSeq, evenSrcInput);

		// Test #2: Correctness test, Non-Square Matrix (Row != Col)
		//std::string testUnevenDataPath{ "even_test_10_50.dat" };
		std::string testUnevenDataPath{ "even_test_10_50_plain.dat" };

		const EncryptedMatrix mat_10_50(testUnevenDataPath, false);

		std::string unevenSearchSeqStr{ "56 92 86 26 10 41 39 92 87 10 2 5 17 19 77 76 69 100" };
		std::vector<std::string> unevenSearchStrList = StringUtils::Split(unevenSearchSeqStr, ' ');
		std::vector<int> unevenInputSeq = StringUtils::IntParseSearchSequence(unevenSearchStrList, false);
		std::string unevenInputSeqStr = StringUtils::StrParseSearchSequence(unevenSearchStrList, false);
		SearchInput unevenSrcInput{ unevenSearchStrList, false };

		std::cout << "Test #2a: Correctness test, Non-Square Matrix, Matching Non-full Row" << std::endl;
		std::cout << "Search string: " << unevenInputSeqStr << std::endl;
		std::cout << "SearchSequence search row(s) expected: 5" << std::endl;
		MatrixSearch::SearchMatrix(searchSeq, mat_10_50, unevenSearchStrList, unevenInputSeqStr, unevenInputSeq, unevenSrcInput);
		std::cout << "SearchUnordered search row(s) expected: 5" << std::endl;
		MatrixSearch::SearchMatrix(searchUnOrd, mat_10_50, unevenSearchStrList, unevenInputSeqStr, unevenInputSeq, unevenSrcInput);
		std::cout << "SearchBestMatch search row expected: 5" << std::endl;
		MatrixSearch::SearchMatrix(searchBM, mat_10_50, unevenSearchStrList, unevenInputSeqStr, unevenInputSeq, unevenSrcInput);

		unevenSearchSeqStr = "15 16 99 81 69 39 24 73 62 50 26 15 20 67 22 58 58 50 25 14 67 34 98 96 27 87 49 83 45 97 87 20 12 92 74 33 81 96 34 9 4 55 25 7 55 73 71 56 27 59" ;
		unevenSearchStrList = StringUtils::Split(unevenSearchSeqStr, ' ');
		unevenInputSeq = StringUtils::IntParseSearchSequence(unevenSearchStrList, false);
		unevenInputSeqStr = StringUtils::StrParseSearchSequence(unevenSearchStrList, false);
		unevenSrcInput.Update(unevenSearchStrList, false);

		std::cout << "Test #2b: Correctness test, Non-Square Matrix, Matching Full Row" << std::endl;
		std::cout << "Search string: " << unevenInputSeqStr << std::endl;
		std::cout << "SearchSequence search row(s) expected: 10" << std::endl;
		MatrixSearch::SearchMatrix(searchSeq, mat_10_50, unevenSearchStrList, unevenInputSeqStr, unevenInputSeq, unevenSrcInput);
		std::cout << "SearchUnordered search row(s) expected: 10" << std::endl;
		MatrixSearch::SearchMatrix(searchUnOrd, mat_10_50, unevenSearchStrList, unevenInputSeqStr, unevenInputSeq, unevenSrcInput);
		std::cout << "SearchBestMatch search row expected: 10" << std::endl;
		MatrixSearch::SearchMatrix(searchBM, mat_10_50, unevenSearchStrList, unevenInputSeqStr, unevenInputSeq, unevenSrcInput);

		unevenSearchSeqStr = "90";
		unevenSearchStrList = StringUtils::Split(unevenSearchSeqStr, ' ');
		unevenInputSeq = StringUtils::IntParseSearchSequence(unevenSearchStrList, false);
		unevenInputSeqStr = StringUtils::StrParseSearchSequence(unevenSearchStrList, false);
		unevenSrcInput.Update(unevenSearchStrList, false);

		std::cout << "Test #2c: Correctness test, Non-Square Matrix, Matching Single Digit, Repeated" << std::endl;
		std::cout << "Search string: " << unevenInputSeqStr << std::endl;
		std::cout << "SearchSequence search row(s) expected: 3, 4, 6, 8" << std::endl;
		MatrixSearch::SearchMatrix(searchSeq, mat_10_50, unevenSearchStrList, unevenInputSeqStr, unevenInputSeq, unevenSrcInput);
		std::cout << "SearchUnordered search row(s) expected: 3, 4, 6, 8" << std::endl;
		MatrixSearch::SearchMatrix(searchUnOrd, mat_10_50, unevenSearchStrList, unevenInputSeqStr, unevenInputSeq, unevenSrcInput);
		std::cout << "SearchBestMatch search row expected: 3" << std::endl;
		MatrixSearch::SearchMatrix(searchBM, mat_10_50, unevenSearchStrList, unevenInputSeqStr, unevenInputSeq, unevenSrcInput);

		// Test #3: Performance test (1000 x 1000 matrix)
		//std::string perf1000_1000TestDataPath{ "perf_test_1000_1000.dat" };
		std::string perf1000_1000TestDataPath{ "perf_test_1000_1000_plain.dat" };

		const EncryptedMatrix mat_1000_1000(perf1000_1000TestDataPath, false);

		std::string perf1000_1000SearchSeqStr{ "42 47 31 8 52 99 32 22 72 90 73 2 97 27 66 84 40 89 8 100 84 40 20 19 8 29 25 91 80 98 60 40 74 53 5 40 76 68 85 72 9 53 14 35 60 67 31 50 57 20 45 57 99 48 17 38 8 95 6 15 39 86 5 76 40 76 95 13 11 42 12 65 30 63 38 40 48 46 55 62 26 56 51 24 25 87 95 34 64 55 10 22 31" };
		std::vector<std::string> perf1000_1000SearchStrList = StringUtils::Split(perf1000_1000SearchSeqStr, ' ');
		std::vector<int> perf1000_1000InputSeq = StringUtils::IntParseSearchSequence(perf1000_1000SearchStrList, false);
		std::string perf1000_1000InputSeqStr = StringUtils::StrParseSearchSequence(perf1000_1000SearchStrList, false);
		SearchInput perf1000_1000SrcInput{ perf1000_1000SearchStrList, false };

		std::cout << "Test #3a: Performance test (1000 x 1000 matrix), Non-full Row" << std::endl;
		std::cout << "Search string: " << perf1000_1000InputSeqStr << std::endl;
		std::cout << "SearchSequence search row(s) expected: 16" << std::endl;
		MatrixSearch::SearchMatrix(searchSeq, mat_1000_1000, perf1000_1000SearchStrList, perf1000_1000InputSeqStr, perf1000_1000InputSeq, perf1000_1000SrcInput);
		std::cout << "SearchUnordered search row(s) expected: Entire matrix" << std::endl;
		MatrixSearch::SearchMatrix(searchUnOrd, mat_1000_1000, perf1000_1000SearchStrList, perf1000_1000InputSeqStr, perf1000_1000InputSeq, perf1000_1000SrcInput);
		std::cout << "SearchBestMatch search row expected: 1" << std::endl;
		MatrixSearch::SearchMatrix(searchBM, mat_1000_1000, perf1000_1000SearchStrList, perf1000_1000InputSeqStr, perf1000_1000InputSeq, perf1000_1000SrcInput);

		perf1000_1000SearchSeqStr = "64 3 12 31 24 4 80 71 84 92 88 13 47 49 24 81 70 30 3 31 79 74 24 93 7 93 22 66 88 8 72 69 87 14 97 13 26 57 27 100 42 31 82 79 43 35 12 12 84 11 91 67 20 7 3 45 28 54 4 99 19 43 13 77 33 19 14 94 40 53 12 18 8 85 63 77 55 61 1 80 47 65 16 53 64 75 87 16 94 54 13 75 48 78 23 78 68 12 73 8 53 54 66 92 91 62 71 19 10 51 13 36 33 4 38 37 60 16 85 70 100 2 21 36 42 26 52 11 2 19 16 15 13 10 42 56 5 34 77 8 89 42 61 69 89 4 84 22 55 20 26 14 17 68 40 43 69 49 36 90 91 98 91 96 97 47 12 18 17 5 95 100 6 20 76 14 12 73 87 37 89 21 91 61 32 90 46 55 21 92 37 64 1 11 16 58 76 79 100 31 96 47 71 84 68 54 8 44 40 19 83 33 31 41 15 30 74 71 54 14 87 83 29 63 10 12 46 34 82 96 18 51 96 28 54 64 11 97 27 7 24 51 44 87 12 78 53 18 17 46 86 24 50 31 10 19 9 59 68 44 44 76 29 77 48 85 32 39 32 83 58 54 57 3 78 66 88 18 12 60 81 85 60 14 54 26 62 7 99 39 43 67 17 78 18 13 24 16 60 98 22 94 77 81 49 84 96 59 79 92 85 65 28 19 1 32 72 78 90 44 91 72 35 4 85 5 58 9 13 54 99 20 37 60 80 25 83 95 80 50 2 16 56 17 36 48 73 21 39 42 49 18 77 46 76 50 93 51 70 83 46 100 78 10 22 31 51 62 23 6 48 42 65 86 89 71 88 4 3 78 47 89 17 24 26 13 1 22 79 51 65 95 63 16 31 28 88 70 25 7 10 51 53 32 38 82 72 60 53 15 29 94 57 73 56 34 16 89 52 96 82 93 74 14 53 100 90 57 39 20 91 21 63 64 19 39 87 32 12 55 37 13 53 50 52 33 79 93 42 58 35 67 95 81 44 15 15 47 65 74 75 11 93 32 46 79 41 40 39 80 34 69 31 58 48 13 12 85 26 85 37 36 63 91 44 99 48 16 25 16 94 78 89 18 91 47 36 58 80 70 82 54 86 21 32 78 26 80 45 96 49 69 19 3 51 17 80 48 74 70 40 69 59 58 37 1 69 10 83 35 73 54 1 26 32 72 86 66 98 71 56 52 92 46 11 40 17 49 51 78 66 11 23 65 38 61 1 32 26 78 58 37 54 7 39 56 60 89 80 44 50 25 72 52 14 87 53 25 83 78 34 86 83 75 22 28 52 60 95 71 20 75 66 28 64 3 37 49 41 13 82 73 32 11 22 9 64 41 94 71 7 25 32 89 11 41 57 82 52 82 90 22 89 36 97 32 10 71 93 95 1 96 37 10 1 52 57 53 78 32 93 19 15 97 41 81 16 62 97 15 32 80 22 5 30 38 50 13 6 33 73 31 50 57 100 73 17 61 29 29 44 51 22 47 72 95 90 43 87 98 21 83 18 30 20 93 22 28 38 59 2 1 33 78 89 61 75 52 8 45 78 1 66 3 66 29 45 43 34 68 32 16 86 6 7 31 75 4 67 63 47 30 15 74 23 3 1 11 7 34 73 65 77 78 7 99 52 40 40 20 53 67 14 88 27 36 67 44 72 39 19 75 80 82 1 49 93 25 24 20 87 70 14 41 61 86 48 88 52 83 59 31 60 99 79 32 56 93 66 80 57 83 83 67 14 72 51 74 83 78 16 40 51 78 1 16 54 67 53 61 87 32 15 71 26 38 61 69 33 26 79 80 8 66 87 15 7 18 27 88 95 45 23 30 11 9 11 58 81 11 78 51 15 26 88 61 87 75 49 29 95 85 16 39 61 74 79 8 26 9 27 91 95 22 39 54 28 11 88 92 93 24 95 97 15 97 94 76 36 82 83 48 21 51 55 46 78 1 55 38 19 98 52 4 42 24 48 89 5 32 11 34 34 28 63 12 68 17 16 85 64 47 23 38 3 41 45 9 21 61 70 72 43 35 6 7 57 81 56 83 23 20 34 55 45 29 96 52 40 86 48 43 55 42 48 50 82 65 6 31 77 17 97 83 1 70 97 35 55 4 85 55 41 19 75 52 60 78 92 40 6 36 44 35 89 19 60 76 69 5 93 37 63 45 60 87 73 22 1 85 80 54 45 70 99 77 59 81 78 11 4 49 19 67 69 65 75 46 77 81";
		perf1000_1000SearchStrList = StringUtils::Split(perf1000_1000SearchSeqStr, ' ');
		perf1000_1000InputSeq = StringUtils::IntParseSearchSequence(perf1000_1000SearchStrList, false);
		perf1000_1000InputSeqStr = StringUtils::StrParseSearchSequence(perf1000_1000SearchStrList, false);
		perf1000_1000SrcInput.Update(perf1000_1000SearchStrList, false);

		std::cout << "Test #3b: Performance test (1000 x 1000 matrix), Full Row (Worst Case)" << std::endl;
		std::cout << "Search string: " << perf1000_1000InputSeqStr << std::endl;
		std::cout << "SearchSequence search row(s) expected: 1" << std::endl;
		MatrixSearch::SearchMatrix(searchSeq, mat_1000_1000, perf1000_1000SearchStrList, perf1000_1000InputSeqStr, perf1000_1000InputSeq, perf1000_1000SrcInput);
		std::cout << "SearchUnordered search row(s) expected: 1" << std::endl;
		MatrixSearch::SearchMatrix(searchUnOrd, mat_1000_1000, perf1000_1000SearchStrList, perf1000_1000InputSeqStr, perf1000_1000InputSeq, perf1000_1000SrcInput);
		std::cout << "SearchBestMatch search row expected: 1" << std::endl;
		MatrixSearch::SearchMatrix(searchBM, mat_1000_1000, perf1000_1000SearchStrList, perf1000_1000InputSeqStr, perf1000_1000InputSeq, perf1000_1000SrcInput);

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