#include "stc++.h"

using namespace std;

/* 121. Best Time to Buy and Sell Stock */
int maxProfit(vector<int>& prices) {
    int res = 0;
    int tmp = 0;
    for (int i = 1; i < prices.size(); i++) {
        tmp = max(0, tmp + prices[i] - prices[i - 1]);
        res = max(res, tmp);
    }
    return res;
}

/* 70. Climbing Stairs */
int climbStairs(int n) {
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    if (n == 2)
        return 2;
    long long pre_1 = 1;
    long long pre_2 = 2;
    long long tmp = pre_2;
    int i = 3;
    while (i <= n) {
        tmp = pre_2;
        pre_2 = pre_1 + tmp;
        pre_1 = tmp;
        i++;
    }
    return pre_2;
}

/* 53. Maximum Subarray */
int maxSubArray(vector<int>& nums) {
    if (nums.size() == 0)
        return 0;
    int res = nums[0];
    int pre = 0;
    for (auto num : nums) {
        pre = max(num, pre + num);
        res = max(pre, res);
    }
    return res;
}

/* 63. Unique Paths II */
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int n = obstacleGrid.size();
    if (n == 0)
        return 0;
    int m = obstacleGrid[0].size();
    vector<vector<long>> res;
    for (int i = 0; i < n; ++i) {
        vector<long> tmp;
        for (int j = 0; j < m; ++j) {
            tmp.push_back(0);
        }
        res.push_back(tmp);
    }
    res[0][0] = 0;
    if (obstacleGrid[0][0] == 1)
        return 0;
    if (n == 1) {
        for (int i = 0; i < m; ++i) {
            if (obstacleGrid[0][i] == 1)
                return 0;
        }
        return 1;
    }
    if (m == 1) {
        for (int i = 0; i < n; ++i) {
            if (obstacleGrid[i][0] == 1)
                return 0;
        }
        return 1;
    }

    if (obstacleGrid[0][1] == 0)
        res[0][1] = 1;
    if (obstacleGrid[1][0] == 0)
        res[1][0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i + j <= 1 || obstacleGrid[i][j] == 1)
                continue;
            if (i == 0)
                res[i][j] = res[i][j - 1];
            else if (j == 0)
                res[i][j] = res[i - 1][j];
            else
                res[i][j] = res[i - 1][j] + res[i][j - 1];
        }
    }
    return res[n - 1][m - 1];
}

/* 413. Arithmetic Slices */
int numberOfArithmeticSlices(vector<int>& A) {
    if (A.size() < 3)
        return 0;
    int res = 0;
    int count = 0;
    int comp = A[1] - A[0];
    for (int i = 1; i < A.size(); i++) {
        if ((A[i] - A[i - 1]) == comp) {
            count += 1;
        }
        else {
            count = 1;
        }
        comp = A[i] - A[i - 1];
        res += max(0, count - 1);

    }
    return res;
}

/* 1277. Count Square Submatrices with All Ones */
int countSquares(vector<vector<int>>& matrix) {
    int res = 0;
    int m = matrix.size();
    vector<vector<int>> tmp;
    if (m == 0) {
        return 0;
    }
    int n = matrix[0].size();
    for (int i = 0; i < m; i++) {
        vector<int> line;
        for (int j = 0; j < n; j++) {
            line.push_back(0);
        }
        tmp.push_back(line);
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0) {
                if (matrix[i][j] == 1) {
                    res += 1;
                    tmp[i][j] = 1;
                }
            }
            else if (j == 0) {
                if (matrix[i][j] == 1) {
                    res += 1;
                    tmp[i][j] = 1;
                }
            }
            else {
                if (matrix[i][j] == 1) {
                    res += 1 + min(min(tmp[i - 1][j], tmp[i][j - 1]), tmp[i - 1][j - 1]);
                    tmp[i][j] = 1 + min(min(tmp[i - 1][j], tmp[i][j - 1]), tmp[i - 1][j - 1]);
                }
            }

        }
    }
    return res;

}

