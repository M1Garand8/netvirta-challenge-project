#include "EncryptedMatrix.h"
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <fstream>

EncryptedMatrix::EncryptedMatrix(int row, int col) : _row(row), _col(col)	{ }

EncryptedMatrix::EncryptedMatrix(int row, int col, const std::string filename) : _row(row), _col(col)
{
	
}

void EncryptedMatrix::GenerateMatrix()
{
	std::srand(time(nullptr));

	for (int i = 0; i < _row; ++i)
	{
		std::vector<int> newRow;
		_matrix.push_back(newRow);

		for (int j = 0; j < _col; ++j)
		{
			int newNum = std::rand();
			std::srand(newNum);

			_matrix[i].push_back(newNum);
		}
	}
}

// For testing
void EncryptedMatrix::Print()
{
	for (int i = 0; i < _row; ++i)
	{
		std::string currRow = GetRowString(i, _matrix[i]);

		if (i < (_row - 1))
		{
			std::cout << EncryptDecrypt(currRow) << "\n";
		}
		else
		{
			std::cout << EncryptDecrypt(currRow);
		}
	}
}

void EncryptedMatrix::PrintToFile(const std::string filename)
{
	std::string path = "\\Matrices\\" + filename + ".dat";
	std::ofstream file;

	file.open(path, std::ios::out | std::ios::app);

	for (int i = 0; i < _row; ++i)
	{
		std::string currRow = GetRowString(i, _matrix[i]);

		if (i < (_row - 1))
		{
			file << EncryptDecrypt(currRow) << "\n";
		}
		else
		{
			file << EncryptDecrypt(currRow);
		}
	}

	file.close();
}

EncryptedMatrix::~EncryptedMatrix()
{
	// Pop columns
	for (int i = 0; i < _row; ++i)
	{
		_matrix[i].clear();
	}

	// Pop rows
	_matrix.clear();
}

std::string EncryptedMatrix::GetRowString(int rowIdx, std::vector<int> rowData)
{
	std::string currRow = "";

	for (int j = 0; j < _col; ++j)
	{
		currRow += std::to_string(rowData[j]);

		if (j < (_col - 1))
		{
			currRow += " ";
		}
	}

	return currRow;
}

std::string EncryptedMatrix::EncryptDecrypt(std::string toEncrypt)
{
	char key = 'K'; //Any char will work
	std::string output = toEncrypt;

	for (int i = 0; i < toEncrypt.size(); i++)
	{
		output[i] = toEncrypt[i] ^ key;
	}

	return output;
}