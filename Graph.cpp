#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <climits>
#include <unordered_set>
#include <unordered_map>

using namespace std;

/*
GRAPH
    1) Graph Representation
        1-1) Adjacency Matrix
            Operations:
                space : O(v * v)
                Check if u and v are adjacent : O(1)
                Find all vertices adjacent to u : O(v)
                Find degree of U : O(v)
                Add/Remove an edge : O(1)
                Add/Remove an vertix : O(v*v)

        1-2) Adjacency List, when using Dynamic sized array
            Operations:
                space : O(v + e)
                Check if u and v are adjacent : O(v)
                Find all vertices adjacent to u : O(degree(v))
                Find degree of U : O(1)
                Add an edge : O(1)
                Remove an edge : O(v)
                Add/Remove an vertix : O(1)
*/

// undirected graph
class Graph_AdjacencyMat{
private:
    vector<vector<bool>> adj;

public:
    Graph_AdjacencyMat(){}
    Graph_AdjacencyMat(int size) : adj(size, vector<bool>(size,false)){}

    bool isAdjacent(int u, int v){
        return adj[u][v];
    }

    vector<int> adjacentVertices(int u){
        vector<int> adjs;
        for(int i=0; i<adj[u].size(); ++i){
            if(adj[u][i]==true){
                adjs.push_back(i);
            }
        }
        return adjs;
    }

    int degree(int u){
        int degree=0;
        for(int i=0; i<adj[u].size(); ++i){
            if(adj[u][i]==true){
                degree++;
            }
        }
        return degree;
    }

    void addEdge(int u, int v){
        adj[u][v]=true;
        adj[v][u]=true;
    }

    void removeEdge(int u, int v){
        adj[u][v]=false;
        adj[v][u]=false;
    }

    void addVertex(){
        for(int i=0; i<adj.size(); ++i){
            adj[i].push_back(false);
        }
        adj.push_back(vector<bool>(adj.size()+1,false));
    }

    void removeVertex(int u){
        for(int i=0; i<adj.size(); ++i){
            for(int j=0; j<adj[i].size(); ++j){
                if(i<u && j>u){
                    adj[i][j-1]=adj[i][j];
                }
                else if(i>u && j<u){
                    adj[i-1][j]=adj[i][j];
                }
                else if(i>u && j>u){
                    adj[i-1][j-1]=adj[i][j];
                }
            }
        }
    }
};

class Graph_AdjacencyList{
private:
    vector<vector<int>> adj;

public:
    Graph_AdjacencyList(){}
    Graph_AdjacencyList(int size):adj(size){}

    bool isAdjacent(int u, int v){
        for(int nei : adj[u]){
            if(nei==v){
                return true;
            }
        }
        return false;
    }

    vector<int> adjacentVertices(int u){
        vector<int> adjs;
        for(int i=0; i<adj[u].size(); ++i){
            adjs.push_back(adj[u][i]);
        }
        return adjs;
    }

    int degree(int u){
        return adj[u].size();
    }

    void addEdge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void removeEdge(int u, int v){
        adj[u].erase(find(adj[u].begin(), adj[u].end(), v));
        adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
    }

    void addVertex(){
        adj.push_back(vector<int>());
    }

    void removeVertex(int u){
        adj.erase(adj.begin()+u);
    }
};

// BFS : Given src
void BFS(vector<int> adj[], int v, int src){
    vector<bool> visited(v, false);

    queue<int> q;
    q.push(src);
    visited[src]=true;

    while(!q.empty()){
        int cur=q.front();
        q.pop();

        printf("%d -> ", cur);

        for(int neighbor : adj[cur]){
            if(!visited[neighbor]){
                q.push(neighbor);
                visited[neighbor]=true;
            }
        }
    }
    printf("\n");
}

