#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

int main () {
    string input;
    getline(cin, input);
    /*this will take into account white spaces*/

    stringstream ss(input);
    vector<int> A;
    int n;

    while(ss >> n) {
        A.push_back(n);
        /*making use of string stream to break the line
        down into numbers which we proceed to introduce in the
        array*/
    }
    int dim = A.size();
    vector<int> subseqLength(dim, 1);
    /*vector for storing the last Index of the longest subsequence*/
    vector<int> prevInd(dim, -1);

    for(int i = 0; i < dim; i ++) {
        for(int j = 0; j < i; j ++) 
        /*for each pair(i, j), i < j*/
        {
            if(A[i] > A[j] && subseqLength[j] + 1 > subseqLength[i])
            /*if the elements are in ascending order and if the subsequence
            ending at A[i] is longer than the current known subsequence ending 
            at A[i]*/
            {
                subseqLength[i] = subseqLength[j] + 1;
                prevInd[i] = j;
            }
        }
    }
    int maxLength = subseqLength[0];
    int lastInd = 0;
    for(int i = 1; i < dim; i ++) {
        if(subseqLength[i] > maxLength) {
            maxLength = subseqLength[i];
            /*finding the longest subsequence*/
            lastInd = i;
            /*storing the index of the last element of the longest subsequence*/
        }
    }
    vector<int> List;
    for(int i = lastInd; i != -1; i = prevInd[i]) 
    /*i starts from the last index and then then it takes
    the value of the element found at index i in prevInd*/
    {
        List.push_back(A[i]);
    }
    reverse(List.begin(), List.end());
    for(int i = 0; i < List.size(); i ++) {
        cout << List[i];
        if(i != List.size() - 1) cout << " ";
    }
    cout << endl;
    return 0;
}
