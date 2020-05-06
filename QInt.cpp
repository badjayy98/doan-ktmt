#include "QInt.h"

QInt::QInt()
{
	this->data.resize(4);
	for (int i = 0; i < 4; i++)
	{
		data[i] = 0;
	}
}

// Khởi tạo 1 QInt bằng cách nhập 1 chuỗi binary, tối đa 128 ký tự 
QInt::QInt(string binary)
{
	if (binary.size() == 0)
	{
		throw ("Khoi tao 0 ky tu");
	}
	if (binary.size() > 128)
	{
		throw ("Tran so");
	}
	this->data.resize(4);
	int i, position, offset;
	for (i = 0; i < binary.size(); i++)
	{
		if (binary[i] == '1')
		{
			position = getPosition(binary.size(), i); // Tính index vector bit này được thêm vào
			offset = getOffset(binary.size(), i); // Tính xem sẽ dịch trái bao nhiêu bit để có thêm bật bit lên
			data[position] = data[position] | (1 << offset);
		}
	}
}

vector<unsigned int> QInt::getData()
{
	return data;
}

void QInt::setData(int position, int value)
{
	data[position] = value;
}

bool QInt::isEqualZero()
{
	for (int i = 0; i < this->getData().size(); i++)
	{
		if (this->getData()[i] != 0)
		{
			return false;
		}
	}

	return true;
}
// Kiểm tra QInt có phải số âm hay không
bool QInt::isNegative()
{
	if (((this->data[3] >> 31) & 1) == 1)
	{
		return true;
	}
	return false;
}


// Lấy vị trí phần tử để đặt bit, phục vụ khởi tạo QInt với 1 chuỗi binary
int QInt::getPosition(int size, int i)
{
	return (size - 1 - i) / 32;
}

// Tính toán xem sẽ phải dịch chuyển bao nhiêu bit, phục vụ khởi tạo QInt với 1 chuỗi binary
int QInt::getOffset(int size, int i)
{
	if ((size - i) % 32 == 0)
	{
		return 31;
	}
	else
	{
		return (size - i) % 32 - 1;
	}
}


// Convert chuỗi nhị phân sang QInt
QInt QInt::convertBinaryToQInt(string binary)
{
	if (binary == "0")
	{
		return QInt("0");
	}
	QInt result;
	if (binary.size() == 0)
	{
		throw "Khoi tao 0 ky tu";
	}
	if (binary.size() > 128)
	{
		throw "Tran so";
	}
	result.data.resize(4);
	int i, position, offset;
	for (i = 0; i < binary.size(); i++)
	{
		if (binary[i] == '1')
		{
			position = result.getPosition(binary.size(), i); // Tính index vector bit này được thêm vào
			offset = result.getOffset(binary.size(), i); // Tính xem sẽ dịch trái bao nhiêu bit để có thêm bật bit lên
			result.data[position] = result.data[position] | (1 << offset);
		}
	}
	return result;
}

// Convert từ chuỗi thập phân sang QInt
QInt QInt::convertDecimalToQInt(string decimal)
{
	if (decimal == "0")
	{
		return QInt("0");
	}
	bool negative = false;
	if (decimal[0] == '-')
	{
		negative = true;
		decimal.erase(decimal.begin());
	}
	string binResult = decimalToBinary(decimal);
	QInt result(binResult);
	if (negative)
	{
		result = result.SoBu2();
	}
	return result;
}

// Convert từ chuỗi thập lục phân sang QInt
QInt QInt::convertHexToQInt(string hex)
{
	if (hex == "0")
	{
		return QInt("0");
	}
	bool negative = false;
	if (hex[0] == '-')
	{
		negative = true;
		hex.erase(hex.begin());
	}
	string binResult = hexToBinary(hex);
	QInt result(binResult);
	if (negative)
	{
		result = result.SoBu2();
	}
	return result;
}

// Convert QInt sang Binary
string QInt::convertQIntToBinary()
{
	bool startPrint = false;
	string binary;
	for (int i = data.size() - 1; i >= 0; i--)
	{
		if (data[i] != 0)
		{
			startPrint = true;
		}


		if (startPrint)
		{
			for (int j = 0; j < 32; j++)
			{
				int bitNow = ((data[i] >> (31 - j)) & 1);
				binary.push_back(bitNow + '0');
			}

		}

	}

	// Xoá các bit 0 đầu chuỗi
	if (binary.find('1') != string::npos)
	{
		binary.erase(binary.begin(), binary.begin() + binary.find('1'));
	}
	else
	{
		return "0";
	}

	if (binary == "")
	{
		binary = "0";
	}

	return binary;
}

