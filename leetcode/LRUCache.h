#include <iostream>
#include <list>
#include <map>

class LRUCache
{
private:
    uint16_t cap;
    std::list<std::pair<int, int>> cache;
    std::map<int, std::list<std::pair<int, int>>::iterator> hash;

public:
    LRUCache(int capacity) : 
        cap(capacity), 
        cache(), 
        hash() {}

    int get(int key)
    {
        auto ret = hash.find(key);
        if (ret == hash.end())
            return -1;
        else
        {
            if (ret->second != cache.begin())
            {
                cache.splice(cache.begin(), cache, ret->second);
                ret->second = cache.begin();
            }
            return cache.begin()->second;
        }
    }

    void put(int key, int value)
    {
        auto ret = hash.find(key);
        if (ret != hash.end())
        {
            cache.splice(cache.begin(), cache, ret->second);
            cache.begin()->second = value;
            hash[key] = cache.begin();
        }
        else
        {
            if (cache.size() == cap)
            {
                int tmp = cache.back().first;
                cache.pop_back();
                cache.push_front({key, value});
                hash[key] = cache.begin();
                hash.erase(tmp);
            }
            else
            {
                cache.push_front({key, value});
                hash[key] = cache.begin();
            }
        }
    }
};