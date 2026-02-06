#include <iostream>
#include <algorithm>
using namespace std;

void MaxHeapify(int arr[], int heapsize, int i) 
/*creating a MaxHeapify that will assure that the max-heap property
will remain stable*/
{
    int largest = i;//assume the parent node to be the largest
    int left = 2 * i + 1;//the left child index
    int right = 2 * i + 2;//the right child index

    if(left < heapsize && arr[left] > arr[i])
        largest = left;
        /*if we find left child larger than the parent node we update
        the value of large*/
    if(right < heapsize && arr[right] > arr[largest])
        largest = right;
        /*if the right child is larger than the previous largest 
        we update the value of that again*/
    if (largest != i)

    {
        swap(arr[i], arr[largest]);
        /*if we find a value larger than the one we 
    assumed initially we swap it as the parent(not 
    necessarily the topmost one)*/
        MaxHeapify(arr, heapsize, largest);/*repeat the function until
        the max-heap property is met*/
    }

}
/*while MaxHeapify ensures the max-heap property is followed subtree, 
BuildMaxHeap applies MaxHeapify non-leaf nodes, starting from the last
parent node, to transform the entire array into a maxheap*/
void BuildMaxHeap(int arr[], int dim) {
    for(int i = (dim/2) - 1; i >= 0; i --) {
        MaxHeapify(arr, dim, i);
    }
}
void HeapSort(int arr[], int dim) {
    BuildMaxHeap(arr, dim);//ensuring the maxheap property is met
    int heapsize = dim;
    for(int i = dim - 1; i > 0; i --) {
        swap(arr[0], arr[i]);
        /*swap the largest element at the end and then exracting it*/
        heapsize --;
        MaxHeapify(arr, heapsize, 0);
        /*reaplying MaxHeapify to restore the maxheap property after swapping
        the root at the end, and doing the above steps over again until we 
        extract all the elements from the largest to the smalles*/
        
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
