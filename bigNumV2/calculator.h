#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "bignum.h"
using namespace std;
enum MyEnum
{
	ADDITION,
	SUBSTRACTION,
	MULTIPLICATION,
	DIVISION,
	FACTORIAL,
	POWER
};
class calculator : public bignum
{
public:
	calculator();
	struct oper
	{
		int op;
		int precedence;
		char associativity;
		oper();
		oper(int op);
	};
	struct opValue
	{
		oper op;
		bignum val;
		opValue(oper op, bignum val);
	};
	bignum compute(bignum l, oper op, bignum r);
	oper GetOp();
	bignum getValue(bignum&);
	bignum fuction();
	void Removewhite();
	string getnum();
	void button(char);
	void parse();
// input() was here
	void reset();
	bignum result;
	string to_be_cal; // raw input
	string output;
	int index;
	vector<opValue> vec;
	bool floating;
};