// BFS 
//      No Source Given and Graph may be disconnected
// T/C : O(v+e)
void BFS_Disconnected(vector<int> adj[], int v){
    vector<bool> visited(v, false);
    queue<int> q;

    for(int i=0; i<v; ++i){
        if(!visited[i]){
            q.push(i);
            visited[i]=true;

            while(!q.empty()){
                int cur=q.front();
                q.pop();

                printf("%d -> ", cur);

                for(int neighbor : adj[cur]){
                    if(!visited[neighbor]){
                        q.push(neighbor);
                        visited[neighbor]=true;
                    }
                }
            }
        }
    }
    printf("\n");
}

// Counting Connected Components in an undirected graph
// By BFS Based
int connectedComponentBFS(vector<int> adj[], int v){
    vector<bool> visited(v, false);
    queue<int> q;

    int island=0;
    for(int i=0; i<v; ++i){
        if(!visited[i]){
            q.push(i);
            visited[i]=true;

            while(!q.empty()){
                int cur=q.front();
                q.pop();

                printf("%d -> ", cur);

                for(int neighbor : adj[cur]){
                    if(!visited[neighbor]){
                        q.push(neighbor);
                        visited[neighbor]=true;
                    }
                }
            }
            ++island;
        }
    }
    return island;
}

// DFS : Given src
void DFS(vector<int> adj[], int v, int src){
    stack<int> st;
    vector<bool> visited(v, false);

    st.push(src);
    
    while(!st.empty()){
        int cur=st.top();
        st.pop();
        if(!visited[cur]){
            visited[cur]=true;

            printf("%d -> ", cur);
            for(int neighbor : adj[cur]){
                if(!visited[neighbor]){
                    st.push(neighbor);
                }
            }
        }
    }
    printf("\n");
}

// DFS 
//      No Source Given and Graph may be disconnected
// T/C : O(v+e)
void DFS_Disconnected(vector<int> adj[], int v){
    stack<int> st;
    vector<bool> visited(v, false);

    for(int i=0; i<v; ++i){
        if(!visited[i]){
            st.push(i);

            while(!st.empty()){
                int cur=st.top();
                st.pop();

                if(!visited[cur]){
                    visited[cur]=true;
                    printf("%d -> ", cur);

                    for(int neighbor : adj[cur]){
                        if(!visited[neighbor]){
                            st.push(neighbor);
                        }
                    }
                }
            }
        }
    }
    printf("\n");
}

// Counting Connected Components in an undirected graph
// By DFS Based
int connectedComponentDFS(vector<int> adj[], int v){
    stack<int> st;
    vector<bool> visited(v, false);

    int island=0;
    for(int i=0; i<v; ++i){
        if(!visited[i]){
            st.push(i);

            while(!st.empty()){
                int cur=st.top();
                st.pop();

                if(!visited[cur]){
                    visited[cur]=true;

                    for(int neighbor : adj[cur]){
                        if(!visited[neighbor]){
                            st.push(neighbor);
                        }
                    }
                }
            }
            ++island;
        }
    }
    return island;
}

// Shortest Path in an Unweighted Graph
// Given an Unweighted Graph and a source point, the task is to find the shortest path between the source point and every other point in the graph.
// IDEA : BFS
// T/C : O(v+e)
// S/C : O(v) for visited
vector<int> shortestPath(vector<int> adj[], int v, int src){
    queue<int> q;
    vector<int> visited(v, -1);
    visited[src]=0;
    q.push(src);

    while(!q.empty()){
        int cur=q.front();
        q.pop();
        
        for(int neighbor : adj[cur]){
            if(visited[neighbor]==-1){
                visited[neighbor]=visited[cur]+1;
                q.push(neighbor);
            }
        }
    }
    return visited;
}

// Detect Cycle in Undirected Graph
// IDEA : DFS Based
// T/C : O(v+e)
bool isCyclicRecur(vector<int> adj[], vector<bool>& visited, int cur, int prev){
    visited[cur]=true;

    for(int neighbor : adj[cur]){
        if(!visited[neighbor]){
            if(isCyclicRecur(adj, visited, neighbor, prev)){
                return true;
            }
        }
        else if(neighbor!=prev){
            return true;
        }
    }
    return false;
}

