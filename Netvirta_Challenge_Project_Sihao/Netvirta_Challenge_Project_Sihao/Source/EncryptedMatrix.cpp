#include "../Header/EncryptedMatrix.h"
#include "../Header/StringUtils.h"
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <tuple>
#include <limits>

EncryptedMatrix::EncryptedMatrix(unsigned row, unsigned col) : _row(row), _col(col)	{ }

EncryptedMatrix::EncryptedMatrix(const std::string path, bool encryptDecrypt)
{
	//std::string path = filename + ".dat";
	std::ifstream file;

	file.open(path, std::ios::in);

	if (file.is_open())
	{
		std::string currLine;
		while (std::getline(file, currLine))
		{
			if (encryptDecrypt == true)
			{
				currLine = EncryptDecrypt(currLine);
			}

			int realSize = currLine.size() - 2;
			if (currLine.find("\n", realSize) != std::string::npos)
			{
				// Remove nextline token
				currLine = currLine.substr(0, realSize);
			}

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
	else
	{
		std::cout << "File " + path + " not found!" << std::endl;
	}

	file.close();

	// Generate sorted matrix from normal matrix
	// Sorted by rows
	for (unsigned i = 0; i < _row; ++i)
	{
		std::vector<ElemData> rowData = GenerateSortedRow(i);

		_matrixSortedOld.insert(_matrixSortedOld.end(), rowData.begin(), rowData.end());
	}
	// Ordered by Num -> Pos
	GenerateSortedMatrix();
	GenerateMatrixMap();
}

const unsigned EncryptedMatrix::Row() const
{
	return _row;
}

const unsigned EncryptedMatrix::Col() const
{
	return _col;
}

const std::unordered_map<int, std::unordered_map<int, std::vector<int>>>& EncryptedMatrix::GetMatrixData() const
{
	return _matrixMap;
}

const std::vector<ElemData>& EncryptedMatrix::GetSortedMatrixData() const
{
	return _matrixSorted;
}

const std::vector<ElemData>& EncryptedMatrix::GetOldSortedMatrixData() const
{
	return _matrixSortedOld;
}

const ElemData& EncryptedMatrix::operator[](unsigned i) const
{
	unsigned size = _matrixSorted.size();
	if (i >= size)
	{
		std::cout << "Index out of bounds." << std::endl;
		unsigned end = size - 1;
		return _matrixSorted[end];
	}

	return _matrixSorted[i];
}

const ElemData& EncryptedMatrix::GetElemOld(unsigned i) const
{
	unsigned size = _matrixSorted.size();
	if (i >= size)
	{
		std::cout << "Index out of bounds." << std::endl;
		unsigned end = size - 1;
		return _matrixSorted[end];
	}

	return _matrixSortedOld[i];
}

const std::vector<int> EncryptedMatrix::GetRowData(const unsigned row) const
{
	unsigned rowBegin = (row * _col);
	unsigned rowEnd = rowBegin + _col;
	std::vector<int> rowData{ _matrix.begin() + rowBegin, _matrix.begin() + rowEnd };

	return rowData;
}

const std::vector<ElemData> EncryptedMatrix::GetSortedRowData(const unsigned row) const
{
	unsigned rowBegin = (row * _col);
	unsigned rowEnd = rowBegin + _col;
	std::vector<ElemData> rowData{ _matrixSorted.begin() + rowBegin, _matrixSorted.begin() + rowEnd };

	return rowData;
}

const std::vector<ElemData> EncryptedMatrix::GetOldSortedRowData(const unsigned row) const
{
	unsigned rowBegin = (row * _col);
	unsigned rowEnd = rowBegin + _col;
	std::vector<ElemData> rowData{ _matrixSortedOld.begin() + rowBegin, _matrixSortedOld.begin() + rowEnd };

	return rowData;
}

const MatrixNumMap& EncryptedMatrix::GetMatrixMap() const
{
	return _matrixMap;
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
		int newNum = (std::rand() % std::numeric_limits<int>::max()) + 1;

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

void EncryptedMatrix::PrintToFile(const std::string filename, bool encryptDecrypt)
{
	std::string path = filename + ".dat";
	std::ofstream file;

	file.open(path, std::ios::out | std::ios::trunc);

	// File exists
	if (file.is_open())
	{
		WriteToFile(file, encryptDecrypt);

		file.close();
	}
	// File doesn't exist
	else
	{
		std::ofstream newFile{ path, std::ios::out | std::ios::trunc };

		WriteToFile(newFile, encryptDecrypt);

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

void EncryptedMatrix::WriteToFile(std::ofstream& fs, bool encryptDecrypt)
{
	for (unsigned i = 0; i < _row; ++i)
	{
		std::string rowStrRaw{ GetRowString(i) };
		std::string currRow = encryptDecrypt == true ? EncryptDecrypt(rowStrRaw) : rowStrRaw;

		if (i < (_row - 1))
		{
			fs << currRow << "\n";
		}
		else
		{
			fs << currRow;
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
		pos = StringUtils::SafeConvertUnsigned(i);
		ElemData data{ _matrix[i], pos };
		rowData.push_back(data);
	}
	std::sort(rowData.begin(), rowData.end(), [](const ElemData& data1, const ElemData& data2) {
		int lhsNum = data1.Num();
		int lhsPos = data1.Pos();
		int rhsNum = data2.Num();
		int rhsPos = data2.Pos();
		return std::tie(lhsNum, lhsPos) < std::tie(rhsNum, rhsPos);
	});

	return rowData;
}

void EncryptedMatrix::GenerateSortedMatrix()
{
	for (unsigned i = 0; i < (_row * _col); ++i)
	{
		int num = _matrix[i];
		int pos = StringUtils::SafeConvertUnsigned(i);

		ElemData newData{ num, pos };
		_matrixSorted.push_back(newData);
	}
	std::sort(_matrixSorted.begin(), _matrixSorted.end(), [](const ElemData& data1, const ElemData& data2) {
		int lhsNum = data1.Num();
		int lhsPos = data1.Pos();
		int rhsNum = data2.Num();
		int rhsPos = data2.Pos();
		return std::tie(lhsNum, lhsPos) < std::tie(rhsNum, rhsPos);
	});
}

void EncryptedMatrix::GenerateMatrixMap()
{
	for (unsigned i = 0; i < _row; ++i)
	{
		int row = StringUtils::SafeConvertUnsigned(i) + 1;
		std::vector<ElemData> rowData = GetOldSortedRowData(i);
		for (unsigned j = 0; j < rowData.size(); ++j)
		{
			ElemData data = rowData[j];
			if (_matrixMap.find(data.Num()) == _matrixMap.end())
			{
				std::unordered_map<int, std::vector<int>> newRowMap;
				std::vector<int> posData;
				newRowMap[row] = posData;
				_matrixMap[data.Num()] = newRowMap;
			}

			_matrixMap[data.Num()][row].push_back(data.Pos());
		}
	}
}