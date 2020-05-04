#include "Convert.h"
#include <fstream>
#include <sstream>


// Convert string theo base
string convertToBase(QInt s, string base)
{
	string result; 
	if (base == "binary")
	{
		result = convertToBinary(s);
	}
	else if (base == "decimal")
	{
		result = convertQIntToDecimal(s);
	}
	else if (base == "hexa")
	{
		result = convertQIntToHex(s);
	}
	return result; 
}

// Thực hiện phép tính giữa 2 QInt
string ThucHienPhepTinh2QInt(QInt toantu1, QInt toantu2, string pheptoan, string base)
{
	string res; 
	QInt result; 
	if (pheptoan == "+")
	{
		result = toantu1 + toantu2; 
	}
	else if (pheptoan == "-")
	{
		result = toantu1 - toantu2;
	}
	else if (pheptoan == "*")
	{
		result = toantu1 * toantu2;
	}
	else if (pheptoan == "/")
	{
		result = toantu1 / toantu2;
	}
	else if (pheptoan == "&")
	{
		result = toantu1 & toantu2; 
	}
	else if (pheptoan == "|")
	{
		result = toantu1 | toantu2; 
	}
	else if (pheptoan == "^")
	{
		result = toantu1 ^ toantu2; 
	}

	res = convertToBase(result, base);
	return res; 
}

// Thực hiện phép tính giữa QInt với 1 số


// Xử lý các phép tính lấy được từ các dòng của input.txt
void XuLyPhepTinh(vector<string> calc)
{
	QInt toantu1, toantu2;
	ofstream ofile("output.txt");
	// Yêu cầu quy đổi
	if (calc.size() == 3)
	{

	}

	// Phép tính
	else
	{
		string base; 
		if (calc[0] == "2")
		{
			base = "binary";
		}
		else if (calc[0] == "10")
		{
			base = "decimal";
			toantu1 = convertDecimalToQInt(calc[1]);
			toantu2 = convertDecimalToQInt(calc[3]);
		}
		else
		{
			base = "hexa";
			toantu1 = convertHexToQInt(calc[1]);
			toantu2 = convertHexToQInt(calc[3]);
		}

		if (calc[2] == ">>" || calc[2] == "<<" || calc[2] == "ROR" || calc[2] == "ROL")
		{
			
		}
		else
		{
			ThucHienPhepTinh2QInt(toantu1, toantu2, calc[2], base);
		}


	}
}


int main(int argc, char *argv[])
{
	QInt one("1");
	
	QInt zero("0");
	QInt p("1001"); // p = 9
	// s = -1
	QInt s("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111000");

	// x = -3
	QInt x("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111101");
	QInt a("1001111100"); // a = 636

	QInt b = a % p;
	cout << convertQIntToDecimal(b) << endl;





	/*cout << argv[1] << endl;
	cout << argv[2] << endl; 

	ifstream ifile("input.txt");
	ofstream ofile("output.txt");
	string line;
	string ptu;

	while (getline(ifile, line))
	{
		vector<string> calc;
		istringstream iss(line);
		while (iss >> ptu)
		{
			calc.push_back(ptu);
		}
		for (int i = 0; i < calc.size(); i++)
		{
			cout << calc[i] << endl; 
		}
		cout << endl;
	}*/
}