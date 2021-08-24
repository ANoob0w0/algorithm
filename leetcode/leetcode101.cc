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
#include "algorithm"

#include "List.h"
#include "Tree.h"
#include "RandomizedSet.h"
#include "LRUCache.h"
#include "UnionFind.h"
#include "AllOne.h"
#include "Trie.h"

using namespace std;

class Solution
{
public:
    int candy(vector<int> &ratings)
    {
        if (ratings.empty())
            return 0;
        vector<int> distribute(ratings.size(), 1);
        for (int i = 1; i < ratings.size(); ++i)
        {
            if (ratings[i] > ratings[i - 1])
                distribute[i] = distribute[i - 1] + 1;
        }
        for (int i = ratings.size() - 2; i >= 0; --i)
        {
            if (ratings[i] > ratings[i + 1] && distribute[i] <= distribute[i + 1])
                distribute[i] = distribute[i + 1] + 1;
        }
        int ans = 0;
        for (int i : distribute)
            ans += i;
        return ans;
    }

    int eraseOverlapIntervals(vector<vector<int>> &intervals)
    {
        if (intervals.size() < 2)
            return 0;
        sort(intervals.begin(), intervals.end(),
             [](vector<int> &a, vector<int> &b)
             { return a[1] < b[1]; });
        int ans = 0, right = intervals[0][1];
        for (int i = 1; i < intervals.size(); ++i)
        {
            if (intervals[i][0] < right)
                ++ans;
            else
                right = intervals[i][1];
        }
        return ans;
    }

    bool canPlaceFlowers(vector<int> &flowerbed, int n)
    {
        int sz = flowerbed.size();
        for (int i = 0; i < sz;)
        {
            if (0 == flowerbed[i])
            {
                if ((i == 0 || flowerbed[i - 1] == 0) && (i == sz - 1 || flowerbed[i + 1] == 0))
                {
                    flowerbed[i] = 1;
                    i += 2;
                    --n;
                }
                else
                    ++i;
            }
            else
                i += 2;
        }
        return n <= 0;
    }

    int findMinArrowShots(vector<vector<int>> &points)
    {
        sort(points.begin(), points.end(),
             [](vector<int> &a, vector<int> &b)
             { return a[1] < b[1]; });
        int ans = 1, arrow = points[0][1];
        for (int i = 1; i < points.size(); ++i)
        {
            if (points[i][0] > arrow)
            {
                ++ans;
                arrow = points[i][1];
            }
        }
        return ans;
    }

    vector<int> partitionLabels(string s)
    {
        vector<vector<int>> CharIntervals(26, {-1, -1});
        for (int i = 0; i < s.size(); ++i)
        {
            int idx = s[i] - 'a';
            if (CharIntervals[idx][0] < 0)
            {
                CharIntervals[idx][0] = i;
                CharIntervals[idx][1] = i;
            }
            else
                CharIntervals[idx][1] = i;
        }
        sort(CharIntervals.begin(), CharIntervals.end(),
             [](vector<int> &a, vector<int> &b)
             { return a[0] < b[0]; });
        int left, right, start;
        for (int i = 0; i < 26; ++i)
            if (CharIntervals[i][0] >= 0)
            {
                start = i;
                break;
            }
        left = CharIntervals[start][0];
        right = CharIntervals[start][1];
        vector<int> ans;
        for (int i = start + 1; i < 26; ++i)
        {
            if (CharIntervals[i][0] < right)
                right = max(right, CharIntervals[i][1]);
            else
            {
                ans.push_back(right - left + 1);
                left = CharIntervals[i][0];
                right = CharIntervals[i][1];
            }
        }
        ans.push_back(right - left + 1);
        return ans;
    }

    vector<vector<int>> reconstructQueue(vector<vector<int>> &people)
    {
        vector<vector<int>> ans(people.size(), {-1});
        sort(people.begin(), people.end(),
             [](vector<int> &a, vector<int> &b)
             { return a[0] < b[0]; });
        for (auto p : people)
        {
            int tmp = p[1];
            int idx = 0;
            while (tmp > 0)
            {
                if (ans[idx][0] == -1 || ans[idx][0] == p[0])
                    --tmp;
                ++idx;
            }
            while (ans[idx][0] >= 0)
                ++idx;
            ans[idx] = p;
        }
        return ans;
    }

    bool checkPossibility(vector<int> &nums)
    {
        if (nums.size() < 3)
            return true;
        int cnt = 0;
        for (int i = 1; i < nums.size(); ++i)
        {
            if (nums[i] < nums[i - 1])
            {
                ++cnt;
                if (i == 1 || nums[i - 2] <= nums[i])
                {
                    nums[i - 1] = nums[i];
                }
                else
                {
                    nums[i] = nums[i - 1];
                }
                if (cnt >= 2)
                    return false;
            }
        }
        return true;
    }

    vector<int> twoSum(vector<int> &numbers, int target)
    {
        int left = 0, right = numbers.size() - 1;
        while (left < right)
        {
            while (numbers[left] + numbers[right] > target)
                --right;
            if (numbers[left] + numbers[right] == target)
                break;
            else
                ++left;
        }
        return vector<int>({left, right});
    }

    ListNode *detectCycle(ListNode *head)
    {
        ListNode *fast, *slow;
        if (!head || !head->next)
            return nullptr;
        fast = head->next->next;
        slow = head->next;
        while (fast != slow)
        {
            if (!fast || !fast->next)
                return nullptr;
            fast = fast->next->next;
            slow = slow->next;
        }
        fast = head;
        while (fast != slow)
        {
            fast = fast->next;
            slow = slow->next;
        }
        return fast;
    }

private:
    unordered_map<char, int> hash;

public:
    string minWindow(string s, string t)
    {
        int left = 0, right = -1;
        int minleft = 0;
        int minlen = INT_MAX;
        bool exist = false;
        unordered_map<char, int> dymc;
        for (char &c : t)
        {
            hash[c]++;
            dymc[c];
        }
        int n = s.size() - 1;
        while (right < n)
        {
            auto ret = dymc.find(s[++right]);
            if (ret != dymc.end())
                ++ret->second;
            while (windowCheck(dymc))
            {
                exist = true;
                int currlen = right - left + 1;
                if (currlen < minlen)
                {
                    minleft = left;
                    minlen = currlen;
                }
                auto ret = dymc.find(s[left]);
                if (ret != dymc.end())
                    --ret->second;
                ++left;
            }
        }
        if (exist)
            return string(s, minleft, minlen);
        return string();
    }

    bool windowCheck(unordered_map<char, int> &dymc)
    {
        for (auto &i : dymc)
        {
            if (i.second < hash[i.first])
                return false;
        }
        return true;
    }

    bool judgeSquareSum(int c)
    {
        long right = sqrt(c), left = 0;
        while (left <= right)
        {
            while (left * left + right * right < c)
                ++left;
            if (left * left + right * right == c)
                return true;
            else
                --right;
        }
        return false;
    }

    bool validPalindrome(string s)
    {
        return validPalindrome(s, 0, s.size() - 1, 0);
    }

    bool validPalindrome(string &s, int left, int right, int cnt)
    {
        while (left < right)
        {
            if (s[left] == s[right])
            {
                ++left;
                --right;
            }
            else
            {
                ++cnt;
                if (cnt > 1)
                    return false;
                return validPalindrome(s, left + 1, right, cnt) || validPalindrome(s, left, right - 1, cnt);
            }
        }
        return true;
    }

