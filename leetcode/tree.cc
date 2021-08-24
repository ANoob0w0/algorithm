#include <iostream>
#include <vector>
#include <deque>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

inline bool isValidBST_helper(TreeNode *root, long long max, long long min)
{
    if (!root)
        return true;
    if ((root->val >= max) || root->val <= min)
        return false;
    return isValidBST_helper(root->left, root->val, min) && isValidBST_helper(root->right, max, root->val);
}

bool isValidBST(TreeNode *root)
{
    long long max = LONG_MAX;
    long long min = LONG_MIN;
    return isValidBST_helper(root, max, min);
}

vector<vector<int>> levelOrder(TreeNode *root)
{
    vector<vector<int>> sol;
    if (!root)
        return sol;
    deque<TreeNode *> nodelist;
    nodelist.push_back(root);
    while (!nodelist.empty())
    {
        int levelNum = nodelist.size();
        sol.push_back(vector<int>());
        for (int i = 0; i < levelNum; ++i)
        {
            TreeNode *curr = nodelist.front();
            nodelist.pop_front();
            sol.back().push_back(curr->val);
            if (curr->left)
                nodelist.push_back(curr->left);
            if (curr->right)
                nodelist.push_back(curr->right);
        }
    }
    return sol;
}

TreeNode *sortedArrayToBST(vector<int>::iterator itbeg, vector<int>::iterator itend)
{
    if(itbeg == itend)
    {
        return nullptr;
    }
    int mid = (itend - itbeg)/2;
    TreeNode *root = new TreeNode(*(itbeg + mid));
    root->left = sortedArrayToBST(itbeg, itbeg + mid);
    root->right = sortedArrayToBST(itbeg+mid+1, itend);
    return root;
}

TreeNode *sortedArrayToBST(vector<int> &nums)
{
    if (!nums.size())
        return nullptr;
    return sortedArrayToBST(nums.begin(),nums.end());
}

int main()
{
    // TreeNode *root = new TreeNode(0);
    // TreeNode *lnode = new TreeNode(1);
    // TreeNode *rnode = new TreeNode(2);
    // TreeNode *lnode2 = new TreeNode(3);
    // TreeNode *rnode2 = new TreeNode(4);
    // TreeNode *lnode3 = new TreeNode(5);
    // TreeNode *rnode3 = new TreeNode(6);
    // root->left = lnode;
    // root->right = rnode;
    // lnode->left = lnode2;
    // lnode->right = rnode2;
    // rnode->left = lnode3;
    // rnode->right = rnode3;
    // auto res = levelOrder(root);
    vector<int> vec = {1,2,3,4,5};
    auto root = sortedArrayToBST(vec);
    auto levelvec = levelOrder(root);
    //cout << isValidBST(root) << endl;
    //cout << LONG_MAX <<" "<<LONG_MIN<<endl;
    return 0;
}