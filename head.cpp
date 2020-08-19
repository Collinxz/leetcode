#ifndef life_is_short

// include and using
#include"stc++.h"
using namespace std;
using i64 = int64_t; using u64 = uint64_t;
using i32 = int32_t; using u32 = uint32_t;

// global variable
namespace {
    auto const pi = acos(-1);
    auto const tau = 2 * pi;
    auto const inf = 0x3f3f3f3f;
    i64 mod = 0;

#ifndef ONLINE_JUDGE
    auto const input_style = "\033[34;1m"; // 蓝色加亮
    auto const print_style = "\033[m"; // 默认白色字
    auto const debug_style = "\033[32;1m"; // 绿色加亮
#endif

}

// define
namespace {

#define F(i, x, y) for (decltype(y) i = (x), _##i = (y); i != _##i; ++i)
#define FD(i, x, y) for (decltype(x) i = (x), _##i = (y); i != _##i; --i)
#define Fcs() int T = 0; cin >> T; for (int cs = 0; cs < T and cout << "case #" << cs << ":\n"; cs++)
#define Ft(x) int T##x = 0; cin >> T##x; while (T##x--)
#define BE(v) begin(v), end(v)

#ifndef ONLINE_JUDGE
#define dbg(x) cout << debug_style << #x << ": " << x << "\n" << input_style
#else
#define dbg(x)
#endif

}

// function
namespace {
    // 杂项
    namespace {
        auto CCXXXI() {
#ifdef ONLINE_JUDGE
            ios::sync_with_stdio(false); cin.tie(nullptr);
#else
            cout << input_style;
#endif
        }

        // cout << vector
        template<typename E>
        auto& operator<<(ostream& o, vector<E>& v) {
            copy(begin(v), end(v), ostream_iterator<E>(o, " "));
            return o;
        }

        // py风格print单参数特化
        template<typename T>
        auto print(T a) {
#ifndef ONLINE_JUDGE
            cout << print_style;
#endif // !ONLINE_JUDGE
            cout << a << "\n";
#ifndef ONLINE_JUDGE
            cout << input_style;
#endif // !ONLINE_JUDGE
        }

        // py风格print，多参数，空格分隔，尾随换行
        template<typename T, typename... Targs>
        auto print(T a, Targs... args) {
#ifndef ONLINE_JUDGE
            cout << print_style;
#endif // !ONLINE_JUDGE
            cout << a << " ";
            print(args...);
        }

        // int快速乘
        auto qmul(i64 a, i64 b, i64 m) {
            auto t = a * b - i64((long double)a * b / m) * m;
            return t < 0 ? t + m : t;
        }

        // int快速幂
        auto qpow(i64 a, i64 b, i64 m = 0) {
            i64 r = 1;
            if (m) {
                for (a %= m; b; b >>= 1, a = qmul(a, a, m)) {
                    if (b & 1) { r = qmul(r, a, m); }
                }
            }
            else {
                for (; b; b >>= 1, a *= a) { if (b & 1) { r *= a; } }
            }
            return r;
        }

        // qpow质数m特化
        auto qpow_(i64 a, i64 b, i64 m = mod) {
            return qpow(a, b % (m - 1), m);
        }

        // hash语法简化
        template<typename T>
        auto hs(T a, i64 m = mod) {
            auto h = hash<T>()(a);
            if (m) { h %= m; }
            return h;
        }
    }

    // 逆元
    namespace inv {
        vector<i64>inv;

        auto init(int n, i64 p = mod) {
            inv.resize(n); inv[1] = 1;
            F(i, 2, n) { inv[i] = (p - p / i) * inv[p % i] % p; }
        }
    }

    // 阶乘及其逆元
    namespace fac_inv {
        vector<i64>fac, inv;

        auto init(int n, i64 p = mod) {
            fac.resize(n); inv.resize(n); fac[0] = 1;
            F(i, 1, n) { fac[i] = i * fac[i - 1] % p; }
            inv[n - 1] = qpow_(fac[n - 1], p - 2, p);
            FD(i, n - 2, -1) { inv[i] = (i64(i) + 1) * inv[i + 1] % p; }
        }
    }

