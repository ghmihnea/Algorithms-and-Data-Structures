#include <iostream>
#include <string>
#include "Stack.h"
using namespace std;

int main() {
    Stack<int> stackint;
    stackint.push(1);
    stackint.push(3);

    cout << "the top element is " << stackint.back()<< endl;
    int popped;
    if(stackint.pop(popped)) 
    /*if the stack is not empty*/
    {
        cout << "popped element is " << popped << endl;
    }
    cout << "number of entries " << stackint.getNumEntries() << endl;

    Stack<double> stackdouble(5);
    stackdouble.push(5.5);
    
    cout << "the top element is " << stackdouble.back() << endl;

    Stack<string> stackstring(10);
    stackstring.push("hello!");

    string poppedstring;
    if(stackstring.pop(poppedstring)){
        cout << "popped string is " << poppedstring << endl;
    }

    return 0;

}