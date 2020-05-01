#include "Convert.h"

// Bài 1 : khai báo 2 biến QInt a, QInt b
// Hàm nhập : cin >> a
// Hàm xuất : cout << b
// Chuyển từ QInt sang nhị phân : string binary = a.convertToBinary()
// Chuyển từ nhị phân sang QInt : a = convertToDecimal("01001110")
// Chuyển đổi chuỗi nhị phân sang thập lục phân : string hex = convertBinaryToHex("0110001")
// Chuyển đổi QInt thành chuỗi thập lục phân : string hex = convertDecimalToHex(a)


int main()
{
	QInt one("1");
	
	QInt zero("0");
	QInt p("1001"); // p = 9
	// s = -1
	QInt s("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
	QInt a("100111"); // a = 39

	QInt b = a / p;
	QInt c = s / a;
	QInt d = p / one;

	cout << "a / p = " << b;
	cout << "Gia tri thap phan a / p : " << DecimalValue(b) << endl; 
	cout << "s / a = " << c;
	cout << "Gia tri thap phan s / a : " << DecimalValue(c) << endl; 
	cout << "p / one = " << d;
	cout << "Gia tri thap phan p / one : " << DecimalValue(d) << endl;


}