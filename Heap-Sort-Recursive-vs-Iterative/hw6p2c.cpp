#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
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

void BuildMaxHeap(int arr[], int dim, bool userecursive) {
    for(int i = (dim/2) - 1; i >= 0; i --) {
        if(userecursive)
            MaxHeapify(arr, dim, i);
        else FloatDownMaxHeapify(arr, dim, i);
    }
}
void HeapSort(int arr[], int dim, bool userecursive) {
    BuildMaxHeap(arr, dim, userecursive);//ensuring the maxheap property is met
    int heapsize = dim;
    for(int i = dim - 1; i > 0; i --) {
        swap(arr[0], arr[i]);
        /*swap the largest element at the end and then exracting it*/
        heapsize --;
        if(userecursive)
            MaxHeapify(arr, heapsize, 0);
        else FloatDownMaxHeapify(arr, heapsize, 0);
        
    }

}

void averageCase(int arr[], int dim) {
    for(int i = 0; i < dim; i ++) {
        arr[i] = rand() % 1000000;/*this will seed a random value betweem 0 
        and 99999*/
    }
}
void CompareHeapSort(int n) {
    int *arrA = new int[n];
    /*for recursive heapsort*/
    int *arrB = new int[n];
    /*for the iterative heapsort*/
    /*we dinamically allocate memory for both arrays*/

    averageCase(arrA, n);

    for(int i = 0; i < n; i ++) {
        arrB[i] = arrA[i];
        /*copying each value of A in B*/
    }
    clock_t start = clock();
    HeapSort(arrA, n, true);
    clock_t stop = clock();
    double timeA = double(stop - start) / CLOCKS_PER_SEC;
    /*compute the time for A*/

    start = clock();
    HeapSort(arrA, n, false);
    stop = clock();
    double timeB = double(stop - start) / CLOCKS_PER_SEC;
    /*compute the time for B*/

    cout << "Input Size :" << n << endl;
    cout << "Recursive heap Sort time: " << timeA << " seconds" << endl;
    cout << "Nonrecursive heap Sort time: " << timeB << " seconds" << endl;

    delete[] arrA;
    delete[] arrB;
    /*delete the allocated memory*/
}

int main() {
    srand(time(0));

    CompareHeapSort(1000);
    CompareHeapSort(10000);
    CompareHeapSort(50000);
    CompareHeapSort(100000);
    CompareHeapSort(200000);

    return 0;
}