#include "StringUtils.h"
#include "EncryptedMatrix.h"
#include <iostream>
#include <sstream>

int main(int argc, char *argv[])
{

	if (argc != 4)
	{
		std::cout << "Format: Matrix Generator.exe <row> <column> <filename>\n";

		return 0;
	}

	std::string filename;
	int row, col;
	
	if (StringUtils::TryParse(argv[1], row) == false)
	{
		std::cout << "Invalid row! Please enter a number!\n";

		return 0;
	}

	if (StringUtils::TryParse(argv[2], col) == false)
	{
		std::cout << "Invalid column! Please enter a number!\n";

		return 0;
	}

	filename = argv[3];

	if (row <= 0)
	{
		std::cout << "Row cannot be zero or negative!\n";

		return 0;
	}

	if (col <= 0)
	{
		std::cout << "Column cannot be zero or negative!\n";

		return 0;
	}

	EncryptedMatrix test_matrix{ row, col };
	test_matrix.GenerateMatrix();
	test_matrix.Print();
	test_matrix.PrintToFile(filename);

	return 0;
}