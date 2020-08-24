#include "stc++.h"

using namespace std;

/* 15. 3Sum */
vector<vector<int>> threeSum(vector<int> &nums)
{
    vector<vector<int>> res;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); i++)
    {
        if (i != 0 && (nums[i] == nums[i - 1]))
            continue;
        int l = i + 1;
        int r = nums.size() - 1;
        while (l < r)
        {
            if (nums[i] + nums[l] + nums[r] == 0)
            {
                vector<int> tvector{nums[i], nums[l], nums[r]};
                res.push_back(tvector);
                l++;
                r--;
                while (l < r && nums[l] == nums[l - 1])
                    l++;
                while (r > l && nums[r] == nums[r + 1])
                    r--;
            }
            else if (nums[i] + nums[l] + nums[r] < 0)
                l++;
            else
                r--;
        }
    }
    return res;
}

/* 45. Jump Game II */
int jump(vector<int> &nums)
{
    int sizeN = nums.size();
    int count = 0;
    int maxCount = 0;
    int res = 0;
    for (int i = 0; i < sizeN; i++)
    {
        if (i > count)
        {
            count = maxCount;
            res += 1;
        }
        maxCount = max(maxCount, nums[i] + i);
    }
    return res;
}

/* 3. Longest Substring Without Repeating Characters */
int lengthOfLongestSubstring(string s)
{
    int res = 0;
    int lens = s.length();
    if ((lens == 1) or (lens == 0))
        return lens;
    int st = 0;
    int ed = 1;
    int tmp = 1;
    while (ed != lens)
    {
        for (int i = st; i < ed; ++i)
        {
            if (s[ed] == s[i])
            {
                st = i + 1;
                res = max(res, tmp);
                tmp = ed - i - 1;
                break;
            }
        }
        tmp++;
        ed += 1;
    }
    return max(res, tmp);
}

/* 11. Container With Most Water */
int maxArea(vector<int> &height)
{
    if (height.size() <= 1)
        return 0;
    int l = 0;
    int s = height.size();
    int r = s - 1;
    int res = min(height[r], height[l]) * (s - 1);
    while (l < r)
    {
        res = max(res, min(height[r], height[l]) * (s - 1));
        if (height[l] < height[r])
            l++;
        else
            r--;
        s--;
    }
    return res;
}

/* 922. Sort Array By Parity II */
vector<int> sortArrayByParityII(vector<int> &A)
{
    int flagA = 0, flagB = 0;
    int sA = 0, sB = 1;
    int n = A.size();
    while (sB < n && sA < n)
    {
        if (A[sA] % 2 != 0)
            flagA = 1;
        if (A[sB] % 2 == 0)
            flagB = 1;
        if (flagA && flagB)
        {
            swap(A[sA], A[sB]);
            flagA = flagB = 0;
        }
        if (!flagA)
            sA += 2;
        if (!flagB)
            sB += 2;
    }
    return A;
}