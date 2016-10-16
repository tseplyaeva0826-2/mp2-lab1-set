// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	BitLen = len;
	MemLen = (len + sizeof(int)* 8 - 1) / (sizeof(int)* 8);
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
	{
		for (int i = 0; i<MemLen; i++) { pMem[i] = bf.pMem[i]; }
	}
}

TBitField::~TBitField()
{
	delete pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	int c;
	c = n / (sizeof(int)* 8);
	return c;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	int m;
	m = n % (sizeof(int)* 8);
	int j = n << m;
	return j;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n>-1) && (n< BitLen))
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n>-1) && (n<BitLen))
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	bool b;
	b = pMem[GetMemIndex(n)] && GetMemIndex(n);
	if ((n>-1) && (n<BitLen))
		return b;
	else return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	if (MemLen != bf.MemLen)
	{
		pMem = bf.pMem;
		if (pMem != NULL) delete pMem;
		pMem = new TELEM[MemLen];
	}
	if (pMem != NULL)
	for (int i = 0; i< BitLen; i++)
		pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int res = 1;
	if (BitLen != bf.BitLen) res = 0;
	else
	for (int i = 0; i<BitLen; i++)
	if (pMem[i] != bf.pMem[i])
	{
		res = 0; break;
	}
	return res;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  int res = 1;
	if (BitLen == bf.BitLen) res = 0;
	else
	for (int i = 0; i<BitLen; i++)
	if (pMem[i] == bf.pMem[i])
	{
		res = 0; break;
	}
	return res;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int i, len = BitLen;
	if (bf.BitLen> len) len = bf.BitLen;
	TBitField L(len);
	for (i = 0; i < MemLen; i++) L.pMem[i] = pMem[i];
	for (i = 0; i < bf.MemLen; i++) L.pMem[i] = L.pMem[i] |bf.pMem[i];
	return L;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int i, len = BitLen;
	if (bf.BitLen> len) len = bf.BitLen;
	TBitField L(len);
	for (i = 0; i< MemLen; i++) L.pMem[i] = pMem[i];
	for (i = 0; i < bf.MemLen; i++) L.pMem[i] = L.pMem[i] & bf.pMem[i];
	return L;
}

TBitField TBitField::operator~(void) // отрицание
{
	int len = BitLen;
	TBitField L(len);
	for (int i = 0; i<MemLen; i++)
		L.pMem[i] = ~pMem[i];
	return L;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i = 0;
	char ch;

	do { istr >> ch; } while (ch != ' ');

	while (1)
	{
		istr >> ch;
		if (ch == '0') bf.ClrBit(i++);
		else
		if (ch == '1') bf.SetBit(i++); else break;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int len = bf.GetLength();
	for (int i = 0; i<len; i++)
	if (bf.GetBit(i)) ostr << '1'; else ostr << '0';
	return ostr; 
}
