#include "..\Header\MatrixUtils.h"

ElemData::ElemData(const int num, const int pos) : _num(num), _pos(pos) { }

ElemData::ElemData(const int row, const int num, const int pos) : _row(row), _num(num), _pos(pos) { }

const int ElemData::Row() const
{
	return _row;
}

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

void ElemData::Set(const int row, const int num, const int pos)
{
	_row = row;
	_num = num;
	_pos = pos;
}

OrderedElemData::OrderedElemData(const int pos, const ElemData data) : _pos(pos), _data(data) { }

const int OrderedElemData::Pos() const
{
	return _pos;
}

const ElemData OrderedElemData::Data() const
{
	return _data;
}