    string findLongestWord(string s, vector<string> &dictionary)
    {
        int sz = s.size();
        string ans = "";
        int anslen = 0;
        for (string &word : dictionary)
        {
            int n = word.size();
            int i = 0, j = 0;
            for (; i < sz && j < n; ++i)
            {
                if (s[i] == word[j])
                    ++j;
            }
            if (j == n)
                if (n >= anslen)
                {
                    if (n == anslen)
                        ans = min(ans, word);
                    else
                        ans = word;
                    anslen = n;
                }
        }
        return ans;
    }

    bool search(vector<int> &nums, int target)
    {
        int n = nums.size();
        int left = 0, right = n - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target)
                return true;
            else if (nums[mid] == nums[left])
                ++left;
            else if (nums[mid] <= nums[right])
            {
                if (target > nums[mid] && target <= nums[right])
                    left = mid + 1;
                else
                    right = mid - 1;
            }
            else
            {
                if (target >= nums[left] && target < nums[mid])
                    right = mid - 1;
                else
                    left = mid + 1;
            }
        }
        return false;
    }

    int search_base(vector<int> &nums, int target)
    {
        int n = (int)nums.size();
        if (!n)
        {
            return -1;
        }
        if (n == 1)
        {
            return nums[0] == target ? 0 : -1;
        }
        int l = 0, r = n - 1;
        while (l <= r)
        {
            int mid = (l + r) / 2;
            if (nums[mid] == target)
                return mid;
            if (nums[0] <= nums[mid])
            {
                if (nums[0] <= target && target < nums[mid])
                {
                    r = mid - 1;
                }
                else
                {
                    l = mid + 1;
                }
            }
            else
            {
                if (nums[mid] < target && target <= nums[n - 1])
                {
                    l = mid + 1;
                }
                else
                {
                    r = mid - 1;
                }
            }
        }
        return -1;
    }

    string frequencySort(string s)
    {
        unordered_map<char, int> count;
        int maxcnt = 0;
        for (auto &c : s)
        {
            ++count[c];
            maxcnt = max(maxcnt, count[c]);
        }

        vector<vector<char>> bucket(maxcnt + 1);
        for (auto &i : count)
            bucket[i.second].push_back(i.first);

        string ans;
        for (int i = maxcnt; i > 0; --i)
        {
            for (auto &c : bucket[i])
                ans.append(string(i, c));
        }
        return ans;
    }

    int maxAreaOfIsland(vector<vector<int>> &grid)
    {
        int maxarea = 0;
        for (int row = 0; row < grid.size(); ++row)
        {
            for (int col = 0; col < grid[0].size(); ++col)
            {
                if (grid[row][col])
                {
                    int size = 0;
                    dfs(grid, size, row, col);
                    maxarea = max(size, maxarea);
                }
            }
        }
        return maxarea;
    }

    void dfs(vector<vector<int>> &grid, int &size, int row, int col)
    {
        grid[row][col] = 0;
        size++;
        if (row > 0 && grid[row - 1][col])
            dfs(grid, size, row - 1, col);
        if (row < grid.size() - 1 && grid[row + 1][col])
            dfs(grid, size, row + 1, col);
        if (col > 0 && grid[row][col - 1])
            dfs(grid, size, row, col - 1);
        if (col < grid[0].size() - 1 && grid[row][col + 1])
            dfs(grid, size, row, col + 1);
    }

    int findCircleNum(vector<vector<int>> &isConnected)
    {
        int n = isConnected.size(), ans = 0;
        vector<bool> visited(n, false);
        for (int i = 0; i < n; ++i)
        {
            if (!visited[i])
            {
                ans++;
                dfs(isConnected, visited, i);
            }
        }
        return ans;
    }

    void dfs(vector<vector<int>> &isConnected, vector<bool> &visited, int i)
    {
        visited[i] = true;
        for (int j = 0; j < isConnected.size(); ++j)
        {
            if (isConnected[i][j] && !visited[j])
                dfs(isConnected, visited, j);
        }
    }

    vector<int> findRedundantConnection(vector<vector<int>> &edges)
    {
        int n = edges.size();
        UnionFind uf(n + 1);
        for (auto e : edges)
        {
            if (uf.isConnected(e[0], e[1]))
                return e;
            uf.connect(e[0], e[1]);
        }
        return vector<int>({-1, -1});
    }

    vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights)
    {
        int m = heights.size();
        int n = heights[0].size();
        if (!m || !n)
            return {};
        vector<vector<bool>> p_can(m, vector<bool>(n, false));
        vector<vector<bool>> a_can(m, vector<bool>(n, false));

        for (int i = 0; i < m; ++i)
        {
            dfs(heights, p_can, i, 0);
            dfs(heights, a_can, i, n - 1);
        }
        for (int j = 0; j < n; ++j)
        {
            dfs(heights, p_can, 0, j);
            dfs(heights, a_can, m - 1, j);
        }
        vector<vector<int>> ans;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (p_can[i][j] && a_can[i][j])
                    ans.push_back({i, j});
            }
        return ans;
    }

    void dfs(vector<vector<int>> &heights, vector<vector<bool>> &can, int r, int c)
    {
        if (can[r][c])
            return;
        int curr = heights[r][c];
        can[r][c] = true;
        if (r > 0 && heights[r - 1][c] >= curr)
            dfs(heights, can, r - 1, c);
        if (r < heights.size() - 1 && heights[r + 1][c] >= curr)
            dfs(heights, can, r + 1, c);
        if (c > 0 && heights[r][c - 1] >= curr)
            dfs(heights, can, r, c - 1);
        if (c < heights[0].size() - 1 && heights[r][c + 1] >= curr)
            dfs(heights, can, r, c + 1);
    }

    void evenOddSort(vector<int> &nums)
    {
        int left = 0, right = nums.size() - 1;
        while (left < right)
        {
            if (nums[left] % 2)
            {
                swap(nums[left], nums[right]);
                right--;
            }
            else
                ++left;
        }
    }

    bool isMatch(string s, string p)
    {
        return false;
    }

    int longestCommonSubsequence(string text1, string text2)
    {
        int m = text1.size(), n = text2.size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        int maxlen = 0;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (text1[i] == text2[j])
                {
                    if (i && j)
                        dp[i][j] = dp[i - 1][j - 1] + 1;
                    else
                        dp[i][j] = 1;
                    maxlen = max(maxlen, dp[i][j]);
                }
                else
                {
                    if (i && j)
                        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                    else if (i)
                        dp[i][j] = dp[i - 1][j];
                    else if (j)
                        dp[i][j] = dp[i][j - 1];
                }
            }
        }
        return maxlen;
    }

    vector<vector<int>> combine(int n, int k)
    {
        vector<vector<int>> ans;
        vector<int> curr;
        combine(ans, curr, 0, n, k);
        return ans;
    }

    void combine(vector<vector<int>> &ans, vector<int> &curr, int n, const int &max, const int &k)
    {
        if (curr.size() + (max - n) < k)
            return;
        if (curr.size() == k)
        {
            ans.push_back(curr);
            return;
        }
        for (int i = n + 1; i <= max; ++i)
        {
            curr.push_back(i);
            combine(ans, curr, i, max, k);
            curr.pop_back();
        }
    }

    int shortestBridge(vector<vector<int>> &grid)
    {
        vector<int> direction{-1, 0, 1, 0, -1};
        int m = grid.size(), n = grid[0].size();
        queue<pair<int, int>> bfs_queue;
        for (int r = 0; r < m; ++r)
        {
            if (!bfs_queue.empty())
                break;
            for (int c = 0; c < n; ++c)
                if (grid[r][c] == 1)
                {
                    dfs(grid, bfs_queue, r, c);
                    break;
                }
        }

        int level = 0;
        while (!bfs_queue.empty())
        {
            level++;
            int cnt = bfs_queue.size();
            while (cnt--)
            {
                auto p = bfs_queue.front();
                bfs_queue.pop();
                for (int i = 0; i < 4; ++i)
                {
                    int r = p.first + direction[i], c = p.second + direction[i + 1];
                    if (r >= 0 && r < m && c >= 0 && c < n)
                    {
                        if (grid[r][c] == 0)
                        {
                            bfs_queue.push({r, c});
                            grid[r][c] = 2;
                        }
                        else if (grid[r][c] == 1)
                            return level;
                    }
                }
            }
        }
        return 0;
    }

    void dfs(vector<vector<int>> &grid, queue<pair<int, int>> &bfs_queue, int row, int col)
    {
        if (grid[row][col] == 0)
        {
            bfs_queue.push({row, col});
            grid[row][col] = 2;
            return;
        }
        else if (grid[row][col] == 2)
            return;
        else if (grid[row][col] == 1)
            grid[row][col] = 2;

        if (row > 0)
            dfs(grid, bfs_queue, row - 1, col);
        if (row < grid.size() - 1)
            dfs(grid, bfs_queue, row + 1, col);
        if (col > 0)
            dfs(grid, bfs_queue, row, col - 1);
        if (col < grid[0].size() - 1)
            dfs(grid, bfs_queue, row, col + 1);
    }

    vector<string> binaryTreePaths(TreeNode *root)
    {
        vector<string> ans = {};
        if (!root)
            return ans;
        string firstnode = to_string(root->val);
        if (root->left || root->right)
        {
            binaryTreePaths(root->left, firstnode, ans);
            binaryTreePaths(root->right, firstnode, ans);
        }
        else
            ans.push_back(firstnode);
        return ans;
    }

    void binaryTreePaths(TreeNode *root, string curr, vector<string> &ans)
    {
        if (!root)
            return;
        string node = to_string(root->val);
        if (root->left || root->right)
        {
            binaryTreePaths(root->left, curr + "->" + node, ans);
            binaryTreePaths(root->right, curr + "->" + node, ans);
        }
        else
            ans.push_back(curr.append("->" + node));
    }

    void solve(vector<vector<char>> &board)
    {
        int m = board.size();
        int n = board[0].size();
        if (!m || !n)
            return;
        for (int i = 0; i < m; ++i)
        {
            dfs(board, i, 0);
            dfs(board, i, n - 1);
        }
        for (int j = 0; j < n; ++j)
        {
            dfs(board, 0, j);
            dfs(board, m - 1, j);
        }

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                else if (board[i][j] == 'S')
                    board[i][j] = 'O';
            }
    }

    void dfs(vector<vector<char>> &board, int r, int c)
    {
        if (board[r][c] != 'O')
            return;
        board[r][c] = 'S';
        if (r > 0 && board[r - 1][c] == 'O')
            dfs(board, r - 1, c);
        if (r < board.size() - 1 && board[r + 1][c] == 'O')
            dfs(board, r + 1, c);
        if (c > 0 && board[r][c - 1] == 'O')
            dfs(board, r, c - 1);
        if (c < board[0].size() - 1 && board[r][c + 1] == 'O')
            dfs(board, r, c + 1);
    }

    bool isBipartite(vector<vector<int>> &graph)
    {
        stack<int> dfs_stack;
        int n = graph.size();
        vector<int> color(n, 0);

        int curr_color = -1;
        for (int i = 0; i < n; ++i)
        {
            if (!graph[i].empty() && color[i] == 0)
            {
                dfs_stack.push(i);
                color[i] = -1;
                if (!dfs(graph, dfs_stack, color))
                    return false;
            }
        }
        return true;
    }

    inline bool dfs(vector<vector<int>> &graph, stack<int> &dfs_stack, vector<int> &color)
    {
        while (!dfs_stack.empty())
        {
            int curr = dfs_stack.top();
            int curr_color = colorChange(color[curr]);
            dfs_stack.pop();
            for (int i : graph[curr])
            {
                if (color[i] == 0)
                {
                    dfs_stack.push(i);
                    color[i] = curr_color;
                }
                else
                {
                    if (color[i] != curr_color)
                        return false;
                }
            }
        }
        return true;
    }

    inline int colorChange(const int &color)
    {
        if (color == -1)
            return -2;
        else if (color == -2)
            return -1;
        return 0;
    }

    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<vector<int>> edges(numCourses);
        vector<int> indegree(numCourses, 0);
        vector<int> ans;
        for (auto &course : prerequisites)
        {
            edges[course[1]].push_back(course[0]);
            indegree[course[0]]++;
        }
        queue<int> course_queue;
        for (int i = 0; i < numCourses; ++i)
        {
            if (indegree[i] == 0)
                course_queue.push(i);
        }
        while (!course_queue.empty())
        {
            ans.push_back(course_queue.front());
            for (auto &node : edges[course_queue.front()])
            {
                indegree[node]--;
                if (indegree[node] == 0)
                    course_queue.push(node);
            }
            course_queue.pop();
        }
        for (int i = 0; i < numCourses; ++i)
        {
            if (indegree[i])
                return vector<int>();
        }
        return ans;
    }

    int longestPalindromeSubseq(string s)
    {
        int n = s.size();
        int len = 1;
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i)
            dp[i][i] = 1;
        for (int r = 1; r < n; r++)
        {
            if (s[r - 1] == s[r])
            {
                dp[r - 1][r] = 2;
                len = 2;
            }
            else
                dp[r - 1][r] = 1;
        }
        for (int r = 2; r < n; ++r)
            for (int l = r - 2; l >= 0; --l)
            {
                if (s[l] == s[r])
                {
                    dp[l][r] = dp[l + 1][r - 1] + 2;
                    len = max(len, dp[l][r]);
                }
                else
                    dp[l][r] = max(dp[l][r - 1], dp[l + 1][r]);
            }
        return len;
    }

    int solve()
    {
        auto ret = longestPalindromeSubseq("b");
        // vector<vector<int>> courses = {{0, 1}};
        // auto ret = findOrder(2, courses);
        // vector<vector<int>> graph = {{}};
        // auto ret = isBipartite(graph);
        // Trie* obj = new Trie();
        // obj->insert("apple");
        // obj->insert("app");
        // auto ret = obj->search("apple");
        // ret = obj->search("appl");
        // ret = obj->search("app");
        // obj->insert("children");
        // ret = obj->search("ch");
        // ret = obj->startsWith("ch");
        // ret = obj->startsWith("ap");
        // vector<vector<char>> board = {
        //     {'X', 'X', 'X', 'X'},
        //     {'X', 'X', 'O', 'X'},
        //     {'X', 'O', 'X', 'X'},
        //     {'X', 'O', 'O', 'X'}};
        // solve(board);
        // //-------------------tree generater--------------------
        // TreeNode *root = new TreeNode(1);
        // // root->left = new TreeNode(-2);
        // // root->right = new TreeNode(3);
        // // // root->left->left = new TreeNode(4);
        // // // root->left->right = new TreeNode(5);
        // // root->right->left = new TreeNode(-6);
        // // root->right->right = new TreeNode(7);
        // //-----------------------------------------------------
        // auto ans = binaryTreePaths(nullptr);
        // vector<vector<int>> grid =
        //     {{1, 0, 0, 0},
        //      {1, 1, 0, 0},
        //      {0, 0, 0, 1},
        //      {0, 0, 1, 1}};
        // auto ans = shortestBridge(grid);
        // auto ans = combine(4, 4);
        // auto ans = longestCommonSubsequence("oxcpqrsvwf", "shmtulqrypy");
        // vector<int> nums({1, 3, 5, 2, 4, 7, 9, 10, 6});
        // evenOddSort(nums);
        // vector<vector<int>> heights =
        // {   {1,2,2,3,5},
        //     {3,2,3,4,4},
        //     {2,4,5,3,1},
        //     {6,7,1,4,5},
        //     {5,1,1,2,4}};
        // vector<vector<int>> heights =
        // {   {3,3,3,3,3,3},
        //     {3,0,3,3,0,3},
        //     {3,3,3,3,3,3}};
        // auto ans = pacificAtlantic(heights);
        // AllOne *ao = new AllOne();
        // ao->inc("a");
        // ao->inc("a");
        // ao->inc("b");
        // ao->inc("b");
        // ao->inc("a");
        // ao->dec("b");
        // ao->inc("b");
        // ao->inc("b");
        // ao->inc("c");
        // ao->inc("c");
        // ao->inc("c");
        // auto ret = ao->getMaxKey();
        // ret = ao->getMinKey();
        // vector<vector<int>> edges =
        //     {{1, 2},
        //      {2, 3},
        //      {3, 4},
        //      {1, 4},
        //      {1, 5}};
        // auto ans = findRedundantConnection(edges);
        // vector<vector<int>> isConnected =
        //     {{1, 0, 0, 1},
        //      {0, 1, 1, 0},
        //      {0, 1, 1, 1},
        //      {1, 0, 1, 1}};
        // auto ans = findCircleNum(isConnected);
        // vector<vector<int>> map =
        // {{0,0,1,0,0,0,0,1,0,0,0,0,0},
        //  {0,0,0,0,0,0,0,1,1,1,0,0,0},
        //  {0,1,1,0,1,0,0,0,0,0,0,0,0},
        //  {0,1,0,0,1,1,0,0,1,0,1,0,0},
        //  {0,1,0,0,1,1,0,0,1,1,1,0,0},
        //  {0,0,0,0,0,0,0,0,0,0,1,0,0},
        //  {0,0,0,0,0,0,0,1,1,1,0,0,0},
        //  {0,0,0,0,0,0,0,1,1,0,0,0,0}};
        // auto ans = maxAreaOfIsland(map);
        // LRUCache *c = new LRUCache(2);
        // c->put(1, 2);
        // c->put(2, 3);
        // c->put(3, 3);
        // c->put(2, 4);
        // auto ret = c->get(1);
        // ret = c->get(3);
        // auto ans = frequencySort("aaacccsjsjsjsjs");
        // vector<int> nums = {4,5,6,7,8,1,2};
        // int target = 8;
        // auto ans = search_base(nums, target);
        // string s = "abce";
        // vector<string> dictionary = {"abe", "abc"};
        // auto ans = findLongestWord(s, dictionary);
        // string s = "abdcca";
        // auto ans = validPalindrome(s);
        // auto ans = judgeSquareSum(0);
        // string s = "ADOBECODEBANC", t = "ABC";
        // auto ans = minWindow(s, t);
        // vector<int> nums({-1, 2, 7, 9, 15});
        // auto ans = twoSum(nums, 9);
        // auto res = checkPossibility(nums);
        // vector<vector<int>> people = {{6, 0}, {5, 0}, {4, 0}, {3, 2}, {2, 2}, {1, 4}};
        // auto ans = reconstructQueue(people);
        // string S = "ababcbacadefegdehijhklij";
        // auto res = partitionLabels(S);
        // vector<vector<int>> points = {{10,16},{2,8},{1,6},{7,12}};
        // auto ans = findMinArrowShots(points);
        // vector<int> flowerbed({1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1});
        // auto ans = canPlaceFlowers(flowerbed, 1);
        // vector<vector<int>> intervals({{-52,31},{-73,-26},{82,97},{-65,-11},{-62,-49},{95,99},{58,95},{-31,49},{66,98},{-63,2},{30,47},{-40,-26}});
        // auto ans = eraseOverlapIntervals(intervals);
        // vector<int> rating({1,3,2,2,1});
        // auto ans = candy(rating);
        return 0;
    }
};

int main()
{
    Solution s;
    s.solve();
    return 0;
}