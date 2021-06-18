#pragma once
#include <iostream>
#include <string>
#include "bignum.h"
using namespace std;

void bignum::Stripzero()
{
	int i = 0;
	for (i = 0; i < integer_part.length() - 1; i++)
	{
		if (integer_part[i] != '0')
			break;
	}
	integer_part = integer_part.substr(i, integer_part.length());

	for (i = float_part.length() - 1; i >= 1; i--)
	{
		if (float_part[i] != '0')
			break;
	}
	float_part = float_part.substr(0, i + 1);
}

const bool operator==(bignum lhs, bignum rhs) {//floating not done
	lhs.Stripzero();
	rhs.Stripzero();
	if (lhs.integer_part.length() == rhs.integer_part.length() && lhs.float_part.length() == lhs.float_part.length()) {
		for (size_t i = 0; i < lhs.integer_part.length(); i++) {
			if (lhs.integer_part[i] != rhs.integer_part[i])
				return 0;
		}
		for (size_t i = 0; i < lhs.float_part.length(); i++) {
			if (lhs.float_part[i] != rhs.float_part[i])
				return 0;
		}
		return 1;
	}

	return 0;
}
const bool operator>=(bignum lhs, bignum rhs) {
	lhs.Stripzero();
	rhs.Stripzero();

	if (lhs < rhs)
		return 0;
	return 1;
}
const bool operator>(bignum lhs, bignum rhs) {//floating not done
	lhs.Stripzero();
	rhs.Stripzero();
	if (!lhs.isNegtive() && !rhs.isNegtive()) {
		if (lhs.integer_part.length() > rhs.integer_part.length())
			return 1;
		if (lhs.integer_part.length() < rhs.integer_part.length())
			return 0;
		for (size_t i = 0; i < lhs.integer_part.length(); i++) {
			if (lhs.integer_part[i] > rhs.integer_part[i])
				return 1;
			if (lhs.integer_part[i] < rhs.integer_part[i])
				return 0;
		}
		for (size_t i = 0; i < lhs.float_part.length(); i++) {
			if (lhs.float_part[i] > rhs.float_part[i])
				return 1;
			if (lhs.float_part[i] < rhs.float_part[i])
				return 0;
		}
	}
	else if (!lhs.isNegtive() && rhs.isNegtive()) {
		return 1;
	}
	else if (lhs.isNegtive() && !rhs.isNegtive()) {
		return 0;
	}
	else {
		if (lhs.integer_part.length() > rhs.integer_part.length())
			return 0;
		if (lhs.integer_part.length() < rhs.integer_part.length())
			return 1;
		for (size_t i = 0; i < lhs.integer_part.length(); i++) {
			if (lhs.integer_part[i] > rhs.integer_part[i])
				return 0;
			if (lhs.integer_part[i] < rhs.integer_part[i])
				return 1;
		}
		for (size_t i = 0; i < lhs.float_part.length(); i++) {
			if (lhs.float_part[i] > rhs.float_part[i])
				return 0;
			if (lhs.float_part[i] < rhs.float_part[i])
				return 1;
		}
	}
	return 0;
}
const bool operator<(bignum lhs, bignum rhs) {//floating not done
	lhs.Stripzero();
	rhs.Stripzero();
	if (lhs > rhs || (lhs == rhs))
		return 0;
	return 1;
}
const bool operator!=(bignum lhs, bignum rhs)
{
	return !(lhs == rhs);
}

