#include <iostream>

using namespace std;

bool isBadVersion(int n){
    if(n >= 9)
        return true;
    else 
        return false;
}

inline int find(int low, int high)
{
    if(low == high)
        return low;
    auto mid = low + (high - low) / 2;
    if (isBadVersion(mid))
    {
        return find(low, mid);
    }
    else
    {
        return find(mid + 1, high);
    }
}

int firstBadVersion(int n)
{
    return find(1, n);
}

int main(){
    cout << firstBadVersion(4545454) << endl;
    return 0;
}