#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Node {
    int distance;
    int city;
};
struct Compare {
    bool operator()(Node a, Node b) {
        return a.distance > b.distance;
    }
/*overloading the comparison between the two nodes 
by signaling it with operator()*/
};

vector<int> Dijkstra(int s, const vector< vector<int> > &adjMatrix) {
    int dim = adjMatrix.size();
    vector<int> dist(dim, INT_MAX);/*initially assuming that all distances
    are infinite*/
    dist[s] = 0;
    /*the distance corresponding to the starting node is 0*/

    priority_queue<Node, vector<Node>, Compare> priorityQueue;
    /*declaring a priority queue storing Node structs
    when elements are inside it,
    it's automatically giving the node with the smallest distance from the top*/
    priorityQueue.push({0, s});
    /*pushing the starting point with the value 0*/

    while (!priorityQueue.empty()) {
        Node node = priorityQueue.top();
        priorityQueue.pop();
        int i = node.city;
        /*taking just the city part from the node we just created*/

        for (int j = 0; j < dim; j ++) {
            if(adjMatrix[i][j] != -1 && dist[j] > dist[i] + adjMatrix[i][j])
            /*if there s an edge between i and j and if we have found a shorter
            path to city j*/
            {
                dist[j] = dist[i] + adjMatrix[i][j];
                /*update dist[j] with the shorter distance*/
                priorityQueue.push({dist[j], j});
                /*push the updated city(j) and its new distance into
                the priority queue*/

            }
        }
    }
        return dist;

}
    int findMeetUpPoint(const vector< vector<int> > & adjMatrix,
                        int currentCity, int friendCity) {
        int dim = adjMatrix.size();

        vector<int> distancesFromCurrent = Dijkstra(currentCity, adjMatrix);
        /*vector storing the shortest distances from the current city to all 
        other city*/
        vector<int> distancesFromFriend = Dijkstra(friendCity, adjMatrix);

        int bestMeetingPoint = -1;
        int minOfMax = INT_MAX;

        for (int i = 0; i < dim; i ++) {
            if (distancesFromCurrent[i] != INT_MAX && 
            distancesFromFriend[i] != INT_MAX) 
            /*if both vertices are connected to the current city(no inf
            distance)*/
            {
                int maxTime = max(distancesFromCurrent[i],
                     distancesFromFriend[i]);
                /*max distance for current meeting point*/
                if(maxTime < minOfMax) {
                    minOfMax = maxTime;
                    /*updating the smallest max distance*/
                    bestMeetingPoint = i;
                    /*updating the index*/
                }
            }
        }
        return bestMeetingPoint;
    }
    int main () {
        vector< vector<int> > adjMatrix = {
            {0, 5, -1, 3, 10},
            {4, 0, -1, -1, 8},
            {8, 4, 0, 11, 14},
            {6, 12, -1, 0, -1},
            {-1, 8, 2, 11, 0}
        };
    int currentCity = 0;
    int friendCity = 4;

    int meetUpCity = findMeetUpPoint(adjMatrix, currentCity, friendCity);
    cout << "the optimal meeting point is: " << meetUpCity << endl;
    
    return 0;

}
