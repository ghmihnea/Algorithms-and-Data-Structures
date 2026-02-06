#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {

    vector<string> v;
    string input;

    while(1) {
        cin >> input;
        if(input == "END") break;
        /*when END is entered by the user the program endless loop breaks*/
        v.push_back(input);
        /*while the loop is still going we make use of the predefined
        vector function push_back to add to the the words in the vector*/
    }

    for(size_t i = 0; i < v.size(); i ++){
        cout << v[i];
        if(i < v.size() - 1) cout << " ";
    }
    cout << endl;
    /*outputting the elements of the vecor using an index*/

    typedef vector<string>::iterator vecIt;
    /*this allows us to write vecIt instead of vector<string>::iterator*/
    for(vecIt vic = v.begin(); vic != v.end(); vic ++) {
        if(vic != v.begin()) cout << ", ";
        /*we add , before each word in the vector besides the first one*/

        cout << *vic;
        /*iterators are pointers so we have to dereference it to output
        the values*/
    }
    cout << endl;

    return 0;
}