#include <iostream>
#include "LinkedList.h"
using namespace std;

int main() {
    LinkedList<int> intlinkedlist;
    intlinkedlist.AddFront(2);
    intlinkedlist.AddFront(4);
    intlinkedlist.AddBack(1);

    cout << "List elements ";
    intlinkedlist.printList();
    cout << endl;

    LinkedList<double> doublelinkedlist;
    doublelinkedlist.AddBack(1);
    doublelinkedlist.AddBack(3);
    doublelinkedlist.AddFront(0);

    cout << "First element " << doublelinkedlist.getFirst() << endl;
    cout << "Last element " << doublelinkedlist.getLast() << endl;

    LinkedList<string> stringlinkedlist;
    stringlinkedlist.AddFront("Constructor");
    stringlinkedlist.AddBack("University");
    stringlinkedlist.AddBack("Bremen");

    cout << "remove first element " << stringlinkedlist.removeFirst() << endl;
    cout << "remove last element " << stringlinkedlist.removeLast() << endl;

    cout << "list after removal : " << endl;
    stringlinkedlist.printList();

    cout << "number of elements : " << stringlinkedlist.getSize() << endl;

    return 0;
}