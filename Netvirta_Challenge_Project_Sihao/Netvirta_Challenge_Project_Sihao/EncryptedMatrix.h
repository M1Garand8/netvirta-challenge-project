#include <vector>
#include <string>

class EncryptedMatrix
{
public:
	EncryptedMatrix(int row, int col);
	EncryptedMatrix(int row, int col, const std::string data);
	void GenerateMatrix();
	void Print();
	void PrintToFile(const std::string filename);
	~EncryptedMatrix();
private:
	std::string GetRowString(int rowIdx, std::vector<int> rowData);
	std::string EncryptDecrypt(std::string toEncrypt);
	int _row;
	int _col;
	std::vector<std::vector<int> > _matrix;
};