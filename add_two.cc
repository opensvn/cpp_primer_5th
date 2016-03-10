#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

vector<int> add_two(vector<int> &nums, int target)
{
    for (decltype(nums.size()) i = 0; i != nums.size(); ++i)
    {
        int first_part = nums[i];
        int second_part = target - first_part;

        for (decltype(i) j = 0; j != nums.size(); ++j)
        {
            if (j == i) continue;
            if (nums[j] == second_part)
            {
                return i < j ? vector<int>({i+1, j+1}) : vector<int>({j+1, i+1});
            }
        }
    }

    return vector<int>();
}

template <typename T>
ostream &print(ostream &os, T &c)
{
    for (auto it = c.begin(); it != c.end(); ++it)
    {
        os << *it << " ";
    }
    return os;
}

int main()
{
    vector<int> ivec;
    srand(time(NULL));
    for (int i = 0; i < 10; ++i)
    {
        ivec.push_back(rand() % 100);
    }

    print(cout, ivec) << endl;

    int target = ivec[rand() % 10] + ivec[rand() % 10];

    cout << "target: " << target << endl;

    vector<int> result = add_two(ivec, target);
    print(cout, result) << endl;

    return 0;
}