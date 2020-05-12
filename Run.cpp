#include "pch.h"
#include "Run.h"
#include "supportFunction.h"
#include "FPNumber.h"

//abstract:
//Chạy tham số dòng lệnh, đọc tham số để chọn chương trình
//Chọn yêu cầu: đọc ghi ra file hay nhập xuất số Qfloat
//In ra menu cho nó chọn
//Nếu là convert trong file thì nhập tên file

string decToBin(string decStr) {
	int inputlen = decStr.size();

	string phanNguyenNP = "";// Phan truoc dau '.'
	string phanDuNP = "";//Phan sau dau '.'

	string phanTPInput = "";
	string phanNguyenInput = tachChuoi(decStr, '.', phanTPInput);
	//Phan dau xu ly sau
	char sgn = phanNguyenInput[0];
	int isgn = 0;
	if (sgn == '-') {
		popHead(phanNguyenInput);
		isgn = 1;
	}

	while (phanNguyenInput != "0")
	{
		if (isChan(phanNguyenInput[phanNguyenInput.size() - 1]))
			phanNguyenNP = '0' + phanNguyenNP;
		else
			phanNguyenNP = '1' + phanNguyenNP;
		phanNguyenInput = div2(phanNguyenInput);
	}
	while (!isEqual0(phanTPInput)) {
		char tmp = phanTPInput[0];
		phanTPInput = nhanDoiPhanTP(phanTPInput);
		if (tmp < '5')
			phanDuNP.push_back('0');
		else {
			phanDuNP.push_back('1');
			//Nếu sau khi nhân 2 nó lớn hơn 1 thì xóa cái số 1 ở đầu đi
			string tmp2 = "";
			for (int i = 1; i < phanTPInput.size(); i++) {
				tmp2.push_back(phanTPInput[i]);
			}
			phanTPInput = tmp2;
		}
		if (phanDuNP.size() == 112) {
			lamTron(isgn, phanDuNP);
			break;
		}
	}

	if (phanNguyenNP == "")
		phanNguyenNP = "0";
	//cout << phanNguyenNP << "." << phanDuNP << endl;

	int itmp = 0;
	if (phanNguyenNP == "0") {
		for (int i = 0; i < phanDuNP.size(); i++) {
			if (phanDuNP[i] == '1') {
				phanDuNP[i] = '0';
				itmp = i + 1;
				break;
			}
		}
		for (int i = 0; i < itmp; i++) {
			popHead(phanDuNP);
		}
		phanNguyenNP = "1";	//Chuyen so 1 qua phan nguyen
	}

	//Thiet lap Exponent
	int exp = phanNguyenNP.size() - 1 + pow(2, 14) - 1 - itmp;
	string fraction = phanNguyenNP + phanDuNP;
	popHead(fraction);
	FPNumber* Qfloat = new FPNumber();
	if (sgn == '-') {
		Qfloat->getSoChamDong()[3] = setBit1(Qfloat->getSoChamDong()[3], 31);
	}
	else {
	}
	for (int i = 17; i < 32; i++) {
		if (getBit(exp, i) == 1)
			Qfloat->getSoChamDong()[3] = setBit1(Qfloat->getSoChamDong()[3], 143 - i);	//Phan mu bat dau tu bit so 112 thuoc so thu 4(96-127)
	}
	
	int fraclen = fraction.size() - 1;
	//cout << fraction << endl;
	for (int i = 0; i <= fraclen; i++) {
		if (fraction[i] == '1')
			Qfloat->getSoChamDong()[(111 - i) / 32] = setBit1(Qfloat->getSoChamDong()[(111 - i) / 32], (111 - i) % 32);
	}
	return Qfloat->out();
}

string binToDec(string binStr) {
	string res = "";
	
	//Chia ra phần mũ với phần trị
	string strExp = binStr.substr(1, 15);
	string strVal = binStr.substr(16, 127);

	//Xét dấu
	string sign = "";
	if (binStr[0] == '1') {
		res = '-' + res;
	}

	//Xét trường hợp EXP toàn số 0
	if (isEqual0(strExp))
	{
		if (isEqual0(strVal))
		{
			return string("0");
		}
		else
		{
			return string("CHUOI KHONG CHUAN HOA");
		}
	}
	//Xét trường hợp EXP toàn số 1
	if (isFullOf(strExp, '1'))
	{
		if (isFullOf(strVal, '0'))
		{
			return string("INFINITY");
		}
		else
		{
			return string("NaN");
		}
	}

	//Đưa về dạng nhị phân đúng
	unsigned int uexp = stoi(strExp, nullptr, 2);
	int exp = uexp - pow(2,14)+1;
	
	string phanNguyenNP = "1";
	string phanDuNP = strVal;

	if (exp > 0) {
		strVal = strVal.substr(exp, strVal.size() - 1);
		for (int i = 0; i < exp; i++) {
			phanNguyenNP += popHead(phanDuNP);
		}
	}
	else {
		phanNguyenNP = "";
		phanDuNP = "1" + phanDuNP;
		exp++;
		if(exp<0){
			for (int i = 0; i > exp; i--) {
				phanDuNP = "0" + phanDuNP;
			}
		}
	}
	//res = res + phanNguyenNP + phanDuNP;
	//Chuyen phan nguyen tu nhi phan thanh thap phan
	string phanNguyenTP = "0";
	for (int i = 0; i < phanNguyenNP.size() - 1; i++) {
		if (phanNguyenNP[i] == '1') {
			string temp = "1";
			for (int j = 0; j < phanNguyenNP.size()-i; j++) {
				temp = mulby2Int(temp);
			}
			phanNguyenTP = plus2Int(phanNguyenTP, temp);
		}
	}

	

	//Chuyển phần sau dấu  từ nhị phân sang thập phân
	string phanDuTP = "0";
	for (int i = 0; i < phanDuNP.size(); i++) {
		if (phanDuNP[i] == '1') {
			string itemp = "1";
			for (int j = 0; j <= i; j++) {
				itemp = mulBy5Int(itemp);
			}
			int delta = i - itemp.size();
			for (int i = 0; i < delta; i++) {
				itemp = "0" + itemp;
			}
			phanDuTP = plus2Float(phanDuTP, itemp);
		}
	}
	res = phanNguyenTP + '.' + phanDuTP;
	return res;
}

void RunFloatProgram(string fileinput, string fileoutput)
{
	string fileIn = fileinput;
	ifstream file;
	string res = "";
	file.open(fileIn);
	while (file)
	{
		string src = "";
		string des = "";
		getline(file, src);
		if (src.substr(0, 4) == "10 2") {
			des = decToBin(src.substr(5, src.size() - 1));
		}
		else {
			if (src.substr(0, 4) == "2 10") {
				des = binToDec(src.substr(5, src.size() - 1));
			}
		}
		res = res + des + '\n';
	}
	file.close();
	ofstream out;
	out.open(fileoutput, 'w');
	out << res << endl;
	out.close();
	cout << SuccessOutput << endl;

}