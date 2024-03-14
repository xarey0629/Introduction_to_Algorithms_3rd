#include <iostream>
#include <vector>
#include <climits>
#include <string>
#include <cmath>
using namespace std;

int CUT_ROD(vector<int> &p, int n)
{
    if (n == 0)
        return 0;
    int q = INT_MIN;
    for (int i = 1; i <= n; i++)
    {
        q = max(q, p[i] + CUT_ROD(p, n - i));
    }
    return q;
}

// Top-down "memoization"
int MEMOIZED_CUT_ROD_AUX(vector<int> &p, int n, vector<int> &r)
{
    int q;
    if (r[n] >= 0) // check the table
        return r[n];
    if (n == 0) // Base case
        q = 0;
    else
    {
        q = INT_MIN;
        for (int i = 1; i <= n; i++)
        {
            q = max(q, p[i] + MEMOIZED_CUT_ROD_AUX(p, n - i, r)); // Top-down recursive
        }
    }
    r[n] = q; // memoized
    return q;
}
int MEMOIZED_CUT_ROD(vector<int> &p, int n)
{
    vector<int> r(n + 1, INT_MIN);
    return MEMOIZED_CUT_ROD_AUX(p, n, r);
}

// Bottom-up
int BOTTOM_UP_CUT_ROD(vector<int> &p, int n)
{
    vector<int> r(n + 1, INT_MIN);
    r[0] = 0;
    for (int i = 1; i <= n; i++) // Bottom-up
    {
        int q = INT_MIN;
        for (int j = 1; j <= i; j++)
        {
            q = max(q, p[j] + r[i - j]);
        }
        r[i] = q;
    }
    return r[n];
}

// Matrix chain problems
void MATRIX_CHAIN_ORDER(vector<int> &p, vector<vector<int>> &m, vector<vector<int>> &s)
{
    // Time -> O(n^3), Space -> O(n^2);
    int n = p.size() - 1;
    // memos
    // vector<vector<int>> m(n + 1, vector<int>(n + 1, INT_MAX));
    // vector<vector<int>> s(n + 1, vector<int>(n + 1, INT_MIN));

    for (int i = 1; i <= n; i++)
    {
        m[i][i] = 0;
    }
    for (int l = 2; l <= n; l++)
    {
        for (int i = 1; i <= n - l + 1; i++)
        {
            int j = i + l - 1;
            // m[i][j] = INT_MAX;
            int q;
            for (int k = i; k <= j - 1; k++)
            {
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    // return m[1][n];
}

void PRINT_OPTIMAL_PARENS(vector<vector<int>> &s, int i, int j)
{
    if (i == j)
        cout << "A" << i;
    else
    {
        cout << "(";
        PRINT_OPTIMAL_PARENS(s, i, s[i][j]);
        PRINT_OPTIMAL_PARENS(s, s[i][j] + 1, j);
        cout << ")";
    }
}

void LCS_LENGTH(string x, string y)
{
    int m = x.size(), n = y.size();
    vector<vector<int>> b(m + 1, vector<int>(n + 1, INT_MAX));
    vector<vector<int>> c(m + 1, vector<int>(n + 1, INT_MAX));

    for (int i = 0; i <= m; i++)
    {
        c[i][0] = 0;
    }
    for (int i = 0; i <= n; i++)
    {
        c[0][i] = 0;
    }

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (x[i - 1] == y[j - 1])
            {
                c[i][j] = c[i - 1][j - 1] + 1;
                // b[i][j] = b[i - 1][j - 1];
            }
            else if (c[i - 1][j] >= c[i][j - 1])
            {
                c[i][j] = c[i - 1][j];
                // b[i][j] =
            }
            else
            {
                c[i][j] = c[i][j - 1];
            }
        }
    }
    cout << c[x.size()][y.size()];
    return;
}

// Optimal BST
void root_DFS(vector<vector<int>> &root, int l, int r)
{
    if (l > r)
        return;
    if (l == r)
    {
        cout << root[l][r] << ' ';
    }
    else
    {
        int rootNode = root[l][r];
        root_DFS(root, l, rootNode - 1);
        cout << rootNode << ' ';
        root_DFS(root, rootNode + 1, r);
    }
    return;
}

void OPTIMAL_BST(vector<int> &p, vector<int> &q, int n)
{
    vector<vector<int>> e(n + 2, vector<int>(n + 1));
    vector<vector<int>> w(n + 2, vector<int>(n + 1));
    vector<vector<int>> root(n + 1, vector<int>(n + 1));

    for (int i = 1; i <= n + 1; i++)
    {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }
    // for (int i = 1; i <= n; i++)
    // {
    //     root[i][i] = i;
    // }
    for (int l = 1; l <= n; l++)
    {
        for (int i = 1; i <= n - l + 1; i++)
        {
            int j = i + l - 1;
            e[i][j] = INT_MAX;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            int lf, ri;
            if (l == 1)
            {
                lf = i, ri = j;
            }
            else
            {
                lf = root[i][j - 1];
                ri = root[i + 1][j];
            }
            for (int r = lf; r <= ri; r++)
            {
                int t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j])
                {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }
    cout << "Optimal cost: " << e[1][n] << endl;
    cout << "Root: " << root[1][n] << endl;

    // Call Tree Structure
    root_DFS(root, 1, n);

    return;
}

int main()
{
    // vector<int> price = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    // int n = 30;
    // cout << "Recursive with memoization: " << MEMOIZED_CUT_ROD(price, n) << '\n';
    // cout << "Recursive with memoization(Bottom-up): " << BOTTOM_UP_CUT_ROD(price, n) << '\n';
    // cout << "Recursive: " << CUT_ROD(price, n) << '\n';
    // // cout << price[10];

    // vector<int> p = {30, 35, 15, 5, 10, 20, 25};
    // int n = p.size() - 1;
    // vector<vector<int>> m(n + 1, vector<int>(n + 1, INT_MAX));
    // vector<vector<int>> s(n + 1, vector<int>(n + 1, INT_MIN));

    // MATRIX_CHAIN_ORDER(p, m, s);
    // PRINT_OPTIMAL_PARENS(s, 1, n);
    // for (auto vec : m)
    // {
    //     for (auto num : vec)
    //     {
    //         cout << num << " ";
    //     }
    //     cout << '\n';
    // }

    // LCS
    // string x = "ABCBDAB", y = "BDCABA";
    // LCS_LENGTH(x, y);

    // Optimal BST
    vector<int> p = {INT_MAX, 15, 10, 5, 10, 20};
    vector<int> q = {5, 10, 5, 5, 5, 10};
    OPTIMAL_BST(p, q, 5);

    return 0;
}
