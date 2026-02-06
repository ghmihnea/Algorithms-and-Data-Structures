#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int HoarePartition(vector<int> &v, int low, int high) 
/*source: Wikipedia*/
{
    int pivot = v[low];/*we consider the pivot to be the first elemnt*/
    int i = low - 1;/*index before first element*/
    int j = high + 1;/*index after the last element*/

    while(1) {
        do {
            i ++;/*we firstly move 
            i into a valid position*/
        } while (v[i] < pivot);
        /*the loop stops when we find an el larger
        than the pivot on the left side(<= pivot)*/
        do {
            j --;/*moving j into 
            a valid position*/
        } while (v[j] > pivot);
        /*the loop stops when we find an el smaller
        than the pivot on the right side(>= pivot)*/
        if( i >= j) return j;
        /*j represents where the
        left and right sections are divided*/
        swap(v[i], v[j]);
        /*ensures that the elements
        are moved to the correct side relative 
        to the pivot*/
    }
}
void QuickSort(vector<int> &v, int low, int high){
    if(low < high){
        int p = HoarePartition(v, low, high);
        QuickSort(v, low, p);
        QuickSort(v, p + 1, high);
    }
}
int main () {
    vector<int> v = {4, 2, 9, 8 ,5, 1};

    cout << "vector before applying quicksort" << endl;
    for( int num : v){
        cout << num << " ";
    }
    cout << endl;
    QuickSort(v, 0, 5);
    cout << "vectpr after applying quicksort" << endl;
    for(int num : v) {
        cout << num << " ";
    }
    cout << endl;

    return 0;

}