#include "QFloat.h"

// Nhân 1 số dạng 0.xx với 2
string FloatMul2(string number)
{
	string result; 
	int foundDot = number.find('.');
	int carry = 0, temp; 

	for (int i = number.size() - 1; i > foundDot; i--)
	{
		temp = (number[i] - '0') * 2 + carry; 
		if (temp >= 10)
		{
			result.insert(result.begin(), char(temp - 10 + '0'));
			carry = 1; 
		}
		else
		{
			result.insert(result.begin(), char(temp + '0'));
			carry = 0; 
		}
	}


	// Xoá các số 0 thừa đằng sau
	int i = result.size() - 1; 
	while (result[i] == '0' && i != 0)
	{
		result.pop_back();
		i--;
	}

	if (carry == 1)
	{
		result = "1." + result; 
	}
	else
	{
		result = "0." + result; 
	}
	return result; 
}
// Exp = số mũ, trả về chuỗi significand
string getSignificandAndExponent(string number, int &exp)
{
	string result; 
	bool negative = false;
	if (number[0] == '-')
	{
		negative = true;
		number.erase(number.begin());
	}
	int K = pow((double)2, (double)14) - 1;

	// Nếu nhập số nguyên, chuyển về dạng .0
	size_t foundPos;
	if (number.find('.') == string::npos)
	{
		number += ".0";
	}
	foundPos = number.find('.');

	// Cắt phần nguyên và thập phân
	string nguyen = number.substr(0, foundPos);

	string thapPhan = "0." + number.substr((int)foundPos + 1);

	// Chuyển phần nguyên sang binary
	nguyen = decimalToBinary(nguyen);

	// Chuyển phần thập phân sang binary
	string temp, binThapPhan = "";
	
	if (nguyen != "0")
	{
		exp = nguyen.size() - 1 + K;
		for (int i = 0; i < 112 - nguyen.size(); i++)
		{
			thapPhan = FloatMul2(thapPhan);
			binThapPhan += thapPhan[0];
			thapPhan[0] = '0';
		}
	}
	else
	{
		int gap1 = 0; 
		while (gap1 < K)
		{
			thapPhan = FloatMul2(thapPhan);
			binThapPhan += thapPhan[0];
			thapPhan[0] = '0';
			if (binThapPhan.back() == '1')
			{
				break;
			}
			gap1++;
		}
		// gap1 + 1 la so bit phai dich de phan nguyen la 1
		exp = K - (gap1 + 1);

		// So chuan hoa
		if (gap1 + 1 < K)
		{
			for (int i = 0; i < 112; i++)
			{
				thapPhan = FloatMul2(thapPhan);
				binThapPhan += thapPhan[0];
				thapPhan[0] = '0';
			}
		}

		// So khong the chuan hoa -> bien no thanh so co the chuan hoa bang cach gan exp = 1
		else
		{
			binThapPhan = "";
			while (exp < 1)
			{
				thapPhan = FloatMul2(thapPhan);
				binThapPhan += thapPhan[0];
				thapPhan[0] = '0';
				exp++;
				result = nguyen + binThapPhan;
				while (result.size() < 112)
				{
					result += '0';
				}
				return result; 
			}
		}
	}
	if (nguyen != "" && nguyen != "0")
	{
		nguyen = nguyen.substr(1);
	}
	result = nguyen  + binThapPhan;
	//Xoa bit 0 thua o dau
	while (result[0] == '0')
	{
		result.erase(0, 1);
	}
	while (result.size() < 112)
	{
		result += '0';
	}
	return result;
}


QFloat::QFloat()
{
	data.resize(4);
	for (int i = 0; i < 4; i++)
	{
		data[i] = 0;
	}
}
QFloat::QFloat(string number)
{
	data.resize(4);
	if (number[0] == '-')
	{
		setBit(1, 1);
	}
	// Nếu nhận số vô cực
	if (number == "Inf" || number == "-Inf")
	{
		// Set toan bo 15 bit sau bit dau = 1
		for (int i = 2; i <= 16; i++)
		{
			setBit(i, 1);
		}
	}
	else if (number == "Nan")
	{
		// Set toan bo 15 bit sau bit dau = 1
		for (int i = 2; i <= 16; i++)
		{
			setBit(i, 1);
		}
		data[3] = 1;
	}
	else
	{
		int exp;
		string significand;
		significand = getSignificandAndExponent(number, exp);
		for (int i = 2; i <= 16; i++)
		{
			int bitCanSet = ((exp >> (16 - i)) & 1);
			setBit(i,bitCanSet);
		}
		for (int i = 17; i <= 128; i++)
		{
			if (significand[i - 17] == '0')
			{
				setBit(i, 0);
			}
			else
			{
				setBit(i, 1);
			}
		}

	}
}

string QFloat::DangFloatingPoint()
{
	string result; 
	for (int i = 1; i <= 128; i++)
	{
		result += getBit(i) + '0';
		if (i == 1 || i == 16)
		{
			result += ' ';
		}
	}
	return result; 
}

void QFloat::setBit(int position, int value)
{
	int offset; 
	int posToInsert = (position - 1) / 32;
	if (position % 32 != 0)
	{
		offset = (32 - (position % 32));
	}
	else
	{
		offset = 0;
	}
	data[posToInsert] = data[posToInsert] | (value << offset);
}

int QFloat::getBit(int position)
{
	int offset;
	int pos = (position - 1) / 32; 
	if (position % 32 != 0)
	{
		offset = 32 - (position % 32);
	}
	else
	{
		offset = 0;
	}

	return ((data[pos] >> offset) & 1); 
}


QFloat QFloat::convertBinaryToQFloat(string binary)
{
	QFloat res; 
	if (binary[0] == '-')
	{
		res.setBit(1, 1);
		binary.erase(0, 1);
	}
	int K = pow((double)2, (double)14) - 1;

	// Nếu nhập số nguyên, chuyển về dạng .0
	size_t foundPos;
	if (binary.find('.') == string::npos)
	{
		binary += ".0";
	}
	foundPos = binary.find('.');

	// Cắt phần nguyên và thập phân
	string nguyen = binary.substr(0, foundPos);
	while (nguyen[0] == '0')
	{
		nguyen.erase(0, 1);
	}
	string thapPhan = binary.substr((int)foundPos + 1);
	int exp = nguyen.size() - 1 + K;

	if (nguyen == "0" || nguyen == "")
	{
		while (thapPhan[0] == '0' && thapPhan.size() > 1)
		{
			if (exp == 1)
			{
				break; 
			}
			thapPhan.erase(0, 1);
			exp--;
		}
		if (exp == 1)
		{
			while (thapPhan.size() > 112)
			{
				thapPhan.pop_back();
			}
		}
	}
	string result = nguyen + thapPhan;
	while (result[0] == '0')
	{
		result.erase(0, 1);
	}
	while (result.size() < 112)
	{
		result += '0';
	}
	for (int i = 2; i <= 16; i++)
	{
		int bitCanSet = ((exp >> (16 - i)) & 1);
		res.setBit(i, bitCanSet);
	}
	for (int i = 17; i <= 128; i++)
	{
		res.setBit(i, result[i - 17]);
	}
	return res; 
}