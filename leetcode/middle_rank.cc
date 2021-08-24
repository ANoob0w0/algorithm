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

#include "List.h"
#include "Tree.h"

using namespace std;

class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        vector<vector<int>> sol;
        sort(nums.begin(), nums.end());
        if (nums.size() < 3 || nums.back() < 0 || nums.front() > 0)
            return sol;
        for (auto it = nums.begin(); it != nums.end() - 1; ++it)
        {
            if (it != nums.begin() && *it == *(it - 1))
                continue;
            auto tar = 0 - *it;
            auto itbeg = it + 1;
            auto itend = nums.end() - 1;
            while (itend - itbeg > 0)
            {
                if (itbeg != (it + 1) && *itbeg == *(itbeg - 1))
                {
                    ++itbeg;
                    continue;
                }
                auto temp = *itbeg + *itend;
                if (temp > tar)
                {
                    --itend;
                }
                else if (temp < tar)
                {
                    ++itbeg;
                }
                else
                {
                    sol.push_back({*it, *itbeg, *itend});
                    ++itbeg;
                }
            }
        }
        return sol;
    }

    void setZeroes(vector<vector<int>> &matrix)
    {
        int m = matrix.size();
        int n = matrix[0].size();
        bool rowZero = false, colZero = false;

        for (int i = 0; i < m; ++i)
        {
            if (matrix[i][0] == 0)
            {
                colZero = true;
                break;
            }
        }

        for (int j = 0; j < n; ++j)
        {
            if (matrix[0][j] == 0)
            {
                rowZero = true;
                break;
            }
        }

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (!matrix[i][j])
                {
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                }
            }
        }

        for (int i = 1; i < m; ++i)
        {
            if (!matrix[i][0])
                for (int j = 1; j < n; ++j)
                    matrix[i][j] = 0;
        }

        for (int j = 1; j < n; ++j)
        {
            if (!matrix[0][j])
                for (int i = 1; i < m; ++i)
                    matrix[i][j] = 0;
        }

        for (int i = 0; i < m; ++i)
        {
            if (colZero)
                matrix[i][0] = 0;
        }

        for (int j = 0; j < n; ++j)
        {
            if (rowZero)
                matrix[0][j] = 0;
        }
    }

    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        map<string, int> strMap;
        vector<vector<string>> sol;
        for (auto &str : strs)
        {
            auto temp = str;
            sort(temp.begin(), temp.end());
            auto ret = strMap.find(temp);
            if (strMap.end() == ret)
            {
                sol.push_back(vector<string>({str}));
                int idx = sol.size() - 1;
                strMap.insert({temp, idx});
            }
            else
            {
                bool flag = false;
                for (auto &s : sol[ret->second])
                    if (s == str)
                        flag = true;
                if (!flag)
                    sol[ret->second].push_back(str);
            }
        }
        return sol;
    }

    int lengthOfLongestSubstring(string s)
    {
        int max = 0;
        unordered_set<char> hash;
        int ridx = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            if (i != 0)
                hash.erase(s[i - 1]);
            while (ridx < s.size() && !hash.count(s[ridx]))
            {
                hash.insert(s[ridx]);
                ++ridx;
            }
            max = max > ridx - i ? max : ridx - i;
        }
        return max;
    }

    string longestPalindrome(string s)
    {
        int n = s.size();
        int maxl = 0, maxr = 0;
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        for (int i = 0; i < n; ++i)
        {
            dp[i][i] = true;
        }
        for (int ridx = 1; ridx < n; ++ridx)
        {
            for (int lidx = 0; lidx < ridx; ++lidx)
            {
                if (ridx - lidx == 1)
                {
                    if (s[ridx] == s[lidx])
                    {
                        dp[lidx][ridx] = true;
                        if ((ridx - lidx) > (maxr - maxl))
                        {
                            maxl = lidx;
                            maxr = ridx;
                        }
                    }
                }
                else
                {
                    if (dp[lidx + 1][ridx - 1] && s[ridx] == s[lidx])
                    {
                        dp[lidx][ridx] = true;
                        if ((ridx - lidx) > (maxr - maxl))
                        {
                            maxl = lidx;
                            maxr = ridx;
                        }
                    }
                }
            }
        }
        return string(s, maxl, maxr - maxl + 1);
    }

    bool increasingTriplet(const vector<int> &nums)
    {
        if (nums.size() < 3)
            return false;
        int min = INT_MAX, mid = INT_MAX;
        for (int i = 0; i < nums.size(); ++i)
        {
            if (nums[i] <= min)
            {
                min = nums[i];
            }
            else if (nums[i] <= mid)
            {
                mid = nums[i];
            }
            else
                return true;
        }
        return false;
    }

    forward_list<int> addTwoNumbers(const forward_list<int> &l1, const forward_list<int> &l2)
    {
        forward_list<int> sol;
        int carry = 0;
        auto it1 = l1.begin();
        auto it2 = l2.begin();
        while (it1 != l1.end() || it2 != l2.end())
        {
            int tmp;
            if (it1 == l1.end())
            {
                tmp = *it2 + carry;
                ++it2;
            }
            else if (it2 == l2.end())
            {
                tmp = *it1 + carry;
                ++it1;
            }
            else
            {
                tmp = *it1 + *it2 + carry;
                ++it1;
                ++it2;
            }
            if (tmp >= 10)
                carry = 1;
            else
                carry = 0;
            sol.push_front(tmp % 10);
        }
        return sol;
    }

    ListNode *oddEvenList(ListNode *head)
    {
        if (!head || !head->next || !head->next->next)
            return head;
        ListNode *odd_last = head;
        ListNode *even_head = head->next;
        ListNode *even_last = head->next;
        ListNode *curr = head->next->next;
        bool is_odd = true;
        while (curr)
        {
            if (is_odd)
            {
                odd_last->next = curr;
                odd_last = odd_last->next;
            }
            else
            {
                even_last->next = curr;
                even_last = even_last->next;
            }
            curr = curr->next;
            is_odd = !is_odd;
        }
        even_last->next = nullptr;
        odd_last->next = even_head;
        return head;
    }

    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        if (!headA || !headB)
            return nullptr;
        ListNode *pA = headA;
        ListNode *pB = headB;
        while (pA != pB)
        {
            pA = pA != nullptr ? pA->next : headB;
            pB = pB != nullptr ? pB->next : headA;
        }
        return pA;
    }

    vector<int> inorderTraversal(TreeNode *root)
    {
        vector<int> sol;
        inorderRec(root, sol);
        return sol;
    }

    void inorderRec(TreeNode *root, vector<int> &sol)
    {
        if (!root)
            return;
        inorderRec(root->left, sol);
        sol.push_back(root->val);
        inorderRec(root->right, sol);
        return;
    }

    vector<vector<int>> zigzagLevelOrder(TreeNode *root)
    {
        vector<vector<int>> sol;
        zigzagRec(root, sol, 0);
        for (int i = 0; i < sol.size(); ++i)
            if (i % 2 == 1)
                reverse(sol[i].begin(), sol[i].end());
        return sol;
    }

    void zigzagRec(TreeNode *root, vector<vector<int>> &sol, int level)
    {
        if (!root)
            return;
        if (sol.size() <= level)
            sol.push_back({root->val});
        else
            sol[level].push_back(root->val);
        zigzagRec(root->left, sol, level + 1);
        zigzagRec(root->right, sol, level + 1);
        return;
    }

