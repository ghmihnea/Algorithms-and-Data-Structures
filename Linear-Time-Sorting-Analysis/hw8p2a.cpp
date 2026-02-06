#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

void print(vector<int>& a) {
    for (int i = 0; i < a.size(); i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

int Digit(int n, int exp) {
    return (n / exp) % 10;
}

int Max(vector<int>& a) {
    int max = a[0];
    for (int i = 1; i < a.size(); i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    return max;
}

void MostSignificantBitRadixSort(vector<int>& a, int left, int right, int exp) {
    if(left >= right || exp == 0) return;
    /*if there is only one element left or if all digits
    have been processed (exp == 0)(exp has to be a power of 10)*/

    vector<vector<int> > buckets(10);
    /*creating 10 buckets to store the digits
    from 0 to 9*/

    for (int i = left; i <= right; i ++) {
        int digit = Digit(a[i], exp);
        buckets[digit].push_back(a[i]);
        /*we partition the digits in the adequate bucket*/
    }
    int index = left;
    for(int i = 0; i < 10; i ++) {
        for(int j = 0; j < buckets[i].size(); j ++) {
            a[index] = buckets[i][j];
            /*we place in a[index] the ordered elements
            (as substracted from the buckets)*/
            index ++;
            /*we increment the index making room for the next element*/
        }
    }

    index = left;
    for(int i = 0; i < 10; i ++) {
        if(!buckets[i].empty()) {
            MostSignificantBitRadixSort(a, index, index + buckets[i].size() - 1,
        exp / 10);
        /*by executing this we recursively sort each bucket
        based on the next lower place value(exp / 10) and update the index 
        range appropiately(from index to index + bucket.size() - 1)*/
            index += buckets[i].size();
        }
    }
}
void HollerithRadixSort(vector<int>& a) {
    int max = Max(a);
    int exp = pow(10, floor(log10(max)));
    /*determine the largest place value (exp) by finding
    the highest power of 10 within the maximum number*/
    MostSignificantBitRadixSort(a, 0, a.size() - 1, exp);
    /*recursively sort the array(from start (0) to end (a.size() - 1))
    starting from the most significant digit and move to the next lower place value*/
}

int main() {
    vector<int> a = {10, 45, 56, 34, 2, 5, 6, 3, 2, 1};

    cout << "Unsorted array: " << endl;
    print(a);
    cout << endl;

    HollerithRadixSort(a);  

    cout << "Sorted array: " << endl;
    print(a);

    return 0;
}
