#include<iostream>
#include <cmath>
#include <ctime>
#include <fstream>
using namespace std;


long long NaiveSearchFibonacci(int n) {
    if (n < 2) {
        return n;
        /*if n is 0 fibonacci returns 0 and if n is 1 fibonacci returns 1*/
    }
    else return NaiveSearchFibonacci(n - 1) + NaiveSearchFibonacci(n - 2);
    //else will return the sum of the two previous elements
}
long long BottomUpFibonacci(int n) {
    if (n < 2) return n;
    long long prev2 = 0;
    long long prev1 = 1;
    long long current = 0;
    for (int i = 2; i <= n; i ++) 
    /*in this case we create an array in which we will store
    the two previous numbers*/
    {
        current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    return current;
    /*n th element will be obtained in current and returned*/
}

long long ClosedFormFibonacci(int n) {
    double sqrt5 = sqrt(5);
    double phi = (1 + sqrt5)/2;
    return round(pow(phi, n)/ sqrt5);
    /*for closed form we use thr given formula:
    (phi^n)/ square root of 5*/

}
void multiplyMatrix(long long F[2][2], long long M[2][2]) {
    long long a = F[0][0] * M[0][0] + F[0][1] * M[1][0];
    long long b = F[0][0] * M[0][1] + F[0][1] * M[1][1];
    long long c = F[1][0] * M[0][0] + F[1][1] * M[1][0];
    long long d = F[1][0] * M[0][1] + F[1][1] * M[1][1];

    F[0][0] = a;
    F[0][1] = b;
    F[1][0] = c;
    F[1][1] = d;
}
//function for matrix multiplication

void powerMatrix(long long F[2][2], int n) {

    if(n == 0 || n == 1) {
        return;
       /*base case: if the exponent is 0 or 1, the matrix is already
        at the correct power (M^0 or M^1).*/
    }
    long long M[2][2] = {{1,1}, {1,0}};
    /*above we defined the fibonacci matrix M that will be used 
    to multiply the result when n is odd*/

    powerMatrix(F, n/2);
    /*we calculate M^(n/2) recursively ->this will break
    the problems into smaller ones*/
    multiplyMatrix(F, F);
    /*we swquare the matrix, e.g. : F^(n/2) * F^(n/2)*/

    if(n % 2 != 0) multiplyMatrix(F, M);
    /*if n is odd we multiply M once more to obtain
    theneeded result*/

}
long long FibonacciMatrix(int n) {
    if(n == 0) return 0;
    /*if n is 0 we will return 0*/
    long long F[2][2] = {{1, 1}, {1, 0}};
    /*we initialize3 F as the Fibonnaci transformation matrix and we will
    further use it to compute fibonacci numbers*/

    powerMatrix(F, n);
    /*we raise n to the power of n-1 which will allow us to extract the nth 
    fibonacci number*/

    return F[0][1];
    /*nth fibonacci number*/

}
void measureTime(int n, ofstream& fout) {
    clock_t start, end;
    double timenaive, timebottomup, timeclosedform, timematrix;

    start = clock();
    NaiveSearchFibonacci(n);
    end = clock();
    timenaive = double(end - start) / CLOCKS_PER_SEC * 1000;

    start = clock();
    BottomUpFibonacci(n);
    end = clock();
    timebottomup = double(end - start) / CLOCKS_PER_SEC * 1000;
    
    start = clock();
    ClosedFormFibonacci(n);
    end = clock();
    timeclosedform = double(end - start) / CLOCKS_PER_SEC * 1000;

    start = clock();
    FibonacciMatrix(n);
    end = clock();
    timematrix = double (end - start) / CLOCKS_PER_SEC * 1000;

    fout << n << " " << timenaive << " " << timebottomup << " " ;
    fout << timeclosedform << " " << timematrix << endl;
    
}
int main() {
    int valuesofn[] = {1, 10, 20, 30, 40, 50};
    
    ofstream fout("fibonacci_times.txt");
    if(!fout){
        cerr << "error opening the file";
        return -1;
    }
    
    for(int n : valuesofn) {
        fout << "\n results for n : " << n << endl;
        measureTime(n, fout);
    }

    fout.close();
    return 0;

}
