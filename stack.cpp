#include "stc++.h"

using namespace std;

/*******************/
/* Stack functions */
/*******************/

void printStack(stack<int> myStack) {
	cout << "Stack size: " << myStack.size() << endl;
	while (!myStack.empty()) {
		cout << myStack.top() << endl;
		myStack.pop();
	}
}


/* 1047. Remove All Adjacent Duplicates In String */
int minAddToMakeValid(string S) {
	stack<char> parentheses;
	int carry = 0;
	int res = 0;
	for (int i = 0; i < S.length(); i++) {
		parentheses.push(S[i]);
	}
	while (!parentheses.empty()) {
		if (parentheses.top() == '(') {
			if (!carry)
				res++;
			else
				carry--;
		}
		else {
			carry++;
		}
		parentheses.pop();
	}
	res += carry;
	return res;
}

/* 1047. Remove All Adjacent Duplicates In String */
string removeDuplicates(string S) {
	stack<char> tmp;
	if (S.length() == 0)
		return S;
	tmp.push(S[0]);
	for (int i = 1; i < S.length(); i++) {
		if (tmp.empty() || S[i] != tmp.top())
			tmp.push(S[i]);
		else
			tmp.pop();
	}
	string res = "";

	while (!tmp.empty()) {
		res = tmp.top() + res;
		tmp.pop();
	}
	return res;
}

/* 856. Score of Parentheses */
int scoreOfParentheses(string S) {
	int res = 0;
	int t_res = 0;
	int prev = 0;
	int curr = 0;
	int flag = 1;
	int rightP = 0;
	stack<char> tmp;
	for (int i = 0; i < S.length(); i++) {
		tmp.push(S[i]);
	}
	while (!tmp.empty()) {
		if (tmp.top() == ')') {
			res += t_res;
			t_res = 0;
			rightP++;
			curr = 0;
		}
		else {
			rightP--;
			if (curr == 0) {
				prev = 0;
				curr = 1;
				t_res += 1;
			}
			else {
				prev = 1;
				t_res *= 2;
			}
		}
		tmp.pop();
		if (rightP == 0 && !tmp.empty()) {
			flag = 0;
		}
	}
	if (flag)
		res = (res + (t_res / 2)) * 2;
	else
		res += t_res;

	return res;
}


/* 844. Backspace String Compare */
bool backspaceCompare(string S, string T) {
	stack<char> chr_s;
	stack<char> chr_t;

	for (auto s : S) {
		if (s == '#') {
			if (!chr_s.empty())
				chr_s.pop();
		}
		else {
			chr_s.push(s);
		}
	}
	for (auto t : T) {
		if (t == '#') {
			if (!chr_t.empty())
				chr_t.pop();
		}
		else {
			chr_t.push(t);
		}
	}

	while (!chr_s.empty() and !chr_t.empty()) {
		if (chr_s.top() != chr_t.top())
			return false;
		chr_s.pop();
		chr_t.pop();
	}
	if (!chr_s.empty() or !chr_t.empty())
		return false;
	return true;
}

/* 20. Valid Parentheses */
bool isValid(string s) {
	stack<char> left;
	stack<char> right;

	for (auto i : s) {
		left.push(i);
	}
	while (!left.empty()) {
		if (left.top() == '(') {
			if (right.empty()) {
				return false;
			}
			else {
				if (right.top() == ')') {
					left.pop();
					right.pop();
				}
				else {
					return false;
				}
			}
		}
		else if (left.top() == '[') {
			if (right.empty()) {
				return false;
			}
			else {
				if (right.top() == ']') {
					left.pop();
					right.pop();
				}
				else {
					return false;
				}
			}
		}
		else if (left.top() == '{') {
			if (right.empty()) {
				return false;
			}
			else {
				if (right.top() == '}') {
					left.pop();
					right.pop();
				}
				else {
					return false;
				}
			}
		}
		else {
			right.push(left.top());
			left.pop();
		}
	}
	if (!right.empty())
		return false;
	return true;
}


/* 1190. Reverse Substrings Between Each Pair of Parentheses */
