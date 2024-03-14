#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

void insertionSort(vector<int> &nums)
{
    for (int j = 1; j < nums.size(); j++)
    {
        int key = nums[j];
        int i = j - 1;

        while (i >= 0 && key < nums[i])
        {
            nums[i + 1] = nums[i];
            i--;
        }
        nums[i + 1] = key;
    }
    return;
}

int main()
{
    vector<int> nums;

    for (int i = 0; i < 10; i++)
    {
        nums.push_back(rand() % 10);
        cout << nums[i] << ' ';
    }
    cout << '\n';
    insertionSort(nums);
    for (auto num : nums)
    {
        cout << num << ' ';
    }

    return 0;
}