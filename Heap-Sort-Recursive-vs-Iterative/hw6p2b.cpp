#include <iostream>
#include <algorithm>
using namespace std;


void FloatDownMaxHeapify(int arr[], int heapsize, int i) {
    int current = i;
    int left = 2 * i + 1;//left child index
    int right = 2 * i + 2;//right child index

    while(left < heapsize) 
    /*while there still are elements in the heap*/
    {
        int LargerChild = left;/*we assume the left element to be 
        the larger one*/
        if(right < heapsize && arr[right] > arr[LargerChild]) {
            LargerChild = right;
            /*if the right child is larger we update the value of largerchild*/
        }
        swap(arr[current], arr[LargerChild]);
        /*move the largest element in place of the largest child*/
        current = LargerChild;
        left = 2 * current + 1;
        right = 2 * current + 2;
        /*update the current left and right index*/
    }
    while(current > 0) {
        int parent = (current - 1) /2;//we store the index of the parent
        if(arr[current] > arr[parent]) {
            /*if the child is larger than the parent we swap them*/
            swap(arr[current], arr[parent]);
            current = parent;
            /*we also swap their indexes*/
        }
        else break;
    }
}

void BuildMaxHeap(int arr[], int dim) {
    for(int i = (dim/2) - 1; i >= 0; i --) {
        FloatDownMaxHeapify(arr, dim, i);
    }
}
void HeapSort(int arr[], int dim) {
    BuildMaxHeap(arr, dim);//ensuring the maxheap property is met
    int heapsize = dim;
    for(int i = dim - 1; i > 0; i --) {
        swap(arr[0], arr[i]);
        /*swap the largest element at the end and then exracting it*/
        heapsize --;
        FloatDownMaxHeapify(arr, heapsize, 0);       
    }

}
void printArr(int arr[], int dim) {
    for(int i = 0; i < dim; i ++){
        cout << arr[i] << " ";
    }
    cout << endl;
}
int main() {
    int arr[] = {2, 7, 9, 4, 3, 6};
    int dim = sizeof(arr) / sizeof(arr[0]);

    cout << "original array:" << endl;
    printArr(arr, dim);

    HeapSort(arr, dim);

    cout << "after Heap-Sort:" << endl;
    printArr(arr, dim);
}