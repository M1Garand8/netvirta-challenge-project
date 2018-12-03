#ifndef MATRIXUTILS_H
#define MATRIXUTILS_H

class ElemData
{
public:
	ElemData(const int num, const int pos);
	ElemData(const int row, const int num, const int pos);
	const int Row() const;
	const int Num() const;
	const int Pos() const;
	void Set(const int num, const int pos);
	void Set(const int row, const int num, const int pos);

private:
	int _row;
	int _num;
	int _pos;
};

class OrderedElemData
{
public:
	OrderedElemData(const int pos, const ElemData data);
	const int Pos() const;
	const ElemData Data() const;

private:
	int _pos;
	ElemData _data;
};

#endif