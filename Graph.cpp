#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <climits>

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




int main(){
    vector<int> adj[6];
    
    adj[0].push_back(1);
    adj[0].push_back(2);
    adj[1].push_back(3);


    adj[2].push_back(3);

    adj[3].push_back(4);
    adj[3].push_back(5);
   // adj[2].push_back(1);
    
    cout << boolalpha << isCyclicBasedTopologicalSort(adj, 6) << endl;
    return 0;
}