#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int MedianOfThree(vector<int> &v, int low, int high)
/*source : Wikipedia*/
{
    int mid = (high + low) /2;
    /*we compute the index of the middle element*/
    if(v[low] > v[mid]) {
        swap(v[low], v[mid]);
    }
    if(v[low] > v[high]) {
        swap(v[low], v[high]);
    }
    if(v[high] > v[mid]) {
        swap(v[high], v[mid]);
    }
    /*after these swaps the order based on values will be:
    v[low] < v[high] < v[mid] cause we want to store the 
    median value in the highest position*/
    return v[high];
    /*we return the median value*/
}
int LomotoPartition(vector<int> &v, int low, int high) {
    MedianOfThree(v, low, high);
    /*after calling this function v[high will represent the
    pivot*/
    int pivot = v[high];
    /*store the value of the pivot in a new variable*/
    int i = low - 1;
    /*i will be right before the 
    first element of the sequence*/

    for(int j = low; j < high; j ++) {
        if(v[j] <= pivot) 
        /*we place the elements <= pivot on
        its left side*/
        {
            i ++;
            /*we allocate space for the left side*/
            swap(v[i], v[j]);
            /*we swap v[j to the left]*/
        }
    }
    swap(v[i + 1], v[high]);
    /*we swap the pivot(v[high]) in the correct position*/
    return i + 1;
    /*we retrun the position of the pivot*/
}
void QuickSort(vector<int> &v, int low, int high){
    if(low < high) 
    {
        int pivot = LomotoPartition(v, low, high);
        QuickSort(v, low, pivot - 1);
        /*this will sort elements from the left side, <= pivot*/
        QuickSort(v, pivot + 1, high);
        /*this will store the elements in the right side, >= pivot*/
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