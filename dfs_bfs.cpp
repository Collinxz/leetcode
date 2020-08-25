#include "stc++.h"

using namespace std;

/* 394. Decode String */
string decodeString(string s)
{
    stack<int> nums;
    stack<string> strs;
    string res = "", str = "";
    char ch;
    int i = 0;
    while (i < s.length())
    {
        ch = s[i];
        if (isalpha(ch))
        {
            str += ch;
        }
        else if (isdigit(ch))
        {
            if (nums.empty())
            {
                while (!strs.empty())
                {
                    res += strs.top();
                    strs.pop();
                }
                res += str;
            }
            else
            {
                strs.push(str);
            }
            int num = ch - '0';
            while (isdigit(s[i + 1]))
            {
                i += 1;
                num = num * 10 + s[i] - '0';
            }
            nums.push(num);
            str = "";
        }
        else if (ch == ']')
        {
            string tmp = "";
            int repn = nums.top();
            string reps = str;
            while (strs.top() != "[")
            {
                reps = strs.top() + reps;
                strs.pop();
            }
            while (repn)
            {
                tmp += reps;
                repn--;
            }
            nums.pop();
            strs.pop();
            strs.push(tmp);
            str = "";
        }
        else
        {
            string tmp = "";
            tmp += ch;
            strs.push(tmp);
        }
        i++;
    }
    if (!strs.empty())
    {
        res = res + strs.top();
        strs.pop();
    }
    res += str;
    return res;
}

/* 542. 01 Matrix */
bool isVisit(int i, int j, int m, int n)
{
    if (i == m || j == n || i < 0 || j < 0)
        return false;
    return true;
}
vector<vector<int>> updateMatrix(vector<vector<int>> &matrix)
{
    queue<pair<int, int>> bfs;
    int m = matrix.size();
    if (m == 0)
        return matrix;
    int n = matrix[0].size();
    vector<vector<int>> res(m, vector<int>(n, -1));
    vector<vector<int>> moves{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (matrix[i][j] == 0)
            {
                res[i][j] = 0;
                bfs.push({i, j});
            }
        }
    }
    while (!bfs.empty())
    {
        pair<int, int> curr = bfs.front();
        for (auto move : moves)
        {
            int p = curr.first + move[0];
            int q = curr.second + move[1];
            if (isVisit(p, q, m, n) && res[p][q] == -1)
            {
                res[p][q] = res[curr.first][curr.second] + 1;
                bfs.push({p, q});
            }
        }
        bfs.pop();
    }
    return res;
}

/* 752. Open the Lock */
vector<string> nbrStrs(string key)
{
    vector<string> res;
    for (int i = 0; i < 4; i++)
    {
        string tmp = key;
        tmp[i] = (key[i] - '0' + 1) % 10 + '0';
        res.push_back(tmp);
        tmp[i] = (key[i] - '0' - 1 + 10) % 10 + '0';
        res.push_back(tmp);
    }
    return res;
}
int openLock(vector<string> &deadends, string target)
{
    map<string, int> dist;
    for (auto deadend : deadends)
        dist[deadend] = -1;
    string st = "0000";
    if (dist[st] == -1)
        return -1;
    queue<string> qstr;
    int t = 0;
    dist[st] = t;
    qstr.push(st);
    while (!qstr.empty())
    {
        string prev = qstr.front();
        t = dist[prev] + 1;
        qstr.pop();
        vector<string> nstrs = nbrStrs(prev);
        for (string nstr : nstrs)
        {
            if (dist.find(nstr) == dist.end())
            {
                dist[nstr] = t;
                qstr.push(nstr);
            }
            if (nstr == target)
                return dist[nstr];
        }
    }
    return -1;
}

/* 886. Possible Bipartition */
bool possibleBipartition(int N, vector<vector<int>> &dislikes)
{
    vector<vector<int>> edges(N + 1);
    vector<int> colors(N + 1, 0);
    vector<int> isVisit(N + 1, 0);
    for (auto dislike : dislikes)
    {
        edges[dislike[0]].push_back(dislike[1]);
        edges[dislike[1]].push_back(dislike[0]);
    }
    queue<int> bfs;
    for (int i = 1; i <= N; ++i)
    {
        if (colors[i] == 0)
        {
            colors[i] = 1;
            bfs.push(i);
        }
        else
            continue;
        while (!bfs.empty())
        {
            int t = bfs.front();
            isVisit[t] = 1;
            bfs.pop();
            for (int nex : edges[t])
            {
                if (isVisit[nex])
                    continue;
                if (colors[nex] == colors[t])
                {
                    return false;
                }
                if (colors[nex] == 0)
                {
                    colors[nex] = colors[t] * -1;
                }
                bfs.push(nex);
            }
        }
    }
    return true;
}