private:
    unordered_map<int, vector<int>::iterator> itMap;

public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        for (auto it = inorder.begin(); it != inorder.end(); ++it)
        {
            itMap.insert({*it, it});
        }
        return buildHelper(preorder.begin(), preorder.end(), inorder.begin(), inorder.end());
    }

    TreeNode *buildHelper(vector<int>::iterator prebeg, vector<int>::iterator preend, vector<int>::iterator inbeg, vector<int>::iterator inend)
    {
        if (preend == prebeg)
            return nullptr;
        TreeNode *root = new TreeNode(*prebeg);
        auto inRoot = itMap.find(*prebeg)->second;
        root->left = buildHelper(prebeg + 1, prebeg + (inRoot - inbeg) + 1, inbeg, inRoot - 1);
        root->right = buildHelper(prebeg + (inRoot - inbeg) + 1, preend, inRoot + 1, inend);
        return root;
    }

    Node *connect(Node *root)
    {
        vector<Node *> next;
        int level = 0;
        connectHelper(root, next, level);
        return root;
    }

    void connectHelper(Node *&root, vector<Node *> &next, int level)
    {
        if (!root)
            return;
        if (next.size() <= level)
            next.push_back(nullptr);
        root->next = next[level];
        next[level] = root;
        connectHelper(root->right, next, level + 1);
        connectHelper(root->left, next, level + 1);
    }

    int kthSmallest(TreeNode *root, int k)
    {
        int res;
        inorder(root, k, res);
        return res;
    }

    void inorder(TreeNode *root, int &k, int &res)
    {
        if (!root)
            return;
        inorder(root->left, k, res);
        --k;
        if (k <= 0)
        {
            if (k == 0)
                res = root->val;
            return;
        }
        inorder(root->right, k, res);
    }

    int numIslands(vector<vector<char>> &grid)
    {
        int res = 0;
        for (int row = 0; row < grid.size(); ++row)
            for (int col = 0; col < grid[row].size(); ++col)
            {
                if ('1' == grid[row][col])
                {
                    res += 1;
                    dfs(grid, row, col);
                }
            }
        return res;
    }

    void dfs(vector<vector<char>> &grid, int row, int col)
    {
        grid[row][col] = '0';
        if (col > 0 && grid[row][col - 1] == '1')
            dfs(grid, row, col - 1);
        if (row > 0 && grid[row - 1][col] == '1')
            dfs(grid, row - 1, col);
        if (col < grid[row].size() - 1 && grid[row][col + 1] == '1')
            dfs(grid, row, col + 1);
        if (row < grid.size() - 1 && grid[row + 1][col] == '1')
            dfs(grid, row + 1, col);
    }

