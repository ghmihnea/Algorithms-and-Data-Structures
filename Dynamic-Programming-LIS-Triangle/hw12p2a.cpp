#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string input;
    vector< vector<int> > triangle;

    while(getline(cin, input))
    {
        if(input.empty()) break;
        /*an empty line will break this loop*/
        stringstream ss(input);
        vector<int> row;
        int num;
        while(ss >> num){
            row.push_back(num);
            /*extracting numbers from the input line and adding them
            to the current row*/
        }
        triangle.push_back(row);
        /*adding the current row to the triangle*/
    }

    int n = triangle.size();
    if (n == 0) return 0;
    /*return 0 if the size of the triangle is 0*/

    vector< vector<int> > maxSum(n);
    /*creating a vector to store the maximum sum*/
    maxSum[0].push_back(triangle[0][0]);

    for(int i = 1; i < n; i ++) {
        maxSum[i].resize(i + 1);
        /*resizing row i to fit i + 1 elements*/
        for(int j = 0; j <= i; j ++) {
            if(j == 0)
                maxSum[i][j] = maxSum[i - 1][j] + triangle[i][j];
                /*the first element of the row can only be reached
                from the element right above it*/
            else if (j == i)
                maxSum[i][j] = maxSum[i - 1][j - 1] + triangle[i][j];
                /*the last element of the row can be reached from the 
                element directly to the left above it*/
            else 
                maxSum[i][j] = triangle[i][j] + max(maxSum[i - 1][j],
                maxSum[i - 1][j - 1]);
                /*for all other elements we add the maximum from the 
                two elements above it*/
        }
    }
    int max = *max_element(maxSum[n - 1].begin(), maxSum[n - 1].end());
    /*extracting the max element from the last row*/
    cout << max << endl;


    vector<int> path;
    int column = distance(maxSum[n - 1].begin(), find(maxSum[n - 1].begin(), 
maxSum[n - 1].end(), max));
/*finding the index of the column in which the max element is stored
(which is in the n-1 th row)*/
    path.push_back(triangle[n - 1][column]);
    /*adding it in our path as the 1st element*/

    for(int i = n - 2; i >= 0; i --)
    {
        if(column > 0 && maxSum[i][column - 1] >= maxSum[i][column])
        /*if the element to the top-left leads to a >= path sum than
        the element above:*/
        {
            column --;
            /*move to the left*/
        }
        path.push_back(triangle[i][column]);
        /*adding the selected element from the triangle to the path*/
    }
    reverse(path.begin(), path.end());
    /*reversing to have the path from top to bottom*/

    for(int i : path) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}