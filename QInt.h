#ifndef _QINT_H_
#define _QINT_H_
#endif

#include "Function.h"

// Ý tưởng : biểu diễn số nguyên dưới dạng 1 vecto chứa 4 unsigned int, 1 unsigned int = 4 byte.

class QInt
{
private:
	vector<uint32_t> data;
public:
	// Nhóm hàm khởi tạo ---------------------------------------------------------------------------------------
	// Khởi tạo mặc định vector có 4 phần tử
	QInt()
	{
		this->data.resize(4);
		for (int i = 0; i < 4; i++)
		{
			data[i] = 0;
		}
	}

	// Khởi tạo 1 QInt bằng cách nhập 1 chuỗi binary, tối đa 128 ký tự 
	QInt(string binary)
	{
		if (binary.size() == 0)
		{
			cout << "Khong the nhan chuoi 0 co ky tu" << endl;
			return;
		}
		if (binary.size() > 128)
		{
			cout << "Khogn the nhan chuoi qua 128 ky tu" << endl;
			return;
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
	// -----------------------------------------------------------------------------------------------------------

	// Nhóm hàm Get, Set ------------------------------------------------------------------
	vector<unsigned int> getData()
	{
		return data;
	}

	void setData(int position, int value)
	{
		data[position] = value;
	}
	// -------------------------------------------------------------------------------------

	// Nhóm hàm hỗ trợ ---------------------------------------------------------------------------
	// Kiểm tra QInt có bằng 0 hay ko
	bool isEqualZero()
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
	bool isNegative()
	{
		if (((this->data[3] >> 31) & 1 )== 1)
		{
			return true;
		}
		return false; 
	}

	// Lấy vị trí phần tử để đặt bit, phục vụ khởi tạo QInt với 1 chuỗi binary
	int getPosition(int size, int i)
	{
		return (size - 1 - i) / 32;
	}

	// Tính toán xem sẽ phải dịch chuyển bao nhiêu bit, phục vụ khởi tạo QInt với 1 chuỗi binary
	int getOffset(int size, int i)
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

	// --------------------------------------------------------------------------------------------

	// NHÓM HÀM CONVERT --------------------------------------------------------------------------

	// Đổi 1 QInt sang dạng nhị phân

	string convertToBinary()
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



	// Chuyển số QInt dương thành QInt âm
	QInt SoBu2()
	{
		return ~(*this) + QInt("1");
	}

	// -------------------------------------------------------------------------------------------

	// TOÁN TỬ BIT >> <<, ROR, ROL -------------------------------------------------------------------------

	// Ý tưởng : Biến QInt thành dạng chuỗi binary, lấy chuỗi con dựa theo số bit dịch chuyển, thêm '0' phía sau để đủ 128 bit, chuyển từ binary thành QInt
	QInt operator << (int n)
	{
		// Chạy tốt khi n < 32 bit, tuy nhiên khi n >= 32 bit thì chạy không đúng
		//QInt result;
		//
		//for (int i = 3; i >= 1; i--)
		//{
		//	result.data[i] = (data[i] << n) | (data[i - 1] >> (32 - n));
		//}
		//result.data[0] = (data[0] << n) | (0 >> (32 - n));
		//return result;

		if (n > 128)
		{
			return QInt("0");
		}

		string binary = convertToBinary();

		while (binary.size() != 128)
		{
			binary.insert(binary.begin(), '0');
		}

		string resultAfterSL;

		resultAfterSL = binary.substr(n, 128 - n);

		while (resultAfterSL.size() != 128)
		{
			resultAfterSL = resultAfterSL + '0';
		}

		QInt resultQInt(resultAfterSL);
		return resultQInt;
	}

	// Toán tử >>
	QInt operator >> (int n)
	{
		if (n > 128)
		{
			return QInt("0");
		}
		string binary = convertToBinary();
		while (binary.size() != 128)
		{
			binary.insert(binary.begin(), '0');
		}

		string resultAfterSr; 

		resultAfterSr = binary.substr(0, 128 - n);

		while (resultAfterSr.size() != 128)
		{
			resultAfterSr.insert(resultAfterSr.begin(), '0');
		}

		QInt resultQInt(resultAfterSr);
		
		return resultQInt;
	}

	// Toán tử ROL

	QInt ROL(int n)
	{
		string binary = convertToBinary();

		string nBitDau = binary.substr(0, n);
		string remain = binary.substr(n, binary.size() - n);
		string resultBinary = remain + nBitDau;

		while (resultBinary.size() != 128)
		{
			resultBinary.insert(resultBinary.begin(), '0');
		}

		QInt resultQInt(resultBinary);
		return resultQInt;

	}

	// Toán tử ROR

	QInt ROR(int n)
	{
		string binary = convertToBinary();

		string nBitCuoi = binary.substr(binary.size() - n, n);
		string remain = binary.substr(0, binary.size() - n);

		string resultBinary = nBitCuoi + remain; 

		while (resultBinary.size() != 128)
		{
			resultBinary.insert(resultBinary.begin(), '0');
		}

		QInt resultQInt(resultBinary);
		return resultQInt;
	}

	// Toán tử AND
	QInt operator & (QInt s)
	{
		QInt result; 
		for (int i = 0; i < this->data.size(); i++)
		{
			result.data[i] = this->data[i] & s.data[i];
		}
		return result; 
	}

	// Toán tử OR
	QInt operator | (QInt s)
	{
		QInt result; 
		for (int i = 0; i < this->data.size(); i++)
		{
			result.data[i] = this->data[i] | s.data[i];
		}
		return result; 
	}

	// Toán tử XOR
	QInt operator ^ (QInt s)
	{
		QInt result; 
		for (int i = 0; i < this->data.size(); i++)
		{
			result.data[i] = this->data[i] ^ s.data[i];
		}
		return result; 
	}

	// Toán tử NOT
	QInt operator~()
	{
		QInt result; 
		for (int i = 0 ;i < this->data.size(); i++)
		{
			result.data[i] = ~this->data[i];
		}
		return result; 
	}

	// Toán tử so sánh >
	bool operator > (QInt s)
	{
		for (int i = 3; i >= 0; i--)
		{
			if (i != 0)
			{
				if (this->data[i] < s.data[i])
				{
					return false;
				}
			}
			else
			{
				if (this->data[i] <= s.data[i])
				{
					return false; 
				}
			}
		}
		return true; 
	}

	// Toán tử so sánh <
	bool operator < (QInt s)
	{
		for (int i = 3; i >= 0; i--)
		{
			if (i != 0)
			{
				if (this->data[i] > s.data[i])
				{
					return false; 
				}
			}
			else
			{
				if (this->data[i] >= s.data[i])
				{
					return false; 
				}
			}
		}
		return true;
	}
	
	// Toán tử so sánh ==
	bool operator == (QInt s)
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
	bool operator >= (QInt s)
	{
		for (int i = 3; i >= 0; i--)
		{
			if (this->data[i] < s.data[i])
			{
				return false;
			}
		}
		return true;
	}

	// Toán tử so sánh <=
	bool operator <= (QInt s)
	{
		for (int i = 3; i >= 0; i--)
		{
			if (this->data[i] > s.data[i])
			{
				return false;
			}
		}
		return true;
	}

	// Toán tử gán =
	QInt operator =(QInt s)
	{
		for (int i = 0; i < 4; i++)
		{
			this->data[i] = s.data[i];
		}
		return *this;
	}

	// Toán tử xuất
	friend ostream& operator <<(ostream& os, QInt& c)
	{
		os << c.convertToBinary() << endl; 
		return os; 
	}

	// Toán tử nhập 
	friend istream& operator >>(istream& is, QInt& c)
	{
		string binary;
		cout << "Nhap chuoi binary : ";
		is >> binary;
		QInt cac(binary);
		c = cac;
		return is; 
	}

	// NHÓM TOÁN TỬ +, -, x, /

	// Toán tử +
	QInt operator+(QInt s)
	{
		QInt result = *this;
		QInt carry("1");
		while (!(carry.isEqualZero()))
		{
			carry = (result & s);
			result = result ^ s;
			s = carry << 1;
		}
		return result;
	}

	// Toán tử - 
	QInt operator-(QInt s)
	{
		QInt bu2s = s.SoBu2();
		return *this + bu2s;
	}

	// Toán tử *

	QInt operator *(QInt s)
	{
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
			thaythe = thaythe << 1;
			s = s >> 1; 
		}

		if (negative)
		{
			result = result.SoBu2();
		}
		return result;
	}

	// Toán tử /

	QInt operator /(QInt bichia)
	{
		if (bichia.isEqualZero())
		{
			cout << "Khong the chia cho 0" << endl;
			return QInt("0");
		}
		bool negative = false; 
		QInt sochia = *this;
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

		if (sochia == bichia)
		{
			return QInt("1");
		}
		else if (sochia < bichia)
		{
			return QInt("0");
		}
		

		QInt thuong, temp("1");

		while (bichia <= sochia)
		{
			bichia = bichia << 1; 
			temp = temp << 1; 
		}

		while (temp > QInt("1"))
		{
			bichia = bichia >> 1; 
			temp = temp >> 1; 

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
	QInt operator %(QInt s)
	{
		QInt thuong = *this / s; 
		QInt sodu = *this - (s * thuong);
		return sodu;
	}
};




