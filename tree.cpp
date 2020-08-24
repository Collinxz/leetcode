#include "stc++.h"

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

/* 617. Merge Two Binary Trees */
TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
    if (t1 && t2) {
        t1->val += t2->val;
        t1->left = mergeTrees(t1->left, t2->left);
        t1->right = mergeTrees(t1->right, t2->right);
        return t1;
    }
    else if (!t1 && t2) {
        return t2;
    }
    else if (t1 && !t2) {
        return t1;
    }
    else {
        return NULL;
    }
}

/* 104. Maximum Depth of Binary Tree */
int maxDepth(TreeNode* root) {
    if (!root)
        return 0;
    else
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}

/* 700. Search in a Binary Search Tree */
TreeNode* searchBST(TreeNode* root, int val) {
    if (!root)
        return NULL;
    TreeNode* left = new TreeNode(0);
    TreeNode* right = new TreeNode(0);
    if (root->val == val)
        return root;
    else {
        left = searchBST(root->left, val);
        right = searchBST(root->right, val);
        if (left)
            return left;
        if (right)
            return right;
    }
    return NULL;
}

/* 100. Same Tree */
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p and !q)
        return true;
    if (!p or !q)
        return false;
    if (p->val == q->val)
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    return false;
}

/* 102. Binary Tree Level Order Traversal */
void LOHelper(TreeNode* node, vector<vector<int>>& res, int i) {
    if (!node)
        return;
    if (res.size() < i) {
        vector<int> tmp;
        res.push_back(tmp);
    }
    res[i - 1].push_back(node->val);
    LOHelper(node->left, res, i + 1);
    LOHelper(node->right, res, i + 1);
}

vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res;
    LOHelper(root, res, 1);
    return res;
}


/* 108. Convert Sorted Array to Binary Search Tree */
TreeNode* SATBHelper(vector<int>& nums, int l, int r) {
    TreeNode* node = new TreeNode();
    if (l > r) {
        return NULL;
    }
    if (l == r) {
        node->val = nums[l];
        return node;
    }
    int m = l + (r - l) / 2;
    node->val = nums[m];
    node->left = SATBHelper(nums, l, m - 1);
    node->right = SATBHelper(nums, m + 1, r);
    return node;
}
TreeNode* sortedArrayToBST(vector<int>& nums) {
    return SATBHelper(nums, 0, nums.size() - 1);
}


/* 101. Symmetric Tree */
bool ISHelper(TreeNode* root1, TreeNode* root2) {
    if (!root1 and !root2)
        return true;
    if (!root1 or !root2)
        return false;
    if (root1->val != root2->val)
        return false;
    return ISHelper(root1->left, root2->right) && ISHelper(root1->right, root2->left);

}
bool isSymmetric(TreeNode* root) {
    return ISHelper(root, root);
}

/* 94. Binary Tree Inorder Traversal */
vector<int> inorderTraversal(TreeNode* root) {
    stack<TreeNode*> tmp;
    vector<int> res;
    TreeNode* node = root;
    tmp.push(node);
    TreeNode* tn = tmp.top();
    while (tn) {
        if (tn->left) {
            tmp.push(tn->left);
            tn->left = NULL;
            tn = tmp.top();
        }
        else if (tn->right) {
            res.push_back(tn->val);
            tmp.pop();
            tmp.push(tn->right);
            tn->right = NULL;
            tn = tmp.top();
        }
        else {
            res.push_back(tn->val);
            tmp.pop();
            if (!tmp.empty()) {
                tn = tmp.top();
            }
            else
                break;
        }
    }
    return res;
}

/* 114. Flatten Binary Tree to Linked List */
TreeNode* findRLeaf(TreeNode* node) {
    if (node->right)
        return findRLeaf(node->right);
    else
        return node;
}
void FHelper(TreeNode* root) {
    if (!root)
        return;
    if (root->left) {
        TreeNode* rleaf = findRLeaf(root->left);
        rleaf->right = root->right;
        root->right = root->left;
        root->left = NULL;
    }
    FHelper(root->right);
}
void flatten(TreeNode* root) {
    FHelper(root);
}

