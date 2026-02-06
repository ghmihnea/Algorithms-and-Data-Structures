#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime> 
using namespace std;

int LomotoPartition(vector<int> &v, int p, int q) {
    int x = v[p];
    int i = p;
    /*we store both the value of the pivot and its index*/
    for(int j = p + 1; j <= q; j ++) 
    /*we start iterating from the first element after the pivot*/
    {
        if(v[j] <= x) 
        {
            i ++;
            swap(v[i], v[j]);
        }
    }
    swap(v[p], v[i]);
    return i;
    /*we return the position in where we placed the pivot*/
}
void QuickSortLomotoPartition(vector<int> &v, int p, int r){
    if(p < r) 
    {
        int q = LomotoPartition(v, p, r);
        QuickSortLomotoPartition(v, p, q - 1);
        QuickSortLomotoPartition(v, q + 1, r);
    }
}
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
        do {
            j --;
        } while (v[j] > pivot);
        if( i >= j) return j;
        /*j represents where the
        left and right sections are divided*/
        swap(v[i], v[j]);
    }
}
void QuickSortHoarePartition(vector<int> &v, int low, int high){
    if(low < high){
        int p = HoarePartition(v, low, high);
        QuickSortHoarePartition(v, low, p);
        QuickSortHoarePartition(v, p + 1, high);
    }
}
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
    return v[high];
    /*we return the median value*/
}
int LomotoPartitionMedianOfThree(vector<int> &v, int low, int high) {
    MedianOfThree(v, low, high);
    int pivot = v[high];
    int i = low - 1;

    for(int j = low; j < high; j ++) {
        if(v[j] <= pivot) 
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
void QuickSortMedianOfThree(vector<int> &v, int low, int high){
    if(low < high) 
    {
        int pivot = LomotoPartitionMedianOfThree(v, low, high);
        QuickSortMedianOfThree(v, low, pivot - 1);
        /*this will sort elements from the left side, <= pivot*/
        QuickSortMedianOfThree(v, pivot + 1, high);
        /*this will store the elements in the right side, >= pivot*/
    }
}
vector<int> GenerateRandomVector(int n) {
    vector<int> v(n);
    for(int i = 0; i < n; i ++) {
        v[i] = rand() % 10000;
    }
    return v;
}
int main() {
    srand(time(0));
    const int tests = 100000;
    const int dim = 1000;

    double timeLomoto = 0, timeHoare = 0, timeMedian = 0;

    for(int i = 0; i < tests; i ++) {
        vector<int> v1 = GenerateRandomVector(dim);
        vector<int> v2 = v1;
        vector<int> v3 = v1;

        clock_t start = clock();
        QuickSortLomotoPartition(v1, 0, dim - 1);
        clock_t end = clock();
        timeLomoto += (double)(end - start) / CLOCKS_PER_SEC * 1000;

        start = clock();
        QuickSortHoarePartition(v2, 0, dim - 1);
        end = clock();
        timeHoare += (double)(end - start) / CLOCKS_PER_SEC * 1000;

        start = clock();
        QuickSortMedianOfThree(v3, 0, dim - 1);
        end = clock();
        timeMedian += (double)(end - start) / CLOCKS_PER_SEC * 1000;
        
    }
    cout << "average sorting times over " << tests << " (" << dim;
    cout << " elements each)" << endl;
    cout << "Lomoto Partition: " << timeLomoto / tests << " ms" << endl;
    cout << "Hoare Partition: " << timeHoare / tests << " ms" << endl;
    cout << "Median-of-three partition: " << timeMedian / tests << " ms";
    cout << endl;

    return 0;
    
}