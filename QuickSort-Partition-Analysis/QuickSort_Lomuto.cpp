#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int LomotoPartition(vector<int> &v, int p, int q) {
    int x = v[p];
    int i = p;
    /*we store both the value of the pivot and its index*/
    for(int j = p + 1; j <= q; j ++) 
    /*we start iterating from the first element after the pivot*/
    {
        if(v[j] <= x) 
        /*if an element after the pivot is smaller or equal than it*/
        {
            i ++;
            /*we allocate one more position for the
            side with smaller elements*/
            swap(v[i], v[j]);
            /*we swap the elememnts 
            for an ascending order*/
        }
    }
    swap(v[p], v[i]);
    /*after iterating through the loop we obtained 
    the correct poition for thw pivot so we place it in v[i]*/
    return i;
    /*we return the position in where we placed the pivot*/
}
void QuickSort(vector<int> &v, int p, int r){
    if(p < r) 
    /*while there's still more than one element 
    to compare*/
    {
        int q = LomotoPartition(v, p, r);
        /*we store in q the position of the pivot*/
        QuickSort(v, p, q - 1);
        /*this will sort elements from the left side, <= pivot*/
        QuickSort(v, q + 1, r);
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
