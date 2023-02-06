#include <stdio.h>
#include <vector>
#include <climits>
#include <queue>
#include <utility>

using namespace std;

/*
Minimum Spanning Tree(MST)
    1) Definition
        - A graph which has v-1 edges and in which all vertices are connected with minimum weighted sum.
        - there in no cycle in MST

    2) Making minimum spanning tree when given an weighted and connected graph.
        - BRUTE FORCE : generate all possible spanning tree and then, find the minimum spanning tree.
        - Prim's algorithm (Vertex Selection Method)
        - Kruskal's algorithm (Edge Selection Method)
*/

// Naive Prim's algorithm
// IDEA : Pick a vertex which is not in MST and has the lowest edge from MST, and then, add it in MST
//      : add Vertex one by one to MST
// T/C : O(v*v)
// S/C : O(v)
int naivePrim(vector<int> graph[], int n){
    int weightSum=0;
    vector<int> key(n, INT_MAX);        // the lowest edges From MST to idx vertex
    vector<bool> inMstSet(n, false);    // vertices in MST

    key[0]=0;
    for(int count=0; count<n; ++count){
        int u=-1;
        for(int i=0; i<n; ++i){
            if(!inMstSet[i] && (u==-1 || key[u] > key[i])){
                u=i;
            }
        }

        inMstSet[u]=true;
        weightSum+=key[u];

        for(int v=0; v<n; ++v){
            if(!inMstSet[v] && graph[u][v]!=0){
                key[v]=min(key[v], graph[u][v]);
            }
        }
    }

    return weightSum;
}

// Optimized Prim
// IDEA : when finding the lowest edge from MST vertices to not-MST vertices, using min heap
// T/C : O(eloge)
// S/C : O(v)
int prim(vector<pair<int,int>> graph[], int n){
    int weightSum=0;
    
    vector<bool> isMstSet(n, false);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    pq.push(make_pair(0, 0));
    while(!pq.empty()){
        int curWeight=pq.top().first;
        int cur=pq.top().second;
        pq.pop();

        if(isMstSet[cur]){
            continue;
        }

        isMstSet[cur]=true;
        weightSum+=curWeight;

        for(const pair<int,int>& weightToDst : graph[cur]){
            int weight=weightToDst.first;
            int neighbor=weightToDst.second;

            if(!isMstSet[neighbor]){
                pq.push(make_pair(weight, neighbor));
            }
        }
    }
    return weightSum;
}


int main(){

}