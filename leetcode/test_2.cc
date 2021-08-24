#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <set>
#include <list>

#include "MinStack.h"
using namespace std;

class ShufSol;

class Solutions
{
public:
    int solution(int n)
    {
        // write code here
        if (n < 10)
            return n;
        for (int i = 9; i > 1; --i)
        {
            if (n % i == 0)
            {
                auto res = solution(n / i);
                if (res != -1)
                    return res * 10 + i;
            }
        }
        return -1;
    }

    int reverse(int x)
    {
        bool flag = false;
        if (x < 0)
        {
            x = abs(x);
            flag = true;
        }
        int sol = 0;
        while (x > 0)
        {
            int i = x % 10;
            if (sol > INT_MAX / 10)
                return 0;
            sol = sol * 10 + i;
            x = x / 10;
        }
        if (flag)
            sol *= -1;
        return sol;
    }

    bool isPalindrome(string s)
    {
        auto it = s.begin();
        auto itr = --s.end();
        while (itr - it > 0)
        {
            while ((itr - it > 0) && (ispunct(*it) || isspace(*it)))
                ++it;
            while ((itr - it > 0) && (ispunct(*itr) || isspace(*itr)))
                --itr;
            if (tolower(*it) == tolower(*itr))
            {
                ++it;
                --itr;
            }
            else
                return false;
        }
        return true;
    }

    int myAtoi(string s)
    {
        auto it = s.begin();
        bool sign = false;
        while (isspace(*it))
            ++it;
        if (ispunct(*it))
        {
            if (*it == '-')
            {
                sign = true;
                ++it;
            }
            else if (*it == '+')
                ++it;
        }
        int sol = 0;
        while (it != s.end() && isdigit(*it))
        {
            if (sol < INT_MIN / 10)
            {
                if (sign)
                    return INT_MIN;
                else
                    return INT_MAX;
            }
            int num = *it - '0';
            if (sol == INT_MIN / 10)
            {
                if (sign && num >= 8)
                    return INT_MIN;
                if (!sign && num >= 7)
                    return INT_MAX;
            }
            sol = sol * (10) - num;
            ++it;
        }
        if (!sign)
            if (sol != INT_MIN)
                sol *= -1;
            else
                return INT_MAX;
        return sol;
    }

    int strStr(string haystack, string needle)
    {
        if (needle.empty())
            return 0;
        if (needle.size() > haystack.size())
            return -1;
        auto it_n = needle.cbegin();
        auto it_h = haystack.cbegin();
        while (it_n != needle.cend() && it_h != haystack.cend())
        {
            if (*it_h == *it_n)
            {
                ++it_h;
                ++it_n;
            }
            else
            {
                it_h = it_h - (it_n - needle.cbegin()) + 1;
                it_n = needle.cbegin();
            }
        }
        if (it_n == needle.cend())
            return it_h - needle.size() - haystack.cbegin();
        return -1;
    }

    string countAndSay_gen(string s)
    {
        string gen;
        char curr = s.front();
        auto it = s.begin();
        auto it_last = s.begin();
        for (; it != s.end(); ++it)
        {
            if (curr != *it)
            {
                gen.push_back('0' + it - it_last);
                gen.push_back(curr);
                curr = *it;
                it_last = it;
            }
        }
        gen.push_back('0' + it - it_last);
        gen.push_back(curr);
        return gen;
    }

    string countAndSay(int n)
    {
        string s = "1";
        while (n - 1)
        {
            s = countAndSay_gen(s);
            --n;
        }
        return s;
    }

