#include "stc++.h"

using namespace std;

#define MAXN 10010
#define INF 0x3f3f3f3f
#define MOD 10000007
#define LL long long
#define in(a) a=read()
#define REP(i,k,n) for(long long i=k;i<=n;i++)
#define DREP(i,k,n) for(long long i=k;i>=n;i--)
#define cl(a) memset(a,0,sizeof(a))

/* Dijkstra */
bool vis[MAXN];
int pre[MAXN];
vector<vector<int>> cost(MAXN, vector<int>(MAXN, INF));
// 记录beg到图里每个点的距离
int lowcost[MAXN];

void Dijkstra(int n, int beg){
    /* init */
    for(int i = 1; i <= n; ++i){
        lowcost[i] = INF;
        vis[i] = false;
        pre[i] = -1;
    }
    lowcost[beg] = 0;

    for(int j = 1; j <= n; ++j){
        int k = -1;
        int Min = INF;
        for(int i = 1; i <= n; ++i){
            if(!vis[i] && lowcost[i] < Min){
                Min = lowcost[i];
                k = i;
            }
        }
        if(k == -1) break;
        vis[k] = true;
        for(int i = 1; i <= n; ++i){
            if(!vis[i] && lowcost[k] + cost[k][i] < lowcost[i]){
                lowcost[i] = lowcost[k] + cost[k][i];
                pre[i] = k;
            }
        }

        for(int i = 1; i <= n; ++i){
            cout << lowcost[i] << " ";
        }
        cout << endl;
    }
}


/* bellman_ford */
vector<int> dist(MAXN, 0);

struct Edge{
    int u, v;
    int cost;
    Edge(int _u = 0, int _v = 0, int _cost = 0):u(_u),v(_v),cost(_cost){}
};

vector<Edge> E;

bool bellMan_ford(int start, int n){
    for(int i = 1; i <= n; ++i)
        dist[i] = INF;
    dist[start] = 0;
    for(int i = 0; i < n; ++i){
        bool flag = false;
        for(int j = 0; j < E.size(); ++j){
            int u = E[j].u;
            int v = E[j].v;
            int cost = E[j].cost;
            if(dist[v] > dist[u] + cost){
                dist[v] = dist[u] + cost;
                flag = true;
            }
        }
        if(!flag) return true; //没有负环回路
    }
    for(int j = 0; j < E.size(); ++j){
        if(dist[E[j].v] > dist[E[j].u] + E[j].cost)
            return false; //有负环回路
    }

    return true;
}

/* prim */
bool visPrim[MAXN];
int lowc[MAXN];
vector<vector<int>> costPrim(MAXN, vector<int>(MAXN, INF));

int Prim(int n){
    int ans = 0;
    memset(visPrim, false, sizeof(vis));
    vis[0] = true;
    for(int i = 1; i < n; ++i)
        lowc[i] = cost[0][i];
    for(int i = 1; i < n; ++i){
        int minc = INF;
        int p = -1;
        for(int j = 0; j < n; ++j){
            if(!vis[j] && minc > lowc[j]){
                minc = lowc[j];
                p = j;
            }
        }
        if(minc == INF) return -1; //原图不连通
        ans += minc;
        vis[p] = true;
        for(int j = 0; j < n; ++j){
            if(!vis[j] && lowc[j] > cost[p][j])
                lowc[j] = cost[p][j];
        }
    }
    return ans;
}

/* Inverse element */
long long quickpow(long long a, long long b)
{
    if (b < 0)
        return 0;
    long long ret = 1;
    a %= MOD;
    while (b)
    {
        if (b & 1)
            ret = (ret * a) % MOD;
        b >>= 1;
        a = (a * a) % MOD;
    }
    return ret;
}

long long inv(long long a)
{
    return quickpow(a, MOD - 2);
}

/* c(m, n) */

long long c[101][101];
void init()
{
    c[0][0] = 1;
    for (int i = 1; i <= 100; i++)
    {
        c[i][0] = 1;
        for (int j = 1; j <= 100; j++)
        {
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD;
        }
    }
}

