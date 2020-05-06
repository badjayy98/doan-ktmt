// Các hàm hỗ trợ

#ifndef _FUNCTION_H
#define _FUNCTION_H
#endif
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

// Hàm đảo ngược chuỗi
void reverseStr(string& str);
// Biến chuỗi nhị phân thành 1 số nguyên
int binaryToDecimal(string n);

// Kiểm tra giá trị str1 có nhỏ hơn giá trị str2 hay ko
bool isSmaller(string str1, string str2);



// Hàm trừ 2 string, 2 str ko phải số âm
string TruHaiChuoiKhongXetDau(string str1, string str2);

// Cộng hai chuỗi 
string CongHaiChuoi(string str1, string str2);



// Trừ hai chuỗi
string TruHaiChuoi(string str1, string str2);


// Nhân hai chuỗi
string NhanHaiChuoi(string s1, string s2);


// Chia 1 chuỗi cho 2 
string Division2(string number);

// Kiểm tra chuỗi có phải số chẵn 
bool isEven(string number);

// Chuyển chuỗi decimal thành chuỗi binary
string decimalToBinary(string decimal);

// Chuyển chuỗi hex thành chuỗi binary
string hexToBinary(string hex);


// Tính 2^n
string LuyThua2(int n);

string convertBinaryToHex(string binary);


