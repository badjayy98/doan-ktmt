#ifndef QFLOAT_H
#define QFLOAT_H
#endif

#include "QInt.h"

string SoTron10(string num)
{
	string result = "1";
	for (int i = 0; i < num.size(); i++)
	{
		result += '0';
	}
	return result; 
}

string convertFloatToBinary(string number)
{
	bool CanLamTron = true; 
	bool negative = false;
	if (number[0] == '-')
	{
		negative = true;
		number.erase(number.begin());
	}

	// Nếu nhập số nguyên, chuyển về dạng .0
	size_t foundPos;
	if (number.find('.') == string::npos)
	{
		number += ".0";
	}
	foundPos = number.find('.');

	// Cắt phần nguyên và thập phân
	string nguyen = number.substr(0, foundPos);
	string thapPhan = number.substr((int)foundPos + 1, number.size() - (int)foundPos);

	// Chuyển phần nguyên sang binary
	nguyen = decimalToBinary(nguyen);

	// Chuyển phần thập phân sang binary
	string temp, binThapPhan = "";
	while (nguyen.size() + binThapPhan.size() < 112)
	{
		string soTron10 = SoTron10(thapPhan);
		temp = NhanHaiChuoi(thapPhan, "2");
		if (temp == soTron10)
		{
			binThapPhan += '1';
			CanLamTron = false; 
			break; 
		}
		else
		{
			if (isSmaller(temp, soTron10))
			{
				binThapPhan += '0';
				thapPhan = temp; 
			}
			else
			{
				binThapPhan += '1';
				thapPhan = TruHaiChuoiKhongXetDau(temp, soTron10);
			}
		}
	}
	string result = nguyen + '.' + binThapPhan;
	if (CanLamTron)
	{

	}
	return result; 
}


class QFloat
{
public:
	unsigned char data[16];
	QFloat()
	{
		for (int i = 0; i < 16; i++)
		{
			data[i] = 0;
		}
	}
	QFloat(string number)
	{
		


		
	}
};