    // 组合数
    namespace comb {
        vector<vector<i64>>c;

        // 直接预处理
        auto init(int n, i64 m = mod) {
            c.resize(n); for (auto& v : c) { v.resize(n); }
            F(i, 1, n) {
                c[i][0] = c[i][i] = 1;
                F(j, 1, i) { c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % m; }
            }
        }

        // 数较小，模较大时使用，需fac_inv::init()
        auto c1(int n, int m) {
            return n < m ? 0 :
                fac_inv::fac[n] * fac_inv::inv[m] % mod * fac_inv::inv[n - m] % mod;
        }

        // 模较小，数较大时使用，利用Lucas定理，需fac_inv::init(mod)
        auto c2(i64 n, i64 m)->i64 {
            return m ? c1(int(n % mod), int(m % mod)) * c2(n / mod, m / mod) % mod : 1;
        }
    }

    // 质数
    namespace prime {
        vector<int> phi, pri;

        // 欧拉筛法，O(n)
        auto init(int n) {
            phi.resize(n); pri.reserve(n / int(log(n)));
            vector<bool>vis(n);
            phi[1] = 1;
            F(i, 2, n) {
                if (not vis[i]) {
                    phi[i] = i - 1;
                    pri.push_back(i);
                }
                F(j, 0, pri.size()) {
                    if (i64(i) * pri[j] >= n) { break; }
                    vis[i * pri[j]] = true;
                    if (i % pri[j]) { phi[i * pri[j]] = phi[i] * (pri[j] - 1); }
                    else { phi[i * pri[j]] = phi[i] * pri[j]; break; }
                }
            }
        }

        // check辅助函数
        auto check_(i64 a, i64 n) {
            if (n == 2 or a >= n) { return true; }
            if (n == 1 or !(n & 1)) { return false; }
            auto d = n - 1;
            while (!(d & 1)) { d >>= 1; }
            auto t = qpow(a, d, n);
            while (d != n - 1 and t != 1 and t != n - 1) {
                t = qmul(t, t, n);
                d <<= 1;
            }
            return t == n - 1 or d & 1;
        }

        // 直接检查
        auto check(i64 n) {
            if (n <= 1) { return false; }
            for (auto k : { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 }) {
                if (!check_(k, n)) { return false; }
            }
            return true;
        }
    }
}

// data structure
namespace {
    // 并查集
    struct Dsu {
        vector<size_t>fa, size;

        Dsu(size_t n) {
            fa.resize(n); iota(BE(fa), 0);
            size.resize(n, 1);
        }

        auto find(size_t x)->size_t {
            return fa[x] == x ? x : (fa[x] = find(fa[x]));
        }

        auto unite(size_t x, size_t y) {
            x = find(x); y = find(y);
            if (x == y)return;
            if (size[x] > size[y])swap(x, y);
            fa[x] = y; size[y] += size[x];
        }

        auto same(size_t x, size_t y) {
            return find(x) == find(y);
        }

        auto size_of(size_t x) {
            return size[find(x)];
        }
    };

    // 并查集，带删除操作
    struct Dsu_ {
        vector<size_t>fa, size;

        Dsu_(size_t n) {
            fa.resize(n + n); F(i, 0, n)fa[i] = fa[i + n] = i + n;
            size.resize(n + n, 1);
        }

        auto find(size_t x)->size_t {
            return fa[x] == x ? x : (fa[x] = find(fa[x]));
        }

        auto unite(size_t x, size_t y) {
            x = find(x); y = find(y);
            if (x == y)return;
            if (size[x] > size[y])swap(x, y);
            fa[x] = y; size[y] += size[x];
        }

        auto same(size_t x, size_t y) {
            return find(x) == find(y);
        }

        auto size_of(size_t x) {
            return size[find(x)];
        }

        auto erase(size_t x) {
            fa[x] = x;
        }
    };
}

// nonsense
namespace rubbish {
    // use python
    class BigInt {};
}

#endif
////////////////////////////////////////////////////////////////
