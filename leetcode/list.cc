#include <iostream>
#include <cmath>
#include <map>
#include <vector>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *removeNthFromEnd(ListNode *head, int n)
{
    if (!head->next)
        return nullptr;
    ListNode *pre = head, *curr = head;
    int cnt = 1;
    while (curr->next != nullptr)
    {
        if (cnt >= n + 1)
        {
            curr = curr->next;
            pre = pre->next;
        }
        else
            curr = curr->next;
        ++cnt;
    }
    if (cnt == n)
        return pre->next;
    pre->next = pre->next->next;
    return head;
}

inline ListNode *deleteList(ListNode *head)
{
    auto curr = head;
    while (curr)
    {
        auto p = curr;
        curr = p->next;
        delete p;
    }
    return nullptr;
}

inline void printList(ListNode *head)
{
    auto curr = head;
    while (curr)
    {
        cout << curr->val << endl;
        curr = curr->next;
    }
    head = nullptr;
}

ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
{
    if (!l1)
        return l2;
    if (!l2)
        return l1;
    ListNode *newhead, *curr;
    if (l1->val < l2->val)
    {
        newhead = l1;
        l1 = l1->next;
    }
    else
    {
        newhead = l2;
        l2 = l2->next;
    }
    newhead->next = nullptr;
    curr = newhead;
    while (l1 && l2)
    {
        if (l1->val < l2->val)
        {
            curr->next = l1;
            l1 = l1->next;
        }
        else
        {
            curr->next = l2;
            l2 = l2->next;
        }
        curr = curr->next;
        curr->next = nullptr;
    }
    if (l1)
    {
        curr->next = l1;
    }
    else
    {
        curr->next = l2;
    }

    return newhead;
}

inline ListNode *genList(ListNode *head)
{
    //ListNode *head = new ListNode(0);
    ListNode *pre = head;
    for (int i = 1; i < 5; ++i)
    {
        ListNode *newNode = new ListNode(i);
        pre->next = newNode;
        pre = newNode;
    }
    return head;
}

ListNode *reverseList(ListNode *head)
{
    if (!head || !head->next)
        return head;
    else
    {
        ListNode *pre = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return pre;
    }
}

ListNode *reverseList_DualList(ListNode *head)
{
    ListNode* newHead = nullptr;
    while (head) {
        //先保存访问的节点的下一个节点，保存起来
        //留着下一步访问的
        ListNode* temp = head->next;
        //每次访问的原链表节点都会成为新链表的头结点，
        //其实就是把新链表挂到访问的原链表节点的
        //后面就行了
        head->next = newHead;
        //更新新链表
        newHead = head;
        //重新赋值，继续访问
        head = temp;
    }
    //返回新链表
    return newHead;
}

int main()
{
    ListNode *l1 = new ListNode(0);
    //ListNode *l2 = new ListNode(0);
    ListNode *l2 = nullptr;
    l1 = genList(l1);
    //l2 = genList(l2);

    auto newhead = mergeTwoLists(l1, l2);
    newhead = reverseList_DualList(newhead);
    printList(newhead);
    //delete
    //l1 = deleteList(l1);
    //l2 = deleteList(l2);
    l1 = nullptr;
    l2 = nullptr;
    newhead = deleteList(newhead);
    return 0;
}