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
#include <string.h>

#include "List.h"
#include "Tree.h"
#include "RandomizedSet.h"
#include "LRUCache.h"
#include "UnionFind.h"
#include "AllOne.h"
#include "Trie.h"
#include "MinHeap.h"

using namespace std;

class Solution
{
private:
    bool row[9][9];
    bool col[9][9];
    bool block[3][3][9];
    vector<pair<int, int>> space;
    bool ans = false;

public:
    void solveSudoku(vector<vector<char>> &board)
    {
        memset(row, false, sizeof(row));
        memset(col, false, sizeof(col));
        memset(block, false, sizeof(block));
        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                if (board[i][j] != '.')
                {
                    int num = board[i][j] - '1';
                    row[i][num] = true;
                    col[j][num] = true;
                    block[i / 3][j / 3][num] = true;
                }
                else
                    space.push_back({i, j});
            }
        }
        dfs(space.begin(), board);
    }

    void dfs(vector<pair<int, int>>::iterator it, vector<vector<char>> &board)
    {
        if (ans)
            return;
        if (it == space.end())
        {
            ans = true;
            return;
        }
        for (int fill = 0; fill < 9; ++fill)
        {
            if (!row[it->first][fill] && !col[it->second][fill] && !block[it->first / 3][it->second / 3][fill])
            {
                row[it->first][fill] = col[it->second][fill] = block[it->first / 3][it->second / 3][fill] = true;
                board[it->first][it->second] = fill + '1';
                dfs(it + 1, board);
                if (!ans)
                {
                    row[it->first][fill] = col[it->second][fill] = block[it->first / 3][it->second / 3][fill] = false;
                    board[it->first][it->second] = '.';
                }
            }
        }
    }

    int trap(vector<int> &height)
    {
        stack<int> minstack;
        int ans = 0;
        for (int i = 0; i < height.size(); ++i)
        {
            while (!minstack.empty() && height[i] >= height[minstack.top()])
            {
                int top = minstack.top();
                minstack.pop();
                if (minstack.empty())
                    break;
                int left = minstack.top();
                int w = i - left - 1;
                int h = min(height[left], height[i]) - height[top];
                ans += w * h;
            }
            minstack.push(i);
        }
        return ans;
    }

    int maxEnvelopes(vector<vector<int>> &envelopes)
    {
        int ans = 0;
        sort(envelopes.begin(), envelopes.end(),
             [](vector<int> &a, vector<int> &b)
             {
                 if (a[0] == b[0])
                     return a[1] > b[1];
                 return a[0] < b[0];
             });
        int n = envelopes.size();
        vector<int> dp(n, 1);
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (envelopes[i][1] > envelopes[j][1])
                    dp[i] = max(dp[i], dp[j] + 1);
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }

    int calculate(string s)
    {
        char presign = '+';
        stack<int> cal_stk;
        string num;
        int len = s.size();
        for (int i = 0; i <= len; ++i)
        {
            if (s[i] == ' ')
                continue;
            if (i < len && isdigit(s[i]))
                num.push_back(s[i]);
            else
            {
                int n = stoi(num);
                num.clear();
                if (presign == '+')
                    cal_stk.push(n);
                else if (presign == '-')
                    cal_stk.push(-n);
                else if (presign == '*')
                    cal_stk.top() = cal_stk.top() * n;
                else if (presign == '/')
                    cal_stk.top() = cal_stk.top() / n;
                if (i < len)
                    presign = s[i];
            }
        }
        int ans = 0;
        while (!cal_stk.empty())
        {
            ans += cal_stk.top();
            cal_stk.pop();
        }
        return ans;
    }

    int calculateii(string s)
    {
        auto it = s.begin();
        return calculate_helper(it, s.end());
    }

    int calculate_helper(string::iterator &it, const string::iterator &end)
    {
        char presign = '+';
        stack<long long> cal_stk;
        long long num = 0;
        for (; it != end && *it != ')'; ++it)
        {
            if (*it == ' ')
                continue;
            if (it != end && *it != ')' && isdigit(*it) || *it == '(')
            {
                if (isdigit(*it))
                    num = 10 * num + *it - '0';
                else
                    num = calculate_helper(++it, end);
            }
            else
            {
                if (presign == '+')
                    cal_stk.push(num);
                else if (presign == '-')
                    cal_stk.push(-num);
                else if (presign == '*')
                    cal_stk.top() = cal_stk.top() * num;
                else if (presign == '/')
                    cal_stk.top() = cal_stk.top() / num;
                if (it != end)
                    presign = *it;
                num = 0;
            }
        }

        if (presign == '+')
            cal_stk.push(num);
        else if (presign == '-')
            cal_stk.push(-num);
        else if (presign == '*')
            cal_stk.top() = cal_stk.top() * num;
        else if (presign == '/')
            cal_stk.top() = cal_stk.top() / num;
        if (it != end)
            presign = *it;

        long long ans = 0;
        while (!cal_stk.empty())
        {
            ans += cal_stk.top();
            cal_stk.pop();
        }
        return ans;
    }

    int solve()
    {
        vector<int>nums = {7,6,5,4,3,2,1,3,6,9,10};
        MinHeap mh;
        for (int &i : nums)
            mh.push(i);
        while(!mh.empty())
            mh.pop();
        
        // auto ret = calculateii("2147483648 - 1000 + 2");

        // vector<vector<int>> envelopes = {{5,4},{6,4},{6,7},{2,3}};
        // auto ans = maxEnvelopes(envelopes);

        // vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
        // auto ans = trap(height);

        // vector<vector<char>> board = {
        //     {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        //     {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        //     {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        //     {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        //     {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        //     {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        //     {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        //     {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        //     {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
        // solveSudoku(board);
        return 0;
    }
};

int main()
{
    Solution s;
    s.solve();
    return 0;
}