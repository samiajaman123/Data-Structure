#include <iostream>
#include <stack>
using namespace std;

struct N
{
    int d;
    N *next;
    N(int v) : d(v), next(nullptr) {}
};

class Q
{
private:
    N *front, *rear;

public:
    Q() : front(nullptr), rear(nullptr) {}

    void enq(int v)
    {
        N *newN = new N(v);
        if (!rear)
        {
            front = rear = newN;
        }
        else
        {
            rear->next = newN;
            rear = newN;
        }
    }

    int deq()
    {
        if (!front)
        {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        int v = front->d;
        N *temp = front;
        front = front->next;
        if (!front)
            rear = nullptr;
        delete temp;
        return v;
    }

    void printFrontToRear()
    {
        N *temp = front;
        cout << "Queue (Front to Rear): ";
        while (temp)
        {
            cout << temp->d << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void reverse()
    {
        stack<int> samia;
        while (front)
        {
            samia.push(deq());
        }
        while (!samia.empty())
        {
            enq(samia.top());
            samia.pop();
        }
    }

    void printRearToFront()
    {
        reverse();
        printFrontToRear();
        reverse();
    }
};

int main()
{
    Q queue;
    int n, val;

    cout << "Enter the number of elements to enqueue: ";
    cin >> n;

    cout << "Enter the elements:\n";
    for (int i = 0; i < n; ++i)
    {
        cin >> val;
        queue.enq(val);
    }

    cout << "\nQueue printed from Front to Rear:\n";
    queue.printFrontToRear();

    cout << "\nQueue printed from Rear to Front:\n";
    queue.printRearToFront();

    return 0;
}

