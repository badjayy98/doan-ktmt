#include "ChamTuDongQInt.h"
string convertToBase(QInt s, string base)
{
	string result;
	if (base == "binary")
	{
		result = s.convertQIntToBinary();
	}
	else if (base == "decimal")
	{
		result = s.convertQIntToDecimal();
	}
	else if (base == "hexa")
	{
		result = s.convertQIntToHex();
	}
	return result;
}

// Thực hiện phép tính giữa 2 QInt
string ThucHienPhepTinh2QInt(QInt toantu1, QInt toantu2, string pheptoan, string base)
{
	bool right;
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
	else if (pheptoan == ">>")
	{
		result = toantu1 >> toantu2;
	}
	else if (pheptoan == "<<")
	{
		result = toantu1 << toantu2; 
	}
	else if (pheptoan == "ror")
	{
		result = toantu1.ROR(toantu2);
	}
	else if (pheptoan == "rol")
	{
		result = toantu1.ROL(toantu2);
	}
	else if (pheptoan == ">")
	{
		if (toantu1 > toantu2)
		{
			return "true";
		}
		else
		{
			return "false";
		}
	}
	else if (pheptoan == "<")
	{
		if (toantu1 < toantu2)
		{
			return "true";
		}
		else
		{
			return "false";
		}
	}
	else if (pheptoan == ">=")
	{
		if (toantu1 >= toantu2)
		{
			return "true";
		}
		else
		{
			return "false";
		}
	}
	else if (pheptoan == "<=")
	{
		if (toantu1 <= toantu2)
		{
			return "true";
		}
		else
		{
			return "false";
		}
	}
	else if (pheptoan == "==")
	{
		if (toantu1 == toantu2)
		{
			return "true";
		}
		else
		{
			return "false";
		}
	}
	res = convertToBase(result, base);
	return res;
}

// Thực hiện phép tính giữa QInt với 1 số


// Xử lý các phép tính lấy được từ các dòng của input.txt
void XuLyPhepTinh(vector<string> calc, string fileoutput)
{
	/*cout << "Phep tinh : ";
	for (int i = 0; i < calc.size(); i++)
	{
		cout << calc[i] << " ";
	}
	cout << endl;*/
	QInt toantu1, toantu2, quyDoiVeQInt;
	ofstream ofile;
	ofile.open(fileoutput, ios_base::app);
	// Yêu cầu quy đổi hoặc NOT
	if (calc.size() == 3)
	{
		// NOT
		if (calc[1] == "~")
		{
			string result;
			if (calc[0] == "2")
			{
				QInt bin = QInt::convertBinaryToQInt(calc[2]);
				bin = ~bin;
				result = bin.convertQIntToBinary();
			}
			else if (calc[0] == "10")
			{
				QInt dec = QInt::convertDecimalToQInt(calc[2]);
				dec = ~dec;
				result = dec.convertQIntToDecimal();
			}
			else if (calc[0] == "16")
			{
				QInt hex = QInt::convertHexToQInt(calc[2]);
				hex = ~hex;
				result = hex.convertQIntToHex();
			}
			ofile << result << endl;

		}
		// Quy đổi
		else
		{
			string result;
			string heTruoc = calc[0];
			string heSau = calc[1];
			string so = calc[2];
			if (heTruoc == "2")
			{
				quyDoiVeQInt = QInt::convertBinaryToQInt(so);
			}
			else if (heTruoc == "10")
			{
				quyDoiVeQInt = QInt::convertDecimalToQInt(so);
			}
			else if (heTruoc == "16")
			{
				quyDoiVeQInt = QInt::convertHexToQInt(so);
			}

			if (heSau == "2")
			{
				result = quyDoiVeQInt.convertQIntToBinary();
			}
			else if (heSau == "10")
			{
				result = quyDoiVeQInt.convertQIntToDecimal();
			}
			else if (heSau == "16")
			{
				result = quyDoiVeQInt.convertQIntToHex();
			}
			ofile << result << endl;
		}

	}

	// Phép tính giữa 2 toán tử 
	else
	{
		string base;

		if (calc[2] == "<<" || calc[2] == ">>" || calc[2] == "ror" || calc[2] == "rol")
		{
			toantu2 = QInt::convertDecimalToQInt(calc[3]);
			if (calc[0] == "2")
			{
				base = "binary";
				toantu1 = QInt::convertBinaryToQInt(calc[1]);
			}
			else if (calc[0] == "10")
			{
				base = "decimal";
				toantu1 = QInt::convertDecimalToQInt(calc[1]);
			}
			else
			{
				base = "hexa";
				toantu1 = QInt::convertHexToQInt(calc[1]);
			}
		}
		else
		{
			if (calc[0] == "2")
			{
				base = "binary";
				toantu1 = QInt::convertBinaryToQInt(calc[1]);
				toantu2 = QInt::convertBinaryToQInt(calc[3]);
			}
			else if (calc[0] == "10")
			{
				base = "decimal";
				toantu1 = QInt::convertDecimalToQInt(calc[1]);
				toantu2 = QInt::convertDecimalToQInt(calc[3]);
			}
			else
			{
				base = "hexa";
				toantu1 = QInt::convertHexToQInt(calc[1]);
				toantu2 = QInt::convertHexToQInt(calc[3]);
			}
		}
		string result = ThucHienPhepTinh2QInt(toantu1, toantu2, calc[2], base);
		ofile << result << endl;
	}
}
void ThucHienChamTuDong(string fileinput, string fileoutput)
{
	ifstream ifile(fileinput);
	ofstream ofile;
	ofile.open(fileoutput, ios::out | ios::trunc);
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
		XuLyPhepTinh(calc, fileoutput);
	}
}