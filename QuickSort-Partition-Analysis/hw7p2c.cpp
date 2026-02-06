#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

void threeWayQuickSort(vector<int>& v, int left, int right) {
    if(right - left < 1) return;
    if(right - left == 1) {
        if(v[right] < v[left])swap(v[right], v[left]);
        return;
    }
    int randind1 = left + rand() % (right - left + 1);
    int randind2 = left + rand() % (right - left + 1);
    /*choosing 2 random indeces*/

    while(randind1 == randind2) {
        randind2 = left + rand() % (right - left + 1);
    }
    if(v[randind1] > v[randind2]) swap (v[randind1], v[randind2]);
    int pivot1 = v[randind1];
    int pivot2 = v[randind2];
    /*ensuring that pivot1 <= pivot2 */

    vector<int> mid, low, high;
    for(int i = left; i <= right; i ++) 
    /*iterating from the lefttmost index
    to the rightmost one(< = right to include 
    all elements)*/
    {
        if(i == randind1 || i == randind2) continue;
        else if(v[i] < pivot1) low.push_back(v[i]);
        else if(v[i] > pivot2) high.push_back(v[i]);
        else mid.push_back(v[i]);
        /*we add the elements in their
        appropiate space disregarding the pivots*/
    }
    int ind = left;
    /*index starting from the leftmost side*/
    for(int num:low) v[ind++] = num;
    v[ind++] = pivot1;
    for(int num:mid) v[ind++] = num;
    v[ind++] = pivot2;
    for(int num:high) v[ind++] = num;

    int piv1ind = left + low.size();
    int piv2ind = piv1ind + 1 + mid.size();/*piv1ind + 1 because we want to 
    surpass the position where the 1st pivot is placed*/

    /*clearly indicating the positions of the 2 pivots after sorting(above)*/

    threeWayQuickSort(v, left, piv1ind - 1);
    threeWayQuickSort(v, piv1ind + 1, piv2ind - 1);
    threeWayQuickSort(v, piv2ind + 1, right);

}

int main () {
    srand(time(0));

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