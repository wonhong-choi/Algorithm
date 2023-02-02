#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

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
}

// Counting Connected Components in an undirected graph
int connectedComponent(vector<int> adj[], int v){
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

int main(){

    return 0;
}