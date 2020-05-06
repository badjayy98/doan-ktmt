#include "QFloat.h"

// Convert 1 chuỗi binary thành 1 chuỗi hexadecimal
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












// Chuyển đổi chuỗi thành QInt

// Convert 1 chuỗi binary thành 1 QInt
QInt convertBinaryToQInt(string Binary)
{
	QInt result;
	string temp;
	int position = 3;

	if (Binary.size() > 128)
	{
		cout << "Khong the luu so lon hon 128 bit" << endl;
		return result;
	}

	while (Binary.size() != 128)
	{
		Binary.insert(Binary.begin(), '0');
	}

	for (int i = 0; i < Binary.size(); i = i + 32)
	{
		temp = Binary.substr(i, 32);
		result.setData(position, binaryToDecimal(temp));
		position--;
		temp.clear();
	}
	return result;
}


// Chuyển đổi 1 chuỗi decimal thành QInt
QInt convertDecimalToQInt(string decimal)
{
	bool negative = false;
	if (decimal[0] == '-')
	{
		negative = true;
		decimal.erase(decimal.begin());
	}
	string binResult = decimalToBinary(decimal);
	QInt result(binResult);
	if (negative)
	{
		result = result.SoBu2();
	}
	return result;
}


// Chuyển đổi 1 chuỗi hex thành QInt
QInt convertHexToQInt(string hex)
{
	bool negative = false;
	if (hex[0] == '-')
	{
		negative = true;
		hex.erase(hex.begin());
	}
	string binResult = hexToBinary(hex);
	QInt result(binResult);
	if (negative)
	{
		result = result.SoBu2();
	}
	return result;
}


// Chuyển đổi QInt thành 1 chuỗi

// Đổi 1 QInt sang dạng nhị phân
string convertToBinary(QInt s)
{
	bool startPrint = false;
	vector<uint32_t> data = s.getData();
	string binary;
	for (int i = data.size() - 1; i >= 0; i--)
	{
		if (data[i] != 0)
		{
			startPrint = true;

		}
		if (startPrint)
		{
			for (int j = 0; j < 32; j++)
			{
				int bitNow = ((data[i] >> (31 - j)) & 1);
				binary.push_back(bitNow + '0');
			}
		}

	}

	// Xoá các bit 0 đầu chuỗi
	if (binary.find('1') != string::npos)
	{
		binary.erase(binary.begin(), binary.begin() + binary.find('1'));
	}
	else
	{
		return "0";
	}

	return binary;
}

// Convert QInt thành dạng thập phân
string convertQIntToDecimal(QInt s)
{
	string Binary = convertToBinary(s);
	string Decimal;
	for (int i = 0; i < Binary.size(); i++)
	{
		if (Binary[i] != '0')
		{
			if ((i == 0) && (Binary.size() == 128))
			{
				Decimal = TruHaiChuoi(Decimal, LuyThua2(Binary.size() - i - 1));
			}
			else
			{
				Decimal = CongHaiChuoi(Decimal, LuyThua2(Binary.size() - i - 1));
			}
		}
	}
	if (Decimal[0] == '-')
	{
		string temp = Decimal.substr(1, Decimal.size() - 1);
		while (temp[0] == '0')
		{
			temp.erase(temp.begin());
		}
		Decimal = '-' + temp;
	}
	return Decimal;
}

// Convert 1 số QInt thành dạng thập lục phân
string convertQIntToHex(QInt s)
{
	string binary = convertToBinary(s);
	return convertBinaryToHex(binary);
}