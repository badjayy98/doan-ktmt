#include "Function.h"

// Hàm đảo ngược chuỗi
void reverseStr(string& str)
{
    int n = str.length();
    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
}

// Biến chuỗi nhị phân thành 1 số nguyên
int binaryToDecimal(string n)
{
    string num = n;
    int dec_value = 0;

    int base = 1;

    int len = num.length();
    for (int i = len - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }

    return dec_value;
}

// Kiểm tra giá trị str1 có nhỏ hơn giá trị str2 hay ko
bool isSmaller(string str1, string str2)
{
    // Calculate lengths of both string 
    int n1 = str1.length(), n2 = str2.length();

    if (n1 < n2)
        return true;
    if (n2 < n1)
        return false;

    for (int i = 0; i < n1; i++)
        if (str1[i] < str2[i])
            return true;
        else if (str1[i] > str2[i])
            return false;

    return false;
}


// Hàm trừ 2 string, 2 str ko phải số âm
string TruHaiChuoiKhongXetDau(string str1, string str2)
{
    bool negative = false;
    // Nếu str1 nhỏ hơn str2, ta cần swap 
    if (isSmaller(str1, str2))
    {
        swap(str1, str2);
        negative = true;
    }


    string str = "";

    int n1 = str1.length(), n2 = str2.length();

    // Đảo ngược 2 str để phục vụ phép trừ
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());

    int carry = 0;

    for (int i = 0; i < n2; i++)
    {

        int sub = ((str1[i] - '0') - (str2[i] - '0') - carry);

        if (sub < 0)
        {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;

        str.push_back(sub + '0');
    }

    for (int i = n2; i < n1; i++)
    {
        int sub = ((str1[i] - '0') - carry);

        if (sub < 0)
        {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;

        str.push_back(sub + '0');
    }

    reverse(str.begin(), str.end());

    if (negative)
    {
        str = '-' + str;
    }

    return str;
}

// Cộng hai chuỗi 
string CongHaiChuoi(string str1, string str2)
{
    bool negative = false;
    if (str1[0] == '-' && str2[0] == '-')
    {
        str1.erase(str1.begin());
        str2.erase(str2.begin());
        negative = true;
    }
    else if (str1[0] == '-' && str2[0] != '-')
    {
        str1.erase(str1.begin());
        return TruHaiChuoiKhongXetDau(str2, str1);
    }
    else if (str1[0] != '-' && str2[0] == '-')
    {
        str2.erase(str2.begin());
        return TruHaiChuoiKhongXetDau(str1, str2);
    }

    // Đảm bảo str2 có độ dài lớn hơn hoặc bằng str1
    if (str1.length() > str2.length())
        swap(str1, str2);

    string str = "";

    int n1 = str1.length(), n2 = str2.length();

    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());

    int carry = 0;
    for (int i = 0; i < n1; i++)
    {
        int sum = ((str1[i] - '0') + (str2[i] - '0') + carry);
        str.push_back(sum % 10 + '0');

        carry = sum / 10;
    }

    for (int i = n1; i < n2; i++)
    {
        int sum = ((str2[i] - '0') + carry);
        str.push_back(sum % 10 + '0');
        carry = sum / 10;
    }

    if (carry)
        str.push_back(carry + '0');

    reverse(str.begin(), str.end());

    if (negative)
    {
        str = '-' + str;
    }

    return str;
}



