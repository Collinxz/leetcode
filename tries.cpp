#include "stc++.h"

using namespace std;

struct node
{
    int val;
    int keyCount = 0;
    vector<struct node *> keys;
    node()
    {
        val = 0;
    }
    node(const int keyNum)
    {
        val = 0;
        keyCount = keyNum;
        for (int i = 0; i < keyCount; ++i)
            keys.push_back(NULL);
    }
};
struct node *head = new node(2);

void insertTrie(int num)
{
    struct node *ptr = head;
    int i = 31;
    while (i >= 0)
    {
        bool t = (num & (1 << i));
        if (!ptr->keys[t])
            ptr->keys[t] = new node(2);
        ptr = ptr->keys[t];
        i--;
    }
    ptr->val = num;
}

int checkTrie(int num)
{
    struct node *ptr = head;
    int i = 31;
    while (i >= 0)
    {
        bool t = (num & (1 << i));
        if (ptr->keys[1 - t])
            ptr = ptr->keys[1 - t];
        else if (ptr->keys[t])
            ptr = ptr->keys[t];
        i--;
    }
    return ptr->val;
}

int findMaximumXOR(vector<int> &nums)
{
    if (nums.size() < 2)
        return 0;
    int res = 0;
    for (int num : nums)
    {
        insertTrie(num);
        res = max(res, num ^ checkTrie(num));
    }
    return res;
}