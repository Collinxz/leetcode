#include "stc++.h"

using namespace std;

/* 179. Largest Number */
static int compLN(const int a, const int b) {
    return (to_string(a) + to_string(b)) > (to_string(b) + to_string(a));
}
string largestNumber(vector<int>& nums) {
    sort(nums.begin(), nums.end(), compLN);
    string res = "";
    for (auto num : nums) {
        res += to_string(num);
    }

    return res[0] == '0' ? "0" : res;
}


/* 56. Merge Intervals */
static int compM(const vector<int>& a, const vector<int>& b) {
    return a[0] < b[0];
}
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    vector<vector<int>> res;
    if (intervals.size() == 0)
        return res;
    sort(intervals.begin(), intervals.end(), compM);
    vector<int> tmp = intervals[0];
    for (int i = 1; i < intervals.size(); ++i) {
        if (intervals[i][0] <= tmp[1]) {
            tmp[1] = max(intervals[i][1], tmp[1]);
        }
        else {
            res.push_back(tmp);
            tmp = intervals[i];
        }
    }
    res.push_back(tmp);
    return res;
}