#include "pch.h"
#include "supportFunction.h"
#include "FPNumber.h"

//Đọc sô thập phân như 112113.123123123 thành dãy 0 1
void FPNumber::scanFPN(string inputNum)
{
	//string inputNum = getStringFromFile(fileIn); 
	int inputlen = inputNum.size();
	string phanNguyenNP = "";// Phan truoc dau '.'
	string phanDuNP = "";//Phan sau dau '.'
	string phanTPInput = "";
	string phanNguyenInput = tachChuoi(inputNum, '.', phanTPInput);

	//Phan dau xu ly sau
	char sgn = phanNguyenInput[0];
	int isgn = 0;
	if (sgn == '-') {
		isgn = 1;
		popHead(phanNguyenInput);
	}

	while (phanNguyenInput!="0")
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
			lamTron(isgn,phanDuNP);
			break;
		}
	}

	if (phanNguyenNP == "")
		phanNguyenNP = "0";

	int itmp = 0;
	if (phanNguyenNP == "0"){
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

	if (sgn == '-') {
		this->soChamDong[3]=setBit1(this->soChamDong[3], 31);
	}

	for (int i = 17; i <32; i++) {
		if (getBit(exp, i) == 1)
			this->soChamDong[3] = setBit1(this->soChamDong[3], 143-i);	//Phan mu bat dau tu bit so 112 thuoc so thu 4(96-127)
	}

	int fraclen = fraction.size() - 1;
	for (int i = 0; i <= fraclen; i++) {
		if (fraction[i] == '1')
			this->soChamDong[(111-i) / 32] = setBit1(this->soChamDong[(111-i) / 32], (111-i) % 32);
	}

}

string FPNumber::printFPN()
{
	//Phương thức out() thay thế cái này
	cout << this->out() << endl;
	return string();
}

string FPNumber::binToDec(string fileIn)
{
	return string();
}

string FPNumber::decToBin(string dec)
{
	return string();
}

string FPNumber::out()
{
	string res = "";
	for (int i = 3; i >=0; i--)
	{
		for (int j = 31; j >= 0; j--)
			res = res + char(getBit(this->soChamDong[i], j) + 48);
	}
	return res;
}

FPNumber::FPNumber()
{
	for (int i = 0; i < 4; i++) {
		soChamDong[i] = 0;
	}
}
