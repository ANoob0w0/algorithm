#include <string>
#include <list>
#include <unordered_map>
#include <unordered_set>

class AllOne
{
private:
    typedef std::pair<int, std::unordered_set<std::string>> Node;
    std::list<Node> valuelist;
    std::unordered_map<std::string, std::list<Node>::iterator> hash;

public:
    /** Initialize your data structure here. */
    AllOne()
    {
    }

    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(std::string key)
    {
        if (key.empty())
            return;
        auto ret = hash.find(key);
        if (hash.end() == ret)
        {
            if (valuelist.begin()->first != 1)
                valuelist.push_front({1, {}});
            valuelist.begin()->second.insert(key);
            hash[key] = valuelist.begin();
        }
        else
        {
            int cnt = ret->second->first + 1;
            auto it = ret->second;
            it->second.erase(key);
            if(it->second.empty())
                it = valuelist.erase(it);
            while (it != valuelist.end() && it->first < cnt)
                ++it;
            if (it != valuelist.end() && it->first == cnt)
            {
                it->second.insert(key);
                hash[key] = it;
            }
            else
            {
                it = valuelist.insert(it, 1, {cnt,{}});
                it->second.insert(key);
                hash[key] = it;
            }
        }
    }

    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(std::string key)
    {
        auto ret = hash.find(key);
        if (hash.end() == ret)
            return;
        if (ret->second->first == 1)
        {
            ret->second->second.erase(key);
            if (ret->second->second.empty())
                valuelist.pop_front();
            hash.erase(key);
        }
        else
        {
            int cnt = ret->second->first - 1;
            auto it = ret->second;
            auto it_c = ret->second;
            it->second.erase(key);
            while (it != valuelist.begin() && it->first > cnt)
                --it;
            if(it->first == cnt)
            {
                it->second.insert(key);
                hash[key] = it;
            }
            else
            {
                it = valuelist.insert(++it, 1, {cnt,{}});
                it->second.insert(key);
                hash[key] = it;
            }
            if(it_c->second.empty())
                it_c = valuelist.erase(it_c);
        }
    }

    /** Returns one of the keys with maximal value. */
    std::string getMaxKey()
    {
        if(hash.empty())
            return "";
        return *(valuelist.back().second.begin());
    }

    /** Returns one of the keys with Minimal value. */
    std::string getMinKey()
    {
        if(hash.empty())
            return "";
        return *(valuelist.front().second.begin());
    }
};