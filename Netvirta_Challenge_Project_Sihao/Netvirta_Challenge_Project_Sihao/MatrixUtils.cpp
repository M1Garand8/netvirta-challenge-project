#include "MatrixUtils.h"

ElemData::ElemData(const int num, const int pos) : _num(num), _pos(pos) { }

const int ElemData::Num() const
{
	return _num;
}

const int ElemData::Pos() const
{
	return _pos;
}

void ElemData::Set(const int num, const int pos)
{
	_num = num;
	_pos = pos;
}