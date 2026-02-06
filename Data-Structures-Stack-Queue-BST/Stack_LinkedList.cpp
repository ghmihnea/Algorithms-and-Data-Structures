#include <iostream>
#include <stack>
using namespace std;

template <typename T>
class Stack {
private:
        struct StackNode {
            T data;
            StackNode* next;

            StackNode(T x, StackNode* n = nullptr) 

            {
                data = x;
                next = n;
            }
        };
        StackNode *top;
        int size;
        int current_size;
public: 
        void push(T x);
        T pop();
        bool empty();
        void print();
        Stack(int new_size);
        Stack();
        /*empty constructor: no size limit*/
};
template <typename T>
Stack<T>::Stack(int new_size) {
    size = new_size;
    current_size = 0;
    top = nullptr;
    /*when the parametherized
    constructor is called an empty stack
    will be created with a limitted size*/
}
template <typename T>
Stack<T>::Stack() {
    size = -1;
    top = nullptr;
    current_size = 0;
    /*default constructor -> no size limit*/
}
template <typename T> 
void Stack<T>::push(T x) {
    if(size != -1 && current_size >= size) {
        cout << "Stack overflow!" << endl;
        return;
        /*if the stack has a size limit and
        the current size exceeds the limit*/
    }
    StackNode* new_node = new StackNode(x, top);
    /*creating new node with data: x and pointing to the 
    top(due to FIFO principles,  we always place on top
    and remove from the top)*/
    top = new_node;
    /*the top will get the value
    of the newly introduced top*/
    current_size ++;

}
template <typename T>
T Stack<T>::pop() {
    if(empty()) {
        cout << "Stack underflow!" << endl;
        return T();
    }
    StackNode* temp = top;
    /*create temporary 
    pointer to the top to avoid memory leak*/
    T popped = top->data;

    top = top->next;
    delete temp;
    current_size --;

    return popped;
}
template <typename T>
bool Stack<T>::empty() {
    if(top == nullptr){
        return true;
    }
    else return false;
}
template <typename T>
void Stack<T>::print() {
    if(empty()) {
        cout << "Stack is empty" << endl;
        return;
    }
    StackNode* current_node = top;
    /*initialising a current node
    pointing at the top*/
    while(current_node) {
        cout << current_node->data << "->";
        current_node = current_node->next;
        /*printing from top to bottom*/
    }  
    cout << "NULL" << endl;
}
int main() {
    Stack<int> stack(5);

    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);
    stack.push(6);
    cout << "print stack with limited size: " << endl;
    stack.print();

    cout << "popping: " << stack.pop() << endl;
    stack.print();

    Stack<int> stackWithNoSizeRestrictions;
    stackWithNoSizeRestrictions.push(12);
    stackWithNoSizeRestrictions.push(13);
    stackWithNoSizeRestrictions.push(16);
    stackWithNoSizeRestrictions.push(45);

    cout << "print stack with no size restrictions" << endl;
    stackWithNoSizeRestrictions.print();

    return 0;
}