/* 120. Triangle */
int minimumTotal(vector<vector<int>>& triangle) {
    int res = triangle[0][0];
    vector<vector<int>> tmp;
    for (int i = 0; i < triangle.size(); ++i) {
        vector<int> line;
        int temp = 0;
        for (int j = 0; j < triangle[i].size(); ++j) {
            if (i == 0) {
                line.push_back(triangle[i][j]);
            }
            else if (i == triangle.size() - 1) {
                if (j == 0) {
                    res = triangle[i][j] + tmp[i - 1][j];
                }
                else if (j == triangle[i].size() - 1) {
                    res = min(res, triangle[i][j] + tmp[i - 1][j - 1]);
                }
                else {
                    res = min(res, min(triangle[i][j] + tmp[i - 1][j - 1], triangle[i][j] + tmp[i - 1][j]));
                }
            }
            else {
                if (j == 0) {
                    temp = triangle[i][j] + tmp[i - 1][j];
                }
                else if (j == triangle[i].size() - 1) {
                    temp = triangle[i][j] + tmp[i - 1][j - 1];
                }
                else {
                    temp = min(triangle[i][j] + tmp[i - 1][j - 1], triangle[i][j] + tmp[i - 1][j]);
                }
                line.push_back(temp);
            }
        }
        tmp.push_back(line);
    }
    return res;
}

/* 650. 2 Keys Keyboard */
int minSteps(int n) {
    int res = n;
    vector<int> dp;
    dp.push_back(0);
    int tmp = n;
    for (int i = 2; i <= n; i++) {
        tmp = i;
        for (int j = 1; j < i; j++) {
            if (i % j == 0) {
                tmp = min(tmp, dp[j - 1] + i / j);
            }
        }
        dp.push_back(tmp);
    }
    return dp[n - 1];
}

/* 96. Unique Binary Search Trees */
int numTrees(int n) {
    vector<int> dp;
    dp.push_back(1);
    dp.push_back(1);
    dp.push_back(2);
    int tmp = 0;
    for (int i = 3; i <= n; ++i) {
        tmp = 0;
        for (int j = 1; j <= i; ++j) {
            tmp += dp[j - 1] * dp[i - j];
        }
        dp.push_back(tmp);
    }
    return dp[n];
}

/* 264. Ugly Number II */
int nthUglyNumber(int n) {
    if (n == 0)
        return 0;
    vector<int> dp(n);
    int twoC = 0;
    int threeC = 0;
    int fiveC = 0;
    dp[0] = 1;
    for (int i = 1; i < n; i++) {
        dp[i] = min(min(dp[twoC] * 2, dp[threeC] * 3), dp[fiveC] * 5);
        if (dp[i] == dp[twoC] * 2)
            twoC++;
        if (dp[i] == dp[threeC] * 3)
            threeC++;
        if (dp[i] == dp[fiveC] * 5)
            fiveC++;
    }
    return dp[n - 1];
}


/* 213. House Robber II */
int rob(vector<int>& nums) {
    if (nums.size() == 0)
        return 0;
    if (nums.size() == 1)
        return nums[0];
    if (nums.size() == 2)
        return max(nums[0], nums[1]);
    int oneodd = 0;
    int oneeven = 0;
    for (int i = 0; i < nums.size() - 1; i++) {
        if (i % 2 == 0) {
            oneodd = max(oneodd, oneeven);
            oneeven += nums[i];
        }
        else {
            oneeven = max(oneeven, oneodd);
            oneodd += nums[i];
        }
    }
    int res = max(oneodd, oneeven);
    int twoodd = 0;
    int twoeven = 0;
    for (int i = 1; i < nums.size(); i++) {
        if (i % 2 == 0) {
            twoodd = max(twoodd, twoeven);
            twoeven += nums[i];
        }
        else {
            twoeven = max(twoodd, twoeven);
            twoodd += nums[i];
        }
    }
    res = max(max(res, twoeven), twoodd);
    return res;
}


/* 1143. Longest Common Subsequence */
int longestCommonSubsequence(string text1, string text2) {
    vector<vector<int>> arr;
    int len1 = text1.length();
    int len2 = text2.length();
    for (int i = 0; i <= len2; i++) {
        vector<int> tmp;
        for (int j = 0; j <= len1; j++)
            tmp.push_back(0);
        arr.push_back(tmp);
    }
    for (int i = 1; i <= len2; i++) {
        for (int j = 1; j <= len1; j++) {
            if (text1[j - 1] == text2[i - 1])
                arr[i][j] = arr[i - 1][j - 1] + 1;
            else
                arr[i][j] = max(arr[i - 1][j], arr[i][j - 1]);
        }
    }

    return arr[len2][len1];
}

