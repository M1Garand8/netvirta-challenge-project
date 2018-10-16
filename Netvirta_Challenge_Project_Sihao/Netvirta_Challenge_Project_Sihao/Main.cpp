#include "EncryptedMatrix.h"
#include <iostream>
#include <sstream>

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cout << "Format: Matrix Generator.exe <row> <column>\n";

		return 0;
	}

	std::stringstream row_str(argv[1]), col_str(argv[2]);
	int row, col;

	row_str >> row;
	if (row_str.fail())
	{
		std::cout << "Invalid row! Please enter a number!\n";

		return 0;
	}

	col_str >> col;
	if (col_str.fail())
	{
		std::cout << "Invalid column! Please enter a number!\n";

		return 0;
	}

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

	return 0;
}