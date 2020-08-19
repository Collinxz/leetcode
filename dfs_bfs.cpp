#include "stc++.h"

using namespace std;

/* 394. Decode String */
string decodeString(string s) {
    stack<int> nums;
    stack<string> strs;
    string res = "", str = "";
    char ch;
    int i = 0;
    while (i < s.length()) {
        ch = s[i];
        if (isalpha(ch)) {
            str += ch;
        }
        else if (isdigit(ch)) {
            if (nums.empty()) {
                while (!strs.empty()) {
                    res += strs.top();
                    strs.pop();
                }
                res += str;
            }
            else {
                strs.push(str);
            }
            int num = ch - '0';
            while (isdigit(s[i + 1])) {
                i += 1;
                num = num * 10 + s[i] - '0';
            }
            nums.push(num);
            str = "";
        }
        else if (ch == ']') {
            string tmp = "";
            int repn = nums.top();
            string reps = str;
            while (strs.top() != "[") {
                reps = strs.top() + reps;
                strs.pop();
            }
            while (repn) {
                tmp += reps;
                repn--;
            }
            nums.pop();
            strs.pop();
            strs.push(tmp);
            str = "";
        }
        else {
            string tmp = "";
            tmp += ch;
            strs.push(tmp);
        }
        i++;
    }
    if (!strs.empty()) {
        res = res + strs.top();
        strs.pop();
    }
    res += str;
    return res;
}

/* 542. 01 Matrix */
bool isVisit(int i, int j, int m, int n) {
    if (i == m || j == n || i < 0 || j < 0)
        return false;
    return true;
}
vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
    queue<pair<int, int>> bfs;
    int m = matrix.size();
    if (m == 0)
        return matrix;
    int n = matrix[0].size();
    vector<vector<int>> res(m, vector<int>(n, -1));
    vector<vector<int>> moves{ {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == 0) {
                res[i][j] = 0;
                bfs.push({ i, j });
            }
        }
    }
    while (!bfs.empty()) {
        pair<int, int> curr = bfs.front();
        for (auto move : moves) {
            int p = curr.first + move[0];
            int q = curr.second + move[1];
            if (isVisit(p, q, m, n) && res[p][q] == -1) {
                res[p][q] = res[curr.first][curr.second] + 1;
                bfs.push({ p, q });
            }
        }
        bfs.pop();
    }
    return res;
}