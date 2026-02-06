#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

const int totalAschii = 256;

void padWords(vector<string>& wordList, int maxLen) {
    for(int i = 0; i < wordList.size(); i++) {
        while(wordList[i].length() < maxLen) {
            wordList[i].push_back(' '); 
            /*we add empty spaces to make all of our words
            the same length(this will make the comparison process
            possible)*/ 
        }
    }
}

void removeBlanks(vector<string>& wordList) {
    for(int i = 0; i < wordList.size(); i++) {
        while(!wordList[i].empty() && wordList[i].back() == ' ') {
            wordList[i].pop_back(); 
            /*after building the sorted array
            we remove the empty spaces we have
            added previously*/
        }
    }
}

void countingSortByChar(vector<string>& wordList, int pos) {
    int dim = wordList.size();
    vector<string> sorted(dim);
    /*we create an array in which we will place, in order, the
    elements from the given array*/
    int count[totalAschii] = {0};
    /*we initiaze the counting array for the occurance 
    of each element with 0*/
    
    for(int i = 0; i < dim; i++) {
        int ch = wordList[i][pos];
        count[int(ch)]++;
        /*count each occurance of each element at 'pos' and store it in the
        'count' array (count[97] = stores the occurances of 'a' at position
        'pos' across all words*/
    }

    for(int i = 1; i < totalAschii; i++) {
        count[i] += count[i - 1];
        /*we now compute the starting index for
        each letter by accumulation of previous counts*/
    }

    for(int i = dim - 1; i >= 0; i--) {
        int ch = wordList[i][pos];
        int index = count[int(ch)] - 1;
        /*to place the character in the correct 
        position we have to keep in mind that we start
        from 0 index so we have to substract 1 from the 
        count array*/
        sorted[index] = wordList[i];
        /*we place the character in its appropiate position
        in the sorted array*/
        count[int(ch)]--;
        /*decrease the count to update the position
        for the next occurance */
    }

    for(int i = 0; i < dim; i++) {
        wordList[i] = sorted[i];
    }
}

void RadixSort(vector<string>& wordList) {
    int dim = wordList.size();
    int maxLen = 0;

    for(int i = 0; i < dim; i++) {
        if(wordList[i].length() > maxLen) {
            maxLen = wordList[i].length();
        }
    }

    padWords(wordList, maxLen);
    /*we make all the words the same size as the
    longest one*/

    for(int pos = maxLen - 1; pos >= 0; pos--) {
        countingSortByChar(wordList, pos);
        /*we sort the elements by each character, starting
        from the end to keep the algorithm stable*/
    }

    removeBlanks(wordList);  
    /*we remove the blank spaces from our sorted vector*/
}

int main() {
    vector<string> wordList = { "word", "category", "cat", "new", "news", 
                                "world", "bear", "at", "work", "time" };

    cout << "elements before sorting: " << endl;
    for(int i = 0; i < wordList.size(); i++) {
        cout << wordList[i] << " ";
    }
    cout << endl;

    RadixSort(wordList);

    cout << "Elements after sorting: " << endl;
    for(int i = 0; i < wordList.size(); i++) {
        cout << wordList[i] << " ";
    }
    cout << endl;

    return 0;
}
