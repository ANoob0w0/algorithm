#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <forward_list>
#include <deque>
#include <unordered_set>
#include <queue>
#include <math.h>
#include <stack>

#include "List.h"
#include "Tree.h"
#include "RandomizedSet.h"

using namespace std;

class Solution
{
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        int col = 0, row = matrix.size() - 1;
        while (col < matrix[0].size() && row >= 0)
        {
            if (matrix[row][col] > target)
                row--;
            else if (matrix[row][col] < target)
                col++;
            else
                return true;
        }
        return false;
    }

    bool canJump(vector<int> &nums)
    {
        int farthest = 0;
        int target = nums.size() - 1;
        for (int i = 0; i < nums.size(); ++i)
        {
            if (i <= farthest)
            {
                int tmp = i + nums[i];
                if (tmp > farthest)
                    farthest = tmp;
                if (farthest >= target)
                    return true;
            }
            else
                return false;
        }
        return false;
    }

    int uniquePaths(int m, int n)
    {
        long long res = 1;
        if (1 == n)
            return res;
        for (int i = 1, j = m; i < n && j < m + n + 1; ++i, ++j)
        {
            res = res * j / i;
        }
        return res;
    }

    int coinChange(vector<int> &coins, int amount)
    {
        if (!amount)
            return 0;
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;
        sort(coins.begin(), coins.end());
        for (int i = 1; i <= amount; ++i)
        {
            for (int j = 0; j < coins.size(); ++j)
                if (i >= coins[j] && dp[i - coins[j]] != INT_MAX)
                    dp[i] = min(dp[i], dp[i - coins[j]] + 1);
        }
        map<int, int> debug;
        for (int i = 0; i < amount + 1; ++i)
            if (dp[i] != INT_MAX)
                debug.insert({i, dp[i]});
        if (dp[amount] == INT_MAX)
            return -1;
        return dp[amount];
    }

    int lengthOfLIS(vector<int> &nums)
    {
        if (nums.size() == 1)
            return 1;
        vector<int> dp(nums.size(), 1);
        int max = 1;
        for (int i = 1; i < nums.size(); ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (nums[i] > nums[j] && dp[i] <= dp[j])
                {
                    dp[i] = dp[j] + 1;
                    max = std::max(max, dp[i]);
                }
            }
        }
        return max;
    }

    int lengthOfLIS2(vector<int> &nums)
    {
        if (nums.size() == 1)
            return 1;
        vector<int> dp({nums[0]});
        for (int i = 1; i < nums.size(); ++i)
        {
            if (nums[i] > dp.back())
                dp.push_back(nums[i]);
            else
            {
                int left = 0, right = dp.size() - 1, mid;
                while (left < right)
                {
                    mid = (left + right) >> 1;
                    if (dp[mid] >= nums[i])
                        right = mid;
                    else
                        left = mid + 1;
                }
                if (dp[left] > nums[i])
                    dp[left] = nums[i];
                else
                    dp[left + 1] = nums[i];
            }
        }
        return dp.size(); //为啥会在最后return的时候报错？？？
    }

    int binarySearch_iteration(vector<int> &nums, int target)
    {
        int left = 0, right = nums.size() - 1, mid;
        while (left < right)
        {
            mid = left + (right - left) / 2;
            if (nums[mid] >= target)
                right = mid;
            else
                left = mid + 1;
        }
        if (nums[left] == target)
            return left;
        return -1;
    }

    bool isHappy(int n)
    {
        unordered_set<int> mem({n});
        while (n != 1)
        {
            int next = 0;
            while (n > 0)
            {
                int curr = n % 10;
                n = (n - curr) / 10;
                next += curr * curr;
            }
            n = next;
            if (mem.find(n) != mem.end())
                return false;
            else
                mem.insert(n);
        }
        return true;
    }

    int trailingZeroes(int n)
    {
        int ans = 0;
        while (n > 0)
        {
            n /= 5;
            ans += n;
        }
        return ans;
    }

    int titleToNumber(string columnTitle)
    {
        int ans = 0;
        for (auto &c : columnTitle)
        {
            ans = ans * 26 + (c - '@');
        }
        return ans;
    }

    double myPow(double x, int n)
    {
        if (!n)
            return 1;
        double half;
        if (n < 0)
        {
            x = 1 / x;
            if (n == -1)
                return x;
            half = myPow(x, -n / 2);
        }
        else
        {
            if (n == 1)
                return x;
            half = myPow(x, n / 2);
        }
        if (n % 2)
            return x * half * half;
        else
            return half * half;
    }

    int mySqrt(int x)
    {
        int l = 0, r = x, ans = -1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if ((long long)mid * mid <= x)
            {
                ans = mid;
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        return ans;
    }

    int divide(int dividend, int divisor)
    {
        if (divisor == 0 || (dividend == INT_MIN && divisor == -1))
            return INT_MAX;
        if (dividend == INT_MIN && divisor == 1)
            return INT_MIN;
        int ans = 0;
        bool sign = false; //false为正
        uint32_t beichu = dividend, chu = divisor;
        if (dividend < 0)
        {
            beichu = ~dividend;
            beichu++;
            sign = !sign;
        }
        if (divisor < 0)
        {
            chu = ~divisor;
            chu++;
            sign = !sign;
        }
        while (beichu >= chu)
        {
            uint32_t tmp = chu, i = 1;
            while (tmp < beichu)
            {
                tmp <<= 1;
                i <<= 1;
            }
            if (tmp > beichu)
            {
                tmp >>= 1;
                i >>= 1;
            }
            beichu = beichu - tmp;
            ans += i;
        }
        if (sign)
            ans = ~ans + 1;
        return ans;
    }

    string fractionToDecimal(int numerator, int denominator)
    {
        uint64_t integer;
        if (numerator == 0)
            return "0";
        if (numerator == INT_MIN && denominator == -1)
            integer = INT_MAX;
        uint64_t numerator_u = numerator, denominator_u = denominator, mod;
        bool sign = false, circle = false;
        if (numerator < 0)
        {
            numerator_u = ~numerator;
            ++numerator_u;
            sign = !sign;
        }
        if (denominator < 0)
        {
            denominator_u = ~denominator;
            ++denominator_u;
            sign = !sign;
        }
        integer = numerator_u / denominator_u;
        vector<int8_t> decimal;
        unordered_map<uint64_t, int> ModMap;
        mod = numerator_u % denominator_u;
        int idx = 0;
        ModMap.insert({mod, idx++});
        while (mod != 0)
        {
            uint64_t tmp = mod * 10;
            decimal.push_back(tmp / denominator_u);
            uint64_t new_mod = tmp % denominator_u;
            auto ret = ModMap.find(new_mod);
            if (ret != ModMap.end())
            {
                circle = true;
                idx = ret->second;
                break;
            }
            else
            {
                mod = new_mod;
                ModMap.insert({mod, idx++});
            }
        }
        string ans;
        if (integer == 0)
            ans.push_back('0');
        while (integer != 0)
        {
            uint8_t num = integer % 10;
            ans.insert(ans.begin(), '0' + num);
            integer = (integer - num) / 10;
        }
        if (sign)
            ans.insert(ans.begin(), '-');
        if (!decimal.empty())
        {
            ans.push_back('.');
            idx += ans.size();
            for (auto num : decimal)
            {
                ans.push_back('0' + num);
            }
            if (circle)
            {
                ans.insert(ans.begin() + idx, '(');
                ans.push_back(')');
            }
        }
        return ans;
    }

    int getSum(int a, int b)
    {
        while (b != 0)
        {
            int tmp = a ^ b;
            b = (unsigned)(a & b) << 1;
            a = tmp;
        }
        return a;
    }

    int evalRPN(vector<string> &tokens)
    {
        stack<int> calstack;
        for (string s : tokens)
        {
            if (s.size() != 1 || (s != "+" && s != "-" && s != "*" && s != "/"))
            {
                calstack.push(atoi(s.c_str()));
            }
            else
            {
                int b = calstack.top();
                calstack.pop();
                int a = calstack.top();
                calstack.pop();
                if (s == "+")
                    calstack.push(a + b);
                else if (s == "-")
                    calstack.push(a - b);
                else if (s == "*")
                    calstack.push(a * b);
                else
                    calstack.push(a / b);
            }
        }
        return calstack.top();
    }

    int majorityElement(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        int count = 0, n = (nums.size() + 1) / 2, last = nums[0];
        for (int i : nums)
        {
            if (count == n)
                return last;
            else
            {
                if (last == i)
                    ++count;
                else
                {
                    last = i;
                    count = 1;
                }
            }
        }
        return last;
    }

    int leastInterval(vector<char> &tasks, int n)
    {
        unordered_map<char, int> TaskMap;
        for (auto c : tasks)
            ++TaskMap[c];
        int MaxExe = 0, MaxCnt = 0;
        for (auto task : TaskMap)
        {
            if (task.second > MaxExe)
            {
                MaxExe = task.second;
                MaxCnt = 1;
            }
            else if (task.second == MaxExe)
                MaxCnt++;
        }
        int tmp = (MaxExe - 1) * (n + 1) + MaxCnt;
        if (tmp >= tasks.size())
            return tmp;
        return tasks.size();
    }

    int solve()
    {
        // auto res = trailingZeroes(100);

        //auto res = titleToNumber("ZY");

        // auto ans = myPow(3, -1);
        // auto ans = mySqrt(8);

        // auto ans = divide(INT_MIN, 2);

        //auto ans = fractionToDecimal(1, INT_MIN);

        //auto ans = getSum(-7, 7);

        // vector<string> tokens = {"10","6","9","3","+","-11","*","/","*","17","+","5","+"};
        // auto ans = evalRPN(tokens);

        // vector<int> nums = {-1, 3, 3, 2, 3, 2};
        // auto ans = majorityElement(nums);

        vector<char> tasks = {'A', 'A', 'A', 'A', 'A', 'A', 'B', 'C', 'D', 'E', 'F', 'G'};
        auto ans = leastInterval(tasks, 2);
        return 0;

        // vector<vector<int>> matrix = {{1, 4, 7, 11, 15}, {2, 5, 8, 12, 19}, {3, 6, 9, 16, 22}, {10, 13, 14, 17, 24}, {18, 21, 23, 26, 30}};
        // auto res = searchMatrix(matrix, 20);

        // vector<int> nums = {0, 2, 3};
        // auto res = canJump(nums);

        //auto res = uniquePaths(3, 3);

        // vector<int> coins({1,2,5});
        // auto res = coinChange(coins, 11);

        // vector<int> nums({7,7,7,7,7,7,7});
        // int res = lengthOfLIS2(nums);

        // vector<int> nums({2, 3, 5, 6, 7, 8, 9});
        // int res = binarySearch_iteration(nums, 1);

        //-------------------tree generater--------------------
        // TreeNode *root = new TreeNode(1);
        // root->left = new TreeNode(-2);
        // root->right = new TreeNode(3);
        // // root->left->left = new TreeNode(4);
        // // root->left->right = new TreeNode(5);
        // root->right->left = new TreeNode(-6);
        // root->right->right = new TreeNode(7);
        //-----------------------------------------------------

        // Codec ser, deser;
        // TreeNode* ans = deser.deserialize(ser.serialize(root));
        // auto res = ser.serialize(root);
        // auto ans = deser.deserialize(res);

        // RandomizedSet r;
        // bool ret;
        // ret = r.insert(-1);
        // ret = r.insert(-2);
        // ret = r.insert(-2);
        // ret = r.remove(-1);
        // ret = r.insert(-1);
        // ret = r.insert(-3);
        // ret = r.insert(-4);
        // ret = r.insert(-5);
        // ret = r.remove(-5);
        // int rand = r.getRandom();
        // rand = r.getRandom();
        // rand = r.getRandom();
        // rand = r.getRandom();
        // rand = r.getRandom();
        // rand = r.getRandom();
        // rand = r.getRandom();

        // auto res = isHappy(19);
    }
};

int main()
{
    Solution s;
    s.solve();
    return 0;
}