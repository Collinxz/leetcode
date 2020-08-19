#include "stc++.h"
#define MAXN 100001
typedef long long ll;

using namespace std;

ll fa[MAXN];
ll ds_rank[MAXN];

void init(int size) {
	for (auto i = 1; i <= size; ++i) {
		fa[i] = i;
		ds_rank[i] = 1;
	}
}

ll find(ll x) {
	return fa[x] ? fa[x] == x : (fa[x] = find(fa[x]));
}

inline void merge(ll i, ll j) {
	/* i and j are child nodes */
	ll fa_i = find(i);
	ll fa_j = find(j);

	if (ds_rank[fa_i] >= ds_rank[fa_j]) 
		fa[fa_j] = fa_i;
	else
		fa[fa_i] = fa_j;

	if (ds_rank[fa_i] == ds_rank[fa_j]) {
		ds_rank[fa_i] ++;
	}
}

/* 684. Redundant Connection */
map<int, int> faRC;

int findFa(int a) {
    if (faRC.find(a) == faRC.end())
        return a;
    return findFa(fa[a]);
}

bool setFa(int a, int b) {
    int faA = findFa(a);
    int faB = findFa(b);
    if (faA == faB) {
        return false;
    }
    faRC[faB] = faA;
    return true;
}

vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    vector<int> res;
    for (auto edge : edges) {
        // cout << edge[0] << ":" << edge[1] << endl;
        if (!setFa(edge[0], edge[1])) {
            return edge;
        }
    }
    return res;
}

/* 200. Number of Islands */
vector<vector<pair<int, int>>> faNI;

void init(int n, int m) {
    for (int i = 0; i < n; i++) {
        vector<pair<int, int>> tmp;
        for (int j = 0; j < m; j++) {
            tmp.push_back({ i,j });
        }
        faNI.push_back(tmp);
    }
}

pair<int, int> findfa(int i, int j) {
    if (faNI[i][j].first == i && faNI[i][j].second == j)
        return { i, j };

    return faNI[i][j] = findfa(faNI[i][j].first, faNI[i][j].second);
}

void setfa(int i, int j, int p, int q) {
    pair<int, int> faNIA = findfa(i, j);
    pair<int, int> faNIB = findfa(p, q);
    faNI[faNIA.first][faNIA.second] = faNIB;
}

int numIslands(vector<vector<char>>& grid) {
    int n = grid.size();
    if (!n)
        return 0;
    int m = grid[0].size();
    init(n, m);
    int res = n * m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '1') {
                if (i == 0 && j == 0) continue;
                else if (j == 0 && i != 0) {
                    if (grid[i - 1][j] == '1') {
                        res--;
                        setfa(i, j, i - 1, j);
                    }
                }
                else if (i == 0 && j != 0) {
                    if (grid[i][j - 1] == '1') {
                        res--;
                        setfa(i, j, i, j - 1);
                    }
                }
                else {
                    if (grid[i][j - 1] == '1') {
                        res--;
                        setfa(i, j, i, j - 1);
                    }
                    if (grid[i - 1][j] == '1') {
                        if (findfa(i, j) != findfa(i - 1, j)) {
                            res--;
                        }
                        setfa(i, j, i - 1, j);
                    }
                }
            }
            else
                res--;
            // cout << res << endl;
        }
    }
    return res;
}