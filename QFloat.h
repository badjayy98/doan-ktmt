#ifndef QFLOAT_H
#define QFLOAT_H
#endif

#include "QInt.h"

string FloatMul2(string number);


string convertFloatToBinary(string number);

string getSignifcand(string binary);

string getExponent(string binary);

string mulFractionByTwo(string number);

string toStrBit(string number, int& exp);


class QFloat
{
public:
	vector <uint32_t> data;
	QFloat();
	QFloat(string number);
	void setBit(int position, int value);
	int getPosition(int size, int i);
	int getOffset(int size, int i);
};