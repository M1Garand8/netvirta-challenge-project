#ifndef MATRIXUTILS_H
#define MATRIXUTILS_H

class ElemData
{
public:
	ElemData(const int num, const int pos);
	const int Num() const;
	const int Pos() const;
	void Set(const int num, const int pos);

private:
	int _num;
	int _pos;
};

#endif