#include "ChamTuDongQInt.h"
#include "Run.h"

int main(int argc, char *argv[])
{
	string type = argv[3];
	if (type == "1")
	{
		cout << "Thuc hien cham tu dong QInt" << endl; 
		ThucHienChamTuDong(argv[1], argv[2]);
	}
	else if (type == "2")
	{
		cout << "Thuc hien cham tu dong QFloat" << endl; 
		RunFloatProgram(argv[1], argv[2]);
	}

}