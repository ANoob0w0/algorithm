#include <vector>
#include <iostream>
#include <set>
#include <map>

using namespace std;

int removeDuplicates(vector<int> &nums)
{
    auto it = nums.begin();
    auto it_n = nums.begin();
    while (it != nums.end())
    {
        if (*it != *it_n)
        {
            ++it_n;
            *it_n = *it;
        }
        ++it;
    }
    return it_n - nums.begin();
}

vector<int> plusOne(vector<int> &digits)
{
    for (auto rit = digits.rbegin(); rit != digits.rend(); ++rit)
    {
        if (*rit != 9)
        {
            ++*rit;
            return digits;
        }
        else
        {
            *rit = 0;
        }
    }
    digits.push_back(0);
    digits[0] = 1;
    return digits;
}

bool isValidSudoku(vector<vector<char>> &board)
{
    vector<set<char>> rowset(9);
    vector<set<char>> colset(9);
    vector<set<char>> boxset(9);
    for (int row = 0; row < 9; ++row)
    {
        for (int col = 0; col < 9; ++col)
        {
            if (board[row][col] == '.')
                continue;
            if(!rowset[row].insert(board[row][col]).second)
                return false;
            if(!colset[col].insert(board[row][col]).second)
                return false;
            if(!boxset[row/3*3+col/3].insert(board[row][col]).second)
                return false;
        }
    }

    return true;
}

int add(int n)
{
    static int i = 100;
    i += n;
    return i;
}

int main()
{
    // vector<vector<char>> board =
    //     {
    //         {'5', '.', '.', '.', '7', '1', '.', '.', '.'},
    //         {'6', '.', '.', '.', '9', '5', '.', '.', '.'},
    //         {'0', '9', '8', '.', '.', '.', '.', '6', '.'},
    //         {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
    //         {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
    //         {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
    //         {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
    //         {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
    //         {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

    // cout << isValidSudoku(board);
    cout << add(10) << endl;
    cout << add(10) << endl;
    return 0;
}