bool isCyclic(vector<int> adj[], int v){
    vector<bool> visited(v, false);

    for(int i=0; i<v;++i){
        if(!visited[i]){
            if(isCyclicRecur(adj, visited, i, -1)){
                return true;
            }
        }
    }
    return false;
}

// Detect Cycle in directed Graph
// IDEA : DFS Based
// T/C : O(v+e)
bool isCyclicRecurDirected(vector<int> adj[], vector<bool>& visited, vector<bool>& recSt, int cur){
    visited[cur]=true;
    recSt[cur]=true;

    for(int neighbor : adj[cur]){
        if(!visited[neighbor] && isCyclicRecurDirected(adj, visited, recSt, neighbor)){
            return true;
        }
        else if(recSt[neighbor]){
            return true;
        }
    }
    recSt[cur]=false;
    return false;
}

bool isCyclicDirected(vector<int> adj[], int v){
    vector<bool> visited(v, false), recSt(v,false);

    for(int i=0; i<v; ++i){
        if(!visited[i]){
            if(isCyclicRecurDirected(adj, visited, recSt, i)){
                return true;
            }
        }
    }
    return false;
}

// Topological Sorting
// IDEA : BFS based using Kahn's algorithm
// T/C : O(v+e)
// S/C : O(v)
vector<int> topologicalSorting(vector<int> adj[], int v){
    vector<int> indegree(v,0);
    for(int i=0; i<v;++i){
        for(int neighbor : adj[i]){
            indegree[neighbor]++;
        }
    }

    queue<int> q;
    for(int i=0; i<v; ++i){
        if(indegree[i]==0){
            q.push(i);
        }
    }

    vector<int> sorted;
    while(!q.empty()){
        int cur=q.front();
        q.pop();

        sorted.push_back(cur);

        for(int neighbor : adj[cur]){
            indegree[neighbor]--;
            if(indegree[neighbor]==0){
                q.push(neighbor);
            }
        }
    }
    return sorted;
}

// Cycle Detection using Topological Sorting
// IDEA : BFS based using Kahn's algorithm
//        if there is/are cycle, topological sorted vector has less than v. (because the vertex which don't have indegree edge is not exist.)
// T/C : O(v+e)
// S/C : O(v)
bool isCyclicBasedTopologicalSort(vector<int> adj[], int v){
    vector<int> indegree(v,0);
    for(int i=0; i<v;++i){
        for(int neighbor : adj[i]){
            indegree[neighbor]++;
        }
    }

    queue<int> q;
    for(int i=0; i<v; ++i){
        if(indegree[i]==0){
            q.push(i);
        }
    }

    int count=0;
    while(!q.empty()){
        int cur=q.front();
        q.pop();

        count++;

        for(int neighbor : adj[cur]){
            indegree[neighbor]--;
            if(indegree[neighbor]==0){
                q.push(neighbor);
            }
        }
    }
    return count!=v;
}

// Topological Sorting
// IDEA : DFS based
// T/C : O(v+e)
// S/C : O(v)
void topologicalSortingDFSRecur(vector<int> adj[], vector<bool>& visited, stack<int>& st, int cur){
    visited[cur]=true;

    for(int neighbor : adj[cur]){
        if(!visited[neighbor]){
            topologicalSortingDFSRecur(adj, visited, st, neighbor);
        }
    }
    st.push(cur);
}

vector<int> topologicalSortingDFS(vector<int> adj[], int v){
    vector<bool> visited(v, false);
    stack<int> st;

    for(int i=0; i<v; ++i){
        if(!visited[i]){
            topologicalSortingDFSRecur(adj, visited, st, i);
        }
    }

    vector<int> sorted;
    while(!st.empty()){
        sorted.push_back(st.top());
        st.pop();
    }
    return sorted;
}