// Trừ hai chuỗi
string TruHaiChuoi(string str1, string str2)
{
    if (str1[0] == '-' && str2[0] == '-')
    {
        str1.erase(str1.begin());
        str2.erase(str2.begin());
        return TruHaiChuoi(str2, str1);
    }
    else if (str1[0] == '-' && str2[0] != '-')
    {
        str1.erase(str1.begin());
        return CongHaiChuoi(str2, str1);
    }
    else if (str1[0] != '-' && str2[0] == '-')
    {
        str2.erase(str2.begin());
        return CongHaiChuoi(str1, str2);
    }

    bool negative = false;
    // Nếu str1 nhỏ hơn str2, ta cần swap 
    if (isSmaller(str1, str2))
    {
        swap(str1, str2);
        negative = true;

    }


    string str = "";

    int n1 = str1.length(), n2 = str2.length();

    // Đảo ngược 2 str để phục vụ phép trừ
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());

    int carry = 0;

    for (int i = 0; i < n2; i++)
    {

        int sub = ((str1[i] - '0') - (str2[i] - '0') - carry);

        if (sub < 0)
        {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;

        str.push_back(sub + '0');
    }

    for (int i = n2; i < n1; i++)
    {
        int sub = ((str1[i] - '0') - carry);

        if (sub < 0)
        {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;

        str.push_back(sub + '0');
    }

    reverse(str.begin(), str.end());

    if (negative)
    {
        str = '-' + str;
    }

    return str;
}


// Nhân hai chuỗi
string NhanHaiChuoi(string s1, string s2)
{
    bool negative = false;

    if (s1[0] == '-' && s2[0] == '-')
    {
        s1.erase(s1.begin());
        s2.erase(s2.begin());
    }
    else if (s1[0] == '-' || s2[0] == '-')
    {
        negative = true;
        if (s1[0] == '-')
        {
            s1.erase(s1.begin());
        }
        else
        {
            s2.erase(s2.begin());
        }
    }


    int len1 = s1.size();
    int len2 = s2.size();
    if (len1 == 0 || len2 == 0)
        return "0";


    // Khởi tạo vector chứa các int với size = len1 + len2, giá trị khởi tạo = 0 
    vector<int> result(len1 + len2, 0);

    // Các biến dùng để xác định vị trí phép cộng nằm ở hàng đơn vị, chục, trăm...
    int i_n1 = 0;
    int i_n2 = 0;


    for (int i = len1 - 1; i >= 0; i--)
    {
        int carry = 0;

        // Lấy giá trị dạng int trong chuỗi
        int n1 = s1[i] - '0';

        i_n2 = 0;

        for (int j = len2 - 1; j >= 0; j--)
        {
            int n2 = s2[j] - '0';

            int sum = n1 * n2 + result[i_n1 + i_n2] + carry;

            // Phần nhớ
            carry = sum / 10;

            result[i_n1 + i_n2] = sum % 10;

            i_n2++;
        }

        // Nếu sau khi nhân 1 số vs tất cả các chữ số mà vẫn còn phần nhớ, ta cần cộng thêm vào phần hiện tại
        if (carry > 0)
            result[i_n1 + i_n2] += carry;

        i_n1++;
    }

    // Kêt quả được lưu vào vector theo dạng đảo ngược, ví dụ = 200 thì res[0] = 0, res[1] = 0, res[2] = 2 -> cần xoá phần thừa nằm bên phải
    int i = result.size() - 1;
    while (i >= 0 && result[i] == 0)
        i--;

    // Nếu tất cả các số đều = 0 -> có nghĩa s1 hoặc s2 = 0
    if (i == -1)
        return "0";

    string s = "";

    // Tạo hàm string lưu kết quả tính được
    while (i >= 0)
        s += to_string(result[i--]);

    return s;
}


// Chia 1 chuỗi cho 2 
string Division2(string number)
{
    if (number < "2" && number.size() == 1)
    {
        return "0";
    }
    string ans;

    int idx = 0;
    int temp = number[idx] - '0';
    while (temp < 2)
        temp = temp * 10 + (number[++idx] - '0');

    // Repeatedly divide 2 with temp. After  
    // every division, update temp to include one  
    // more digit. 
    while (number.size() > idx)
    {
        // Store result in answer i.e. temp / divisor 
        ans += (temp / 2) + '0';

        // Take next digit of number 
        temp = (temp % 2) * 10 + number[++idx] - '0';
    }

    // If divisor is greater than number 
    if (ans.length() == 0)
        return "0";

    // else return ans 
    return ans;
}

// Kiểm tra chuỗi có phải số chẵn 
bool isEven(string number)
{
    return (number[number.size() - 1] - '0') % 2 == 0;
}

// Chuyển chuỗi decimal thành chuỗi binary
string decimalToBinary(string decimal)
{
    string result = "";

    if (decimal[0] == '-')
    {
        decimal.erase(decimal.begin());
    }

    while (decimal > "0")
    {
        if (isEven(decimal))
        {
            result += '0';
        }
        else
        {
            result += '1';
        }
        decimal = Division2(decimal);
    }
    reverseStr(result);
    return result;
}

// Chuyển chuỗi hex thành chuỗi binary
string hexToBinary(string hex)
{
    string result = "";
    for (int i = 0; i < hex.size(); i++)
    {
        if (hex[i] == '0')
        {
            result = result + "0000";
        }
        else if (hex[i] == '1')//1
        {
            result = result + "0001";
        }
        else
        {
            if (hex[i] == '2')
            {
                result = result + "0010";
            }
            else
            {
                if (hex[i] == '3')//3
                {
                    result = result + "0011";
                }
                else
                {
                    if (hex[i] == '4')//4
                    {
                        result = result + "0100";
                    }
                    else
                    {
                        if (hex[i] == '5')//5
                        {
                            result = result + "0101";
                        }
                        else
                        {
                            if (hex[i] == '6')//6
                            {
                                result = result + "0110";
                            }
                            else
                            {
                                if (hex[i] == '7')//7
                                {
                                    result = result + "0111";
                                }
                                else
                                {
                                    if (hex[i] == '8')//8
                                    {
                                        result = result + "1000";
                                    }
                                    else
                                    {
                                        if (hex[i] == '9')//9
                                        {
                                            result = result + "1001";
                                        }
                                        else
                                        {
                                            if (hex[i] == 'A')//10
                                            {
                                                result = result + "1010";
                                            }
                                            else
                                            {
                                                if (hex[i] == 'B')//11
                                                {
                                                    result = result + "1011";
                                                }
                                                else
                                                {
                                                    if (hex[i] == 'C')//12
                                                    {
                                                        result = result + "1100";
                                                    }
                                                    else
                                                    {
                                                        if (hex[i] == 'D')//13
                                                        {
                                                            result = result + "1101";
                                                        }
                                                        else
                                                        {
                                                            if (hex[i] == 'E')//14
                                                            {
                                                                result = result + "1110";
                                                            }
                                                            else
                                                            {
                                                                if (hex[i] == 'F')//15
                                                                {
                                                                    result = result + "1111";
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}


// Tính 2^n
string LuyThua2(int n)
{
    string result;

    // Nếu n lớn hơn 31 có khả năng tràn số uint32_t
    if (n > 31)
    {
        result = to_string((uint32_t)pow(2, 31));

        // Phần còn lại ta sẽ nhân chuỗi kết quả với 2 liên tục cho tới khi đủ n
        for (int i = 32; i <= n; i++)
        {
            result = NhanHaiChuoi(result, "2");
        }
    }
    else
    {
        result = to_string((uint32_t)pow(2, n));
    }

    return result;
}

string convertBinaryToHex(string binary)
{
    string temp;
    string result;

    // Ý tưởng : chia hexa thành từng phần 4 bit, sau đó quy đổi từng phần ra hex. Cần thêm các bit 0 lên đầu để size của hexa chia hết cho 4
    while (binary.size() % 4 != 0)
    {
        binary.insert(binary.begin(), '0');
    }

    for (int i = 0; i < binary.size(); i = i + 4)
    {
        temp = binary.substr(i, 4);
        if (temp == "0000")//0
        {
            result.push_back('0');
        }
        else
        {
            if (temp == "0001")//1
            {
                result.push_back('1');
            }
            else
            {
                if (temp == "0010")//2
                {
                    result.push_back('2');
                }
                else
                {
                    if (temp == "0011")//3
                    {
                        result.push_back('3');
                    }
                    else
                    {
                        if (temp == "0100")//4
                        {
                            result.push_back('4');
                        }
                        else
                        {
                            if (temp == "0101")//5
                            {
                                result.push_back('5');
                            }
                            else
                            {
                                if (temp == "0110")//6
                                {
                                    result.push_back('6');
                                }
                                else
                                {
                                    if (temp == "0111")//7
                                    {
                                        result.push_back('7');
                                    }
                                    else
                                    {
                                        if (temp == "1000")//8
                                        {
                                            result.push_back('8');
                                        }
                                        else
                                        {
                                            if (temp == "1001")//9
                                            {
                                                result.push_back('9');
                                            }
                                            else
                                            {
                                                if (temp == "1010")//10
                                                {
                                                    result.push_back('A');
                                                }
                                                else
                                                {
                                                    if (temp == "1011")//11
                                                    {
                                                        result.push_back('B');
                                                    }
                                                    else
                                                    {
                                                        if (temp == "1100")//12
                                                        {
                                                            result.push_back('C');
                                                        }
                                                        else
                                                        {
                                                            if (temp == "1101")//13
                                                            {
                                                                result.push_back('D');
                                                            }
                                                            else
                                                            {
                                                                if (temp == "1110")//14
                                                                {
                                                                    result.push_back('E');
                                                                }
                                                                else
                                                                {
                                                                    if (temp == "1111")//15
                                                                    {
                                                                        result.push_back('F');
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        temp.clear(); // Sau khi xét 4 bit, ta phải xoá đi để tiến hành tiếp tục 4 bit tiếp theo
    }

    int i = 0;
    while (result[i] == '0')
    {
        result.erase(result.begin());
    }
    return result;
}