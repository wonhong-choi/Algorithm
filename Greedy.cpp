#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

#define loop(i, n) for(int i=0; i<(n); ++i)
#define fastio ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);

typedef long long ll;

typedef vector<int> vi;
typedef vector<pair<int,int>> vpi;
typedef vector<vector<int>> vvi;
typedef pair<int,int> pi;

/*

    GREEDY GENERAL STRUCTURE
        1) Initialize : res =0;
        2) while(all itmes are not considered){
            i = selectAnItem()
            if(feasible(i)){
                res = res + i
            }
        }
        3) return res

*/

// min change problem
// EXCEPTION OCCURS !! > coins=[18, 1, 10], amount=20
int minCoins(vi& coins, int amount){
    sort(coins.begin(), coins.end(), less<int>());
    
    int cnt =0;
    for(int coin : coins){
        cnt += amount/coin;
        amount%=coin;
    }
    return cnt;
}

// Activity Selection Problem
// Maximum # of activities that can happen on a single tasking machine.
int activitySelectionProblem(const vpi& activities){
    
}

int main(){
    
}