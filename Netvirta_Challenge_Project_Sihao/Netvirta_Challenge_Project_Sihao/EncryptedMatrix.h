#ifndef ENCRYPTEDMATRIX_H
#define ENCRYPTEDMATRIX_H

#include "MatrixUtils.h"
#include <vector>
#include <string>

class EncryptedMatrix
{
public:
	EncryptedMatrix(unsigned row, unsigned col);
	EncryptedMatrix(const std::string data);
	const unsigned Row() const;
	const unsigned Col() const;
	const std::vector<int> GetMatrixData() const;
	const std::vector<int> GetRowData(const unsigned row) const;
	const std::string GetRowString(const unsigned row) const;
	void GenerateMatrix();
	void Print();
	void PrintToFile(const std::string filename);
	~EncryptedMatrix();
private:
	bool CheckColumnEven();
	std::string GetRowString(int rowIdx, std::vector<int>& rowData) const;
	void WriteToFile(std::ofstream& fs);
	std::string EncryptDecrypt(std::string toEncrypt);
	std::vector<ElemData> GenerateSortedRow(const unsigned row);
	unsigned _row;
	unsigned _col;
	std::vector<int> _matrix;
	std::vector<ElemData> _matrixSorted;
};

#endif