// Convert QInt sang Decimal
string QInt::convertQIntToDecimal()
{
	string Binary = this->convertQIntToBinary();
	string Decimal;
	for (int i = 0; i < Binary.size(); i++)
	{
		if (Binary[i] != '0')
		{
			if ((i == 0) && (Binary.size() == 128))
			{
				Decimal = TruHaiChuoi(Decimal, LuyThua2(Binary.size() - i - 1));
			}
			else
			{
				Decimal = CongHaiChuoi(Decimal, LuyThua2(Binary.size() - i - 1));
			}
		}
	}
	if (Decimal[0] == '-')
	{
		string temp = Decimal.substr(1, Decimal.size() - 1);
		while (temp[0] == '0')
		{
			temp.erase(temp.begin());
		}
		Decimal = '-' + temp;
	}
	return Decimal;
}

// Convert QInt sang hex
string QInt::convertQIntToHex()
{
	string binary = this->convertQIntToBinary();
	return convertBinaryToHex(binary);
}

// Chuyển số QInt dương thành QInt âm
QInt QInt::SoBu2()
{
	return ~(*this) + QInt("1");
}

QInt QInt::operator << (QInt n)
{
	if (n >= QInt("10000000"))
	{
		return QInt("0");
	}

	string binary = this->convertQIntToBinary();

	while (binary.size() != 128)
	{
		binary.insert(binary.begin(), '0');
	}

	string resultAfterSL;

	resultAfterSL = binary.substr(stoi(n.convertQIntToDecimal()), 128 - stoi(n.convertQIntToDecimal()));

	while (resultAfterSL.size() != 128)
	{
		resultAfterSL = resultAfterSL + '0';
	}

	QInt resultQInt = QInt::convertBinaryToQInt(resultAfterSL);
	return resultQInt;
}

// Toán tử >>
QInt QInt::operator >> (QInt n)
{
	if (n >= QInt("10000000"))
	{
		return QInt("0");
	}
	string binary = this->convertQIntToBinary();
	while (binary.size() != 128)
	{
		binary.insert(binary.begin(), '0');
	}

	string resultAfterSr;

	resultAfterSr = binary.substr(0, 128 - stoi(n.convertQIntToDecimal()));

	while (resultAfterSr.size() != 128)
	{
		resultAfterSr = '0' + resultAfterSr;
	}
	QInt resultQInt = QInt::convertBinaryToQInt(resultAfterSr);
	return resultQInt;
}

QInt QInt::ROL(QInt n)
{
	QInt du = n % QInt("10000000");
	string binary = this->convertQIntToBinary();

	string nBitDau = binary.substr(0, du.getData()[0]);
	string remain = binary.substr(du.getData()[0], binary.size() - du.getData()[0]);
	string resultBinary = remain + nBitDau;

	while (resultBinary.size() != 128)
	{
		resultBinary.insert(resultBinary.begin(), '0');
	}

	QInt resultQInt(resultBinary);
	return resultQInt;

}

QInt QInt::ROR(QInt n)
{
	QInt du = n % QInt("10000000");
	string binary = this->convertQIntToBinary();

	string nBitCuoi = binary.substr(binary.size() - du.getData()[0], du.getData()[0]);
	string remain = binary.substr(0, binary.size() - du.getData()[0]);

	string resultBinary = nBitCuoi + remain;

	while (resultBinary.size() != 128)
	{
		resultBinary.insert(resultBinary.begin(), '0');
	}

	QInt resultQInt(resultBinary);
	return resultQInt;
}

// Toán tử AND
QInt QInt::operator & (QInt s)
{
	QInt result;
	for (int i = 0; i < this->data.size(); i++)
	{
		result.data[i] = this->data[i] & s.data[i];
	}
	return result;
}

// Toán tử OR
QInt QInt::operator | (QInt s)
{
	QInt result;
	for (int i = 0; i < this->data.size(); i++)
	{
		result.data[i] = this->data[i] | s.data[i];
	}
	return result;
}

// Toán tử XOR
QInt QInt::operator ^ (QInt s)
{
	QInt result;
	for (int i = 0; i < this->data.size(); i++)
	{
		result.data[i] = this->data[i] ^ s.data[i];
	}
	return result;
}

// Toán tử NOT
QInt QInt::operator~()
{
	QInt result;
	string binary = this->convertQIntToBinary();
	while (binary.size() < 128)
	{
		binary = '0' + binary;
	}
	string resultBin = "";
	for (int i = 0; i < 128; i++)
	{
		if (binary[i] == '1')
		{
			resultBin += '0';
		}
		else
		{
			resultBin += '1';
		}
	}

	result = QInt::convertBinaryToQInt(resultBin);
	return result;
}