bignum::bignum(double input_int)
{
	negtive = 0;
	string input = to_string(input_int);
	if (input.find("-") != string::npos)
	{
		input = input.substr(1, input.length());
		negtive = 1;
	}
	if (input.find(".") != string::npos) {
		integer_part = input.substr(0, input.find("."));
		float_part = input.substr(input.find(".") + 1, input.length());
		floating = true;
	}
	else {
		integer_part = input;
		float_part = "0";
		floating = false;
	}
}
bignum::bignum(const bignum& rhs) {
	integer_part = rhs.integer_part;
	float_part = rhs.float_part;
	negtive = rhs.negtive;
	floating = rhs.floating;

}
bignum::bignum() :integer_part("0"), float_part("0"), negtive(false), floating(false) {
}
bignum::bignum(string input) {
	negtive = 0;
	if (input == "") {
		integer_part = "0";
		float_part = "0";
		negtive = 0;
		floating = false;
	}
	if (input.find("-") != string::npos)
	{
		input = input.substr(1, input.length());
		negtive = 1;
	}
	if (input.find(".") != string::npos) {
		integer_part = input.substr(0, input.find("."));
		float_part = input.substr(input.find(".") + 1, input.length());
		floating = true;
	}
	else {
		integer_part = input;
		float_part = "0";
		floating = false;
	}
}
bignum::bignum(string input, string input_floating, bool neg) {
	integer_part = input;
	float_part = input_floating;
	negtive = neg;
	if (input_floating != '0')
		floating = true;
	else
		floating = false;
}
bool bignum::isNegtive()const {
	return negtive;
}
bool bignum::isFloating()const {
	for (size_t i = 0; i < float_part.length(); i++)
	{
		if (float_part[i] != '0')
			return 1;
	}
	return 0;
}

