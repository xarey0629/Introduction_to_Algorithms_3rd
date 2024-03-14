#include <iostream>
#include <climits>
using namespace std;

struct myNode
{
    myNode *prev;
    myNode *next;
    int key;
    int value;

    // Constructor
    myNode(int key, int val = 0)
    {
        this->key = key;
        this->value = val;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

class myLinkedList
{
private:
    /* data */
    myNode *nil;

public:
    myLinkedList()
    {
        this->nil = new myNode(INT_MIN);
        this->nil->next = this->nil;
        this->nil->prev = this->nil;
    }
    ~myLinkedList()
    {
        delete this->nil;
    }

    // Methods
    myNode *List_Search(int key)
    {
        myNode *cur = this->nil->next;
        this->nil->key = key; // Assign key to sentinel, to neglect cur != L->nil
        while (cur->key != key)
        // while (cur != this->nil && cur->key != key)
        {
            cur = cur->next;
        }
        return cur;
    }

    void List_Insert(int key)
    {
        myNode *newNode = new myNode(key);
        newNode->next = this->nil->next;
        this->nil->next->prev = newNode;
        newNode->prev = this->nil;
        this->nil->next = newNode;
        return;
    }

    void List_Delete(int key)
    {
        myNode *cur = this->List_Search(key);
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        return;
    }

    void printList()
    {
        if (this->nil->next != this->nil)
        {
            myNode *cur = this->nil->next;
            while (cur != this->nil)
            {
                cout << cur->key << " -> ";
                cur = cur->next;
            }
        }
        else
            cout << "The list is empty.\n";
        return;
    }
};

int main()
{
    myLinkedList *list = new myLinkedList();
    for (int i = 1; i <= 5; i++)
    {
        list->List_Insert(i);
    }

    list->List_Delete(3);
    list->printList();

    return 0;
}