/* 516. Longest Palindromic Subsequence */
int longestPalindromeSubseq(string s) {
    vector<vector<int>> arr;
    int lens = s.length();
    if (lens == 0)
        return 0;
    for (int i = 0; i < lens; i++) {
        vector<int> tmp;
        for (int j = 0; j < lens; j++) {
            if (i == j)
                tmp.push_back(1);
            else
                tmp.push_back(0);
        }
        arr.push_back(tmp);
    }
    for (int i = 1; i < lens; i++) {
        for (int j = 0; j < lens - i; j++) {
            if (i == 1)
                arr[j][j + i] = max(max(arr[j][j + i - 1], arr[j + 1][j + i]), s[j] == s[j + i] ? 2 : 0);
            else
                arr[j][j + i] = max(max(arr[j][j + i - 1], arr[j + 1][j + i]), (s[j] == s[j + i] ? 2 : 0) + arr[j + 1][j + i - 1]);
        }
    }
    return arr[0][lens - 1];
}

/* 139. Word Break */
bool wordBreak(string s, vector<string>& wordDict) {
    map<string, bool> wmap;
    for (int i = 0; i < wordDict.size(); i++) {
        wmap[wordDict[i]] = true;
    }
    int lens = s.length();
    vector<int> dp(lens + 1);
    dp[0] = 1;
    for (int i = 1; i <= lens; i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (dp[j] == 1) {
                string tmpstr = s.substr(j, i - j);
                if (wmap.find(tmpstr) != wmap.end()) {
                    dp[i] = 1;
                }
            }
        }
    }
    return dp[lens];
}

/* 486. Predict the Winner */
bool PredictTheWinner(vector<int>& nums) {
    int nsize = nums.size();
    bool flag = (nsize % 2 == 0);
    int numsum = 0;
    vector<vector<int>> dp;
    for (int i = 0; i < nsize; ++i) {
        vector<int> tmp;
        for (int j = 0; j < nsize; ++j) {
            if (i == j) {
                if (flag) tmp.push_back(nums[i]);
                else tmp.push_back(0);
                numsum += nums[i];
            }
            else
                tmp.push_back(0);
        }
        dp.push_back(tmp);
    }
    for (int p = 1; p < nsize; ++p) {
        for (int q = 0; q < nsize - p; ++q) {
            if (flag) {
                if (p % 2 == 0)
                    dp[q][q + p] = max(nums[q] + dp[q + 1][q + p], nums[q + p] + dp[q][q + p - 1]);
                else
                    dp[q][q + p] = min(dp[q + 1][q + p], dp[q][q + p - 1]);
            }
            else {
                if (p % 2 == 0)
                    dp[q][q + p] = min(dp[q + 1][q + p], dp[q][q + p - 1]);
                else
                    dp[q][q + p] = max(nums[q] + dp[q + 1][q + p], nums[q + p] + dp[q][q + p - 1]);
            }
        }
    }
    return (numsum / 2) >= dp[0][nsize - 1];
}

/* 322. Coin Change */
int coinChange(vector<int>& coins, int amount) {
    if (amount == 0)
        return 0;
    vector<int> dp;
    for (int i = 0; i <= amount; ++i) {
        dp.push_back(-1);
    }
    for (int i = 0; i < coins.size(); ++i) {
        if (coins[i] <= amount)
            dp[coins[i]] = 1;
    }
    for (int i = 1; i <= amount; ++i) {
        for (int j = 0; j < coins.size(); ++j) {
            if (coins[j] > i)
                continue;
            else {
                if (dp[i - coins[j]] != -1) {
                    if (dp[i] == -1) dp[i] = dp[i - coins[j]] + 1;
                    else dp[i] = min(dp[i], dp[i - coins[j]] + 1);
                }
            }
        }
    }
    return dp[amount];
}

