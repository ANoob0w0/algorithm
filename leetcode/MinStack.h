#include <vector>
#include "limits.h"

struct StackNode
{
    StackNode() : data(0), pre(nullptr) {}
    StackNode(const int &num) : data(num), pre(nullptr) {}
    int data;
    StackNode *pre;
};

class MinStack
{
private:
    StackNode *topNode;
    std::vector<int> min;

public:
    /** initialize your data structure here. */
    MinStack() : topNode(nullptr), min({INT_MAX}) {}
    ~MinStack()
    {
        while (topNode != nullptr)
        {
            pop();
        }
    };

    void push(int val)
    {
        StackNode *newNode = new StackNode(val);
        newNode->pre = topNode;
        topNode = newNode;
        if(val <= min.back())
            min.push_back(val);
    }

    inline void pop()
    {
        if(!topNode)
        {
            throw std::runtime_error("Stack is empty");
            return;
        }
        auto popNode = topNode;
        topNode = topNode->pre;
        auto val = popNode->data;
        delete popNode;
        popNode = nullptr;
        if(val == min.back())
            min.pop_back();
    }

    int top()
    {
        if(!topNode)
        {
            throw std::runtime_error("Stack is empty");
        }
        return topNode->data;
    }

    int getMin()
    {
        return min.back();
    }
};