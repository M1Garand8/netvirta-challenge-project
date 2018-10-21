#include "..\Netvirta_Challenge_Project_Sihao\EncryptedMatrix.h"

class MatrixSearch
{
public:
	static void SearchSequence(const EncryptedMatrix mat, const std::string inputSeq);	// To be changed
	static void SearchBestMatch(const EncryptedMatrix mat, const std::vector<int> inputSeq);	// To be changed
	static void SearchUnordered(const EncryptedMatrix mat, const std::vector<int> inputSeq);	// To be changed

private:
	static bool CheckTrue(const std::vector<bool> foundList);
	MatrixSearch() { }
};