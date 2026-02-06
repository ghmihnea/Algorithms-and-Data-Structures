#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void insertionSort(vector<float>& bucket) {
    int dim = bucket.size();
    float key = 0;

    for(int i = 1; i < dim; i ++) {
        key = bucket[i];
        /*choosing the first element opf the 
        sequence as key*/
        int j = i - 1;
        while(j >= 0 && bucket[j] > key) {
            bucket[j + 1] = bucket[j];
            j --;
            /*comparing the key to the elements before
            it
            as long as there still is a j we can decrease
            and the ascending order is not respected the while
            will keep going*/
        }
        bucket[j + 1] = key;
        /*place the key in the correct position*/
        
    }
}
void bucketSort(vector<float>& A) {
    int dim = A.size();
    vector<vector<float> > buckets(dim);
    /*creating as many empty buckets as the numbers 
    of elements*/

    for(int i = 0; i < dim; i ++) {
        int index = A[i] * dim;
        /*splitting the elements
        of A in buckets*/
        buckets[index].push_back(A[i]);
        /*Example: if A[i] = 0.3 and dim = 10:
        index = 0.3 * 10, so A[i] will go to bucket three*/
    }
    for(int i = 0; i < dim; i ++) {
        sort(buckets[i].begin(), buckets[i].end());
        /*sort each bucket*/
    }
    int index = 0;
    for(int i = 0; i < dim; i ++) {
        for (int j = 0; j < buckets[i].size(); j ++) {
            A[index ++] = buckets[i][j];
            /*place in A the elements we have sorted and partitioned
            in buckets*/
        }
    }
}   
    int main() {
        vector<float> A = {0.9, 0.1, 0.6, 0.7, 0.6, 0.3, 0.1};
        cout << "Elements before being sorted: " << endl;
        for(float num : A) {
            cout << num << " ";
        }
        cout << endl;
        cout << "Elements after being sorted: " << endl;
        bucketSort(A);
        for(float num : A) {
            cout << num << " ";
        }
        cout << endl;
        return 0;
    }
