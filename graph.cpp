#include "stc++.h"

using namespace std;

/* 997. Find the Town Judge */
int findJudge(int N, vector<vector<int>>& trust) {
    vector<pair<int, int>> tvec(N, make_pair(0, 0));
    for (auto t : trust) {
        int truster = t[0];
        int trusted = t[1];
        tvec[t[1] - 1].first += 1;
        tvec[t[0] - 1].second += 1;
    }
    int res = -1;
    for (int i = 0; i < N; ++i) {
        if (tvec[i].first == N - 1 && tvec[i].second == 0)
            res = i + 1;
    }
    return res;
}

/* 207. Course Schedule */
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> dg(numCourses);
    vector<int> needs(numCourses, 0);
    for (auto i : prerequisites) {
        dg[i[0]].push_back(i[1]);
        needs[i[1]] += 1;
    }
    vector<int> bfs;
    for (int i = 0; i < numCourses; ++i) {
        if (needs[i] == 0)
            bfs.push_back(i);
    }
    for (int i = 0; i < bfs.size(); ++i) {
        for (auto j : dg[bfs[i]]) {
            needs[j] -= 1;
            if (!needs[j])
                bfs.push_back(j);
        }
    }
    return bfs.size() == numCourses;
}

/* 997. Find the Town Judge */
int findJudge(int N, vector<vector<int>> trust) {
    vector<pair<int, int>> tvec(N, make_pair(0, 0));
    for (auto t : trust) {
        int truster = t[0];
        int trusted = t[1];
        tvec[t[1] - 1].first += 1;
        tvec[t[0] - 1].second += 1;
    }
    int res = -1;
    for (int i = 0; i < N; ++i) {
        if (tvec[i].first == N - 1 && tvec[i].second == 0)
            res = i + 1;
    }
    return res;
}

/* 841. Keys and Rooms */
bool canVisitAllRooms(vector<vector<int>>& rooms) {
    int n = rooms.size(), count = 0;
    vector<int> isopen(n, 0);
    queue<int> que;
    isopen[0] = 1;

    for (int i = 0; i < rooms[0].size(); ++i) {
        que.push(rooms[0][i]);
    }
    while (!que.empty()) {
        int t = que.front();
        if (!isopen[t]) {
            isopen[t] = true;
            count++;
            for (auto i : rooms[t]) {
                que.push(i);
            }
        }
        que.pop();
    }
    return count == (n - 1);
}

/* 785. Is Graph Bipartite? */
bool isBipartite(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> sets(n, -1);
    queue<int> que;
    for (int k = 0; k < n; ++k) {
        if (graph[k].size() == 0 || sets[k] != -1)
            continue;
        sets[k] = 0;
        que.push(k);
        while (!que.empty()) {
            int t = que.front();
            for (int i : graph[t]) {
                if (sets[i] == -1) {
                    sets[i] = 1 - sets[t];
                    que.push(i);
                }
                else {
                    if (sets[i] == sets[t])
                        return false;
                }
            }
            que.pop();
        }
    }
    return true;
}

/* 210. Course Schedule II */
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<int> res;
    vector<int> needs(numCourses, 0);
    queue<int> bfs;
    vector<vector<int>> CS(numCourses);
    for (int i = 0; i < prerequisites.size(); ++i) {
        needs[prerequisites[i][0]] ++;
        CS[prerequisites[i][1]].push_back(prerequisites[i][0]);
    }
    for (int i = 0; i < numCourses; ++i) {
        if (needs[i] == 0) {
            bfs.push(i);
            res.push_back(i);
        }
    }
    if (bfs.empty())
        return res;
    while (!bfs.empty()) {
        int t = bfs.front();
        for (auto p : CS[t]) {
            needs[p]--;
            if (needs[p] == 0) {
                bfs.push(p);
                res.push_back(p);
            }
        }
        bfs.pop();
    }
    vector<int> tmp;
    return res.size() == numCourses ? res : tmp;
}

/* 743. Network Delay Time */
int networkDelayTime(vector<vector<int>>& times, int N, int K) {
    vector<int> dists(N, INT32_MAX);
    dists[K - 1] = 0;
    for (int i = 0; i <= N; i++) {
        for (auto time : times) {
            if (dists[time[0] - 1] != INT32_MAX) {
                dists[time[1] - 1] = min(dists[time[1] - 1], dists[time[0] - 1] + time[2]);
            }
        }
    }
    int res = 0;
    for (auto dist : dists) {
        if (dist == INT32_MAX)
            return -1;
        res = max(res, dist);
    }
    return res;
}

/* 1361. Validate Binary Tree Nodes */
bool validateBinaryTreeNodes(int n, vector<int>& leftChild, vector<int>& rightChild) {
    vector<int> isVisit(n, 1);
    vector<int> isHead(n, 1);
    queue<int> bfs;

    int start = -1;
    for (int i = 0; i < n; ++i) {
        if (leftChild[i] != -1)
            isHead[leftChild[i]] = 0;
        if (rightChild[i] != -1)
            isHead[rightChild[i]] = 0;
    }

    for (int i = 0; i < n; ++i) {
        if (isHead[i] != 0) {
            if (start == -1)
                start = i;
            else
                return false;
        }
    }
    if (start == -1)
        return false;
    isVisit[start] = 0;
    bfs.push(start);

    while (!bfs.empty()) {
        int curr = bfs.front();
        bfs.pop();
        if (leftChild[curr] != -1) {
            if (isVisit[leftChild[curr]]) {
                bfs.push(leftChild[curr]);
                isVisit[leftChild[curr]] = 0;
            }
            else
                return false;
        }
        if (rightChild[curr] != -1) {
            if (isVisit[rightChild[curr]]) {
                bfs.push(rightChild[curr]);
                isVisit[rightChild[curr]] = 0;
            }
            else
                return false;
        }
    }
    for (auto v : isVisit) {
        if (v)
            return false;
    }
    return true;
}