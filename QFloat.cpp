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

// Đổi từ số nguyên thành số nhị phân
string toBinary(string number) {
	string result = "";
	string x = number;
	while (x != "0") {
		int bit = x.back() % 2;
		if (bit == 1) result = "1" + result;
		else result = "0" + result;
		x = Division2(x);
	}
	return result;
}

// Nhân đôi số thực
string mulFractionByTwo(string number) {
	int len = number.length();
	string result;
	int k = number.find('.');
	int carry = 0, tmp;

	if (k != string::npos) {
		// Nhân 2 với phần thập phân
		for (int i = len - 1; i > k; --i) {
			tmp = (number[i] - '0') * 2 + carry;
			if (tmp >= 10) {
				result.insert(result.begin(), char(tmp - 10 + '0'));
				carry = 1;
			}
			else {
				result.insert(result.begin(), char(tmp + '0'));
				carry = 0;
			}
		}
		result.insert(result.begin(), '.');

		// Nhân 2 với phần nguyên trước dấu '.'
		for (int i = k - 1; i >= 0; --i) {
			tmp = (number[i] - '0') * 2 + carry;
			if (tmp >= 10) {
				result.insert(result.begin(), char(tmp - 10 + '0'));
				carry = 1;
			}
			else {
				result.insert(result.begin(), char(tmp + '0'));
				carry = 0;
			}
		}
	}
	else {
		for (int i = len - 1; i >= 0; --i) {
			tmp = (number[i] - 48) * 2 + carry;
			if (tmp >= 10) {
				result.insert(result.begin(), char(tmp - 10 + '0'));
				carry = 1;
			}
			else {
				result.insert(result.begin(), char(tmp + '0'));
				carry = 0;
			}
		}
	}
	if (carry == 1) result.insert(result.begin(), '1');
	return result;
}

string toStrBit(string number, int& exp) {
	int pos = number.find('.');
	string intPart, fractionPart;
	if (pos == string::npos) {
		intPart = number;
		fractionPart = "0";
	}
	else {
		intPart = number.substr(0, pos);
		fractionPart = number.substr(pos);
		fractionPart.insert(fractionPart.begin(), '0');
	}
	// Chuyển string của phần nguyên sang binary
	intPart = toBinary(intPart);

	int k = (1 << 14) - 1;
	string fractionBit;

	if (intPart != "") {
		exp = intPart.size() - 1 + k;
		for (int i = 0; i < 112 - int(intPart.size() - 1); ++i) {
			fractionPart = mulFractionByTwo(fractionPart);
			fractionBit += fractionPart[0];
			fractionPart[0] = '0';
		}
	}
	else {
		int cnt = 0;
		while (cnt < k) {
			fractionPart = mulFractionByTwo(fractionPart);
			fractionBit += fractionPart[0];
			fractionPart[0] = '0';
			if (fractionBit.back() == '1') break;
			cnt++;
		}

		exp = -(cnt + 1) + k;
		if (cnt + 1 < k) {
			for (int i = 0; i < 112; ++i) {
				fractionPart = mulFractionByTwo(fractionPart);
				fractionBit += fractionPart[0];
				fractionPart[0] = '0';
			}
		}
		else {
			fractionBit = "";
			while (exp < 1) {
				fractionPart = mulFractionByTwo(fractionPart);
				fractionBit += fractionPart[0];
				fractionPart[0] = '0';
				exp++;
			}
			string res = intPart + fractionBit;
			while (res.size() < 113) res += '0';
			return res;
		}
	}

	string res = intPart + fractionBit;
	while (res[0] == '0') res.erase(0, 1);
	while (res.size() < 113) res += '0';
	return res;
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

	string thapPhan = "0." + number.substr((int)foundPos + 1);

	// Chuyển phần nguyên sang binary
	nguyen = decimalToBinary(nguyen);
	if (nguyen == "")
	{
		nguyen = "0";
	}

	// Chuyển phần thập phân sang binary
	string temp, binThapPhan = "";
	while (nguyen.size() + binThapPhan.size() < 113)
	{
		thapPhan = FloatMul2(thapPhan);
		binThapPhan += thapPhan[0];
		thapPhan[0] = '0';
	}
	string result = nguyen  + binThapPhan;

	/*if (CanLamTron)
	{
		if (negative)
		{
			QInt bin = QInt::convertBinaryToQInt(binThapPhan);
			QInt res = bin - QInt("1");
			binThapPhan = res.convertQIntToBinary();
			while (binThapPhan.size() < 112 - nguyen.size())
			{
				binThapPhan += '0';
			}
			result = nguyen  + binThapPhan;
		}
		else
		{
			QInt bin = QInt::convertBinaryToQInt(binThapPhan);
			QInt res = bin + QInt("1");
			binThapPhan = res.convertQIntToBinary();
			while (binThapPhan.size() > 112 - nguyen.size())
			{
				binThapPhan.pop_back();
			}
			result = nguyen  + binThapPhan;
		}
	}*/

	return result;
}

string getSignifcand(string binary)
{
	// Chuẩn hoá dạng trị thành 1.xxx
	int foundPos = (int)binary.find('.');
	string phanNguyen = binary.substr(0, foundPos);
	string phanThapPhan = binary.substr(foundPos + 1);

	while (phanNguyen[phanNguyen.size() - 1] == '0')
	{
		phanNguyen += phanThapPhan[0];
		phanThapPhan.erase(0, 1);
	}
	string result = phanNguyen + '.' + phanThapPhan;
	return result;
}

string getExponent(string binary)
{
	string result;
	int dich = (int)binary.find('.') - 1;
	int exp = 32767 + dich;
	return result;

}


QFloat::QFloat()
{
	for (int i = 0; i < 16; i++)
	{
		data[i] = 0;
	}
}
QFloat::QFloat(string number)
{


}
void QFloat::setBit(int position, int value)
{
	int posToInsert = (position - 1) / 8;
	int offset = (8 - (position % 8));
	data[posToInsert] = data[posToInsert] | (1 << offset);
}
// Lấy vị trí phần tử để đặt bit, phục vụ khởi tạo QInt với 1 chuỗi binary
int QFloat::getPosition(int size, int i)
{
	return (size - 1 - i) / 32;
}

// Tính toán xem sẽ phải dịch chuyển bao nhiêu bit, phục vụ khởi tạo QInt với 1 chuỗi binary
int QFloat::getOffset(int size, int i)
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