/* 983. Minimum Cost For Tickets */
int mincostTickets(vector<int>& days, vector<int>& costs) {
    vector<int> dp;
    int sized = days.size();
    for (int i = 0; i <= 365; i++) {
        dp.push_back(0);
    }
    for (int i = 0; i < sized; i++) {
        dp[days[i]] = costs[0];
    }
    for (int i = 1; i <= 365; i++) {
        if (i < 7)
            dp[i] = dp[i] + dp[i - 1];
        else if (i >= 7 && i < 30) {
            dp[i] = min(dp[i] + dp[i - 1], dp[i - 7] + costs[1]);
        }
        else
            dp[i] = min(min(dp[i] + dp[i - 1], dp[i - 7] + costs[1]), dp[i - 30] + costs[2]);
    }
    return dp[365];

}

/* 5. Longest Palindromic Substring */
string longestPalindrome(string s) {
    vector<vector<int>> dp;
    string res = "";
    int maxl = 1;
    int lens = s.length();
    for (int i = 0; i < lens; ++i) {
        vector<int> tmp;
        for (int j = 0; j < lens; ++j) {
            if (i == j) {
                tmp.push_back(1);
                res = s[i];
            }
            else
                tmp.push_back(0);
        }
        dp.push_back(tmp);
    }
    for (int i = 1; i < lens; ++i) {
        for (int j = 0; j + i < lens; ++j) {
            if (i == 1) {
                if (s[j] == s[j + i]) {
                    dp[j][j + i] = i + 1;
                    if (maxl < i + 1) {
                        maxl = i + 1;
                        res = s.substr(j, i + 1);
                    }
                }
            }
            else {
                if (dp[j + 1][j + i - 1] == i - 1) {
                    if (s[j] == s[j + i]) {
                        dp[j][j + i] = i + 1;
                        if (maxl < i + 1) {
                            maxl = i + 1;
                            res = s.substr(j, i + 1);
                        }
                    }
                }
            }
        }
    }
    return res;
}

/* 740. Delete and Earn */
int deleteAndEarn(vector<int>& nums) {
    int sizen = nums.size();
    vector<int> count(10001);
    vector<int> dp(10001);
    for (int num : nums) {
        count[num] += 1;
    }
    dp[1] = count[1];
    dp[2] = count[2] * 2;
    for (int i = 3; i < 10001; ++i) {
        dp[i] = max(dp[i - 2], dp[i - 3]) + count[i] * i;
    }
    return dp[10000];
}

/* 1048. Longest String Chain */
static int comp(const string& str1, const string& str2) {
    return str1.length() < str2.length();
}
int longestStrChain(vector<string>& words) {
    sort(words.begin(), words.end(), comp);
    unordered_map<string, int> dp;
    int res = 0;
    for (string word : words) {
        for (int i = 0; i < word.length(); ++i)
            dp[word] = max(dp[word], dp[word.substr(0, i) + word.substr(i + 1)] + 1);
        res = max(res, dp[word]);
    }
    return res;
}

/* 152. Maximum Product Subarray */
int maxProduct(vector<int>& nums) {
    int maxproduct = nums[0];
    int minproduct = nums[0];
    int res = nums[0];
    for (int i = 0; i < nums.size(); i++) {
        if (i != 0) {
            maxproduct *= nums[i];
            minproduct *= nums[i];
        }
        res = max(res, maxproduct);
        res = max(res, minproduct);
        if (nums[i] <= 0) {
            int tmp = maxproduct;
            maxproduct = max(minproduct, 1);
            minproduct = min(tmp, 0);
        }
    }
    return res;
}

/* 464. Can I Win */
int arr[1 << 20] = {};

bool canIWinHelper(int m, int t, int k) {
    if (arr[k] != 0) return arr[k] > 0;
    if (t <= 0) return false;
    for (int i = 0; i < m; i++) {
        if (!(k & (1 << i)) && !canIWinHelper(m, t - i - 1, (k | (1 << i)))) {
            arr[k] = 1;
            return true;
        }
    }
    arr[k] = -1;
    return false;
}