    string longestCommonPrefix(const vector<string> &strs)
    {
        string res = "";
        for (int idx = 0; idx < strs[0].size(); ++idx)
        {
            bool flag = true;
            for (auto &str : strs)
            {
                if (str[idx] != strs[0][idx])
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
                res.push_back(strs[0][idx]);
            else
                break;
        }
        return res;
    }

    //-----------------------------rob------------------------------------------
    using vi_it = std::vector<int>::iterator;
    int rob(vector<int> &nums)
    {
        vector<int> mem(nums.size(), -1);
        return rob_helper(nums.begin(), nums.end(), mem);
    }
    int rob_helper(vi_it it_beg, vi_it it_end, vector<int> &mem)
    {
        if (it_end - it_beg == 1)
            return *it_beg;
        else if (it_end - it_beg == 2)
            return max(*it_beg, *(it_beg + 1));
        else
        {
            vi_it it_back1 = it_end - 1;
            vi_it it_back2 = it_end - 2;
            int res1, res2;
            if (mem[it_back2 - it_beg - 1] == -1)
            {
                res1 = rob_helper(it_beg, it_back2, mem);
                mem[it_back2 - it_beg - 1] = res1;
                res1 = res1 + *it_back1;
            }
            else
                res1 = mem[it_back2 - it_beg - 1] + *it_back1;
            if (mem[it_back1 - it_beg - 1] == -1)
            {
                res2 = rob_helper(it_beg, it_back1, mem);
                mem[it_back1 - it_beg - 1] = res2;
            }
            else
                res2 = mem[it_back1 - it_beg - 1];
            return max(res1, res2);
        }
    }
    //-------------------------------------------------------------

    vector<string> fizzBuzz(int n)
    {
        vector<string> res(n);
        for (int idx = 0; idx < n; ++idx)
        {
            int i = idx + 1;
            if (i % 3 == 0)
                res[idx].insert(res[idx].size(), "Fizz");
            if (i % 5 == 0)
                res[idx].insert(res[idx].size(), "Buzz");
            if (res[idx].empty())
                while (i > 0)
                {
                    int num = i % 10;
                    i = (i - num) / 10;
                    char numc = '0' + num;
                    res[idx].insert(0, 1, numc);
                }
        }
        return res;
    }

    int countPrimes(int n)
    {
        int cnt = 0;
        vector<bool> notPrime(n, false);
        for (int i = 2; i < n; ++i)
        {
            if (notPrime[i])
                continue;
            ++cnt;
            for (int j = 2 * i; j < n; j += i)
            {
                notPrime[j] = true;
            }
        }
        return cnt;
    }

    int romanToInt(string s)
    {
        int res = 0;
        map<string, int> romanMap;
        romanMap.insert({"I", 1});
        romanMap.insert({"V", 5});
        romanMap.insert({"X", 10});
        romanMap.insert({"L", 50});
        romanMap.insert({"C", 100});
        romanMap.insert({"D", 500});
        romanMap.insert({"M", 1000});
        romanMap.insert({"IV", 4});
        romanMap.insert({"IX", 9});
        romanMap.insert({"IV", 4});
        romanMap.insert({"IX", 9});
        romanMap.insert({"XL", 40});
        romanMap.insert({"XC", 90});
        romanMap.insert({"CD", 400});
        romanMap.insert({"CM", 900});

        for (auto it = s.begin(); it != s.end();)
        {
            if (s.end() - it >= 2)
            {
                auto ret = romanMap.find(string(it, it + 2));
                if (ret != romanMap.end())
                {
                    res += ret->second;
                    it += 2;
                    continue;
                }
            }
            res += romanMap.find(string(it, it + 1))->second;
            ++it;
        }
        return res;
    }

    int hammingWeight(uint32_t n)
    {
        int res = 0;
        while (n > 0)
        {
            n = n & (n - 1);
            res++;
        }
        return res;
    }

    int hammingDistance(int x, int y)
    {
        int res = 0;
        int temp = x ^ y;
        while (temp > 0)
        {
            temp = temp & (temp - 1);
            res++;
        }
        return res;
    }

    uint32_t reverseBits(uint32_t n)
    {
        uint32_t res = 0;
        for (int i = 0; i < 32; ++i)
        {
            res <<= 1;
            if (n & 1)
                ++res;
            n >>= 1;
        }
        return res;
    }

    vector<vector<int>> generate(int numRows)
    {
        vector<vector<int>> triangle;
        if (numRows <= 0)
            return triangle;
        triangle.push_back({});
        triangle[0].push_back(1);
        for (int i = 1; i < numRows; ++i)
        {
            triangle.push_back({});
            triangle[i].push_back(1);
            for (int j = 1; j < triangle[i - 1].size(); ++j)
            {
                triangle[i].push_back(triangle[i - 1][j] + triangle[i - 1][j - 1]);
            }
            triangle[i].push_back(1);
        }
        return triangle;
    }

    bool isValid(string s) {
        map<char, char> cmap({{'(',')'},{'{','}'},{'[',']'}});
        list<char> check;
        for(auto &c : s){
            if(cmap.find(check.back())->second == c)
            {
                check.pop_back();
            }else{
                check.push_back(c);
            }
        }
        if(check.empty())
            return true;
        else
            return false;
    }

    int missingNumber(vector<int>& nums) {
        int missing = nums.size();
        for(int i = 0; i< nums.size(); ++i)
        {
            missing ^= i ^ nums[i];
        }
        return missing;
    }

    void rotate(vector<vector<int>> &matrix)
    {
        int sz = matrix.size();
        for (int i = 0; i < sz / 2; ++i)
        {
            for (int j = i; j < sz - 1 - i; ++j)
            {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[sz - 1 - j][i];
                matrix[sz - 1 - j][i] = matrix[sz - 1 - i][sz - 1 - j];
                matrix[sz - 1 - i][sz - 1 - j] = matrix[j][sz - 1 - i];
                matrix[j][sz - 1 - i] = temp;
            }
        }
    }

    int solve()
    {
        //cout << reverse(-2147483648) << endl;
        //cout << abs(-2147483648) << endl;
        //1534236469
        //cout << isPalindrome("A man, a plan, a canal: Panama") << endl;
        //cout << myAtoi("2147483649") << endl;
        //cout << strStr("mississip","issip") << endl;
        //cout << countAndSay(4) << endl;
        //cout << longestCommonPrefix({"cir","car"}) << endl;
        //vector<int> nums = {114,117,207,117,235,82,90,67,143,146,53,108,200,91,80,223,58,170,110,236,81,90,222,160,165,195,187,199,114,235,197,187,69,129,64,214,228,78,188,67,205,94,205,169,241,202,144,240};

        //cout << rob(nums) << endl;
        // ShufSol *s = new ShufSol({1,2,3});
        // for(auto i : s->shuffle())
        //     cout << i << " ";
        // cout << endl;
        // for(auto i : s->shuffle())
        //     cout << i << " ";
        // cout << endl;
        // for(auto i : s->shuffle())
        //     cout << i << " ";
        // cout << endl;

        // MinStack min;
        // min.pop();
        // // min.push(1);
        // // min.push(2);
        // for(int i = 100; i > 0; --i){
        //     min.push(i);
        // }
        // cout << min.getMin();
        // min.pop();

        // auto res = fizzBuzz(155);
        // cout << countPrimes(5000000);
        // cout << romanToInt("MCMXCIV");
        //cout << reverseBits(0x00000001);
        // generate(5);
        // cout << isValid("{[]}");
        vector<vector<int>> matrix = {
            {5,1,9,11},
            {2,4,8,10},
            {13,3,6,7},
            {15,14,12,16}};
        return 0;
    }
};

class ShufSol
{
public:
    ShufSol(const vector<int> &nums) : numbers(nums) {}

    /** Resets the array to its original configuration and return it. */
    vector<int> reset()
    {
        return numbers;
    }

    /** Returns a random shuffling of the array. */
    vector<int> shuffle()
    {
        vector<int> shuf_nums(numbers);
        auto sz = shuf_nums.size();
        // time_t now = time(0);
        // srand(now);
        for (int i = 0; i < sz; ++i)
        {
            int swaptar = rand() % (sz - i) + i;
            auto temp = shuf_nums[swaptar];
            shuf_nums[swaptar] = shuf_nums[i];
            shuf_nums[i] = temp;
        }
        return shuf_nums;
    }

private:
    vector<int> numbers;
};

int main()
{
    Solutions sol;
    sol.solve();
}
