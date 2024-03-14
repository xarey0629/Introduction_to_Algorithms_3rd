#include <iostream>
#include <stdlib.h>
#include <climits>
#include <vector>
using namespace std;

void merge(vector<int> &nums, int p, int q, int r)
{
    // int n1 = q - p + 1;
    // int n2 = r - q - 1;
    vector<int> L(nums.begin() + p, nums.begin() + q + 1);
    vector<int> R(nums.begin() + q + 1, nums.begin() + r + 1);
    L.push_back(INT_MAX);
    R.push_back(INT_MAX);
    int lCur = 0, rCur = 0;
    for (int i = p; i <= r; i++)
    {
        nums[i] = L[lCur] < R[rCur] ? nums[i] = L[lCur++] : nums[i] = R[rCur++];
    }
    return;
}

void mergeSort(vector<int> &nums, int p, int r)
{
    if (p < r)
    {
        int q = (p + r) / 2;
        // ------------------ Recursive Case;
        mergeSort(nums, p, q);
        mergeSort(nums, q + 1, r);

        // ------------------ Base Case;
        merge(nums, p, q, r);
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
    mergeSort(nums, 0, nums.size() - 1);
    for (auto num : nums)
    {
        cout << num << ' ';
    }

    return 0;
}