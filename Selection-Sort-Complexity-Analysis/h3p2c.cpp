#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

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
    for(int i = 0; i < dim; i ++) {
        if(i == 0) {
            a[i] = dim;
            /*we place the largest value at the beginning*/
        }
        else a[i] = i - 1;
        /*the rest of the values will be placed after it in ascending order*/
    }

    return a;

}
/*Case A is the worst case that the generates the most switches between 
the elements. first two are compared and then swaped(because the rest of 
elements are in ascending order, the 2nd element will be the smallest).
thnn the largest will be placed in 2nd position and swaped with the third
because of the same reasons. this will keep repeating until the largest element
initially placed at the beginning will be moved to the end*/

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
    /*seeding a random value generated at runtime*/
    int n = 5;

    vector<int> Rand = generateRand(n);
    cout << "randomly generated array : " << endl;
    printVector(Rand, n);

    selectionsort(Rand, n);
    cout << "after the selection sort :" << endl;
    printVector(Rand, n);

    vector<int> A = CaseA(n);
    cout << "worst case : " << endl;
    printVector(A, n);

    selectionsort(A, n);
    cout << "after selection sort :" << endl;
    printVector(A, n);

    vector<int> B = CaseB(n);
    cout << "best case :" << endl;
    printVector(B, n);

    selectionsort(B, n);
    cout << "after selection sort" << endl;
    printVector(B, n);

    return 0;

}
