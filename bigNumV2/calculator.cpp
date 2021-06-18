#pragma once
#include <iostream>
#include <vector>
#include <assert.h>
#include <string>
#include "calculator.h"
using namespace std;

calculator::calculator() :to_be_cal(""), index(0), output(""), result(0), vec(vector<opValue>()) {}

calculator::oper::oper() : op(-1), precedence(9999), associativity('L') {}

calculator::oper::oper(int op) : op(op)
{
	switch (op)
	{
	case ADDITION:
		precedence = 6;
		associativity = 'L';
		break;
	case -1:
		precedence = 999;
		associativity = 'L';
		break;
	case SUBSTRACTION:
		precedence = 6;
		associativity = 'L';
		break;
	case MULTIPLICATION:
		precedence = 5;
		associativity = 'L';
		break;
	case DIVISION:
		precedence = 5;
		associativity = 'L';
		break;
	case FACTORIAL:
		precedence = 2;
		associativity = 'R';
		break;
	case POWER:
		precedence = 3;
		associativity = 'R';
		break;
	default:
		precedence = 999;
		associativity = 'L';
		break;
	}
}

calculator::opValue::opValue(oper op, bignum val) :op(op), val(val) {}

bignum calculator::compute(bignum l, oper op, bignum r)
{
	switch (op.op)
	{
	case ADDITION:
		return l + r;
		break;
	case SUBSTRACTION:
		return l - r;
		break;
	case MULTIPLICATION:
		return l * r;
		break;
	case DIVISION:
		return l / r;
		break;
	case FACTORIAL:
		return !l;
		break;
	case POWER:
		return l ^ r;
		break;
	default:
		return bignum(0);
		break;
	}
}

calculator::oper calculator::GetOp()
{
	if (index >= to_be_cal.length())
		return oper(-1);

	switch (to_be_cal[index])
	{
	case '+':
		index++;
		return oper(ADDITION);
		break;
	case '-':
		index++;
		return oper(SUBSTRACTION);
		break;
	case '*':
		index++;
		return oper(MULTIPLICATION);
		break;
	case '/':
		index++;
		return oper(DIVISION);
		break;
	case '!':
		index++;
		return oper(FACTORIAL);
		break;
	case '^':
		index++;
		return oper(POWER);
		break;
	case ')':
		index++;
		return oper(-1);
		break;
	default:
		index++;
		return oper(-1);
		break;
	}
}

string calculator::getnum()
{
	string num = "";
	for (; index < to_be_cal.length(); index++)
	{
		if (isdigit(to_be_cal[index]) || to_be_cal[index] == '.')
			num += to_be_cal[index];
		else
			break;
	}
	return num;
}
bignum calculator::getValue(bignum& value)
{
	if (index < to_be_cal.length())
		switch (to_be_cal[index])
		{
		case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':case '0':
			value = bignum(getnum());
			break;
		case '(':
			index++;
			value = fuction();
			break;
		case '-':
			index++;
			value = bignum(-1) * getValue(value);
			break;
		case '+':
			index++;
			value = getValue(value);
			break;
		case '!':
			value.integer_part = "NULL";
		default:

			break;
		}
	if (to_be_cal.find(".") != string::npos)
		value.floating = true;
	return value;
}

template<typename T>
void pop_front(std::vector<T>& vec) {
	assert(!vec.empty());
	vec.erase(vec.begin());
}

bignum calculator::fuction() {
	//3 + 5 + 3
	bignum value;
	bignum start;
	getValue(start);
	vec.push_back(opValue(oper(-1), 0));
	vector <opValue> tmp;

	while (!vec.empty()) {
		oper onthestack = GetOp();
		int sorted = 0;
		while (vec.back().op.precedence < onthestack.precedence || (vec.back().op.precedence == onthestack.precedence && onthestack.associativity == 'L') || !tmp.empty()) {
			if (vec.back().op.op == DIVISION && (vec.back().op.precedence == onthestack.precedence) && !sorted) {
				sorted = 1;
				tmp.push_back(vec.back());
				do {
					tmp.push_back(opValue(onthestack, getValue(value)));
					onthestack = GetOp();
				} while (vec.back().op.precedence == onthestack.precedence);
				if (tmp.size() >= 2)
					vec.pop_back();
				for (int i = 0; i < tmp.size(); i++) {
					for (int j = i; j < tmp.size() - 1; j++) {
						if (tmp[j].op.op == DIVISION)
							swap(tmp[j], tmp[j + 1]);
					}
				}
			}
			if (vec.back().op.op == POWER && (vec.back().op.precedence == onthestack.precedence) && !sorted) {
				sorted = 1;
				tmp.push_back(vec.back());
				do {
					tmp.push_back(opValue(onthestack, getValue(value)));
					onthestack = GetOp();
				} while (vec.back().op.precedence == onthestack.precedence);
				if (tmp.size() >= 2)
					vec.pop_back();
				for (int i = 0; i < tmp.size(); i++) {
					for (int j = i; j < tmp.size() - 1; j++) {
						if (tmp[j].op.op == DIVISION)
							swap(tmp[j], tmp[j + 1]);
					}
				}
			}
			if (!tmp.empty()) {
				vec.push_back(tmp.front());
				pop_front(tmp);
			}
			if (vec.back().op.op == -1) {
				vec.pop_back();
				result = start;
				return start;
			}
			if ((vec.end() - 2)->op.op == -1)
				start = compute(start, vec.back().op, vec.back().val);
			else
				(vec.end() - 2)->val = compute((vec.end() - 2)->val, vec.back().op, vec.back().val);
			vec.pop_back();
		}

		getValue(value);
		if (value.integer_part == "NULL") {
			if (vec.size() == 1)
				start = compute(start, onthestack, 0);
			else if ((vec.end() - 2)->op.op == -1) {
				start = compute(start, vec.back().op, vec.back().val);
				vec.pop_back();

			}
			else {
				(vec.end() - 2)->val = compute((vec.end() - 2)->val, vec.back().op, vec.back().val);
				vec.pop_back();
			}
		}
		else
			vec.push_back(opValue(onthestack, value));
	}
	vec.push_back(opValue(oper(-1), 0));
}

void calculator::Removewhite() {
	for (size_t i = 0; i < to_be_cal.length(); i++) {
		if (to_be_cal[i] == ' ') {
			to_be_cal = to_be_cal.substr(0, i) + to_be_cal.substr(i + 1, to_be_cal.length());
			i--;
		}
	}
}

void calculator::button(char input)
{
	to_be_cal += input;
}

void calculator::parse() {
	string out = "";
	result.Stripzero();
	if (result.isNegtive() && result != bignum(0))
		out += "-";
	if (result.isFloating()) {
		out = out + result.integer_part + "." + result.float_part;
	}
	else
		out = out + result.integer_part;
	output = out;
}

void calculator::reset() {
	index = 0;
	to_be_cal = "";
	result = 0;
}