/* 230. Kth Smallest Element in a BST */
void findkthSmallest(TreeNode* root, int& t, int k, int& res) {
    if (!root)
        return;
    if (root->left) {
        findkthSmallest(root->left, t, k, res);
    }
    t++;
    if (t == k)
        res = root->val;
    if (root->right) {
        findkthSmallest(root->right, t, k, res);
    }
}
int kthSmallest(TreeNode* root, int k) {
    int res = 0;
    int t = 0;
    findkthSmallest(root, t, k, res);
    return res;
}

/* 98. Validate Binary Search Tree */
bool IVBHelper(TreeNode* root, long long left, long long right) {
    if (!root)
        return true;
    if (root->val < right && root->val > left)
        return IVBHelper(root->left, left, root->val) && IVBHelper(root->right, root->val, right);
    return false;
}
bool isValidBST(TreeNode* root) {
    if (!root)
        return true;
    long long min = INT64_MIN;
    long long max = INT64_MAX;
    return  IVBHelper(root->left, min, root->val) && IVBHelper(root->right, root->val, max);
}

/* 129. Sum Root to Leaf Numbers */
void SNHelper(TreeNode* root, int tmp, int& res) {
    if (!root->left && !root->right) {
        res += tmp + root->val;
        return;
    }
    if (root->left) {
        SNHelper(root->left, (tmp + root->val) * 10, res);
    }
    if (root->right) {
        SNHelper(root->right, (tmp + root->val) * 10, res);
    }

}
int sumNumbers(TreeNode* root) {
    int res = 0;
    if (!root)
        return res;
    SNHelper(root, 0, res);
    return res;
}

/* 979. Distribute Coins in Binary Tree */
int DCHelper(TreeNode* root, int& move) {
    if (!root)
        return 0;
    int left = DCHelper(root->left, move);
    int right = DCHelper(root->right, move);
    move += abs(left) + abs(right);
    return root->val + left + right - 1;
}
int distributeCoins(TreeNode* root) {
    int res = 0;
    DCHelper(root, res);
    return res;
}

/* 814. Binary Tree Pruning */
int PTHelper(TreeNode* root) {
    if (!root)
        return 0;
    int l = PTHelper(root->left);
    int r = PTHelper(root->right);
    if (l == 0)
        root->left = NULL;
    if (r == 0)
        root->right = NULL;
    return root->val + l + r;
}
TreeNode* pruneTree(TreeNode* root) {
    PTHelper(root);
    return root;
}

/* 543. Diameter of Binary Tree */
int DOBTHelper(TreeNode* root, int& res) {
    if (!root)
        return 0;
    int l = DOBTHelper(root->left, res);
    int r = DOBTHelper(root->right, res);
    res = max(l + r, res);
    return max(l, r) + 1;
}
int diameterOfBinaryTree(TreeNode* root) {
    int res = 0;
    DOBTHelper(root, res);
    return res;
}

/* Lowest Common Ancestor of a Binary Tree */
TreeNode* findLCA(TreeNode* node, TreeNode*p, TreeNode*q, bool& flag){
    if(!node)
        return NULL;
    TreeNode* l = findLCA(node->left, p, q, flag);
    TreeNode* r = findLCA(node->right, p, q, flag);
    if(flag){
        if(l)
            return l;
        else
            return r;
    }
    else{
        if(l && r){
            flag = true;
            return node;
        }
        else if(l || r){
            if(node->val == p->val || node->val == q->val)
                flag = true;
                return node;
        }
        else{
            if(node->val == p->val || node->val == q->val)
                return node;
            else
                return NULL;
        }
    }
    return NULL;
}
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    bool flag = false;
    return findLCA(root, p, q, flag);
}