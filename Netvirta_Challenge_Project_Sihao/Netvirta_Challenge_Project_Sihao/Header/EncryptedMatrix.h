#ifndef ENCRYPTEDMATRIX_H
#define ENCRYPTEDMATRIX_H

#include "MatrixUtils.h"
#include <vector>

class EncryptedMatrix
{
public:
	EncryptedMatrix(unsigned row, unsigned col);
	EncryptedMatrix(const std::string path, bool encryptDecrypt = true);
	const unsigned Row() const;
	const unsigned Col() const;
	const std::vector<int>& GetMatrixData() const;
	const std::vector<ElemData>& GetSortedMatrixData() const;
	const std::vector<ElemData>& GetOldSortedMatrixData() const;
	const ElemData& operator[](unsigned i) const;
	const ElemData& GetElemOld(unsigned i) const;
	const std::vector<int> GetRowData(const unsigned row) const;
	const std::vector<ElemData> GetSortedRowData(const unsigned row) const;
	const std::string GetRowString(const unsigned row) const;
	void GenerateMatrix();
	void Print();
	void PrintToFile(const std::string filename, bool encryptDecrypt = true);
	~EncryptedMatrix();
private:
	bool CheckColumnEven();
	std::string GetRowString(int rowIdx, std::vector<int>& rowData) const;
	void WriteToFile(std::ofstream& fs, bool encryptDecrypt = true);
	std::string EncryptDecrypt(std::string toEncrypt);
	std::vector<ElemData> GenerateSortedRow(const unsigned row);
	void GenerateSortedMatrix();
	unsigned _row;
	unsigned _col;
	std::vector<int> _matrix;
	std::vector<ElemData> _matrixSorted;
	std::vector<ElemData> _matrixSortedOld;
};

#endif