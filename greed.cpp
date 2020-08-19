#include "stc++.h"

using namespace std;

/* 55. Jump Game */
bool canJump(vector<int>& nums) {
    int maxStep = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (i <= maxStep)
            maxStep = max(maxStep, i + nums[i]);
        else
            return false;
    }
    return true;
}

/* 134. Gas Station */
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int total = 0, curr = 0, start = 0;
    for (int i = 0; i < gas.size(); ++i) {
        if ((curr += gas[i] - cost[i]) < 0) {
            start = i + 1;
            curr = 0;
        }
        total += gas[i] - cost[i];
    }
    return total >= 0 ? start : -1;
}

/* 948. Bag of Tokens */
int bagOfTokensScore(vector<int>& tokens, int P) {
    int res = 0;
    sort(tokens.begin(), tokens.end());
    int i = 0, j = tokens.size() - 1;
    int t = 0;
    while (i <= j) {
        if (P >= tokens[i]) {
            P -= tokens[i];
            t += 1;
            res = max(res, t);
            i++;
        }
        else {
            if (t == 0)
                return res;
            else {
                P += tokens[j];
                j--;
                t--;
            }
        }
    }
    return res;
}

/* 861. Score After Flipping Matrix */
int matrixScore(vector<vector<int>>& A) {
    int col = A.size();
    int row = A[0].size();
    if (row == 0)
        return 0;
    int res = 0;
    for (int i = 0; i < col; i++) {
        if (A[i][0] == 0) {
            for (int j = 0; j < row; j++)
                A[i][j] = 1 - A[i][j];
        }
    }
    int count = 0;
    for (int j = 0; j < row; ++j) {
        count = 0;
        for (int i = 0; i < col; ++i) {
            if (A[i][j] == 0)
                count++;
        }
        count = max(count, col - count);
        res += count * pow(2, row - j - 1);
    }
    return res;
}

/* 376. Wiggle Subsequence */
int wiggleMaxLength(vector<int>& nums) {
    if (nums.size() <= 1)
        return nums.size();
    int res = 1;
    int i = 1;
    while (i + 1 < nums.size()) {
        if (nums[i] != nums[i - 1])
            break;
        i++;
    }
    bool flag = nums[i] > nums[i - 1];
    for (; i < nums.size(); ++i) {
        if (nums[i] == nums[i - 1])
            continue;
        if (flag == (nums[i] > nums[i - 1])) {
            res += 1;
            flag = !flag;
        }
    }
    return res;
}

/* 1046. Last Stone Weight */
int lastStoneWeight(vector<int>& stones) {
    priority_queue<int, vector<int>, less<int>> pq;
    for (auto stone : stones) {
        if (stone != 0)
            pq.push(stone);
    }
    while (pq.size() > 1) {
        int a = pq.top();
        pq.pop();
        int b = pq.top();
        pq.pop();
        a -= b;
        if (a != 0) {
            pq.push(a);
        }
    }
    return pq.size() ? pq.top() : 0;
}

/* 347. Top K Frequent Elements */
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> um;
    for (auto num : nums) {
        um[num] += 1;
    }
    priority_queue<pair<int, int>> pq;
    vector<int> res;
    for (auto iter = um.begin(); iter != um.end(); ++iter) {
        pq.push(make_pair(iter->second, iter->first));
    }
    while (k) {
        res.push_back(pq.top().second);
        pq.pop();
        k--;
    }
    return res;
}

/* 763. Partition Labels */
vector<int> partitionLabels(string S) {
    int len = S.length();
    vector<int> res;
    vector<int> lastposition(26, 0);
    for (int i = 0; i < len; ++i)
        lastposition[S[i] - 'a'] = i;

    int start = 0;
    int end = lastposition[S[start] - 'a'];
    for (int i = 0; i < len; ++i) {
        if (end == i) {
            res.push_back(end - start + 1);
            if (end + 1 < len) {
                start = end + 1;
                end = lastposition[S[start] - 'a'];
            }
        }
        end = max(lastposition[S[i] - 'a'], end);
    }
    return res;
}

/* 1094. Car Pooling */
bool carPooling(vector<vector<int>>& trips, int capacity) {
    vector<int> change(1001, 0);
    for (auto trip : trips) {
        change[trip[1]] += trip[0];
        change[trip[2]] -= trip[0];
    }
    int used = 0;
    for (auto c : change) {
        used += c;
        if (used > capacity)
            return false;
    }
    return true;
}

/* 621. Task Scheduler */
int leastInterval(vector<char>& tasks, int n) {
    unordered_map<int, int> m;
    int count = 0;
    int size = tasks.size();
    for (auto task : tasks) {
        m[task - 'A'] += 1;
        count = max(count, m[task - 'A']);
    }

    int res = (count - 1) * (n + 1);
    for (auto item : m) {
        if (item.second == count)
            res += 1;
    }
    return max(res, size);
}


/* 406. Queue Reconstruction by Height */
static int comp406(const vector<int> a, const vector<int> b) {
    return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0];
}

vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    int size = people.size();
    sort(people.begin(), people.end(), comp406);
    for (int i = size - 1; i >= 0; --i) {
        auto tmp = people[i];
        int count = 0;
        if (tmp[1] == 0)
            continue;
        for (int j = i + 1; j < size; ++j) {
            if (people[j][0] >= tmp[0])
                count += 1;
            if (count == tmp[1]) {
                people[j - 1] = people[j];
                people[j] = tmp;
                break;
            }
            people[j - 1] = people[j];
        }
    }
    return people;
}