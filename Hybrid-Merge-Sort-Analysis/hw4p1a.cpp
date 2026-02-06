#include <iostream>
#include <vector>

using namespace std;

void InsertionSort (vector<int>& v, int low, int high) {
    for(int j = low + 1; j <= high; j ++) 
    /*j starts from the given low + 1, and is incremented until the
    high given*/
    {
        int key = v[j];
        /*v[j] is the element we want to insert into the correct position*/
        int i = j - 1;
        /*v[i] will start right before v[j] and we will decrement i*/
        while( i >= low && v[i] > key) 
        {
            v[i + 1] = v[i];
            /*the effect of this will be to shift the larger value to right*/
            i --;
        }
        v[i + 1] = key; 
        /*after the while loop i is one position smaller than where place it
        so we add 1*/
    }
}
void Merge(vector<int>& v, int low, int mid, int high) {
    int size = high - low + 1;
    vector<int> temp(size);

    int i = low; /*the first half*/
    int j = mid + 1;/*the second half*/
    int k = 0;/*used for the temporary vector*/

    while(i <= mid && j<= high) 
    /*while the first none of the halves are surpassed*/
    {
        if(v[i] <= v[j]) {
            temp[k] = v[i];
            i ++;
        }
        else {
            temp[k] = v[j];
            j ++;
        }
        k ++;
        /*we add the smaller element in the temoporary vector,
        increment in the half from where we took the value to reach the
        next value and also increment the position for temporary*/
     }
     while(i <= mid){
        temp[k] = v[i];
        i ++;
        k ++;
        /*while there still are elements in the first half*/
     }
     while(j <= high) {
        temp[k] =v[j];
        j ++;
        k ++;
        /*while there still are elements in the 2nd half*/
     }

     for(i = low; i <= high; i ++) {
        v[i] = temp[i - low];
        /*we insert the changes in our given vector*/
     }
}
void HybridMergeSort(vector<int> &v, int low, int high, int k) {
    int mid;
    if(high - low + 1 <= k){
        InsertionSort(v, low, high);
        /*if the the sub array of dimension smaller or equal than k 
        we make use of the insertion sort*/
    }
    else {
        mid = (low + high) / 2;
        HybridMergeSort(v, low, mid, k);
        HybridMergeSort(v, mid + 1, high, k);
        Merge(v, low, mid, high);
        /*otherwise we keep dividing the halves in 2 and sort them
        in ascenfing order until the dimension is k*/
    }
}
int main() {
    vector<int> v ={7, 8, 4, 2, 0, 5, 12, 11, 10, 15};
    cout << "Vector before hybrid merging : " << endl;
    for(int num : v){
        cout << num << " ";
    }
    cout << endl;

    int dim = v.size();
    int k = 3;
    cout << "Vector after hybrid merging : " << endl;
    HybridMergeSort(v, 0, dim - 1, k);
    for(int num : v){
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
