#include <iostream>
#include <climits>
using namespace std;

class MyCircularDeque
{
private:
    int *arr;
    int capacity;
    int cnt; // counter
    int head, back;

public:
    MyCircularDeque(int k)
    {
        this->capacity = k;
        this->cnt = 0;
        this->arr = new int[this->capacity]{0};
        this->head = k - 1, this->back = 0;
    }

    bool insertFront(int value)
    {
        if (!isFull())
        {
            this->arr[this->head] = value;
            this->head = (this->head - 1 + capacity) % capacity; // Important skill to plus capacity to handle negative cases.
            this->cnt++;
            return true;
        }
        return false;
    }

    bool insertLast(int value)
    {
        if (!isFull())
        {
            this->arr[back] = value;
            this->back = (this->back + 1) % this->capacity;
            cnt++;
            return true;
        }
        return false;
    }

    bool deleteFront()
    {
        if (!isEmpty())
        {
            this->head = (this->head + 1) % this->capacity;
            cnt--;
            return true;
        }
        return false;
    }

    bool deleteLast()
    {
        if (!isEmpty())
        {
            this->back = (this->back - 1 + this->capacity) % this->capacity;
            cnt--;
            return true;
        }
        return false;
    }

    int getFront()
    {
        if (isEmpty())
            return -1;
        else
        {
            return arr[(head + 1) % capacity];
        }
    }

    int getRear()
    {
        if (isEmpty())
            return -1;
        else
        {
            return arr[(back - 1 + capacity) % capacity];
        }
    }

    bool isEmpty()
    {
        return cnt == 0;
    }

    bool isFull()
    {
        return cnt == capacity;
    }

    void printDeque()
    {
        if (!isEmpty())
        {
            cout << "The Deque has: ";
            for (int i = 0; i < capacity; i++)
            {
                cout << arr[i] << ' ';
            }
            cout << '\n';
        }
        else
        {
            cout << "The Deque is empty.\n";
        }
    }
};

int main()
{
    return 0;
}