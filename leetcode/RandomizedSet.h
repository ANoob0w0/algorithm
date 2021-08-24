#include <vector>
#include <stdlib.h>
#include <unordered_map>


//----------------手写的hash表，超时---------------
// class RandomizedSet
// {
// public:
//     /** Initialize your data structure here. */
//     RandomizedSet() {}

//     /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
//     bool insert(int val)
//     {
//         unsigned hash = zigzag(val);
//         if (hash < hashtable.size())
//         {
//             if (hashtable[hash] >= 0)
//                 return false;
//         }
//         else
//             hashtable.resize(hash + 1, -1);
//         data.push_back(val);
//         hashtable[hash] = data.size() - 1;
//         return true;
//     }

//     /** Removes a value from the set. Returns true if the set contained the specified element. */
//     bool remove(int val)
//     {
//         auto valhash = zigzag(val);
//         if (valhash < hashtable.size() && hashtable[valhash] >= 0)
//         {
//             auto backhash = zigzag(data.back());
//             std::swap(data[hashtable[valhash]], data.back());
//             std::swap(hashtable[backhash], hashtable[valhash]);
//             if (hashtable.size() - 1 == valhash)
//                 hashtable.pop_back();
//             else
//                 hashtable[valhash] = -1;
//             data.pop_back();
//         }
//         else
//             return false;
//         return true;
//     }

//     /** Get a random element from the set. */
//     int getRandom()
//     {
//         unsigned idx = rand() % data.size();
//         return data[idx];
//     }

// private:
//     std::vector<int> hashtable;
//     std::vector<int> data;

//     inline unsigned zigzag(int item)
//     {
//         return item >> 31 ^ ((unsigned)item << 1);
//     }

//     inline int unzigzag(unsigned z)
//     {
//         return z >> 1 ^ -(z & 1);
//     }
// };
//----------------------------------------------

class RandomizedSet
{
public:
    /** Initialize your data structure here. */
    RandomizedSet() {}

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val)
    {
        auto ret = hashtable.find(val);
        if (ret != hashtable.end())
            return false;
        else
        {
            data.push_back(val);
            hashtable.insert({val, data.size() - 1});
        }
        return true;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val)
    {
        auto ret = hashtable.find(val);
        if (ret == hashtable.end())
            return false;
        else
        {
            auto backhash = hashtable.find(data.back());
            std::swap(data[ret->second], data[backhash->second]);
            backhash->second = ret->second;
            hashtable.erase(ret);
            data.pop_back();
        }
        return true;
    }

    /** Get a random element from the set. */
    int getRandom()
    {
        unsigned idx = rand() % data.size();
        return data[idx];
    }

private:
    std::unordered_map<int, int> hashtable;
    std::vector<int> data;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */