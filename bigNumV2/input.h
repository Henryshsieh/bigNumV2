#include <iostream>   
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <iomanip>
#include <sstream>
#include "calculator.h"
using namespace std;
namespace variable {
	map<string, string> v;
}
using namespace variable;
string calculate(string s) {
	return s;
}

void trans_var(string& s) {
	int current = 0, next;
	map<string, string>::iterator it;
	bool repeat = 0;
	for (it = v.begin(); it != v.end(); it++) {
		current = 0;
		next = s.find(it->first, current);
		while (next != string::npos) {
			repeat = 0;
			if (next > 0)
				switch (s[next - 1]) {
				case ' ':
				case '(':
				case ')':
				case '+':
				case '-':
				case '*':
				case '/':
				case '!':
				case '^':break;
				default:
					repeat = 1;
					break;
				}
			if ((next + it->first.size() < s.size()))
				switch (s[next + it->first.size()]) {
				case ' ':
				case '(':
				case ')':
				case '+':
				case '-':
				case '*':
				case '/':
				case '!':
				case '^':break;
				default:
					repeat = 1;
					break;
				}
			if (!repeat) {
				s = s.substr(0, next) + s.substr(next + it->first.size(), s.size() - next + it->first.size());
				s = s.insert(next, it->second);
			}
			current = next + 1;
			if (current < s.size())
				next = s.find(it->first, current);
			else
				next = string::npos;
		}
	}
}

bool isNumOrDot(char c) {
	if (c < '9' && c>'0')
		return 1;
	else if (c == '.')
		return 1;
	else
		return 0;
}

bool check(string s) {
	int count = 0;
	bool error = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '(')
			count++;
		else if (s[i] == ')')
			count--;
		if (count < 0)
			error = 1;
	}
	if (count != 0 || error)
		return 1;
	return 0;
}

void input(calculator& cal) {
	bool error = 0;
	string input_string = cal.to_be_cal;
	getline(cin, input_string);
	error = check(input_string);
	if (!error) {
		if (input_string[0] == 'S' && input_string[1] == 'e' && input_string[2] == 't') {
			int current = 4;
			int next = input_string.find_first_of(" ", current);
			string type = input_string.substr(current, next - current);
			if (type == "Integer") {
				current = next + 1;
				next = input_string.find_first_of("=") - 1;
				string variable_name = input_string.substr(current, next - current);
				current = next + 3;
				next = input_string.size();
				input_string = input_string.substr(current, next - current);
				calculator cal;
				trans_var(input_string);
				cal.to_be_cal = input_string;
				cal.fuction();
				cal.parse();
				string result = calculate(cal.output);
				current = 0;
				next = result.find_first_of(".", 0);
				if (next != string::npos) {
					result = result.substr(current, next - current);
				}
				v[variable_name] = result;

			}
			else if (type == "Decimal") {
				current = next + 1;
				next = input_string.find_first_of("=") - 1;
				string variable_name = input_string.substr(current, next - current);
				current = next + 3;
				next = input_string.size();
				input_string = input_string.substr(current, next - current);
				trans_var(input_string);
				cal.to_be_cal = input_string;
				cal.fuction();
				cal.parse();
				string result = calculate(cal.output);
				v[variable_name] = result;

			}
			else {
				cal.output = "Set variable error";
			}
		}
		else {
			trans_var(input_string);
			cal.to_be_cal = input_string;
			cal.Removewhite();
			cal.fuction();
			cal.parse();
			cout << cal.output << endl;
			cal.reset();
		}
	}
	else
		cal.output = "input error";
}