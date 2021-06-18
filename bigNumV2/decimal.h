#pragma once
#include "bignum.h"

class decimal : public bignum
{
public:
	decimal(string);
	decimal(double);
	decimal(string, string, bool);
	decimal(const decimal&);
	decimal();
	bool isNegtive()const;
	bool isFloating()const;
	void Stripzero();

	decimal operator=(const decimal& rhs);
	const decimal operator+(const decimal& rhs);
	const decimal operator-(const decimal& rhs);
	const decimal operator*(const decimal& rhs);
	const decimal operator/(const decimal& rhs);
	const decimal operator!(void);
	const decimal operator^(const decimal& rhs);
	friend ostream& operator<<(ostream& str, decimal rhs);
	friend istream& operator>>(istream& str, decimal& rhs);
	friend const bool operator>(decimal, decimal);
	friend const bool operator>=(decimal, decimal);
	friend const bool operator<(decimal, decimal);
	friend const bool operator<(decimal, decimal);
	friend const bool operator==(decimal, decimal);
	friend const bool operator!=(decimal, decimal);
	string to_sss();
	string integer_part;
	string float_part;
	bool negtive;
	bool floating;
};