bool canIWin(int maxChoosableInteger, int desiredTotal) {
    if (maxChoosableInteger > desiredTotal)
        return true;
    int sum = maxChoosableInteger * (maxChoosableInteger + 1) / 2;
    if (desiredTotal < 2)
        return true;
    if (sum == desiredTotal)
        return maxChoosableInteger % 2;
    if (sum < desiredTotal)
        return false;
    return canIWinHelper(maxChoosableInteger, desiredTotal, 0);
}

/* 494. Target Sum */
long findTSHelper(vector<int>& nums, int s) {
    vector<int>dp(s + 1);
    dp[0] = 1;
    for (int n : nums) {
        for (int i = s; i >= n; --i) {
            dp[i] += dp[i - n];
        }
    }
    return dp[s];
}

long findTargetSumWays(vector<int>& nums, int S) {
    int sum = 0;
    for (int i = 0; i < nums.size(); i++) {
        sum += nums[i];
    }
    return sum < S || (sum + S) & 1 ? 0 : findTSHelper(nums, (sum + S) >> 1);
}

/* 647. Palindromic Substrings */
int countSubstrings(string s) {
    int lens = s.length();
    vector<vector<int>> dp(lens, vector<int>(lens));
    for (int i = 0; i < lens; i++) {
        dp[i][i] = 1;
    }
    for (int i = 1; i < lens; ++i) {
        for (int j = 0; i + j < lens; ++j) {
            if (s[j] == s[j + i]) {
                if (i == 1)
                    dp[j][j + i] = 1;
                else
                    dp[j][j + i] = dp[j + 1][j + i - 1];
            }
        }
    }
    int res = 0;
    for (int i = 0; i < lens; i++) {
        for (int j = 0; j < lens; j++) {
            res += dp[i][j];
        }
    }
    return res;
}

/* 931. Minimum Falling Path Sum */
int minFallingPathSum(vector<vector<int>>& A) {
    int col = A.size();
    int row = A[0].size();
    vector<vector<int>> dp(col, vector<int>(row));
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (i == 0) {
                dp[i][j] = A[i][j];
            }
            else {
                if (j == 0) {
                    dp[i][j] = min(dp[i - 1][j], dp[i - 1][j + 1]) + A[i][j];
                }
                else if (j == (row - 1)) {
                    dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j]) + A[i][j];
                }
                else {
                    dp[i][j] = min(min(dp[i - 1][j - 1], dp[i - 1][j]), dp[i - 1][j + 1]) + A[i][j];
                }
            }
        }
    }
    int res = dp[col - 1][0];
    for (int k = 0; k < row; k++) {
        res = min(res, dp[col - 1][k]);
    }
    return res;
}

/* 1024. Video Stitching */
static int compVS(const vector<int>& a, const vector<int>& b) {
    return (a[0] == b[0]) ? (a[1] < b[1]) : (a[0] < b[0]);
}
int videoStitching(vector<vector<int>>& clips, int T) {
    int res = 0;
    sort(clips.begin(), clips.end(), compVS);
    vector<int> prev = clips[0];
    if (prev[0] != 0)
        return -1;
    int i = 0;
    for (; i < clips.size(); ++i) {
        if (clips[i][0] != 0)
            break;
        if (clips[i][1] > prev[1])
            prev = clips[i];
    }
    res++;
    vector<int> curr = prev;
    for (; i < clips.size(); ++i) {
        if (prev[1] >= T)
            return res;
        if (curr[1] >= T)
            return (res + 1);
        if (clips[i][0] <= prev[1] && clips[i][1] > curr[1]) {
            curr = clips[i];
        }
        else if (clips[i][0] > prev[1]) {
            if (curr[1] <= prev[1])
                return -1;
            else {
                prev = curr;
                res++;
            }
        }
    }
    return (curr[1] >= T) ? (res + 1) : -1;
}

/* 474. Ones and Zeroes */
int findMaxForm(vector<string>& strs, int m, int n) {
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    for (auto& str : strs) {
        int zo = 0;
        int on = 0;
        for (auto chr : str) {
            if (chr == '0') zo++;
            else on++;
        }
        for (int i = m; i >= zo; --i) {
            for (int j = n; j >= on; --j) {
                dp[i][j] = max(dp[i][j], dp[i - zo][j - on] + 1);
            }
        }
    }
    return dp[m][n];
}

