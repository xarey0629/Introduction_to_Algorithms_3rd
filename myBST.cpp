#include <iostream>
#include <climits>
using namespace std;

void inorder_Traversal(TreeNode *root)
{
    if (root)
    {
        inorder_Traversal(root->left);
        cout << root->key;
        inorder_Traversal(root->right);
    }
    return;
}

TreeNode *tree_Search(TreeNode *root, int target)
{
    if (root->key == NULL || root->key == target)
        return root;
    else
    {
        if (target > root->key)
            return tree_Search(root->right);
        else
            return tree_Search(root->left);
    }
}

TreeNode *Iterative_TreeSearch(TreeNode *root, int target)
{
    TreeNode *x = root;
    while (x != NULL && x->key != target)
    {
        if (target > x->key)
            x = x->right;
        else
            x = x->left;
    }
    return x;
}

TreeNode *tree_Minimum(TreeNode *root)
{
    while (root->left)
        root = root->left;
    return root;
}

TreeNode *tree_Maximum(TreeNode *root)
{
    while (root->right)
        root = root->right;
    return root;
}

TreeNode *tree_Successor(TreeNode *root)
{
    if (root->right)
        return tree_Minimum(root->right);
    TreeNode *y = x->parent;
    while (y != NULL && x == y->right)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

TreeNode *tree_Predecessor(TreeNode *root)
{
    if (root->left)
        return tree_Maximum(root->left);
    TreeNode *y = x->parent;
    while (y != NULL && x == y->left)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

TreeNode *tree_Insert(TreeNode *root, TreeNode *newNode)
{
    TreeNode *y = NULL, *x = root;
    while (x != NULL)
    {
        y = x;
        x = x->key > newNode->key ? x->left : x->right;
    }
    newNode->parent = y;
    if (y == NULL) // Edge case: empty tree.
        root = newNode;
    else
    {
        if (newNode->key < y->key)
            y->left = newNode;
        else
            y->right = newNode;
    }
    return y;
}

void transplant(TreeNode *root, TreeNode *u, TreeNode *v)
// u is replaced by v.
// Note: Only process links btw parent and itself.
{
    if (u->parent == NUll) // u is root.
        root = v;
    else if (u == u->parent->left) // y is left child.
        u->parent->left = v;
    else
        u->parent->right = v; // u is right child.

    if (v != NULL) // make sure v is not NULL.
        v->parent = u->parent;
}

void tree_Delete(TreeNode *root, TreeNode *z)
{
    // Case 1, 2: z has only one child.
    if (z->left == NULL)
        transplant(root, z, z->right);
    else if (z->rigth == NULL)
        transplant(root, z, z->left);
    // --------------------------------
    else // Case 3, 4(two children). Find a successor y to replace z.
    {
        TreeNode *y = tree_Successor(z);
        if (y->parent != z)
        {
            transplant(root, y, y->right);
            // deal with links btw y and z's right child.
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        // links btw z's left child.
        y->left = z->left;
        y->left->parent = y;
    }
}

int main()
{

    return 0;
}