const bignum bignum::operator+(const bignum& rhs) {
	//+ + -
	if (!isNegtive() && rhs.isNegtive())
		return *this - bignum(rhs.integer_part, rhs.float_part, false);
	//- + +
	if (isNegtive() && !rhs.isNegtive())
		return bignum(rhs) - bignum(integer_part, float_part, false);
	//- + -
	//floating
	if (isFloating() || rhs.isFloating()) {
		string left_int_num = integer_part;
		string right_int_num = rhs.integer_part;
		int int_len = 0;
		//int padding
		if (left_int_num.length() > right_int_num.length()) {
			right_int_num.insert(0, left_int_num.length() - right_int_num.length(), '0');
		}
		else {
			left_int_num.insert(0, right_int_num.length() - left_int_num.length(), '0');
		}
		int_len = left_int_num.length();
		//float part padding
		string left_floating_num = float_part;
		string right_floating_num = rhs.float_part;
		if (left_floating_num.length() > right_floating_num.length()) {
			right_floating_num.append(left_floating_num.length() - right_floating_num.length(), '0');
		}
		else {
			left_floating_num.append(right_floating_num.length() - left_floating_num.length(), '0');
		}

		//cout << left_floating_num << endl;
		//cout << right_floating_num << endl;
		string left = left_int_num + left_floating_num;
		string right = right_int_num + right_floating_num;

		bignum result = bignum(bignum(left) + bignum(right));
		//cout << result << endl;
		if (isNegtive() && rhs.isNegtive())
			result.negtive = true;
		result.float_part = result.integer_part.substr(result.integer_part.length() - left_floating_num.length(), result.integer_part.length());
		result.integer_part = result.integer_part.substr(0, result.integer_part.length() - left_floating_num.length());
		return result;
	}
	//integer
	string left_string = integer_part;
	string right_string = rhs.integer_part;
	string result = "";
	if (integer_part.length() > rhs.integer_part.length()) {
		right_string.insert(0, integer_part.length() - right_string.length(), '0');
	}
	else {
		left_string.insert(0, right_string.length() - integer_part.length(), '0');
	}
	int temp;
	int length = left_string.length();
	int carry = 0;
	for (size_t i = 0; i < length; i++) {
		temp = (right_string[length - i - 1] + left_string[length - i - 1]) - '0' - '0' + carry;
		carry = temp / 10;
		temp %= 10;
		result.insert(0, 1, temp + '0');
	}
	if (carry)
		result.insert(0, 1, carry + '0');
	bignum res(result);
	if (isNegtive() && rhs.isNegtive())
		res.negtive = negtive;

	return res;
}
const bignum bignum::operator-(const bignum& rhs) {
	//- - +
	if (isNegtive() && !rhs.isNegtive())
	{
		return bignum(integer_part, float_part, true) + bignum(rhs.integer_part, rhs.float_part, true);
	}
	//- - -
	else if (isNegtive() && rhs.isNegtive())
	{
		return bignum(rhs.integer_part, rhs.float_part, false) - bignum(integer_part, float_part, false);
	}
	//+ - -
	else if (!isNegtive() && rhs.isNegtive())
	{
		return bignum(rhs.integer_part, rhs.float_part, false) + bignum(integer_part, float_part, false);
	}

	if (isFloating() || rhs.isFloating()) {
		//int part padding
		string left_int_num = integer_part;
		string right_int_num = rhs.integer_part;
		int int_len = 0;
		if (left_int_num.length() > right_int_num.length()) {
			right_int_num.insert(0, left_int_num.length() - right_int_num.length(), '0');
		}
		else {
			left_int_num.insert(0, right_int_num.length() - left_int_num.length(), '0');
		}
		int_len = left_int_num.length();
		//float part padding
		string left_floating_num = float_part;
		string right_floating_num = rhs.float_part;
		if (left_floating_num.length() > right_floating_num.length()) {
			right_floating_num.append(left_floating_num.length() - right_floating_num.length(), '0');
		}
		else {
			left_floating_num.append(right_floating_num.length() - left_floating_num.length(), '0');
		}

		string left = left_int_num + left_floating_num;
		string right = right_int_num + right_floating_num;
		//cout << left << endl;
		//cout <<right << endl;
		bignum result;
		result = bignum(left) - bignum(right);
		result.float_part = result.integer_part.substr(left_int_num.length(), result.integer_part.length());
		result.integer_part = result.integer_part.substr(0, left_int_num.length());
		result.negtive = (bignum(left) - bignum(right)).negtive;
		return result;
	}
	string left_string = integer_part;
	string right_string = rhs.integer_part;
	string result = "";
	if (integer_part.length() > right_string.length()) {
		right_string.insert(0, integer_part.length() - right_string.length(), '0');
	}
	else {
		left_string.insert(0, right_string.length() - integer_part.length(), '0');
	}
	int length = left_string.length();
	int carry = 0;
	int left = 0;
	int* arr = new int[length];
	for (int i = length - 1; i >= 0; i--) {
		arr[i] = 0;
		arr[i] = left_string[i] - right_string[i];
		if (arr[i] != 0)
			left = arr[i];
	}
	result = "";
	for (int i = 0; i < length; i++) {
		if (left < 0) {
			arr[i] *= -1;
			int j = i;
			while (arr[j] < 0) {
				arr[j] += 10;
				arr[--j]--;
			}
		}
		else {
			int j = i;
			while (arr[j] < 0) {
				arr[j] += 10;
				arr[--j]--;
			}
		}
	}
	for (size_t i = 0; i < length; i++) {
		result += to_string(arr[i]);
	}
	if (left < 0) {
		result.insert(0, "-");
	}
	return bignum(result);
}
const bignum bignum::operator*(const bignum& rhs) {
	if (isFloating() || rhs.isFloating()) {
		string left_int_num = integer_part;
		string right_int_num = rhs.integer_part;
		string left_floating_num = float_part;
		string right_floating_num = rhs.float_part;
		//decimal place
		int result_floating_part_length = left_floating_num.length() + right_floating_num.length();
		//int + float
		string left = left_int_num + left_floating_num;
		string right = right_int_num + right_floating_num;

		bignum result = bignum(left) * bignum(right);
		result.float_part = result.integer_part.substr(result.integer_part.length() - result_floating_part_length, result.integer_part.length());
		result.integer_part = result.integer_part.substr(0, result.integer_part.length() - result_floating_part_length);
		return result;
	}
	string str = "";
	str.insert(0, MAX, '0');
	bignum result(str);
	string line = "";
	int temp;
	int carry = 0;
	string padding = "";

	bool b = new bool[rhs.integer_part.length()];
	for (int i = rhs.integer_part.length() - 1; i >= 0; i--) {
		for (int j = integer_part.length() - 1; j >= 0; j--) {
			temp = (integer_part[j] - '0') * (rhs.integer_part[i] - '0') + carry;
			carry = temp / 10;
			temp %= 10;
			line.insert(0, to_string(temp));
		}
		if (carry)
			line.insert(0, to_string(carry));
		line += padding;
		result = result + bignum(line);
		line = "";
		carry = 0;
		padding += "0";
	}
	result.negtive = negtive ^ rhs.negtive;
	result.Stripzero();
	return result;
}
const bignum bignum::operator/(const bignum& rhs) {
	if (rhs == bignum("0"))
	{
		return bignum("error");
	}

	if (isFloating() || rhs.isFloating()) {
		bignum left(integer_part + float_part);
		bignum right(rhs.integer_part + rhs.float_part);
		string padding = "";
		if (float_part.length() > rhs.float_part.length())
		{
			padding.insert(0, float_part.length() - rhs.float_part.length(), '0');
			right.integer_part += padding;
		}
		else
		{
			padding.insert(0, rhs.float_part.length() - float_part.length(), '0');
			left.integer_part += padding;
		}
		left.Stripzero();
		right.Stripzero();
		left.floating = true;
		right.floating = true;
		return  left / right;
	}
	string quotient = "";
	string left = integer_part;
	string right = rhs.integer_part;
	bignum fraction;
	int count = 0;
	int length = left.length();
	if (floating || rhs.floating)
	{
		string padding = "";
		padding.insert(0, MAX, '0');
		left += padding;
	}


	for (int i = 0, j = 0; i < left.length(); i++, j++) {
		fraction = bignum(left.substr(0, i + 1));
		//cout << "frac :"<<fraction << endl;
		//cout << "remaing" << left << endl;

		if (fraction >= bignum(right)) {
			while (fraction >= bignum(right)) {
				fraction = fraction - bignum(right);
				count++;
				//	cout << "faaaaaaarac :" << fraction << endl;
			}
			if (fraction.isNegtive()) {
				count--;
				fraction = fraction + bignum(right);
			}
			//cout << "frac :" << fraction << endl;
			//cout << "count:" <<count << endl;
			left = fraction.integer_part + left.substr(i + 1, left.length());
			j = 0;
			//cout << "remaing" << left << endl;
			quotient += to_string(count);
		}
		else {
			quotient += "0";
		}

		count = 0;
	}
	quotient = quotient.substr(0, length) + "." + quotient.substr(length, quotient.length());
	bignum result(quotient);
	result.negtive = negtive ^ rhs.negtive;
	return result;
}
const bignum bignum::operator!(void)
{
	if (isFloating())
	{
		cout << "no\n";
		return bignum("error");
	}
	if (isNegtive())
	{
		cout << "no\n";
		return bignum("error");
	}
	bignum result(1);
	for (int i = 1; i < *this || i == *this; i++)
	{
		//cout << i << endl;
		result = result * i;
	}
	return result;
}
const bignum bignum::operator^(const bignum& rhs)
{
	if (rhs.isNegtive()) {
		// return 0 if exponent < 0
		return bignum(0);
	}

	if (rhs.isFloating()) {
		bignum result(1);
		for (size_t i = 1; i < rhs; i++) {
			result = result * *this;
		}
		// calculating square root
		bignum approx(*this), error(0.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001);
		while ((approx - *this / approx) > error) {
			approx = bignum(approx + *this / approx) / 2;
		}
		result = result * approx;
		if (result.float_part.length() > 100) {
			result.float_part = result.float_part.substr(0, 100);
		}
		return  result;
	}
	// positive integer exponent
	bignum result(1);
	for (size_t i = 0; i < rhs; i++) {
		result = result * *this;
	}
	if (result.float_part.length() > 100) {
		result.float_part = result.float_part.substr(0, 100);
	}
	return result;
}
bignum bignum::operator=(const bignum& rhs) {
	integer_part = rhs.integer_part;
	float_part = rhs.float_part;
	negtive = rhs.negtive;
	floating = rhs.floating;
	return *this;
}
ostream& operator<<(ostream& str, bignum rhs) {
	if (rhs == bignum(0))
		str << 0;
	else if (rhs.isFloating()) {
		if (rhs.isNegtive())
			str << "-" << rhs.integer_part << "." << rhs.float_part;
		else
			str << rhs.integer_part << "." << rhs.float_part;
	}
	else
		if (rhs.isNegtive())
			str << "-" << rhs.integer_part;
		else
			str << rhs.integer_part;
	return str;
}
istream& operator>>(istream& str, bignum& rhs) {
	string tmp;
	str >> tmp;
	if (!rhs.floating && tmp.find(".") != string::npos)
	{
		tmp = tmp.substr(0, tmp.find("."));
	}
	rhs = bignum(tmp);
	rhs.Stripzero();
	return str;
}
string bignum::to_sss()
{
	string res = "";
	if (*this == bignum(0))
		res = "0";
	else if (isFloating()) {
		if (isNegtive())
			res = res + "-" + integer_part + "." + float_part;
		else
			res = res + integer_part + "." + float_part;
	}
	else
		if (isNegtive())
			res = res + "-" + integer_part;
		else
			res = integer_part;
	return res;
}