// Shortest Path in Directed Acyclic Graph
// IDEA : topological sorting
// T/C : O(v+e)
// S/C : O(v)
vector<int> shortestPathDAG(vector<int> adj[], vector<int> weight[], int v, int src){
    vector<int> topologicalSorted = topologicalSorting(adj, v);

    vector<int> dist(v, INT_MAX);

    for(int u=0; u<topologicalSorted.size(); ++u){
        for(int v=0; v<adj[u].size(); ++v){
            int neighbor= adj[u][v];

            dist[neighbor]=min(dist[neighbor], dist[u]+weight[u][v]);
        }
    }
    return dist;
}

// Dijkstra's Algorithm
// Naive approach
// T/C : O(v^2)
// S/C : O(v)
vector<int> dijkstra(const vector<vector<int>>& adj, int n, int src){
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;
    vector<bool> fin(n, false); //finalized

    for(int count=0; count<n-1; ++count){   // last one(the longest vertex from src) do not need to do something
        // pick shortest one
        int u=-1;
        for(int i=0; i<n; ++i){
            if(!fin[i] && (u==-1 || dist[u] > dist[i])){
                u = i;
            }
        }

        fin[u] = true;

        // relax operation
        for(int v=0; v < n; ++v){
            if(adj[u][v] !=0 && !fin[v]){
                dist[v] = min(dist[v], dist[u] + adj[u][v]);
            }
        }
    }
    return dist;
}

// Dijkstra's Algorithm
// Efficient approach
// T/C : O(vlogv)
// S/C : O(v)
vector<int> dijkstraOptimized(const vector<vector<pair<int, int>>>& graph, int n, int src){
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;

    priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push(make_pair(0, src));

    while(!pq.empty()){
        int u = pq.top().second;
        int distU = pq.top().first;
        pq.pop();

        if(dist[u] < distU){    // already min (==finalized)
            continue;
        }

        for(int j=0; j<graph[u].size(); ++j){
            int v = graph[u][j].first;
            int w = graph[u][j].second;

            if(dist[v] > w + distU){
                pq.push(make_pair(w+distU, v));
                dist[v] = w + distU;
            }
        }
    }
    return dist;
}

// Bellman Ford Algorithm
// IDEA : length 1 > length 2 > length 3 > ... > length n-1 edge
// T/C : O(v*e)
// S/C : O(v)
vector<int> bellmanFord(const vector<vector<pair<int, int>>>& graph, int n, int src){
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;

    for(int i=0; i<n-1; ++i){
        for(int u=0; u<graph.size(); ++u){
            for(const pair<int,int>& edge : graph[u]){
                int nei = edge.first;
                int w = edge.second;
                if(dist[nei] > dist[u] + w){
                    dist[nei] = dist[u] + w;
                }
            }
        }
    }
    return dist;
}

// negative cycle detection
// IDEA : Bellman ford Approach
// T/C : O(v*e)
bool negCycleDetection(const vector<vector<pair<int, int>>>& graph, int n, int src){
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;

    for(int i=0; i<n-1; ++i){
        for(int u=0; u<graph.size(); ++u){
            for(const pair<int,int>& edge : graph[u]){
                int nei = edge.first;
                int w = edge.second;
                if(dist[nei] > dist[u] + w){
                    dist[nei] = dist[u] + w;
                }
            }
        }
    }

    for(int u=0; u<graph.size(); ++u){
        for(const pair<int,int>& edge : graph[u]){
            int nei = edge.first;
            int w = edge.second;
            if(dist[nei] > dist[u] + w){
                dist[nei] = dist[u] + w;
                return true;
            }
        }
    }
    return false;
}


