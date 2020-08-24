#include "stc++.h"

using namespace std;

/* Check If a String Contains All Binary Codes of Size K */
bool hasAllCodes(string s, int k)
{
    bitset<1 << 22> bs;
    if (s.length() <= k)
        return false;
    int num = 0;
    for (int i = 0; i < s.length(); ++i)
    {
        if (i >= k)
            num = num & ((1 << k - 1) - 1);
        num <<= 1;
        num += s[i] - '0';
        if (i >= k - 1)
            bs.set(num);
    }
    for (int i = 0; i < 1 << k; ++i)
    {
        if (bs[i] != 1)
            return false;
    }
    return true;
}