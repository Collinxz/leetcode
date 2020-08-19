#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int problem1() {
	int five = 0;
	int ten = 0;
	int index = 1;
	
	vector<int> nums;
	int num;
	char ch;
	while (cin >> num) {
		nums.push_back(num);
		cin.get(ch);
	}
	
	for (int i = 0; i < nums.size(); ++i) {
		if (nums[i] != 5 && nums[i] != 10 && nums[i] != 20) {
			cout << "false" << " " << index << endl;
			return 0;
		}
		if (nums[i] == 5) {
			five += 1;
		}
		if (nums[i] == 10) {
			five -= 1;
			ten += 1;
		}
		if (nums[i] == 20) {
			if (ten > 0) {
				ten -= 1;
				five -= 1;
			}
			else {
				five -= 3;
			}
		}
		if (five < 0) {
			cout << "false" << " " << index << endl;
			return 0;
		}
		index += 1;
	}
	cout << "True" << " " << index - 1 << endl;
	return 0;
}


//int problem2 {
//	int s = 2, m = 3, n = 5;
//	int num;
//	vector<vector<int>> nums{ {1, 0, 1, 0, 0}, {0, 1, 1, 0, 1}, {0, 0, 1, 0, 1} };
//	vector<vector<int>> steps(m, vector<int>(n, 0));
//	steps[0][0] = 1;
//	steps[m - 1][n - 1] = 0;
//	for (int i = 0; i < m; ++i) {
//		for (int j = 0; j < n; ++j) {
//			if (nums[i][j] == 1) {
//				if (i != 0 && i % s == 0) {
//					steps[i][j] = max(steps[i - s][j], steps[i][j]);
//				}
//				if (j != 0 && j % s == 0) {
//					steps[i][j] = max(steps[i][j - s], steps[i][j]);
//				}
//				
//			}
//		}
//	}
//	if (steps[m - 1][n - 1] == 1) {
//		cout << "1" << endl;
//	}
//	else {
//		cout << "0" << endl;
//	}
//}

int main() {
	int ind;
	bool flag = true;
	string str = "EVERYTHINGGOESWELL";
	int s = 5;
	string res = "";
	for (int i = 1; i <= s; i += 2) {
		ind = i;
		flag = true;
		if (i == 1 || i == s) {
			while (ind <= str.length()) {
				res += str[ind - 1];
				ind += 2 * s - 3;
			}
		}
		else {
			while (ind <= str.length()) {
				res += str[ind - 1];
				if (flag) {
					ind += 2 * (s - i) - 1;
				}
				else {
					ind += 2 * (i - 1);
				}
				flag = -flag;
			}
		}
		cout << res << endl;
	}

	for (int i = s - 1; i > 0; i -= 2) {
		ind = i;
		flag = true;
		if (i == 2) {
			while (ind <= str.length()) {
				res += str[ind - 1];
				ind += 2 * s - 3;
			}
		}
		else {
			while (ind <= str.length()) {
				res += str[ind - 1];
				if (flag) {
					ind += 2 * (s - i) + 1;
				}
				else {
					ind += 2 * (i - 1);
				}
				flag = -flag;
			}
		}
		cout << res << endl;
	}
	cout << res << endl;
}