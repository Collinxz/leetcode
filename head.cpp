#include "stc++.h"

using namespace std;

const int mod = 1000000007;

/* Inverse element */
long long quickpow(long long a, long long b)
{
    if (b < 0)
        return 0;
    long long ret = 1;
    a %= mod;
    while (b)
    {
        if (b & 1)
            ret = (ret * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }
    return ret;
}

long long inv(long long a)
{
    return quickpow(a, mod - 2);
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
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
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

int main()
{
    long long a = 98765432112;
    cout << inv(a) << endl;
    return 0;
}