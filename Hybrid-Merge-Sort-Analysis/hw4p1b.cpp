#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

void InsertionSort (vector<int>& v, int low, int high) {
    for(int j = low + 1; j <= high; j ++) 
    /*j starts from the given low + 1, and is incremented until the
    high given*/
    {
        int key = v[j];
        /*v[j] is the element we want to insert into the correct position*/
        int i = j - 1;
        /*v[i] will start right before v[j] and we will decrement i*/
        while( i >= low && v[i] > key) 
        {
            v[i + 1] = v[i];
            /*the effect of this will be to shift the larger value to right*/
            i --;
        }
        v[i + 1] = key; 
        /*after the while loop i is one position smaller than where place it
        so we add 1*/
    }
}
void Merge(vector<int>& v, int low, int mid, int high) {
    int size = high - low + 1;
    vector<int> temp(size);

    int i = low; /*the first half*/
    int j = mid + 1;/*the second half*/
    int k = 0;/*used for the temporary vector*/

    while(i <= mid && j<= high) 
    /*while the first none of the halves are surpassed*/
    {
        if(v[i] <= v[j]) {
            temp[k] = v[i];
            i ++;
        }
        else {
            temp[k] = v[j];
            j ++;
        }
        k ++;
        /*we add the smaller element in the temoporary vector,
        increment in the half from where we took the value to reach the
        next value and also increment the position for temporary*/
     }
     while(i <= mid){
        temp[k] = v[i];
        i ++;
        k ++;
        /*while there still are elements in the first half*/
     }
     while(j <= high) {
        temp[k] =v[j];
        j ++;
        k ++;
        /*while there still are elements in the 2nd half*/
     }

     for(i = low; i <= high; i ++) {
        v[i] = temp[i - low];
        /*we insert the changes in our given vector*/
     }
}
void HybridMergeSort(vector<int> &v, int low, int high, int k) {
    int mid;
    if(high - low + 1 <= k){
        InsertionSort(v, low, high);
        /*if the the sub array of dimension smaller or equal than k 
        we make use of the insertion sort*/
    }
    else {
        mid = (low + high) / 2;
        HybridMergeSort(v, low, mid, k);
        HybridMergeSort(v, mid + 1, high, k);
        Merge(v, low, mid, high);
        /*otherwise we keep dividing the halves in 2 and sort them
        in ascenfing order until the dimension is k*/
    }
}
void TestSorting(int dim, vector<int>& v, vector<int>& kvalues,
vector<double>& times) {
    for(int i = 0; i < kvalues.size(); i ++)
    /*going through the vector with the values of k*/
    {
        int k = kvalues[i];
        /*storing different values of kvalue in the k variable
        with each iteration*/
        vector<int> vcpy = v;
        /*we also create a copy of the vector with each iteration*/

        clock_t start = clock();
        HybridMergeSort(vcpy, 0, vcpy.size() - 1, k);
        clock_t stop = clock();
        /*measuring how much it takes for hybrid merge to sort the
        elements fir diufferent values of k from the kvalues
        vector*/

        double time_taken = double(stop - start) / CLOCKS_PER_SEC;
        times.push_back(time_taken);
        /*creating a vector to store each time of execution*/
        cout << "k = " << k << " time = " << time_taken << " sec" << endl;
    }
    cout << endl;
}
void BestCase(vector<int>& v, int dim) {
    for(int i = 0; i < dim; i ++) {
        v[i] = i;
    }
}
void WorstCase(vector<int>& v, int dim) {
    for(int i = 0; i < dim; i ++) {
        v[i] = dim - i - 1;
    }
}
void AverageCase(vector<int>& v, int dim) {
    srand(time(0));
    for(int i = 0; i < dim; i ++) {
        v[i] = rand() % 100;
    }
}
void SaveResultsToFile(const string& filename, const vector<int>& kvalues, 
    const vector<double>& times){
    ofstream fout(filename);
    /*creating a new output file for each case*/
    if(!fout) {
        cerr << "error opening the file" << endl;
        return;
    }
    for(size_t i = 0; i < kvalues.size(); i ++) {
        fout << kvalues[i] << " " << times[i] << endl;
        /*in the files we will mention the values of k 
        and how long did it take for the program to order the elements*/
    }
    fout.close();
    /*we close the file*/
}
int main() {
    int dim = 1000;
    vector<int> kvalues = {2, 5, 10, 20, 50, 100};

    vector<double> besttimes, worsttimes, avgtimes;

    vector<int> best(dim);
    BestCase(best, dim);
    TestSorting(dim, best, kvalues, besttimes);

    vector<int> worst(dim);
    WorstCase(worst, dim);
    TestSorting(dim, worst, kvalues, worsttimes);

    vector<int> avg(dim);
    AverageCase(avg, dim);
    TestSorting(dim, avg, kvalues, avgtimes);

    SaveResultsToFile("bestcase.txt",kvalues, besttimes);
    SaveResultsToFile("worstcase.txt", kvalues, worsttimes);
    SaveResultsToFile("averagecase.txt", kvalues, avgtimes);

    return 0;
}
