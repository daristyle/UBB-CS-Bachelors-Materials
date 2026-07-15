#include "../Graph/Graph.h"
#include <map>
#include <set>
#include <iostream>
#include <fstream>

using std::map, std::set;

void topologicalSort(int node, bool& isDAG, vector<int>& order, set<int>& visited, set<int>& processing, Graph& g){
    visited.insert(node);
    processing.insert(node);
    for(auto neighbour: g.getOutboundNeighbours(node)){
        if(processing.contains(neighbour)){
            isDAG = false;
        }
        if(!visited.contains(neighbour)){
            topologicalSort(neighbour, isDAG, order, visited, processing, g);
        }
    }
    processing.erase(node);
    order.push_back(node);
}

int countPaths(int node, int end, map<int, int>& memo, Graph& g){
    if(memo.contains(node)){
        return memo[node];
    }

    int retval = 0;
    for(auto neighbour: g.getOutboundNeighbours(node)){
        retval += countPaths(neighbour, end, memo, g);
    }

    return memo[node] = retval;
}

int main(){
    std::ifstream fin("graph6.in");
    Graph g = readGraph(fin, false, true);

    bool isDAG = true;
    vector<int> order;
    set<int> visited, processing;
    for(auto node: g.getVertices()){
        if(!visited.contains(node)){
            topologicalSort(node, isDAG, order, visited, processing, g);
        }
    }
    if(!isDAG){
        std::cout << "The graph is not a DAG" << std::endl;
        return 0;
    }
    std::cout << "The graph is a DAG" << std::endl;
    std::cout << "A topological sorting of the graph is: ";
    for(auto node: order){
        std::cout << node << " ";
    }
    std::cout << std::endl;

    int u, v;
    fin >> u >> v;

    map<int, int> memo;
    memo[v] = 1;
    std::cout << "There are " << countPaths(u, v, memo, g) << " paths from " << u << " to " << v << std::endl;

    return 0;
}