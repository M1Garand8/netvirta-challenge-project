#include "..\Netvirta_Challenge_Project_Sihao\EncryptedMatrix.h"

class MatrixSearch
{
public:
	static void SearchSequence(const EncryptedMatrix mat, const std::string inputSeq);
	static void SearchBestMatch(const EncryptedMatrix mat, const std::vector<int> inputSeq);
	static void SearchUnordered(const EncryptedMatrix mat, const std::vector<int> inputSeq);

private:
	static bool CheckTrue(const std::vector<bool> foundList);
	MatrixSearch() { }
};