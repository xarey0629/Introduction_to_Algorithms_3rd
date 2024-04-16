#include <iostream>
#include <stdlib.h>
#include <climits>
#include <vector>
using namespace std;

void merge(vector<int> &nums, int l, int mid, int r)
{
    // Space Complexity O(N);
    vector<int> L(nums.begin() + l, nums.begin() + mid + 1);     // [begin, end)
    vector<int> R(nums.begin() + mid + 1, nums.begin() + r + 1); // [begin, end)
    L.push_back(INT_MAX);                                        // Sentinel
    R.push_back(INT_MAX);                                        // Sentinel

    int lCur = 0, rCur = 0;
    for (int i = l; i <= r; i++)
    {
        nums[i] = L[lCur] < R[rCur] ? nums[i] = L[lCur++] : nums[i] = R[rCur++];
    }
    return;
}

// Post-order
void mergeSort(vector<int> &nums, int l, int r)
{
    if (l >= r)
        return;

    int mid = (l + r) / 2;
    // ------------------ Recursive Case in a post-order DFS style.
    mergeSort(nums, l, mid);
    mergeSort(nums, mid + 1, r);
    // ------------------ Base Case: Merge Two Chunks.
    merge(nums, l, mid, r);

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