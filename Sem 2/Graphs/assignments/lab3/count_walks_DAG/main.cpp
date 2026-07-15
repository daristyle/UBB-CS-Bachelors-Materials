#include "../Graph/Graph.h"
#include <map>
#include <set>
#include <iostream>
#include <fstream>

using std::map, std::set;

int countWalks(int node, int end, map<int, int>& memo, Graph& g){
    if(memo.contains(node)){
        return memo[node];
    }

    int retval = 0;
    for(auto neighbour: g.getOutboundNeighbours(node)){
        retval += countWalks(neighbour, end, memo, g);
    }

    return memo[node] = retval;
}

int main(){
    std::ifstream fin("graph6.in");
    Graph g = readGraph(fin, false, true);
    int u, v;
    fin >> u >> v;

    map<int, int> memo;
    memo[v] = 1;
    std::cout << "There are " << countWalks(u, v, memo, g) << " paths from " << u << " to " << v << std::endl;

    return 0;
}