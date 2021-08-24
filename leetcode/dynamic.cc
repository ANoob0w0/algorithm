#include <iostream>
#include <deque>
#include <vector>

using namespace std;

int maxProfit(vector<int> &prices)
{
    deque<int> PricesStack;
    int prof = 0;
    prices.push_back(0);
    for (auto &p : prices)
    {
        while (!PricesStack.empty() && p <= PricesStack.back())
        {
            int temp = PricesStack.back() - PricesStack.front();
            prof = temp > prof ? temp : prof;
            PricesStack.pop_back();
        }
        PricesStack.push_back(p);
    }
    return prof;
}

int maxSubArray(vector<int> &nums)
{
    int CurrSum = 0;
    int MaxSum = nums.front();
    for (auto &i : nums)
    {
        if(CurrSum < 0)
            CurrSum = i;
        else
            CurrSum += i;
        if(CurrSum > MaxSum)
            MaxSum = CurrSum;
    }
    return MaxSum;
}

int main()
{
    vector<int> price = {-1};
    //cout << maxProfit(price);
    cout << maxSubArray(price);
    return 0;
}