/* 526. Beautiful Arrangement */
void CAHelper(int& res, int N, vector<int> tmp, int t) {
    if (t > N) {
        res += 1;
        return;
    }
    for (int i = 1; i <= N; ++i) {
        if (tmp[i])
            continue;
        if ((i % t == 0) || (t % i == 0)) {
            tmp[i] = 1;
            CAHelper(res, N, tmp, t + 1);
            tmp[i] = 0;
        }
    }
}

int countArrangement(int N) {
    if (N <= 1)
        return N;
    int res = 0;
    vector<int> tmp(N + 1, 0);
    CAHelper(res, N, tmp, 1);
    return res;
}

/* 1027. Longest Arithmetic Sequence */
int longestArithSeqLength(vector<int>& A) {
    unordered_map<int, unordered_map<int, int>> dp;
    int res = 2;
    for (int i = 1; i < A.size(); i++) {
        for (int j = 0; j < i; j++) {
            int dist = A[i] - A[j];
            dp[i][dist] = dp[j][dist] == 0 ? 2 : (dp[j][dist] + 1);
            res = max(res, dp[i][dist]);
        }
    }
    return res;
}

/* 1130. Minimum Cost Tree From Leaf Values */
int mctFromLeafValues(vector<int>& arr) {
    int s = arr.size();
    vector<vector<int>> dp(s, vector<int>(s, 0));
    vector<vector<int>> mnum(s, vector<int>(s, 16));
    for (int i = 0; i < s; ++i) {
        mnum[i][i] = arr[i];
    }
    for (int i = 1; i < s; ++i) {
        for (int j = 0; j < s - i; ++j) {
            for (int k = j; k < j + i; ++k) {
                mnum[j][j + i] = max(mnum[j][k], mnum[k + 1][i + j]);
                int tmp = dp[j][k] + dp[k + 1][i + j] + mnum[j][k] * mnum[k + 1][i + j];
                if (dp[j][i + j] == 0)
                    dp[j][i + j] = tmp;
                else
                    dp[j][i + j] = min(tmp, dp[j][i + j]);
                // cout << j << " : " << j + i<< " : " << mnum[j][j + i] << endl;
            }
        }
    }
    return dp[0][s - 1];
}

/* 300. Longest Increasing Subsequence */
int lengthOfLIS(vector<int>& nums) {
    int size = nums.size();
    if (size <= 1)
        return size;
    int res = 1;
    vector<int> dp(size, 1);
    for (int i = 1; i < size; ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[i] > nums[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        res = max(res, dp[i]);
    }
    return res;
}

/* 673. Number of Longest Increasing Subsequence */
int findNumberOfLIS(vector<int>& nums) {
    int size = nums.size();
    if (size <= 1)
        return size;
    int res = 1, maxCount = 1;
    vector<int> dp(size, 1);
    vector<int> dp_res(size, 1);
    for (int i = 1; i < size; ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[i] > nums[j]) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    dp_res[i] = dp_res[j];
                }
                else if (dp[i] == dp[j] + 1) {
                    dp_res[i] += dp_res[j];
                }
            }
        }
        if (maxCount < dp[i]) {
            maxCount = dp[i];
            res = dp_res[i];
        }
        else if (maxCount == dp[i]) {
            res += dp_res[i];
        }
    }
    return res;
}

/* 1423. Maximum Points You Can Obtain from Cards */
int maxScore(vector<int>& cardPoints, int k) {
    int res = 0, tmp = 0;
    int size = cardPoints.size();
    int start = size - k;
    for (int i = start; i < size; ++i) {
        tmp += cardPoints[i];
    }
    res = tmp;
    int t = 0;
    for (int i = start; i < size; ++i) {
        tmp = tmp - cardPoints[i] + cardPoints[t];
        res = max(tmp, res);
        t++;
    }
    return res;
}


/* 1105. Filling Bookcase Shelves */
int minHeightShelves(vector<vector<int>>& books, int shelf_width) {
    int size = books.size();
    vector<int> dp(size + 1, 0);
    for (int i = 1; i <= size; ++i) {
        int w = books[i - 1][0];
        int h = books[i - 1][1];
        dp[i] = dp[i - 1] + h;
        for (int j = i - 1; j > 0; --j) {
            h = max(books[j - 1][1], h);
            w += books[j - 1][0];
            if (w > shelf_width)
                break;
            dp[i] = min(dp[i], dp[j - 1] + h);
        }
    }
    return dp[size];
}

