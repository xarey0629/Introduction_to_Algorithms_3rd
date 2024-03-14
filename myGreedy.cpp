#include <iostream>
#include <vector>
#include <climits>
#include <string>
#include <cmath>
#include <queue>   // priority queue
#include <utility> // pair
using namespace std;
vector<int> ans;

void RECURSIVE_ACTIVITY_SELECTOR(vector<int> &s, vector<int> &f, int k, int n)
{
    int m = k + 1; // k -> last ended activity, m -> first allowed activity after k.
    while (m <= n && s[m] < f[k])
    {
        m++;
    }
    if (m <= n)
    {
        ans.push_back(m);
        RECURSIVE_ACTIVITY_SELECTOR(s, f, m, n);
    }
    else
        return;
}

void GREEDY_ACTIVITY_SELECTOR(vector<int> &s, vector<int> &f)
{
    // int n = s.size() - 1;
    ans.push_back(1);
    int k = 1;
    for (int i = 2; i < s.size(); i++)
    {
        if (s[i] >= f[k])
        {
            k = i;
            ans.push_back(i);
        }
    }
    return;
}

struct treeNode
{
    int freq;
    char ch;
    treeNode *left = nullptr;
    treeNode *right = nullptr;

    treeNode(int freq, char ch) : freq(freq), ch(ch), left(nullptr), right(nullptr) {}
};

struct Compare
{
    bool operator()(const treeNode *a, const treeNode *b) const
    {
        return a->freq > b->freq; // True -> swap the order. False -> remain the order.
    }
};

treeNode *HUFFMAN(vector<treeNode *> &nodes)
{
    priority_queue<treeNode *, vector<treeNode *>, Compare> minHeap(nodes.begin(), nodes.end());
    s for (int i = 0; i < nodes.size() - 1; i++)
    {
        treeNode *newNode = new treeNode(0, 'X');

        newNode->left = minHeap.top();
        minHeap.pop();

        newNode->right = minHeap.top();
        minHeap.pop();

        newNode->freq = newNode->left->freq + newNode->right->freq;
        minHeap.push(newNode);
        // cout << "This frequency: " << newNode->freq << endl;
        // cout << "Left frequency: " << newNode->left->freq << " Right frequency: " << newNode->right->freq << endl;
    }
    // while (!minHeap.empty())
    // {
    //     cout << minHeap.top()->freq << ", " << minHeap.top()->ch << endl;
    //     minHeap.pop();
    // }
    return minHeap.top();
}

void PRINT_HUFFMAN_CODE(treeNode *root, string str)
{
    if (root->ch != 'X')
    {
        cout << root->ch << ": " << str << endl;
    }
    else
    {
        PRINT_HUFFMAN_CODE(root->left, str + "0");
        PRINT_HUFFMAN_CODE(root->right, str + "1");
    }
    return;
}

int main()
{
    // vector<int> s = {0, 1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12};
    // vector<int> f = {0, 4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16};
    // // RECURSIVE_ACTIVITY_SELECTOR(s, f, 0, s.size() - 1);
    // GREEDY_ACTIVITY_SELECTOR(s, f);

    // for (auto num : ans)
    // {
    //     cout << num << " ";
    // }

    // Huffman Code
    vector<char> letters = {'a', 'b', 'c', 'd', 'e', 'f'};
    vector<int> freq = {45, 13, 12, 16, 9, 5};
    vector<treeNode *> nodes;
    for (int i = 0; i < letters.size(); i++)
    {
        nodes.push_back(new treeNode(freq[i], letters[i]));
    }

    treeNode *root = HUFFMAN(nodes);
    PRINT_HUFFMAN_CODE(root, "");

    return 0;
}