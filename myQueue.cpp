#include <iostream>
#include <climits>
using namespace std;

class myQueue
{
private:
    /* data */
    int capacity;
    int *arr;
    int head, tail;

public:
    myQueue(int n)
    {
        this->capacity = n + 1;
        this->arr = new int[this->capacity]{0};
        this->head = 0, this->tail = 0;
    }
    ~myQueue()
    {
        delete[] this->arr;
    }
    // Methods
    bool isEmpty()
    {
        return this->head == this->tail;
    }
    bool isFull()
    {
        return this->head == (this->tail + 1) % this->capacity;
    }
    void enQueue(int num)
    {
        if (!isFull())
        {
            this->arr[tail] = num;
            this->tail = (this->tail + 1) % this->capacity;
            cout << "enQueue number: " << num << " successfully.\n";
            return;
        }
        else
        {
            cout << "Queue overflow.\n";
        }
    }
    int deQueue()
    {
        if (!isEmpty())
        {
            int tmp = this->arr[this->head];
            cout << "deQueue number: " << this->arr[this->head] << " successfully.\n";

            this->head = (this->head + 1) % this->capacity;
            cout << "Head: " << head << " Tail: " << tail << '\n';
            // return arr[(head - 1) % capacity]; // Wrong! It return -1;
            return tmp;
        }
        else
        {
            cout << "Queue underflow.\n";
            return INT_MIN;
        }
    }
    void printQueue()
    {
        if (!isEmpty())
        {
            cout << "The queue has: ";
            for (int i = head; i < tail; i = (i + 1) % capacity)
            {
                cout << arr[i] << ' ';
            }
            cout << '\n';
        }
        else
        {
            cout << "The queue is empty.\n";
        }
    }
};

int main()
{
    myQueue q(5);
    q.deQueue();
    for (int i = 0; i < 6; i++)
    {
        q.enQueue(i);
        q.printQueue();
    }

    for (int i = 0; i < 5; i++)
    {
        q.deQueue();
        q.printQueue();
    }
    return 0;
}