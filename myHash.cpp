#include <iostream>
#include <climits>
using namespace std;

int direct_address_search(vector<int> &T, int k)
{
    return T[k];
}

void direct_address_insert(vector<int> &T, auto x)
{
    T[x->key] = x;
}

void direct_address_delete(vector<int> &T, auto x)
{
    T[x->key] = NULL;
}

// Open Addressing
void hash_Insert(vector<int> &T, int k)
{
    int i = 0, m = T.size();
    while (i < m)
    {
        int j = hash_function(k, i);
        if (T[j] == NULL || T[j] == DELETED) // DELETED is a flag showing the element is deleted.
        {
            T[j] == k;
            return j;
        }
        i++;
    }
    throw std::runtime_error("Hash table overflow.");
}

int hash_Search(vector<int> &T, int k)
{
    int i = 0, m = T.size();
    while (i < m)
    {
        int j = hash_function(k, i);
        if (T[j] == NULL)
            return NULL;
        if (T[j] == k)
            return j;
        i++;
    }
    return NULL;
}

void hash_Deleted(vector<int> &T, int k)
{
    int i = 0, m = T.size();
    while (j < m)
    {
        int j = hash_function(k, i);
        if (T[j] != NULL && T[j] != DELETED)
        {
            if (T[hash_function(k, i + 1)] == NULL)
                T[j] = NULL;
            else
                T[j] = DELETED;
        }
    }
    throw std::runtime_error("Could not find key " << k << " in the table.");
}

int main()
{

    return 0;
}