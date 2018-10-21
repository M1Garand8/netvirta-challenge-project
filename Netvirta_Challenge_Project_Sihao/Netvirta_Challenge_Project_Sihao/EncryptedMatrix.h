#include <vector>
#include <string>

class EncryptedMatrix
{
public:
	EncryptedMatrix(int row, int col);
	EncryptedMatrix(const std::string data);
	const int Row() const;
	const int Col() const;
	const std::vector<std::vector<int> > GetMatrixData() const;
	const std::vector<int> GetRowData(const int row) const;
	const std::string GetRowString(const int row) const;
	void GenerateMatrix();
	void Print();
	void PrintToFile(const std::string filename);
	~EncryptedMatrix();
private:
	bool CheckColumnEven();
	std::string GetRowString(int rowIdx, std::vector<int> rowData) const;
	void WriteToFile(std::ofstream& fs);
	std::string EncryptDecrypt(std::string toEncrypt);
	int _row;
	int _col;
	std::vector<std::vector<int> > _matrix;
};