// Kosaraju's Algoritm
// Strongly connected Components
// CONDITION:
//              1) connected graph
//              2) directed graph
// IDEA: DFS Based
//      0) u --> v, u is source, v is sink. so then, search sink first by using dfs. source(u) is NEVER reachable from sink(v)
//      1) Order the vertices in decreasing order of finish times in DFS (sink first)
//      2) Reverse all edges
//      2-1) why reverse all edges?
//          - reversing edges makes source to sink and sink to source, of course stay strongly connected component
//          - counter example:  # when not reveresing edges, start from reverse order of step1
//                  0 -> 1 -> 2
//                  ^    |  
//                  | ---3
//                  [0 1 2 3] order of step1. then, reverse order make component. --> 3-1-0-2 > wrong!
//      3) Do DFS of the reversed graph in the order obtained in Step1.
//           For every vertex, print all reachable vertice as one strongly connected component
// T/C: O(v+e)
// S/C: O(v+e) for graph, O(v) for stack
void kosarajuDFS(const vector<vector<int>>& graph, stack<int>& st, vector<bool>& visited, int cur){
    visited[cur] = true;
    for(int neighbor : graph.at(cur)){
        if(!visited[neighbor]){
            kosarajuDFS(graph, st, visited, neighbor);
        }
    }
    st.push(cur);
}

void kosarajuDFS3(const vector<vector<int>>& graph, vector<bool>& visited, int cur){
    visited[cur] = true;
    cout << cur << " ";

    for(int nei : graph[cur]){
        if(!visited[nei]){
            kosarajuDFS3(graph, visited, nei);
        }
    }
}

void kosaraju(const vector<vector<int>>& graph){
    // step1) decreasing order of finish time.
    vector<bool> visited(graph.size() + 1, false);
    stack<int> st;
    for(int i=0; i<graph.size(); ++i){
        if(!visited[i])
            kosarajuDFS(graph, st, visited, i);
    }

    // step2) reverse all edges
    vector<vector<int>> reverseGraph(graph.size(), vector<int>());
    for(int i=0; i<graph.size(); ++i){
        for(int j=0; j<graph[i].size(); ++j){
            reverseGraph[j].push_back(i);
        }
    }

    // step3) do dfs
    fill(visited.begin(), visited.end(), false);
    while(!st.empty()){
        int cur = st.top();
        st.pop();
        if(!visited[cur]){
            kosarajuDFS3(reverseGraph, visited, cur);
            cout << endl;
        }
    }
}

// Articulation Point
// IDEA : 
//      1) Naive : erase one by one vertex, check graph is disconnected > TOO SLOW
//
//      2) Root RULE : DFS from one by one vertex, if root has more than child, this vertex is articulation point
//      3) Non-Root RULE : e(u, v) in DFS tree, low[v] >= dis[u] then, u is articulation point
void dfsAP(vector<vector<int>>& graph, vector<bool>& visited, vector<int>& disc, vector<int>& low, vector<bool>& isAP, int u, int parent, int time){
    visited[u] = true;
    disc[u] = low[u] = ++time;
    int children = 0;
    for(int v : graph[u]){
        if(!visited[v]){
            ++children;

            dfsAP(graph, visited, disc, low, isAP, v, u, time);

            low[u] = min(low[u], low[v]);

            if(parent != -1 && low[v] >= disc[u]){
                isAP[u] = true;
            }
        }
        else if(v != parent){
            low[v] = min(low[v], disc[u]);
        }
    }
    if(parent == -1 && children > 1){
        isAP[u] = true;
    }
}

vector<int> articualtionPoint(vector<vector<int>>& graph, int n){
    vector<bool> visited(n, false);
    vector<int> disc(n, 0);
    vector<int> low(n, 0);
    vector<bool> isAP(n, false);

    int parent = -1;
    int time = 0;
    for(int i=0; i<n; ++i){
        if(!visited[i]){
            dfsAP(graph, visited, disc, low, isAP, i, parent, time);
        }
    }
}

int main(){
    
    return 0;
}