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
	if (isUseSearchFile == false && StringUtils::TryParse(argv[1], isNum) == false)
	{
		std::string filename{ argv[1] };
		std::string searchfunc{ argv[2] };

		const EncryptedMatrix mat(filename);
		const std::vector<int> inputSeq = StringUtils::IntParseSearchSequence(argc, argv);
		const std::string inputSeqStr = StringUtils::StrParseSearchSequence(argc, argv);

		MatrixSearch::SearchMatrix(searchfunc, mat, inputSeqStr, inputSeq);
	}
	else
	{
		std::string filename{ argv[1] };
		std::string searchFuncsPath{ argv[2] };
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

	return 0;
}