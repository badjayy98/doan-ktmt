// Bai1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include "FPNumber.h"
#include "supportFunction.h"
#include "Run.h"
int main()
{
	//Doc so thap phan dang 21312.213 tu file input thanh dang nhi phan
	/*FPNumber* Qfloat = new FPNumber();
	string input;
	cout << "Nhap vao day can scan: ";
	cin >> input;
	Qfloat->scanFPN(input);
	cout << "Ket qua duoi dang nhi phan la: " << endl;
	//So tai dau '|' thuoc day phia sau
	cout << "S|-----EXP------|-----Value----|" << endl;
	Qfloat->out();
	*/
	//string src = "01000000000000001101011011110011101000001101001010110110110000001110000001011000110011010000011110101100000101001010110010101101";
	//cout << binToDec(src) << endl;
	//cout << plus2Int("00123", "025") << endl;
	RunFloatProgram();
	system("pause");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
