#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main () {
    vector<string> v;
    string input;
    
    while(1) {
        getline(cin, input);
        /*we can read from the keyboard strings containing spaces and symbols*/
        if(input == "END") break;
        v.push_back(input);
        /*pushing at the end of the vector*/
    }
    if(v.size() < 5) cout << "not enough elements" << endl;
    /*if the size of the vector were to be smaller than 5 v[5] would not be
    included*/
    else { string aux = v[1];
           v[1] = v[4];
           v[4] = aux;
           }
    if(!v.empty()) {
        v[v.size() - 1] = "???";
        
    }
    for(size_t i = 0; i < v.size(); i ++) {
        if (i > 0) cout << ", ";
        /*if we got pass the first element*/
        cout << v[i];
    }
    cout << endl;
    typedef vector<string>::iterator vecIt;
    for(vecIt vit = v.begin(); vit != v.end(); vit ++) {
        if (vit != v.begin()) cout << "; ";
        cout << *vit;
        /*iterators are pointers so we dereference them to output their value
        on screen*/
    }
    cout << endl;

    typedef vector<string>::reverse_iterator rvecIt;
    /*initialising a reverse iterator*/
    for(rvecIt rvit = v.rbegin(); rvit != v.rend(); rvit ++) 
    /*rbegin() stands for reverse begin and it is a reverse iterator to the 
    end of the vector
    rend() stands for reverse end and it is a reverse iterator to the beginning
    of the list*/
    {   if(rvit != v.rbegin()) cout << " ";
        cout << *rvit;
    }
    cout << endl;
    return 0;
}