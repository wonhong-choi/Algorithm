#include <iostream>
#include <vector>

using namespace std;

/*
    Disjoint Set (Union Find)
    The main idea of a “disjoint set” is to have all connected vertices have the same parent node or root node, whether directly or indirectly connected.
*/

// Quick find based Union Find
class QuickFindBasedUnionFind{
private:
    vector<int> root;

public:
    // O(n)
    QuickFindBasedUnionFind(int size) : root(size) { 
        for(int i=0; i<size; ++i){
            root[i]=i;
        }
    }

    // O(1)
    int find(int x){
        return root[x];
    }

    // O(n)
    void unionSet(int x, int y){
        // check 
        int rootX = find(x);
        int rootY = find(y);

        // merge children of rootY --> rootX
        if(rootX!=rootY){
            for(int i=0; i<root.size(); ++i){
                if(root[i]==rootY){
                    root[i]=rootX;
                }
            }
        }
    }

    // O(1)
    bool isConnected(int x, int y){
        return find(x) == find(y);
    }
};

// Quick Union based Union Find
class QuickUnionBasedUnionFind{
private:
    vector<int> parent;

public:
    QuickUnionBasedUnionFind(int size) : parent(size){
        for(int i=0; i<size; ++i){
            parent[i]=i;
        }
    }

    // O(n)
    int find(int x){
        while(x!=find(x)){
            x=find(x);
        }
        return x;
    }

    // O(n)
    void unionSet(int x, int y){
        int rootX = find(x);
        int rootY = find(y);

        if(rootX != rootY){
            parent[rootY]=rootX;
        }
    }

    // O(n)
    bool isConnected(int x, int y){
        return find(x)==find(y);
    }

};

// Quick Union --(optimized)--> union by rank
class UnionByRankBasedUnionFind{
private:
    vector<int> rank;
    vector<int> parent;

public:
    UnionByRankBasedUnionFind(int size) : rank(size), parent(size){
        for(int i=0; i<size; ++i){
            parent[i]=i;
            rank[i]=1;
        }
    }

    // O(logn). in the worst-case scenario, when we repeatedly union components of equal rank, the tree height will be at most logn +1.
    int find(int x){
        while(x!=parent[x]){
            x=parent[x];
        }
        return x;
    }

    // O(logn)
    void unionSet(int x, int y){
        int rootX = find(x);
        int rootY = find(y);

        if(rootX != rootY){
            if(rank[rootX] > rank[rootY]){
                parent[rootY]=rootX;
            }
            else if(rank[rootX] < rank[rootY]){
                parent[rootX] = rootY;
            }
            else{
                parent[rootY]=rootX;
                rank[rootX]++;
            }
        }
    }
    
    // O(logn)
    bool isConnected(int x, int y){
        return find(x)==find(y);
    }
};

// union by rank --(optimized)--> Path Compression
class PathCompressedUnionFind{
private:
    vector<int> rank;
    vector<int> root;

public:
    PathCompressedUnionFind(int size) : rank(size), root(size){
        for(int i=0; i<size; ++i){
            root[i]=i;
            rank[i]=1;
        }
    }

    // O(n). but, it will take less if find function is called repeatly.
    int find(int x){
        if(x!=root[x]){
            return root[x]=find(root[x]);
        }
        return x;
    }

    // O(logn)
    void unionSet(int x, int y){
        int rootX = find(x);
        int rootY = find(y);

        if(rootX != rootY){
            if(rank[rootX] > rank[rootY]){
                root[rootY]=rootX;
            }
            else if(rank[rootX] < rank[rootY]){
                root[rootX] = rootY;
            }
            else{
                root[rootY]=rootX;
                rank[rootX]++;
            }
        }
    }
    
    // O(logn)
    bool isConnected(int x, int y){
        return find(x)==find(y);
    }
};


int main(){
    // for displaying booleans as literal strings, instead of 0 and 1
    cout << boolalpha;
    PathCompressedUnionFind uf(10);
    // 1-2-5-6-7 3-8-9 4
    uf.unionSet(1, 2);
    uf.unionSet(2, 5);
    uf.unionSet(5, 6);
    uf.unionSet(6, 7);
    uf.unionSet(3, 8);
    uf.unionSet(8, 9);
    cout << uf.isConnected(1, 5) << endl;  // true
    cout << uf.isConnected(5, 7) << endl;  // true
    cout << uf.isConnected(4, 9) << endl;  // false
    // 1-2-5-6-7 3-8-9-4
    uf.unionSet(9, 4);
    cout << uf.isConnected(4, 9) << endl;  // true

    return 0;
}