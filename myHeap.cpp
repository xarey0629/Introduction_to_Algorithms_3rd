#include <iostream>
#include <climits>
#include <vector>

using namespace std;

int parent(int i)
{
    return i / 2;
}

int left(int i)
{
    return 2i;
}

int right(int i)
{
    return 2i + 1;
}

void MAX_HEAPIFY(vector<int> &A, int i)
{
    int l = left(i);
    int r = right(i);
    int largest;
    if (l <= A.size() - 1 && A[l] > A[i])
    {
        largest = l;
    }
    else
    {
        largest = i;
    }
    if (r <= A.size() - 1 && A[r] > A[largest])
    {
        largest = r;
    }
    if (largest != i)
    {
        swap(A[i], A[largest]);
        swap(largest, i);
        // A[i] = A[largest];
        MAX_HEAPIFY(A, largest);
    }
    return;
}

void BUILD_MAX_HEAP(vector<int> &A)
{
    for (int i = (A.size() - 1) / 2; i >= 0; i--)
    {
        MAX_HEAPIFY(A, i);
    }
}

void HEAP_SORT(vector<int> &A)
{
    BUILD_MAX_HEAP(A);
    for (int i = A.size() - 1; i >= 1; i--)
    {
        swap(A.front(), A.back());
        // A.heapSize--;
        MAX_HEAPIFY(A, 0);
    }
}

// Priority Queue
int HEAP_MAXIMUM(vector<int> &A)
{
    return A[0];
}

int HEAP_EXTRACT_MAX(vector<int> &A)
{
    if (A.size < 1)
    {
        throw runtime_error("Non valid heap size.");
    }
    int max = A[0];
    swap(A.front(), A.back());
    A.heapSize--;
    MAX_HEAPIFY(A, 0);
    return max;
}

void HEAP_INCREASE_KEY(vector<int> &A, int i, int key)
{
    if (key < A[i])
        throw runtime_error("New key is smaller than current key.");

    A[i] = key;
    while (i >= 0 && A[i] > A[parent[i]] {
        swap(A[i], A[parent(i)]);
        i = parent(i);
    })
        return;
}

void MAX_HEAP_INSERT(vector<int> &A, int key)
{
    A.heapSize++;
    A[A.heapSize] = INT_MIN;
    HEAP_INCREASE_KEY(A, A.heapSize, key);
}

// Main function
int main()
{
    return 0;
}