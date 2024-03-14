#include <iostream>
#include <climits>
using namespace std;

class myStack
{
private:
    /* data */
    int *arr;
    int capacity;
    int top = 0;

public:
    myStack(int n)
    {
        this->capacity = n;
        this->arr = new int[this->capacity]{0};
    }
    ~myStack()
    {
        delete[] this->arr;
    }

    bool empty()
    {
        if (top == 0)
            return true;
        return false;
    }

    void push(int num)
    {
        if (top >= capacity)
        {
            cout << "Stack Overflow.\n";
        }
        else
        {
            arr[top++] = num;
        }
        return;
    }

    int pop()
    {
        if (this->empty())
        {
            cout << "Stack Underflow.\n";
            return INT_MIN;
        }
        else
        {
            return arr[--top];
        }
    }

    void printStack()
    {
        if (!empty())
        {
            cout << "The stack has: ";
            for (int i = 0; i < top; i++)
            {
                cout << arr[i] << ' ';
            }
            cout << '\n';
        }
        else
        {
            cout << "The stack is empty.\n";
        }
    }
};

int main()
{
    myStack s(5);
    s.pop();
    for (int i = 0; i < 6; i++)
    {
        s.push(i);
        s.printStack();
    }
    s.printStack();
    for (int i = 0; i < 3; i++)
    {
        s.pop();
        s.printStack();
    }

    return 0;
}