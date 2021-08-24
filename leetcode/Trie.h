#include <string>
#include <vector>

class Trie {
private:
    std::vector<Trie*> node;
    bool isEnd;

public:
    /** Initialize your data structure here. */
    Trie() : node(26, nullptr), isEnd(false){

    }
    
    /** Inserts a word into the trie. */
    void insert(std::string word) {
        Trie* curr = this;
        for(auto c : word)
        {
            int idx = c - 'a';
            if(!curr->node[idx])
            {
                curr->node[idx] = new Trie();
            }
            curr = curr->node[idx];
        }
        curr->isEnd = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(std::string word) {
        Trie* curr = this;
        for(auto c : word)
        {
            int idx = c - 'a';
            if(curr->node[idx])
                curr = curr->node[idx];
            else
                return false;
        }
        return curr->isEnd ? true : false;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(std::string prefix) {
        Trie* curr = this;
        for(auto c : prefix)
        {
            int idx = c - 'a';
            if(curr->node[idx])
                curr = curr->node[idx];
            else
                return false;
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */