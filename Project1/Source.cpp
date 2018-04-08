﻿#include <iostream>
#include <cmath>
#include <string>
#include <bitset>
using namespace std;

#define MAXBITS 127
typedef bitset<128> binary;

class QInt
{
private:
	binary bit;
	string tempBit;
	
public:
	QInt();
	QInt(int mode, string str);
	QInt operator=(QInt const &Qi);
	QInt operator+(QInt Qi);
	binary getBits();
	~QInt();
//private:
	static string strBigDecToBin(string str);
	static string strBigHexToBin(string str);
	void printBin();
	string addBits(binary first, binary second);
	string clearBitZeroes(string bin);
};

int main()
{
	string a = "15";
	string b = "9";
	QInt q1(10, a);
	QInt q2(10, b);
	QInt q3(10, "2");
	
	q1.printBin();
	q2.printBin();
	cout << "\nResult: " << q3.addBits(q1.getBits(), q2.getBits());

	cout << "\n";
	system("pause");
	return 0;
}

QInt::QInt()
{
}

QInt::QInt(int mode, string str)
{
	string currentBit;

	if (mode == 2)
		bit = binary(str);

	if (mode == 10)
	{	
		currentBit = strBigDecToBin(str);
		bit = binary(currentBit);
		tempBit = clearBitZeroes(currentBit);
	}	

	if (mode == 16)
	{
		string hstr = strBigHexToBin(str);
		bit = binary(hstr);
	}
}

QInt QInt::operator=(QInt const & Qi)
{
	this->bit = Qi.bit;
	return Qi;
}

QInt QInt::operator+(QInt Qi)
{
	binary result;
	for (int i = 0; i < 127; i++)
	{
		//result.set(127 - i, )
	}
	return Qi;
}

binary QInt::getBits()
{
	return this->bit;
}

QInt::~QInt()
{
}

//Private functions.
//These functions support calculating process.
bool carry(string str)
{
	int n = str.length();
	return (str[n - 1] - 48) % 2;
}

string DivByTwo(string str)
{
	string result = str;

	int next_add = 0;
	int i = 0;
	for (; i < str.length(); i++)
	{
		int add = next_add;
		if ((str[i] - 48) % 2 != 0)
			next_add = 5;
		else next_add = 0;

		result[i] = ((str[i] - '0') / 2 + add + '0');

	}

	//loại các phần tử khác 0 đầu
	/*while (result[0] == '0' && result.length() != 1)
	{
		result = result.substr(1);
	}*/
	return result;
}

string QInt::strBigDecToBin(string str)
{
	// ASK: nếu str < 0 thì sao?
	string bin = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	for (int i = 0; i < 128 && str != "0"; i++)
	{
		bin[127 - i] = carry(str) + 48;
		str = DivByTwo(str);
	}
	return bin;
}

string conHexBin(char c)
{
	int swh = c - 48;
	switch (swh)
	{
	case 0:
		return "0000";
	case 1:
		return "0001";
	case 2:
		return "0010";
	case 3:
		return "0011";
	case 4:
		return "0100";
	case 5:
		return "0101";
	case 6:
		return "0110";
	case 7:
		return "0111";
	case 8:
		return "1000";
	case 9:
		return "1001";
	case 17:
		return "1010";
	case 18:
		return "1011";
	case 19:
		return "1100";
	case 20:
		return "1101";
	case 21:
		return "1110";
	case 22:
		return "1111";
	default:
		break;
	}
}

string QInt::strBigHexToBin(string str)
{
	string result = "";
	for (int i = 2; i < str.length(); i++)
	{
		result = result + conHexBin(str[i]);
	}
	return string(result);
}

void QInt::printBin()
{
	// ASK: theo yêu cầu của thầy là không in những số 0 đầu?
	 cout << tempBit << endl;
}

string QInt::addBits(binary first, binary second)
{
	string str1 = first.to_string();
	string str2 = second.to_string();
	string result;
	int carry = 0; //Initialize carry

	for (int i = MAXBITS; i >= 0; i--)
	{
		int firstBit = str1.at(i) - '0';
		int secondBit = str2.at(i) - '0';
		// boolean expression for sum of 3 bits
		int sum = (firstBit ^ secondBit ^ carry) + '0';

		result = char(sum) + result;

		// boolean expression for 3-bit addition
		carry = (firstBit & secondBit) | (secondBit & carry) | (firstBit & carry);
	}
	if (carry)
	{
		result = '1' + result;
	}

	result = clearBitZeroes(result);

	return result;
}

string QInt::clearBitZeroes(string bin)
{
	string tempBin = bin;
	int temp = 0;

	for (int i = 0; i < MAXBITS; i++)
	{
		if (tempBin[i] == '1')
		{
			tempBin = tempBin.substr(i);
			break;
		}
	}

	return tempBin;
}

