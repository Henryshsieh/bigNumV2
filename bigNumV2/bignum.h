#pragma once
#include <iostream>
#include <string>
#define MAX 100
using namespace std;

class bignum
{
public:
	bignum(string);
	bignum(double);
	bignum(string, string, bool);
	bignum(const bignum&);
	bignum();
	bool isNegtive()const;
	bool isFloating()const;
	void Stripzero();

	bignum operator=(const bignum& rhs);
	const bignum operator+(const bignum& rhs);
	const bignum operator-(const bignum& rhs);
	const bignum operator*(const bignum& rhs);
	const bignum operator/(const bignum& rhs);
	const bignum operator!(void);
	const bignum operator^(const bignum& rhs);
	friend ostream& operator<<(ostream& str, bignum rhs);
	friend istream& operator>>(istream& str, bignum& rhs);
	friend const bool operator>(bignum, bignum);
	friend const bool operator>=(bignum, bignum);
	friend const bool operator<(bignum, bignum);
	friend const bool operator<(bignum, bignum);
	friend const bool operator==(bignum, bignum);
	friend const bool operator!=(bignum, bignum);
	string to_sss();
	string integer_part;
	string float_part;
	bool negtive;
	bool floating;
};
