 #include <string>
 #include <list>

 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Codec
{
public:
    // Encodes a tree to a single string.
    std::string serialize(TreeNode *root)
    {
        std::string res;
        std::list<TreeNode *> nodelist({root});
        while (!nodelist.empty())
        {
            if (nodelist.front())
            {
                int num = nodelist.front()->val;
                res.append(std::to_string(num) + ",");
                nodelist.push_back(nodelist.front()->left);
                nodelist.push_back(nodelist.front()->right);
            }
            else
                res.append("x,");
            nodelist.pop_front();
        }
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(std::string data)
    {
        std::vector<TreeNode *> nodelist;
        for (auto it = data.begin(); it != data.end();)
        {
            std::string numStr;
            while (*it != ',')
            {
                numStr.push_back(*it);
                ++it;
            }
            ++it;
            if (numStr != "x")
                nodelist.push_back(new TreeNode(stoi(numStr)));
            else
                nodelist.push_back(nullptr);
        }
        int j = 1;
        for (int i = 0; i < nodelist.size(); ++i)
        {
            if (nodelist[i] != nullptr)
            {
                nodelist[i]->left = nodelist[j++];
                nodelist[i]->right = nodelist[j++];
            }
        }
        return nodelist[0];
    }
};