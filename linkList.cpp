#include "stc++.h"

using namespace std;

/*********************/
/* Linklist function */
/*********************/

struct ListNode{
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}   
};

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};


class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};

ListNode* createRandomList(int num) {
    default_random_engine e;
    uniform_real_distribution<double> u(1, 100);
    e.seed(0);

    int head_val = u(e);
    ListNode* head = new ListNode(head_val);
    ListNode* tmp = head;
    for (int i = 1; i < num; ++i) {
        ListNode* newNode = new ListNode(lround(u(e)));
        tmp->next = newNode;
        tmp = tmp->next;
    }
    return head;
}

ListNode* createSortList(int start, int end) {
    ListNode* head = new ListNode(start);
    ListNode* tmp = head;
    for (int i = start + 1; i <= end; ++i) {
        ListNode* newNode = new ListNode(i);
        tmp->next = newNode;
        tmp = tmp->next;
    }
    return head;
}

void printList(ListNode* head) {
    while (head->next) {
        cout << head->val << "->";
        head = head->next;
    }
    cout << head->val << endl;
}

/* 328. Odd Even Linked List */
ListNode* oddEvenList(ListNode* head) {
    ListNode* odd = head;
    if (!head)
        return head;
    ListNode* even = head->next;
    if (!even)
        return head;
    ListNode* nxt = head->next;
    ListNode* nnxt = head->next->next;
    if (!nnxt)
        return head;
    int flag = 0;
    while (nnxt) {
        head->next = nnxt;
        head = nxt;
        nxt = nnxt;
        nnxt = nnxt->next;
        flag = flag ^ 1;
    }
    if (flag) {
        head->next = NULL;
        nxt->next = even;
    }
    else
        head->next = even;
    return odd;
}

/* 21. Merge Two Sorted Lists */
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if (!l1)
        return l2;
    if (!l2)
        return l1;
    ListNode* head = new ListNode(0);
    ListNode* tmp = head;
    while (l1 && l2) {
        if (l1->val >= l2->val) {
            tmp->next = l2;
            l2 = l2->next;
        }
        else {
            tmp->next = l1;
            l1 = l1->next;
        }
        tmp = tmp->next;
    }
    if (l1)
        tmp->next = l1;
    if (l2)
        tmp->next = l2;
    return head->next;
}

/* 725. Split Linked List in Parts */
vector<ListNode*> splitListToParts(ListNode* root, int k) {
    vector<ListNode*> res;
    int length = 0;
    ListNode* tmp = root;
    while (tmp) {
        length += 1;
        tmp = tmp->next;
    }
    int len = length / k;
    int more = length % k;
    ListNode* nxt = root;
    int clock = 0, flag = 0;
    while (flag < k) {
        if (flag < more)
            clock = len + 1;
        else
            clock = len;
        for (int i = 0; i < clock - 1; i++) {
            nxt = nxt->next;
        }
        res.push_back(root);
        if (nxt) {
            root = nxt->next;
            nxt->next = NULL;
            nxt = root;
        }
        flag++;
    }
    return res;
}

/* 24. Swap Nodes in Pairs */
ListNode* swapPairs(ListNode* head) {
    ListNode* res = new ListNode(0);
    res->next = head;
    ListNode* curr = head;
    if (!head)
        return head;
    ListNode* prev = res;
    ListNode* nxt = head->next;
    if (!nxt)
        return head;
    ListNode* nnxt = nxt->next;

    while (true) {
        prev->next = nxt;
        nxt->next = curr;
        curr->next = nnxt;
        prev = curr;
        curr = nnxt;
        if (!curr || !curr->next)
            break;
        nxt = curr->next;
        nnxt = nxt->next;
    }

    return res->next;
}

/* 83. Remove Duplicates from Sorted List */
ListNode* deleteDuplicates1(ListNode* head) {
    if (!head)
        return head;
    ListNode* curr = head;
    ListNode* nxt = head->next;
    if (!nxt)
        return head;
    ListNode* nnxt = nxt->next;
    while (nxt) {
        if (curr->val == nxt->val) {
            curr->next = nnxt;
            nxt = nnxt;
        }
        else {
            curr = nxt;
            nxt = nnxt;
        }
        if (!nxt)
            break;
        nnxt = nxt->next;
    }
    return head;
}

/* 82. Remove Duplicates from Sorted List II */
ListNode* deleteDuplicates2(ListNode* head) {
    if (!head || !head->next)
        return head;

    ListNode* res = new ListNode(0);
    ListNode* wait = res;
    res->next = head;
    ListNode* curr = head;
    ListNode* nxt = head->next;

    while (nxt) {
        if (curr->val != nxt->val) {
            if (wait->next == curr)
                wait = curr;
            else
                wait->next = nxt;
        }
        curr = nxt;
        nxt = curr->next;
    }
    if (wait->next != curr)
        wait->next = nxt;
    return res->next;
}

/* 1171. Remove Zero Sum Consecutive Nodes from Linked List */

/* 86. Partition List */
ListNode* partition(ListNode* head, int x) {
    ListNode* lower = new ListNode(0);
    ListNode* lw = lower;
    ListNode* larger = new ListNode(0);
    ListNode* lg = larger;
    while (head) {
        if (head->val >= x) {
            lg->next = head;
            lg = lg->next;
        }
        else {
            lw->next = head;
            lw = lw->next;
        }
        head = head->next;
    }
    lg->next = NULL;
    lw->next = larger->next;
    return lower->next;
}

