#include "pch.h"
#include "supportFunction.h"

string getStringFromFile(string inputFile) {
    fstream f;
    f.open(inputFile, ios::in);
    string fstring;
    getline(f, fstring);
    f.close();
    return fstring;
}

int setBit1(int X, int i) {
    return (X | (1 << (31 - i)));
}

int getBit(int X, int i)
{
    return (X >> (31 - i)) & 1;
}

bool isChan(char num) {
    if ((num - 48) % 2 == 0)
        return true;
    return false;
}

string mul2(string number) {
    string result = "";
    int tmp = 0;
    int ketQua, soDu;
    for (int i = number.size() - 1; i >= 0; i--) {
        ketQua = (number[i] - 48) * 2 + tmp;
        tmp = ketQua / 10;
        soDu = ketQua % 10;
        result.push_back(soDu + 48);
    }
    string finalResult = "";
    for (int i = result.size() - 1; i >= 0; i--){
        finalResult.push_back(result[i]);
    }
    return finalResult;
}


string div2(string number) {
    string result = number;
    int len = number.length();
    int k = 0, tmp;
    for (int i = 0; i < len; ++i) {
        tmp = k * 10 + (number[i] - '0');
        result[i] = tmp / 2 + '0';
        k = tmp % 2;
    }
    // Xóa 0 ở đầu
    while (result[0] == '0')
        result.erase(0, 1);
    // Nếu kết quả bằng 0
    if (result == "")
        result = "0";
    return result;
}

string nhanDoiPhanTP(string phanTP) {
    //Xử lý phần thập phân đc tách từ file, thêm số 0 vào-- Không thêm dấu chấm để dễ tính toán
    //Chỉ thêm cho trường hợp x2 nó lớn hơn 1, bé hơn 1 không cần thiết.
    if (phanTP[0] > '4')
        phanTP = "0" + phanTP;
    //Nhân 2:
    int rem=0;//biến để nhớ
    string res = "";//chuỗi lưu kết quả
    int sum = 0;
    int modRes = 0;
    for (int i = phanTP.size() - 1; i >=0; i--) {
        sum = (phanTP[i] - 48 + phanTP[i] - 48) + rem;
        rem = 0;
        modRes = sum % 10;
        if (sum > 9)
            rem = 1;
        res = char(modRes+48) + res;
    }
    return res;
}

bool isEqual0(string strNum) {//Kiểm tra xem số này có bằng 0 không(để dừng việc x2)
    for (int i = 0; i < strNum.size(); i++) {
        if (strNum[i] != '0')
            return false;
    }
    return true;
}

bool isFullOf(string src, char c) {
    for (int i = 0; i < src.size(); i++)
        if (src[i] != c)
            return false;
    return true;
}

string tachChuoi(string chuoi, char kitu, string &res2) {
    string res = "";
    int index;
    for (int i = 0; i < chuoi.size(); i++) {
        if (chuoi[i] == kitu) {
            index = i;
            break;
        }
    }
    for (int i = 0; i < index; i++){
        res.push_back(chuoi[i]);
    }
    for (int i = index + 1; i < chuoi.size(); i++) {
        res2.push_back(chuoi[i]);
    }
    return res;
}

int charToNum(char c)
{
    return c - 48;
}

char popHead(string &str) {
    char ret = str[0];
    string res = "";
    for (int i = 1; i < str.size(); i++)
        res.push_back(str[i]);
    str = res;
    return ret;
}
//Lam tron bang cach cong 1 het vao bat ke am duong
string lamTron(int sign, string src) {
    if (sign == 1) {
        int rem = 1;
        for (int i = src.size()-1; i>=0; i--) {
            src[i] = src[i] + rem;
            if (src[i] > '1') {
                src[i] = 0;
                rem = 1;
            }
            else {
                rem = 0;
            }
        }
    }
    else {
        int rem = 1;
        for (int i = src.size() - 1; i >= 0; i--) {
            src[i] = src[i] + rem;
            if (src[i] > '1') {
                src[i] = 0;
                rem = 1;
            }
            else {
                rem = 0;
            }
        }
    }
    return src;
}

string mulby2Int(string intstr) {
    string result = "";
    int ivar = intstr[0];
    int tmp = 0;
    int ketQua, soDu;
    for (int i = intstr.size() - 1; i >= 0; i--) {
        ketQua = (intstr[i] - '0') * 2 + tmp;
        tmp = ketQua / 10;
        soDu = ketQua % 10;
        result.push_back(soDu + 48);
    }
    string finalResult = "";
    for (int i = result.size() - 1; i >= 0; i--) {
        finalResult.push_back(result[i]);
    }
    if (ivar > '4')
        finalResult = "1" + finalResult;
    return finalResult;
}
int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

string plus2Int(string int1, string int2) {
    string res = "";
    int rem = 0;
    int temp;
    if (int1.size()>int2.size()) {
        int1 = "0" + int1;
        while (int2.size()<int1.size())
        {
            int2 = "0" + int2;
        }
    }
    else {
        int2 = "0" + int2;
        while (int1.size() < int2.size())
        {
            int1 = "0" + int1;
        }
    }
    for (int i = int1.size() - 1; i >= 0; i--) {
        temp = (int1[i] - '0' + int2[i] - '0') + rem;
        if (temp > 9)
            rem = 1;
        else
            rem = 0;
        res = char(temp % 10 + '0') + res;
    }
    if (res[0] == '0')
        popHead(res);
    return res;
}

string mulBy5Int(string intstr) {
    string res = "0";
    for (int i = 0; i < 5; i++)
        res = plus2Int(res, intstr);
    return res;
}
string plus2Float(string float1, string float2) {
    string res = "";
    int rem = 0;
    int temp;
    if (float1.size() > float2.size()) {
        while (float2.size() < float1.size())
        {
            float2 = float2 + "0";
        }
    }
    else {
        while (float1.size() < float2.size())
        {
            float1 = float1 + "0";
        }
    }
    for (int i = float1.size() - 1; i >= 0; i--) {
        temp = (float1[i] - '0' + float2[i] - '0') + rem;
        if (temp > 9)
            rem = 1;
        else
            rem = 0;
        res = char(temp % 10 + '0') + res;
    }
    return res;
}