int Search(vector<int> nums, int low, int high, int num)
{
    int mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (num >= nums[mid])
            low = mid + 1;
        else
            high = mid - 1;
    }
    return low;
}

inline long long read(){
    long long x=0,f=1;char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(;isdigit(ch);ch=getchar()) x=x*10+ch-'0';
    return x*f;
}
inline void out(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) out(x/10);
    putchar(x%10+'0');
}

/* Segment tree */
long long n,m,p;
long long input[MAXN];
struct node{
    long long l,r;
    long long sum,mlz,plz;
}tree[4*MAXN];
inline void build(long long i,long long l,long long r){
    tree[i].l=l;
    tree[i].r=r;
    tree[i].mlz=1;
    if(l==r){
        tree[i].sum=input[l]%p;
        return ;
    }
    long long mid=(l+r)>>1;
    build(i<<1,l,mid);
    build(i<<1|1,mid+1,r);
    tree[i].sum=(tree[i<<1].sum+tree[i<<1|1].sum)%p;
    return ;
}
inline void pushdown(long long i){
    long long k1=tree[i].mlz,k2=tree[i].plz;
    tree[i<<1].sum=(tree[i<<1].sum*k1+k2*(tree[i<<1].r-tree[i<<1].l+1))%p;
    tree[i<<1|1].sum=(tree[i<<1|1].sum*k1+k2*(tree[i<<1|1].r-tree[i<<1|1].l+1))%p;
    tree[i<<1].mlz=(tree[i<<1].mlz*k1)%p;
    tree[i<<1|1].mlz=(tree[i<<1|1].mlz*k1)%p;
    tree[i<<1].plz=(tree[i<<1].plz*k1+k2)%p;
    tree[i<<1|1].plz=(tree[i<<1|1].plz*k1+k2)%p;
    tree[i].plz=0;
    tree[i].mlz=1;
    return ;
}
inline void mul(long long i,long long l,long long r,long long k){
    if(tree[i].r<l || tree[i].l>r)  return ;
    if(tree[i].l>=l && tree[i].r<=r){
        tree[i].sum=(tree[i].sum*k)%p;
        tree[i].mlz=(tree[i].mlz*k)%p;
        tree[i].plz=(tree[i].plz*k)%p;
        return ;
    }
    pushdown(i);
    if(tree[i<<1].r>=l)  mul(i<<1,l,r,k);
    if(tree[i<<1|1].l<=r)  mul(i<<1|1,l,r,k);
    tree[i].sum=(tree[i<<1].sum+tree[i<<1|1].sum)%p;
    return ;
}
inline void add(long long i,long long l,long long r,long long k){
    if(tree[i].r<l || tree[i].l>r)  return ;
    if(tree[i].l>=l && tree[i].r<=r){
        tree[i].sum+=((tree[i].r-tree[i].l+1)*k)%p;
        tree[i].plz=(tree[i].plz+k)%p;
        return ;
    }
    pushdown(i);
    if(tree[i<<1].r>=l)  add(i<<1,l,r,k);
    if(tree[i<<1|1].l<=r)  add(i<<1|1,l,r,k);
    tree[i].sum=(tree[i<<1].sum+tree[i<<1|1].sum)%p;
    return ;
}
inline long long search(long long i,long long l,long long r){
    if(tree[i].r<l || tree[i].l>r)  return 0;
    if(tree[i].l>=l && tree[i].r<=r)
        return tree[i].sum;
    pushdown(i);
    long long sum=0;
    if(tree[i<<1].r>=l)  sum+=search(i<<1,l,r)%p;
    if(tree[i<<1|1].l<=r)  sum+=search(i<<1|1,l,r)%p;
    return sum%p;
}

int main()
{
    cost[1][2] = 1;
    cost[2][3] = 4;
    cost[2][5] = 2;
    cost[3][4] = 3;
    cost[4][5] = 2;
    cost[5][3] = 1;
    Dijkstra(5, 5);
    for(int i = 1; i <= 5; ++i){
        cout << lowcost[i] << endl;
    }
    return 0;
}