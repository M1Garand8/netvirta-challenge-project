#include "EncryptedMatrix.h"
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <fstream>

EncryptedMatrix::EncryptedMatrix(int row, int col) : _row(row), _col(col)	{ }

EncryptedMatrix::EncryptedMatrix(int row, int col, std::string data) : _row(row), _col(col)
{

}

void EncryptedMatrix::GenerateMatrix()
{
	// To do: Change matrix to hold string
	// Add encryption
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

void EncryptedMatrix::Print()
{
	// To do: Add decryption
	for (int i = 0; i < _row; ++i)
	{
		std::string currRow = "";

		for (int j = 0; j < _col; ++j)
		{
			currRow += std::to_string(_matrix[i][j]);

			if (j < (_col - 1))
			{
				currRow += " ";
			}
		}

		if (i < (_row - 1))
		{
			currRow += "\n";
		}

		std::cout << EncryptDecrypt(currRow);
	}
}

EncryptedMatrix::~EncryptedMatrix()
{
	// Pop columns
	for (int i = 0; i < _row; ++i)
	{
		for (int j = 0; j < _col; ++j)
		{
			_matrix[i].pop_back();
		}
	}

	// Pop rows
	for (int i = 0; i < _row; ++i)
	{
		_matrix.pop_back();
	}
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