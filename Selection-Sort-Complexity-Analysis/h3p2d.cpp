#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

void selectionsort(vector<int>& a, int dim) {
    for(int j = 0; j < dim - 1; j++) {
        int indmin = j;
        /*assuming j is the index of the minimum value*/
        for(int i = j + 1; i < dim; i++) {
            if(a[indmin] > a[i]) {
                indmin = i;
                /*if we find a value smaller than the one we assumed
                to be min we store its index in indmin*/
            }
        }
        if (indmin != j) {
            int aux = a[indmin];
            a[indmin] = a[j];
            a[j] = aux;
            /*this if loop is executed only when we find an element smaller
            than the element corresponding to j index*/
        }
    }
}
vector<int> generateRand(int dim) {
    vector<int> a(dim);
    for(int i = 0; i < dim; i ++) {
        a[i] = rand() % 101;
        /*we assign to a[i] a randomized value from 0 to 100(the remainders 
        of modulo 101)*/
    }
    return a;
}
/*this function will return a vector with randomly generated elements*/
vector<int> CaseA(int dim) {
    vector<int> a(dim);
    for(int i = 0; i < dim - 1; i ++) {
        a[i] = i + 1;
    }
    a[dim - 1] = 0;
    /*we choose the last element to be the smallest */


    return a;

}
/*Case A, is the worst case scenario. We place the smallest element at the end.
The inner for loop will iterate until the end and switch the last element
with the first one. Now at the end of the vector will be the second element
(the second largest one). this will keep repeating until elements are in the 
ascending order*/

vector<int> CaseB(int dim) {
    vector<int> a(dim);
    for(int i = 0; i < dim; i ++) {
        a[i] = i;
        /*elements are in ascending order*/
    }
    return a;
}
/*best case, all elements are sorted and no swaps need to be done*/

void printVector(vector<int> a, int dim) {
    for(int i = 0; i < dim; i ++) {
        cout << a[i] << " ";
    }
    cout << endl;
}
int main() {
    srand(time(0));

    vector<int> sizesofn = {100, 500, 1000, 5000, 10000, 50000};

    for(int n : sizesofn) {


        vector<int> A = CaseA(n);
        clock_t start = clock();
        selectionsort(A, n);
        clock_t end = clock();
        double timeA = double(end - start) / CLOCKS_PER_SEC;

        vector<int> B = CaseB(n);
        start = clock();
        selectionsort(B, n);
        end = clock();
        double timeB = double(end - start) / CLOCKS_PER_SEC;

        double timeAVG = 0;
        for(int i = 0; i < 10; i ++) {
            
            vector<int> Rand = generateRand(n);
            start = clock();
            selectionsort(Rand, n);
            end = clock();
            timeAVG = timeAVG + (double(end - start) / CLOCKS_PER_SEC);
        }
        timeAVG = timeAVG/10 ;

        cout << "time for worst case(Case A) : " << timeA << endl;
        cout << "time for best case(Case B) : " << timeB << endl; 
        cout << "time for average case(with Randomized values) : " << timeAVG;
        cout << endl;
    }
    return 0;

}
