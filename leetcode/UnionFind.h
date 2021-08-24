#include <vector>
#include <numeric>

class UnionFind
{
private:
    std::vector<int> id;
public:
    UnionFind(int n) : id(n){
        std::iota(id.begin(), id.end(), 0);
    };

    int find(int p)
    {
        while(id[p] != p)
        {
            p = id[p];
        }
        return p;
    }

    void connect(int parent, int child)
    {
        id[find(child)] = find(parent);
    }

    bool isConnected(int a, int b)
    {
        if(find(a) == find(b))
            return true;
        return false;
    }
};

