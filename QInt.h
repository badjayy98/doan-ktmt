#ifndef _QINT_H_
#define _QINT_H_
#endif

#include "Function.h"
#include <stdint.h>

// Ý tưởng : biểu diễn số nguyên dưới dạng 1 vecto chứa 4 unsigned int, 1 unsigned int = 4 byte.

class QInt
{
private:
	vector<uint32_t> data;
public:
	//-Nhóm hàm khởi tạo ---------------------------------------------------------------------------------------//
	QInt();
	QInt(string binary);

	//-Nhóm hàm Get, Set ------------------------------------------------------------------//
	vector<unsigned int> getData();
	void setData(int position, int value);

	//-Nhóm hàm hỗ trợ ---------------------------------------------------------------------------
	bool isEqualZero();
	bool isNegative();
	int getPosition(int size, int i);
	int getOffset(int size, int i);

	//-NHÓM HÀM CONVERT --------------------------------------------------------------------------//
	static QInt convertBinaryToQInt(string binary);
	static QInt convertDecimalToQInt(string decimal);
	static QInt convertHexToQInt(string hex);
	string convertQIntToBinary();
	string convertQIntToDecimal();
	string convertQIntToHex();
	QInt SoBu2();


	//-TOÁN TỬ BIT >> <<, ROR, ROL, AND OR XOR NOT ------------------------------------------------------//
	QInt operator << (QInt n);
	QInt operator >> (QInt n);
	QInt ROL(QInt n);
	QInt ROR(QInt n);

	QInt operator & (QInt s);
	QInt operator | (QInt s);
	QInt operator ^ (QInt s);
	QInt operator~();

	// ------------TOÁN TỬ SO SÁNH--------------------------------------------------------//
	bool operator > (QInt s);
	bool operator < (QInt s);
	bool operator == (QInt s);
	bool operator >= (QInt s);
	bool operator <= (QInt s);
	QInt operator =(QInt s);

	//---------------- NHẬP XUẤT -------------------------------//
	// Toán tử xuất
	friend ostream& operator <<(ostream& os, QInt& c)
	{
		if (c.isEqualZero())
		{
			cout << "0" << endl; 
		}
		else
		{
			os << c.convertQIntToDecimal() << endl;
		}
		return os; 
	}

	// Toán tử nhập 
	friend istream& operator >>(istream& is, QInt& c)
	{
		string decimal; 
		cout << "Nhap chuoi thap phan : ";
		cin.sync();
		getline(is, decimal);
		QInt result = QInt::convertDecimalToQInt(decimal);
		c = result; 
		return is; 
	}

	//-------------------------- NHÓM TOÁN TỬ +, -, x, -----------------------/
	QInt operator+(QInt s); 
	QInt operator-(QInt s);
	QInt operator *(QInt s);
	QInt operator /(QInt bichia);
	QInt operator %(QInt s);

	QInt chia(QInt m);
};




