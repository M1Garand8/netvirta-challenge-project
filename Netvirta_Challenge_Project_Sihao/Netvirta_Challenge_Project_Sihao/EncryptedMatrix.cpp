#include "EncryptedMatrix.h"
#include "StringUtils.h"
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>

EncryptedMatrix::EncryptedMatrix(unsigned row, unsigned col) : _row(row), _col(col)	{ }

EncryptedMatrix::EncryptedMatrix(const std::string path)
{
	//std::string path = filename + ".dat";
	std::ifstream file;

	file.open(path, std::ios::in);

	if (file.is_open())
	{
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

			std::vector<std::string> colList = StringUtils::Split(currLine, ' ');
			_col = colList.size(); // Dangerous if Split does not give consistent col size.
			for (unsigned c = 0; c < colList.size(); ++c)
			{
				std::string colStr = colList[c];
				int val = 0;
				if (StringUtils::TryParse(colStr, val) == true)
				{
					_matrix.push_back(val);
				}
			}
		}

		_row = _matrix.size() / _col;
	}

	file.close();

	// Generate sorted matrix from normal matrix
	// Sorted by rows
	for (unsigned i = 0; i < _row; ++i)
	{
		std::vector<ElemData> rowData = GenerateSortedRow(i);

		_matrixSorted.insert(_matrixSorted.end(), rowData.begin(), rowData.end());
	}
}

const unsigned EncryptedMatrix::Row() const
{
	return _row;
}

const unsigned EncryptedMatrix::Col() const
{
	return _col;
}

const std::vector<int> EncryptedMatrix::GetMatrixData() const
{
	return _matrix;
}

const std::vector<int> EncryptedMatrix::GetRowData(const unsigned row) const
{
	unsigned rowBegin = (row * _col);
	unsigned rowEnd = rowBegin + _col;
	std::vector<int> rowData{ _matrix.begin() + rowBegin, _matrix.begin() + rowEnd };

	return rowData;
}

const std::string EncryptedMatrix::GetRowString(const unsigned row) const
{
	unsigned rowBegin = (row * _col);
	unsigned rowEnd = rowBegin + _col;
	std::vector<int> rowData{ _matrix.begin() + rowBegin, _matrix.begin() + rowEnd };
	return GetRowString(row, rowData);
}

void EncryptedMatrix::GenerateMatrix()
{
	std::srand(time(nullptr));

	// Generate normal, unsorted matrix
	for (unsigned i = 0; i < (_row * _col); ++i)
	{
		int newNum = (std::rand() % 100) + 1; // Limit number range to 1 - 100

		_matrix.push_back(newNum);
	}

	// Generate sorted matrix from normal matrix
	// Sorted by rows
	for (unsigned i = 0; i < _row; ++i)
	{
		std::vector<ElemData> rowData = GenerateSortedRow(i);

		_matrixSorted.insert(_matrixSorted.end(), rowData.begin(), rowData.end());
	}
}

// For testing
void EncryptedMatrix::Print()
{
	for (unsigned i = 0; i < _row; ++i)
	{
		std::string currRow = GetRowString(i);

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

	return _matrix.size() % _col == 0;
}

std::string EncryptedMatrix::GetRowString(int rowIdx, std::vector<int>& rowData) const
{
	std::string currRow = "";

	for (unsigned j = 0; j < _col; ++j)
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
	for (unsigned i = 0; i < _row; ++i)
	{
		std::string currRow = GetRowString(i);

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

std::vector<ElemData> EncryptedMatrix::GenerateSortedRow(const unsigned row)
{
	unsigned rowBegin = (row * _col);
	unsigned rowEnd = rowBegin + _col;

	std::vector<ElemData> rowData;
	for (unsigned i = rowBegin; i < rowEnd; ++i)
	{
		int pos = 0;
		// Safe conversion of unsigned to signed int
		if (i < static_cast<unsigned>(std::numeric_limits<int>::max()))
		{
			pos = int(i);
		}
		else
		{
			pos = -1;
		}
		ElemData data{ _matrix[i], pos };
		rowData.push_back(data);
	}
	std::sort(rowData.begin(), rowData.end(), [](const ElemData& data1, const ElemData& data2) {
		return (data1.Num() < data2.Num()) && (data1.Pos() < data2.Pos());
	});

	return rowData;
}