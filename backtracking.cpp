#include "stc++.h"

using namespace std;

/* 78. Subsets */
void SSHelper(vector<vector<int>>& res, int i, vector<int>& tmp, vector<int> nums) {
    res.push_back(tmp);
    for (int j = i; j < nums.size(); j++) {
        tmp.push_back(nums[j]);
        SSHelper(res, j + 1, tmp, nums);
        tmp.pop_back();
    }
}

vector<vector<int>> subsets(vector<int>& nums) {
    vector<int> tmp;
    vector<vector<int>> res;
    SSHelper(res, 0, tmp, nums);
    return res;
}


/* 46. Permutations */
void PHelper(vector<vector<int>>& res, vector<int>& tmp, vector<int> flag, vector<int> nums) {
    if (tmp.size() == nums.size()) {
        res.push_back(tmp);
        return;
    }
    for (int i = 0; i < nums.size(); i++) {
        if (flag[i] == 0) {
            tmp.push_back(nums[i]);
            flag[i] = 1;
            PHelper(res, tmp, flag, nums);
            tmp.pop_back();
            flag[i] = 0;
        }
    }
}

vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> res;
    int sizen = nums.size();
    vector<int> tmp;
    vector<int> flag(sizen);
    PHelper(res, tmp, flag, nums);
    return res;
}


/* 47. Permutations II */
void PUHelper(vector<vector<int>>& res, vector<int> nums, int i) {
    if ((i + 1) == nums.size()) {
        res.push_back(nums);
        return;
    }
    for (int k = i; k < nums.size(); ++k) {
        if (k != i && (nums[k] == nums[i])) continue;
        swap(nums[i], nums[k]);
        PUHelper(res, nums, i + 1);
    }
}
vector<vector<int>> permuteUnique(vector<int>& nums) {
    vector<vector<int>> res;
    sort(nums.begin(), nums.end());
    PUHelper(res, nums, 0);
    return res;
}

/* 51. N - Queens */
vector<vector<int>> flagFlash(int q, vector<vector<int>> flag, int p) {
    for (int i = q; i < flag.size(); ++i) {
        for (int j = 0; j < flag.size(); ++j) {
            if (j == p)
                flag[i][j] = 1;
            if (j < p && (j + i) == (p + q))
                flag[i][j] = 1;
            if (j > p && (j - i) == (p - q))
                flag[i][j] = 1;
        }
    }
    return flag;
}
void SNQHelper(vector<vector<string>>& res, vector<string>& tmp, int t, vector<vector<int>>& flag, string str) {
    if (tmp.size() == flag.size()) {
        res.push_back(tmp);
        return;
    }
    for (int i = t; i < flag.size(); ++i) {
        if (tmp.size() != i)
            return;
        for (int j = 0; j < flag.size(); ++j) {
            if (flag[i][j] == 1) {
                continue;
            }
            string tstr = str;
            tstr[j] = 'Q';
            tmp.push_back(tstr);
            vector<vector<int>> nflag = flagFlash(i, flag, j);
            SNQHelper(res, tmp, i + 1, nflag, str);
            tmp.pop_back();
        }
    }
}

vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> res;
    vector<string> tmp;
    if (n == 1) {
        tmp.push_back("Q");
        res.push_back(tmp);
        return res;
    }
    if (n <= 3)
        return res;
    vector<vector<int>> flag(n, vector<int>(n));
    string str = "";
    for (int i = 0; i < n; ++i) {
        str += ".";
    }
    SNQHelper(res, tmp, 0, flag, str);
    return res;
}

/* 77. Combinations */
void CHelper(vector<vector<int>>& res, vector<int>& tmp, int p, int n, int k) {
    if (tmp.size() == k) {
        res.push_back(tmp);
        return;
    }
    for (int i = p; i < n; ++i) {
        tmp.push_back(i + 1);
        CHelper(res, tmp, i + 1, n, k);
        tmp.pop_back();
    }
}

vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> res;
    vector<int> tmp;
    CHelper(res, tmp, 0, n, k);
    return res;
}

/* 79. Word Search */
bool EHelper(vector<vector<char>>& board, string word, int i, int j, int t) {
    if (t == word.length()) {
        return true;
    }
    if (i < 0 || i == board.size()) {
        return false;
    }
    if (j < 0 || j == board[0].size()) {
        return false;
    }
    char tmp = board[i][j];
    if (board[i][j] == word[t]) {
        board[i][j] = '\0';
        if (EHelper(board, word, i - 1, j, t + 1) || EHelper(board, word, i + 1, j, t + 1)
            || EHelper(board, word, i, j - 1, t + 1) || EHelper(board, word, i, j + 1, t + 1))
            return true;
        board[i][j] = tmp;
    }
    return false;

}

bool exist(vector<vector<char>>& board, string word) {
    int col = board.size();
    if (col == 0) return false;
    int row = board[0].size();
    for (int p = 0; p < col; ++p) {
        for (int q = 0; q < row; ++q) {
            if (EHelper(board, word, p, q, 0))
                return true;
        }
    }
    return false;
}

/* 39. Combination Sum */
void CSHelper(vector<vector<int>>& res, vector<int>& tmp, int t, int target, vector<int> c) {
    if (target == 0) {
        res.push_back(tmp);
        return;
    }
    if (target < 0) {
        return;
    }
    for (int i = t; i < c.size(); ++i) {
        tmp.push_back(c[i]);
        CSHelper(res, tmp, i, target - c[i], c);
        tmp.pop_back();
    }
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> res;
    vector<int> tmp;
    CSHelper(res, tmp, 0, target, candidates);
    return res;
}

/* 40. Combination Sum II */
void CS2Helper(vector<vector<int>>& res, vector<int>& tmp, int t, int target, vector<int> c) {
    if (target == 0) {
        res.push_back(tmp);
        return;
    }
    if (target < 0) {
        return;
    }
    for (int i = t; i < c.size(); ++i) {
        tmp.push_back(c[i]);
        CS2Helper(res, tmp, i + 1, target - c[i], c);
        tmp.pop_back();
        while (i != c.size() - 1 && c[i + 1] == c[i])
            i++;
    }
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> res;
    vector<int> tmp;
    CS2Helper(res, tmp, 0, target, candidates);
    return res;
}


/* 17. Letter Combinations of a Phone Number */

void LCHelper(vector<string>& res, vector<string> pd, int t, string digits, string tmp) {
    if (t == digits.length()) {
        res.push_back(tmp);
        return;
    }
    int index = digits[t] - '0' - 1;
    string cur = tmp;
    for (int i = 0; i < pd[index].length(); ++i) {
        if (pd[index][i] == '*')
            break;
        tmp += pd[index][i];
        LCHelper(res, pd, t + 1, digits, tmp);
        tmp = cur;
    }
}

vector<string> letterCombinations(string digits) {
    vector<string> pd;
    pd.push_back("****");
    pd.push_back("abc*");
    pd.push_back("def*");
    pd.push_back("ghi*");
    pd.push_back("jkl*");
    pd.push_back("mno*");
    pd.push_back("pqrs");
    pd.push_back("tuv*");
    pd.push_back("wxyz");

    vector<string> res;
    string tmp = "";
    if (digits.length() == 0)
        return res;
    LCHelper(res, pd, 0, digits, tmp);
    return res;
}