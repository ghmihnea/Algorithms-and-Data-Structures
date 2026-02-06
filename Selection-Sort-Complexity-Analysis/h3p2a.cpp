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
        }
        /*this if loop is executed only when we find an element smaller
        than the element corresponding to j index*/
    }
}
int main() {
    int n = 5;
    vector<int> a = {0, 8, 3, 17, 2};

    selectionsort(a, n);

    cout << "sorted vector : " << endl;
    for(int i : a) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
