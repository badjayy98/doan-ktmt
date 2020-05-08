#include "ChamTuDongQInt.h"
int main(int argc, char *argv[])
{
	try
	{
		QInt a, b, c;
		cin >> a; 
		cin >> b; 
		c = a / b; 
		cout << c; 
	}
	catch (const char* msg)
	{
		cout << msg << endl; 
	}

}