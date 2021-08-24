 #include <iostream>

 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

ListNode* sequentialListGen(const int& n)
{
    if(n < 1)
        return new ListNode();
    ListNode* first = new ListNode(1);
    ListNode* curr = first;
    for(int i = 2; i <= n; ++i)
    {
        curr->next = new ListNode(i);
        curr = curr->next;
    }
    return first;
}
