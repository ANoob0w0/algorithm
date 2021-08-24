#include <vector>
class MinHeap
{
private:
    std::vector<int> heap;

public:
    MinHeap() = default;
    ~MinHeap() = default;
    void pop();
    void push(const int &item);
    bool empty(){return heap.empty();};
    size_t size(){return heap.size();};
};

void MinHeap::pop()
{
    if (heap.empty())
        return;
    int hole = 1;
    int item = heap.back();
    heap.pop_back();
    while (2 * hole <= heap.size())
    {
        int child = hole * 2;
        if (child + 1 <= heap.size() && heap[child] < heap[child - 1]) //cmp
            child++;
        if (item > heap[child - 1]) //cmp
        {
            heap[hole - 1] = heap[child - 1];
            hole = child;
        }
        else
            break;
    }
    if (!heap.empty())
        heap[hole - 1] = item;
}

void MinHeap::push(const int &item)
{
    heap.push_back(item);
    int hole = heap.size();
    while (hole / 2 >= 1)
    {
        if (item < heap[hole / 2 - 1]) //cmp
        {
            heap[hole - 1] = heap[hole / 2 - 1];
            hole = hole / 2;
        }
        else
            break;
    }
    heap[hole - 1] = item;
}

