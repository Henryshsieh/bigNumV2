#pragma once
#include "bignum.h"

class integer : public bignum
{
public:
	integer(string);
	integer(double);
	integer(string, string, bool);
	integer(const integer&);
	integer();
	bool isNegtive()const;
	bool isFloating()const;
	void Stripzero();

	integer operator=(const integer& rhs);
	const integer operator+(const integer& rhs);
	const integer operator-(const integer& rhs);
	const integer operator*(const integer& rhs);
	const integer operator/(const integer& rhs);
	const integer operator!(void);
	const integer operator^(const integer& rhs);
	friend ostream& operator<<(ostream& str, integer rhs);
	friend istream& operator>>(istream& str, integer& rhs);
	friend const bool operator>(integer, integer);
	friend const bool operator>=(integer, integer);
	friend const bool operator<(integer, integer);
	friend const bool operator<(integer, integer);
	friend const bool operator==(integer, integer);
	friend const bool operator!=(integer, integer);
	string to_sss();
	string integer_part;
	string float_part;
	bool negtive;
	bool floating;
};