/* 1049. Last Stone Weight II */
int lastStoneWeightII(vector<int>& stones) {
    int res = 0;
    int sum = 0;
    vector<int> dp(30001);
    dp[0] = 1;
    for (auto stone : stones) {
        sum += stone;
    }
    for (auto stone : stones) {
        for (int i = sum; i >= stone * 2; --i) {
            dp[i] += dp[i - stone * 2];
            if (dp[i] != 0) {
                res = max(res, i);
            }
        }
    }
    return sum - res;
}

/* 813. Largest Sum of Averages */
double LSOAHelper(vector<int>& A, int k, int n);
double dp813[201][201];
double largestSumOfAverages(vector<int>& A, int K) {
    memset(dp813, 0, sizeof(dp813));
    double sum = 0;
    for (int i = 0; i < A.size(); ++i) {
        sum += A[i];
        dp813[i + 1][1] = sum / (i + 1);
    }
    return LSOAHelper(A, K, A.size());
}
double LSOAHelper(vector<int>& A, int k, int n) {
    if (dp813[n][k] > 0)
        return dp813[n][k];
    if (k > n)
        return 0;
    double sum = 0;
    for (int i = n - 1; i >= 0; --i) {
        sum += A[i];
        dp813[n][k] = max(dp813[n][k], LSOAHelper(A, k - 1, i) + sum / (n - i));
    }
    // cout << n << " " << k << " " << dp[n][k] << endl;
    return dp813[n][k];
}


/* 887. Super Egg Drop */
int superEggDrop(int K, int N) {
    vector<vector<int>> dp(K + 1, vector<int>(N + 1, 0));
    for (int i = 0; i <= N; ++i)
        dp[1][i] = i;
    for (int j = 1; j <= N; ++j) {
        for (int i = 1; i <= K; ++i) {
            dp[i][j] = dp[i - 1][j - 1] + dp[i][j - 1] + 1;
            if (dp[i][j] >= N)
                return j;
        }
    }
    return dp[K][N];
}

/* 403. Frog Jump */
bool canCross(vector<int>& stones) {
    int size = stones.size();
    if (stones[1] != 1)
        return false;
    if (size == 2)
        return true;
    int maxDist = stones[size - 1] - stones[0];
    vector<vector<int>> dp(size + 1, vector<int>(size + 1, 0));

    dp[1][1] = 1;
    for (int i = 2; i < size; ++i) {
        // cout << i << ":";
        for (int j = i - 1; j >= 1; --j) {
            int dist = stones[i] - stones[j];
            if (j == 0 || dist + 1 > size) {
                continue;
            }
            int tmp = 0;
            tmp = dp[j][dist + 1] + dp[j][dist] + dp[j][dist - 1];
            dp[i][stones[i] - stones[j]] = tmp > 0;
            if (i == size - 1) {
                if (tmp > 0)
                    return true;
            }
            // cout << dp[i][stones[i] - stones[j]] << " ";
        }
        // cout << endl;
    }
    return false;
}
//     bool canCross(vector<int>& stones) {
//         vector<int> move{-1, 0, 1};

//         map<long, bool> isUnit;
//         map<pair<int, int>, bool> isUsed;
//         queue<pair<int,int>> bfs;

//         int size = stones.size();
//         if(stones[1] != 1)
//             return false;
//         if(size == 2)
//             return true;

//         for(auto stone : stones)
//             isUnit[stone] = true;
//         bfs.push({1, 1});
//         while(!bfs.empty()){
//             auto tmp = bfs.front();
//             int step = tmp.second;
//             int po = tmp.first;
//             bfs.pop();
//             for(int m : move){
//                 if(step + m > 0){
//                     if(isUnit[po + step + m]){
//                         if(po + step + m == stones[size - 1])
//                             return true;
//                         if(!isUsed[{po + step + m, step + m}]){
//                             isUsed[{po + step + m, step + m}] = true;
//                             bfs.push({po + step + m, step + m});
//                         }
//                     }
//                 }
//             }
//         }

//         return false;
//     }
