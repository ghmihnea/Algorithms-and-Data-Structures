#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void CountingSort(vector<int>& A) {
    int k = *max_element(A.begin(), A.end());
    /*k represents the maximum element of the array A*/
    int dim = A.size();
    vector<int> C(k + 1, 0);
    /*in C we will store the elements from 0 to k (k + 1 
    elements), initializing the array with k+1 values of 0*/
    vector<int> B(dim);
    /*in B we will store the elements of A sorted*/

    for(int j = 0; j < dim; j ++) {
        C[A[j]] ++;
        /*in C we store the number of occurances of
        each element from A*/
    }
    for(int i = 1; i <= k; i ++) {
        C[i] = C[i] + C[i - 1];
        /*we add C[i - 1] to C[i] to get the cumulative count(which gives
        the correct starting index for each element in the sorted array.)*/
    }
    for(int j = dim - 1; j >= 0; j --) {
        B[C[A[j]] - 1] = A[j];
        C[A[j]]--;
        /*now we store in B the sorted elements:
        *for B[C[A[j]] - 1]: we substract 1 to adjust to 0-based indexing
        *after placing A[j], we decremen C[A[j]] to move to
        the next free spot for the same number in B*/
    }
    A = B;
    /*copy the sorted elements in B back to A*/
}
int main() {
    vector<int> A = {9, 1, 6, 7, 6, 2 ,1};

    cout << "Array before getting sorted: " << endl;
    for(int num: A) {
        cout << num << " ";
    }
    cout << endl;

    CountingSort(A);
    cout << "Array after getting sorted: " << endl;
    for(int num : A) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
