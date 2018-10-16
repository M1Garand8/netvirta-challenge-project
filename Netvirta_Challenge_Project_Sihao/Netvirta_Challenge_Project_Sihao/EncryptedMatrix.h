#include <vector>
#include <string>

class EncryptedMatrix
{
public:
	EncryptedMatrix(int row, int col);
	EncryptedMatrix(int row, int col, std::string data);
	void GenerateMatrix();
	void Print();
	~EncryptedMatrix();
private:
	std::string EncryptDecrypt(std::string toEncrypt);
	int _row;
	int _col;
	std::vector<std::vector<int> > _matrix;
};