/* 141. Linked List Cycle */
bool hasCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (true) {
        if (!slow)
            return false;
        slow = slow->next;
        if (!fast || !fast->next)
            return false;
        fast = fast->next->next;
        if (slow == fast)
            return true;
    }
}

/* 234. Palindrome Linked List */
bool isPalindrome(ListNode* head) {
    return true;
}

/* 203. Remove Linked List Elements */
ListNode* removeElements(ListNode* head, int val) {
    ListNode* res = new ListNode(0);
    res->next = head;
    ListNode* curr = head;
    ListNode* prev = res;
    if (!curr) 
        return head;
    ListNode* nxt = head->next;

    while (curr) {
        if (curr->val == val)
            prev->next = nxt;
        else 
            prev = curr;
        curr = nxt;
        if (!curr)
            break;
        nxt = curr->next;
    }
    return res->next;
}

/* 61. Rotate List */
ListNode* rotateRight(ListNode* head, int k) {
    int length = 1;
    if (!head || !head->next || !k)
        return head;
    ListNode* nend = head;
    ListNode* nhead = nend->next;

    ListNode* end = head;
    while (end->next) {
        end = end->next;
        length++;
    }
    
    int num = k % length;
    if (!num)
        return head;
    int carry = 1;
    while (carry + num != length) {
        nend = nend->next;
        nhead = nhead->next;
        carry++;
    }
    end->next = head;
    nend->next = NULL;
    return nhead;
}

/* 19. Remove Nth Node From End of List */
ListNode* removeNthFromEnd(ListNode* head, int n) {
    if (!n || !head)
        return head;
    ListNode* res = new ListNode(0);
    res->next = head;
    ListNode* fast = head;
    ListNode* slow = head;
    ListNode* prev = res;
    for (int i = 0; i < n; i++) {
        fast = fast->next;
    }
    while (fast) {
        fast = fast->next;
        slow = slow->next;
        prev = prev->next;
    }
    prev->next = slow->next;
    return res->next;
}

/* 92. Reverse Linked List II */
ListNode* reverseBetween(ListNode* head, int m, int n) {
    if (!head || m == n || !head->next)
        return head;
    ListNode* nhead = new ListNode(0);
    nhead->next = head;
    ListNode* rhead = nhead;
    ListNode* start = head;
    ListNode* prev = head;
    ListNode* curr = head->next;
    ListNode* end = curr->next;
    int t = 1;
    while (t < m) {
        rhead = rhead->next;
        start = start->next;
        prev = prev->next;
        curr = curr->next;
        if (!curr)
            return head;
        end = end->next;
        t++;
    }
    while (t < n) {
        curr->next = prev;
        prev = curr;
        curr = end;
        if (!curr)
            break;
        end = end->next;
        t++;
    }
    rhead->next = prev;
    start->next = curr;
    return nhead->next;
}

/* 148. Sort List */
ListNode* mergeSortList(ListNode* node) {
    if (!node)
        return node;
    if (node->next == NULL)
        return node;
    ListNode* mid = node;
    ListNode* end = node;
    ListNode* r = node;
    while (end) {
        end = end->next;
        if (!end or !end->next)
            break;
        end = end->next;
        mid = mid->next;
    }
    r = mid->next;
    mid->next = NULL;
    ListNode* left = mergeSortList(node), * right = mergeSortList(r);
    ListNode* nhead = new ListNode(0);
    ListNode* start = nhead;
    while (true) {
        if (!left) {
            start->next = right;
            break;
        }
        if (!right) {
            start->next = left;
            break;
        }
        if (left->val > right->val) {
            start->next = right;
            right = right->next;
        }
        else {
            start->next = left;
            left = left->next;
        }
        start = start->next;
    }
    return nhead->next;
}
ListNode* sortList(ListNode* head) {
    return mergeSortList(head);
}

/* 109. Convert Sorted List to Binary Search Tree */
TreeNode* sortedListToBST(ListNode* head) {
    TreeNode* node = new TreeNode(0);
    if (!head) {
        return NULL;
    }
    if (!head->next) {
        node->val = head->val;
        return node;
    }
    ListNode* mid = head;
    ListNode* end = head;
    while (end) {
        end = end->next;
        if (!end)
            break;
        end = end->next;
        if (!end or !end->next)
            break;
        mid = mid->next;
    }
    end = mid->next;
    mid->next = NULL;
    mid = end;
    end = end->next;
    mid->next = NULL;

    node->val = mid->val;
    node->left = sortedListToBST(head);
    node->right = sortedListToBST(end);
    return node;
}

/*********************/
/* Main function */
/*********************/

//int main()
//{
//    cout << "hello world!\n";
//    ListNode* newsortlist_1 = createSortList(1, 5);
//    printList(newsortlist_1);
//    ListNode* newsortlist_2 = createSortList(2, 6);
//    printList(newsortlist_2);
//    ListNode* reslist = partition(newsortlist_1, 3);
//    printList(reslist);
//    return 0;
//}


