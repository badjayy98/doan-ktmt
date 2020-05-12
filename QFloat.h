#ifndef QFLOAT_H
#define QFLOAT_H
#endif

#include "QInt.h"

string FloatMul2(string number);

string getSignificandAndExponent(string number, int &exp);

class QFloat
{
private:
	vector<uint32_t> data;
public:
	QFloat();
	QFloat(string number);
	void setBit(int position, int value);
	int getBit(int position);
	string DangFloatingPoint();

	static QFloat convertBinaryToQFloat(string binary);
};

