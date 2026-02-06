#include <iostream>
#include <stack>
using namespace std;

template <typename T>
class Queue {
    private:
        stack<T> s1, s2;
    public:
        void enqueue(T x);
        T dequeue();
        bool empty();
        void print();
};
template <typename T>
void Queue<T>::enqueue(T x) {
    s1.push(x);
    /*we push the elements in the 
    1st stack following FIFO principle(specific to stacks)*/
    cout << "Enqueued: " << x;
    cout << endl;
}
template <typename T>
T Queue<T>::dequeue() {
    if(s1.empty() && s2.empty()) {
        cout << "queue underflow" << endl;
        return T();
        /*if both stacks are empty we
        encounter stack underflow*/
    }
    if(s2.empty()) 
    /*s2 is empty thus
    we transfer elements from s1 to s2
    this ensures the FIFO rule, as the first element in s1
    will be placed on top of s2 and will be dequed first*/
    {
        while(!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }
    } 
    T frontofqueue = s2.top();
    s2.pop();
    cout << "Dequeued: " << frontofqueue << endl;
    return frontofqueue;
}
template <typename T>
bool Queue<T>::empty() {
    return s1.empty() && s2.empty();
}
template <typename T>
void Queue<T>::print() {
    if(empty()) {
        cout << "queue is empty" << endl;
        return;
    }
    stack<T> temp_s2 = s2;
    /*creating a tempoarary stack
    in which we will store the elements
    from the s2 stack*/
    while(!temp_s2.empty()) {
        cout << temp_s2.top() << " ";
        temp_s2.pop();
        /*since s2 is correctly ordered we
        can print form to to bottom and display
        them in the correct queue order*/
    }
    stack<T> temp_s1 = s1;
    /*creating a temporary stack that will
    store the elements from s1(the ones which were not
    introduced in s2 respecting the stack order)*/
    stack<T> inv_s1;

    while(!temp_s1.empty()) {
        inv_s1.push(temp_s1.top());
        /*placing in inv_s1 the elements from s1 to revrse they order,
        so that they follow the queue's FIFO order*/
        temp_s1.pop();
    }
    while(!inv_s1.empty()) {
        cout << inv_s1.top() << " ";
        /*printing*/
        inv_s1.pop();
    }
    cout << endl;
}
int main() {
    Queue<int> queue;

    queue.enqueue(1);
    queue.enqueue(1);
    queue.enqueue(5);
    queue.enqueue(8);

    cout << "Queue: " << endl;
    queue.print();

    queue.dequeue();
    queue.print();

    queue.dequeue();
    queue.dequeue();

    queue.empty();
    queue.print();
    
    return 0;
}