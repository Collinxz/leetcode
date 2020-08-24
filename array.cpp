#include "stc++.h"

using namespace std;

/* 42. Trapping Rain Water */
int trap(vector<int> &height)
{
    int lmax = 0, rmax = 0;
    vector<int> l, r;
    for (int i = 0; i < height.size(); ++i)
    {
        if (height[i] > lmax)
            lmax = height[i];
        l.push_back(lmax);
        if (height[height.size() - i - 1] > rmax)
            rmax = height[height.size() - i - 1];
        r.push_back(rmax);
    }
    int res = 0;
    for (int i = 0; i < height.size(); ++i)
    {
        res += min(l[i], r[height.size() - i - 1]) - height[i];
    }
    return res;
}