private:
    const vector<vector<char>> phoneMap = {
        {'a', 'b', 'c'},
        {'d', 'e', 'f'},
        {'g', 'h', 'i'},
        {'j', 'k', 'l'},
        {'m', 'n', 'o'},
        {'p', 'q', 'r', 's'},
        {'t', 'u', 'v'},
        {'w', 'x', 'y', 'z'},
    };

public:
    vector<string> letterCombinations(string digits)
    {
        vector<string> res;
        if (digits.empty())
            return res;
        int sz = digits.size();
        backtrack(res, digits, 0, sz, "");
        return res;
    }

    void backtrack(vector<string> &res, const string &digits, int currIdx, const int &digitSize, string currLetters)
    {
        if (currIdx >= digitSize)
        {
            res.push_back(currLetters);
            return;
        }
        int lettersIdx = digits[currIdx] - '2';
        for (auto c : phoneMap[lettersIdx])
        {
            backtrack(res, digits, currIdx + 1, digitSize, currLetters + c);
        }
    }

    vector<string> generateParenthesis(int n)
    {
        vector<string> res;
        backtrack(0, res, string(), 0, 0, n);
        return res;
    }

    void backtrack(int cnt, vector<string> &res, string pre, int left, int right, int &n)
    {
        if (2 * n == cnt)
        {
            res.push_back(pre);
            return;
        }
        if (left < n)
            backtrack(cnt + 1, res, pre + "(", left + 1, right, n);
        if (right < left)
            backtrack(cnt + 1, res, pre + ")", left, right + 1, n);
    }

    vector<vector<int>> permute(vector<int> &nums)
    {
        vector<vector<int>> res;
        backtrack(nums, res, 0, nums.size() - 1);
        return res;
    }

    void backtrack(vector<int> &nums, vector<vector<int>> &res, int beg, const int &end)
    {
        if (end == beg)
            res.push_back(nums);
        for (int i = beg; i <= end; ++i)
        {
            int tmp = nums[i];
            nums[i] = nums[beg];
            nums[beg] = tmp;
            backtrack(nums, res, beg + 1, end);
            nums[beg] = nums[i];
            nums[i] = tmp;
        }
    }

    vector<vector<int>> subsets(vector<int> &nums)
    {
        vector<vector<int>> res;
        vector<int> curr;
        backtrack(res, nums, curr, -1, nums.size());
        return res;
    }

    void backtrack(vector<vector<int>> &res, vector<int> &nums, vector<int> &curr, int currEnd, const int &size)
    {
        res.push_back(curr);
        for (currEnd += 1; currEnd < size; ++currEnd)
        {
            curr.push_back(nums[currEnd]);
            backtrack(res, nums, curr, currEnd, size);
            curr.pop_back();
        }
    }

    bool exist(vector<vector<char>> &board, string word)
    {
        bool res = false;
        int m = board.size();
        int n = board[0].size();
        for (int row = 0; row < m; ++row)
            for (int col = 0; col < n; ++col)
            {
                if (board[row][col] == word[0])
                    wordFinder(res, board, word, 1, word.size(), row, col);
            }
        return res;
    }

    void wordFinder(bool &res, vector<vector<char>> &board, string &word, int charCurr, int charEnd, int row, int col)
    {
        if (res || charCurr == charEnd)
        {
            res = true;
            return;
        }
        char tmp = board[row][col];
        if (col > 0 && board[row][col - 1] == word[charCurr])
        {
            board[row][col] = '\0';
            wordFinder(res, board, word, charCurr + 1, charEnd, row, col - 1);
            board[row][col] = tmp;
        }
        if (row > 0 && board[row - 1][col] == word[charCurr])
        {
            board[row][col] = '\0';
            wordFinder(res, board, word, charCurr + 1, charEnd, row - 1, col);
            board[row][col] = tmp;
        }
        if (col < board[row].size() - 1 && board[row][col + 1] == word[charCurr])
        {
            board[row][col] = '\0';
            wordFinder(res, board, word, charCurr + 1, charEnd, row, col + 1);
            board[row][col] = tmp;
        }
        if (row < board.size() - 1 && board[row + 1][col] == word[charCurr])
        {
            board[row][col] = '\0';
            wordFinder(res, board, word, charCurr + 1, charEnd, row + 1, col);
            board[row][col] = tmp;
        }
    }

    void sortColors(vector<int> &nums)
    {
        int p1 = 0, p0 = 0;
        for (int i = 0; i < nums.size(); ++i)
        {
            if (0 == nums[i])
            {
                swap(nums[p0], nums[i]);
                if (p1 > p0)
                    swap(nums[i], nums[p1]);
                ++p0;
                ++p1;
            }
            else if (1 == nums[i])
            {
                swap(nums[p1], nums[i]);
                ++p1;
            }
        }
    }

    void quickSort(vector<int> &nums, int left, int right)
    {
        int pivot;
        if (left < right)
        {
            pivot = partition(nums, left, right);
            quickSort(nums, left, pivot - 1);
            quickSort(nums, pivot + 1, right);
        }
    }

    int partition(vector<int> &nums, int left, int right)
    {
        int pivotvalue = nums[left]; //枢轴默认是第一个
        while (left < right)
        {
            while (left < right && nums[right] >= pivotvalue)
                --right;
            swap(nums[left], nums[right]);
            while (left < right && nums[left] <= pivotvalue)
                ++left;
            swap(nums[left], nums[right]);
        }
        return left;
    }

    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        map<int, int> occurnums;
        for (int i = 0; i < nums.size(); ++i)
            ++occurnums[nums[i]];
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(myCmp) *> minheap(myCmp);
        for (auto p : occurnums)
        {
            if (minheap.size() == k)
            {
                minheap.push(p);
                minheap.pop();
            }
            else
                minheap.push(p);
        }
        vector<int> res;
        while (!minheap.empty())
        {
            res.push_back(minheap.top().first);
            minheap.pop();
        }
        return res;
    }

    static bool myCmp(pair<int, int> &l, pair<int, int> &r)
    {
        return l.second > r.second;
    }

    int findKthLargest(vector<int> &nums, int k)
    {
        priority_queue<int, vector<int>, decltype(cmp) *> minheap(cmp);
        for (int i : nums)
        {
            minheap.push(i);
            if (minheap.size() > k)
                minheap.pop();
        }
        return minheap.top();
    }

    static bool cmp(int &l, int &r)
    {
        return l > r;
    }

    void heapPop(vector<int> &heap)
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

    void heapPush(vector<int> &heap, const int &item)
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

    int findKthLargest_myheap(vector<int> &nums, int k)
    {
        vector<int> minheap;
        for (int i : nums)
        {
            heapPush(minheap, i);
            if (minheap.size() > k)
                heapPop(minheap);
        }
        return minheap[0];
    }

    int findPeakElement(vector<int> &nums)
    {
        return search(nums, 0, nums.size() - 1);
    }

    int search(vector<int> &nums, int left, int right)
    {
        if (left == right)
            return left;
        int mid = (left + right) / 2;
        if (nums[mid] > nums[mid + 1])
            return search(nums, left, mid);
        else
            return search(nums, mid + 1, right);
    }

    vector<int> searchRange(vector<int> &nums, int target)
    {
        if (nums.empty())
            return vector<int>({-1, -1});
        int mid = binarySearch(nums, target, 0, nums.size() - 1);
        if (nums[mid] != target)
            return vector<int>({-1, -1});
        int left = mid, right = mid;
        while (left >= 0 && nums[left] == target)
            --left;
        while (right < nums.size() && nums[right] == target)
            ++right;
        return vector<int>({left + 1, right - 1});
    }

    int binarySearch(vector<int> &nums, int &target, int left, int right)
    {
        if (left == right)
            return left;
        int mid = (left + right) >> 1;
        if (nums[mid] >= target)
            return binarySearch(nums, target, left, mid);
        return binarySearch(nums, target, mid + 1, right);
    }

    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        vector<vector<int>> merge;
        if (intervals.empty())
            return merge;
        sort(intervals.begin(), intervals.end());
        merge.push_back(intervals[0]);
        for (int i = 1; i < intervals.size(); ++i)
        {
            if (intervals[i][0] <= merge.back().back())
            {
                if (intervals[i][1] > merge.back().back())
                    merge.back()[1] = intervals[i][1];
            }
            else
                merge.push_back(intervals[i]);
        }
        return merge;
    }

    int search(vector<int> &nums, int target)
    {
        if (nums.size() == 1)
        {
            if (target == nums[0])
                return 0;
            else
                return -1;
        }

        int k = nums.size() >> 1;
        for (int i = 1; i < nums.size(); ++i)
            if (nums[i] < nums[i - 1])
            {
                k = i;
                break;
            }

        int ret;
        if (target >= nums[0] && target <= nums[k - 1])
            ret = binarySearch(nums, target, 0, k - 1);
        else if (target >= nums[k] && target <= nums.back())
            ret = binarySearch(nums, target, k, nums.size() - 1);
        else
            return -1;

        if (nums[ret] == target)
            return ret;
        else
            return -1;
    }

    int solve()
    {
        vector<int> nums = {1, 3, 4, 5, 6, 7};
        // sortColors(nums);
        // topKFrequent(nums, 2);
        // auto res = findKthLargest(nums, 4);
        // auto res = findKthLargest_myheap(nums, 4);

        // auto res = findPeakElement(nums);
        // auto res = searchRange(nums, 1);
        // auto res = merge(nums);
        auto res = search(nums, 3);

        return 0;

        // vector<int> nums = {0,0,0,0};
        // vector<vector<int>> mat = {{0,1,1,0},{1,2,1,4},{3,5,1,1}};
        // setZeroes(mat);
        // vector<string> strs = {"eat", "eat", "tea", "tan", "ate", "nat", "bat"};
        // auto res = groupAnagrams(strs);
        // auto res = lengthOfLongestSubstring("dvdf");
        // auto res = longestPalindrome("bb");
        // auto res = increasingTriplet(vector<int>({1,2,1,3}));
        // cout << res << endl;
        // auto res = addTwoNumbers(forward_list<int>({9,9,9,9,9,9,9}), forward_list<int>({9,9,9,9}));
        // auto res = oddEvenList(forward_list<int>({1,2,3,4,5,6,7}));
        // ListNode* list = nullptr;
        // auto res = oddEvenList(list);
        // ListNode* headA = new ListNode(1);
        // ListNode* headB = headA;
        // auto res = getIntersectionNode(headA, headB);

        //-------------------tree generater--------------------
        // TreeNode *root = new TreeNode(5);
        // root->left = new TreeNode(3);
        // root->right = new TreeNode(6);
        // root->left->left = new TreeNode(2);
        // root->left->right = new TreeNode(4);
        // // root->right->left = new TreeNode(15);
        // // root->right->right = new TreeNode(7);
        //-----------------------------------------------------

        // auto res = inorderTraversal(root);
        // auto res = zigzagLevelOrder(root);

        // vector<int> preorder = {3, 9, 20, 15, 7};
        // vector<int> inorder = {9, 3, 15, 20, 7};
        // auto res = buildTree(preorder, inorder);

        //-------------------tree generater 2--------------------
        // Node *root = new Node(1);
        // root->left = new Node(2);
        // root->right = new Node(3);
        // root->left->left = new Node(4);
        // root->left->right = new Node(5);
        // root->right->left = new Node(6);
        // root->right->right = new Node(7);
        //-------------------------------------------------------
        // root = connect(root);
        // int k = 2;
        // auto res = kthSmallest(root, k);

        // vector<vector<char>> grid = {
        //     {'1', '0', '1', '1', '0'},
        //     {'1', '1', '0', '1', '0'},
        //     {'1', '1', '0', '0', '0'},
        //     {'0', '0', '0', '0', '1'}};
        // auto res = numIslands(grid);

        // auto res = letterCombinations("456");
        // auto res = generateParenthesis(4);

        // vector<int> nums = {1,2,3};
        // auto res = permute(nums);
        // auto res = subsets(nums);

        // vector<vector<char>> board = {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
        // string word = "ABCB";
        // vector<vector<char>> board = {{'A', 'B', 'C', 'E'}, {'A', 'A', 'C', 'S'}, {'B', 'D', 'E', 'E'}};
        // string word = "AAB";
        // auto res = exist(board, word);
    }
};

int main()
{
    Solution s;
    s.solve();
    return 0;
}