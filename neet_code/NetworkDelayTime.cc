#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        return 0;
    }
};

void printGraph(const vector<vector<int>>& graph) {
    for (const auto& edge : graph) {
        cout << edge[0] << " -> " << edge[1]
             << " | Weight: " << edge[2] << "\n";
    }
}


void Dijkstra(vector<vector<int>>& graph){
    // convert to adj list - for each vertex store adj with existing weight between them
    // init dist pair vector - all max_int
    // init min heap with root

    // loop:
        // pop for PQ - vertex is finalized
        // relax neighbors
            // for each neighbor -
            //  if dist[v] + adj[v][neighbor][1] < dist[neighbor]
            //  dist[neighbor] = dist[v] + adj[v][neighbor][1]
            //  push
    
}



int main(){
    vector<vector<int>> times = {
        {1, 2, 4},
        {1, 3, 1},
        {2, 3, 2},
        {2, 4, 1},
        {3, 4, 5},
        {3, 5, 8},
        {4, 5, 3}
    };

    int n = 5; // Number of vertices
    int k = 1; // Source vertex

    printGraph(times);
    return 0;
}