bool QInt::operator >(QInt s)
{
	bool neg1 = false, neg2 = false, result; 
	neg1 = this->isNegative();
	neg2 = s.isNegative();
	int i; 

	if (neg1 && neg2)
	{
	}
	else if (!neg1 && neg2)
	{
		return true; 
	}
	else if (neg1 && !neg2)
	{
		return false; 
	}
	for (i = 3; i >= 0; i--)
	{
		if (this->data[i] < s.data[i])
		{
			return false; 
		}
		if (this->data[i] > s.data[i])
		{
			return true; 
		}
	}
	return false; 
}

bool QInt::operator < (QInt s)
{
	bool neg1 = false, neg2 = false, nguoc = false;
	neg1 = this->isNegative();
	neg2 = s.isNegative();
	int i;

	if (neg1 && neg2)
	{
	}
	else if (!neg1 && neg2)
	{
		return false; 
	}
	else if (neg1 && !neg2)
	{
		return true; 
	}
	for (i = 3; i >= 0; i--)
	{
		if (this->data[i] > s.data[i])
		{
			return false;
		}
		if (this->data[i] < s.data[i])
		{
			return true; 
		}
	}
	return false;
}

bool QInt::operator == (QInt s)
{
	for (int i = 3; i >= 0; i--)
	{
		if (this->data[i] != s.data[i])
		{
			return false;
		}
	}
	return true;
}

// Toán tử so sánh >=
bool QInt::operator >= (QInt s)
{
	if (*this == s)
	{
		return true;
	}
	else
	{
		return *this > s; 
	}
}

// Toán tử so sánh <=
bool QInt::operator <= (QInt s)
{
	if (*this == s)
	{
		return true; 
	}
	else
	{
		return *this < s; 
	}

}

// Toán tử gán =
QInt QInt::operator =(QInt s)
{
	for (int i = 0; i < 4; i++)
	{
		this->data[i] = s.data[i];
	}
	return *this;
}

// Toán tử +
QInt QInt::operator+(QInt s)
{
	QInt one("1");
	QInt result = *this;
	QInt carry("1");
	while (!(carry.isEqualZero()))
	{
		carry = (result & s);
		result = result ^ s;
		s = carry << one;
	}
	return result;
}

// Toán tử - 
QInt QInt::operator-(QInt s)
{
	QInt bu2s = s.SoBu2();
	return *this + bu2s;
}

// Toán tử *

QInt QInt::operator *(QInt s)
{
	QInt one("1");
	QInt thaythe = *this;
	bool negative = false;
	if (thaythe.isNegative() && s.isNegative())
	{
		thaythe = ~(thaythe - QInt("1"));
		s = ~(s - QInt("1"));
	}
	else if (thaythe.isNegative() && !s.isNegative())
	{
		negative = true;
		thaythe = ~(thaythe - QInt("1"));
	}
	else if (!thaythe.isNegative() && s.isNegative())
	{
		negative = true;
		s = ~(s - QInt("1"));
	}
	QInt result;

	if (thaythe.isEqualZero() || s.isEqualZero())
	{
		return result;
	}

	while (!s.isEqualZero())
	{
		if ((s & QInt("1")) == QInt("1"))
		{
			result = result + thaythe;
		}
		thaythe = thaythe << one;
		s = s >> one;
	}

	if (negative)
	{
		result = result.SoBu2();
	}
	return result;
}

// Toán tử /
QInt QInt::operator /(QInt bichia)
{
	QInt one("1");
	QInt sochia = *this;
	if (bichia.isEqualZero())
	{
		throw "Divide Zero";
	}
	if (sochia == bichia)
	{
		return QInt("1");
	}

	bool negative = false;

	if (sochia.isNegative() && bichia.isNegative())
	{
		sochia = ~(sochia - QInt("1"));
		bichia = ~(bichia - QInt("1"));
	}
	else if (sochia.isNegative() && !bichia.isNegative())
	{
		negative = true;
		sochia = ~(sochia - QInt("1"));
	}
	else if (!sochia.isNegative() && bichia.isNegative())
	{
		negative = true;
		bichia = ~(bichia - QInt("1"));
	}

	if (sochia < bichia)
	{
		return QInt("0");
	}

	QInt thuong, temp("1");

	while (bichia <= sochia)
	{
		bichia = bichia << one;
		temp = temp << one;
	}

	while (temp > QInt("1"))
	{
		bichia = bichia >> one;
		temp = temp >> one;

		if (sochia >= bichia)
		{
			sochia = sochia - bichia;
			thuong = thuong + temp;
		}
	}

	if (negative)
	{
		thuong = thuong.SoBu2();
	}

	return thuong;
}

// Toán tử %
QInt QInt::operator %(QInt s)
{
	QInt thuong = *this / s;
	QInt sodu = *this - (s * thuong);
	return sodu;
}