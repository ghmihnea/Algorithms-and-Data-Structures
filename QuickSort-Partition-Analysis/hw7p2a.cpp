#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void threeWayQuickSort(vector<int>& v, int left, int right) {
    if(right - left < 1) return; /*if there is not enough elemenrs*/
    if(right - left == 1) 
    /*if there are 2 elements*/
    {
        if(v[left] > v[right]) swap(v[left], v[right]);
        /*we output them sorted*/
        return;
    }
    if(v[left] > v[left + 1]) swap(v[left], v[left + 1]);
    int pivot1 = v[left];
    int pivot2 = v[left + 1];
    /*we choose the 2 pivots to follow the rule:
    pivot1 <= pivot2*/

    vector<int> low, mid, high;
    /*we create three vectors: in low we place the elements
    < pivot 2, in mid we place el > pivot1 and < pivot2 and in high
    we place > pivot 2*/
    for(int i = left + 2; i <= right; i ++) {
        if(v[i] < pivot1) low.push_back(v[i]);
        else if(v[i] > pivot2) high.push_back(v[i]);
        else mid.push_back(v[i]);
    }
    int index = left;
    for(int num:low) v[index ++] = num;
    v[index++] = pivot1;
    for(int num:mid) v[index ++] = num;
    v[index++] = pivot2;
    for(int num:high) v[index ++] = num;
    /*above we placed the element in order in our vector v
    starting from the el from the low vector, we place pivot1 then
    the mid vector, pivot2, and finally the el of vector high*/

    int piv1ind = left + low.size();
    int piv2ind = piv1ind + 1 + mid.size();
    /*we store the indeces of the 2 pivots*/

    threeWayQuickSort(v, left, piv1ind - 1);
    threeWayQuickSort(v, piv1ind + 1, piv2ind - 1);
    threeWayQuickSort(v, piv2ind + 1, right);
    /*pivots are not included in the recursive calls 
    of the functions*/
}

int main () {
    vector<int> v = {4, 2, 9, 8 ,5, 1};

    cout << "vector before applying quicksort" << endl;
    for( int num : v){
        cout << num << " ";
    }
    cout << endl;
    threeWayQuickSort(v, 0, 5);
    cout << "vectpr after applying quicksort" << endl;
    for(int num : v) {
        cout << num << " ";
    }
    cout << endl;

    return 0;

}