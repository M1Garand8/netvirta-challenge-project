#include "EncryptedMatrix.h"
#include "StringUtils.h"
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <fstream>

EncryptedMatrix::EncryptedMatrix(int row, int col) : _row(row), _col(col)	{ }

EncryptedMatrix::EncryptedMatrix(const std::string path)
{
	//std::string path = filename + ".dat";
	std::ifstream file;

	file.open(path, std::ios::in);

	if (file.is_open())
	{
		// First draft, to be improved
		int i = 0;
		std::string currLine;
		while (std::getline(file, currLine))
		{
			int realSize = currLine.size() - 2;
			if (currLine.find("\n", realSize) != std::string::npos)
			{
				// Remove nextline token
				currLine = currLine.substr(0, realSize);
			}

			currLine = EncryptDecrypt(currLine);

			std::vector<int> newRow;
			_matrix.push_back(newRow);

			std::vector<std::string> colList = StringUtils::Split(currLine, ' ');
			for (unsigned c = 0; c < colList.size(); ++c)
			{
				std::string colStr = colList[c];
				int val = 0;
				if (StringUtils::TryParse(colStr, val) == true)
				{
					_matrix[i].push_back(val);
				}
			}

			++i;
		}

		_row = _matrix.size();
		_col = _matrix[0].size();
	}

	file.close();
}

const int EncryptedMatrix::Row() const
{
	return _row;
}

const int EncryptedMatrix::Col() const
{
	return _col;
}

const std::vector<std::vector<int> > EncryptedMatrix::GetMatrixData() const
{
	return _matrix;
}

const std::vector<int> EncryptedMatrix::GetRowData(const int row) const
{
	return _matrix[row];
}

const std::string EncryptedMatrix::GetRowString(const int row) const
{
	return GetRowString(row, _matrix[row]);
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
	std::string path = filename + ".dat";
	std::ofstream file;

	file.open(path, std::ios::out | std::ios::trunc);

	// File exists
	if (file.is_open())
	{
		WriteToFile(file);

		file.close();
	}
	// File doesn't exist
	else
	{
		std::ofstream newFile{ path, std::ios::out | std::ios::trunc };

		WriteToFile(newFile);

		newFile.close();
	}
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

// Private functions
bool EncryptedMatrix::CheckColumnEven()
{
	// Degenerate matrix, shouldn't happen
	if (_matrix.empty())
	{
		return false;
	}

	for (unsigned i = 0; i < _matrix.size(); ++i)
	{
		int currSize = _matrix[i].size();
		if (currSize != _col)
		{
			return false;
		}
	}

	return true;
}

std::string EncryptedMatrix::GetRowString(int rowIdx, std::vector<int> rowData) const
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

void EncryptedMatrix::WriteToFile(std::ofstream& fs)
{
	for (int i = 0; i < _row; ++i)
	{
		std::string currRow = GetRowString(i, _matrix[i]);

		if (i < (_row - 1))
		{
			fs << EncryptDecrypt(currRow) << "\n";
		}
		else
		{
			fs << EncryptDecrypt(currRow);
		}
	}
}

std::string EncryptedMatrix::EncryptDecrypt(std::string toEncrypt)
{
	char key = 'K'; //Any char will work
	std::string output = toEncrypt;

	for (unsigned i = 0; i < toEncrypt.size(); i++)
	{
		output[i] = toEncrypt[i] ^ key;
	}

	return output;
}