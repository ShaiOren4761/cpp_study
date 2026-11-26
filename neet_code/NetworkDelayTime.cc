#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

using Entry = pair<int,int>;
using AdjLst = vector<vector<Entry>>; // for each vertex, have a list of pairs - {adj, weight}
using MinHeap = priority_queue<Entry, vector<Entry>, greater<Entry>>;



void printGraph(const vector<vector<int>>& graph) {
    for (const auto& edge : graph) {
        cout << edge[0] << " -> " << edge[1]
             << " | Weight: " << edge[2] << "\n";
    }
}

AdjLst initAdjList(vector<vector<int>>& graph, int n){
    AdjLst adj(n + 1);

    for (auto& edge : graph){
        adj[edge[0]].push_back({edge[1], edge[2]});
    }

    return adj;
}


int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    // convert to adj list - for each vertex store adj with existing weight between them
    AdjLst adj = initAdjList(times, n);
    // init dist pair vector - all max_int
    vector<int> dist(n + 1, INT_MAX);
    // init min heap with root
    MinHeap pq;

    // init root (path len 0, enter into PQ)
    dist[k] = 0;
    pq.push({0, k});

    while (!pq.empty()){
        auto [distance_u, u] = pq.top();
        pq.pop();
        if (dist[u] < distance_u) continue; // Outdated entry
        
        // Relax all adj of u
        for (auto [adj, weight_adj] : adj[u]){

            if (distance_u + weight_adj < dist[adj]){

                int newDist = distance_u + weight_adj;
                dist[adj] = newDist;
                pq.push({newDist, adj});
            }
        }
    }

    // return max path length. If unreachable vertex is found return -1.
    int result = 0;
    for (int i = 1; i < dist.size(); i++){
        if (dist[i] == INT_MAX) return -1;
        if (dist[i] > result) result = dist[i];
    }
    return result;
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

    //printGraph(times);
    cout << networkDelayTime(times, n, k) << "\n";
    return 0;
}