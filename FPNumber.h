#pragma once

class FPNumber
{
private:
	int soChamDong[4];
public:
	void scanFPN(string inputNum);
	int* getSoChamDong() { return soChamDong; }
	string printFPN();
	string binToDec(string fileIn);
	string decToBin(string fileIn);
	string out();
	FPNumber();
};