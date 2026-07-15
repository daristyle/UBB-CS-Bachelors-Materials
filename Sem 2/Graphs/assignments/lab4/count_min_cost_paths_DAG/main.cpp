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

int main(){
    std::ifstream fin("graph1.in");
    Graph g = readGraph(fin, true, true);

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

    map<int, int> cost, ways;
    for(auto node: order){
        cost[node] = INT32_MAX / 2;
        ways[node] = 0;
        if(node == v){
            cost[node] = 0;
            ways[node] = 1;
        }
        for(auto neighbour: g.getOutboundNeighbours(node)){
            int newCost = cost[neighbour] + g.getCost(node, neighbour);
            if(cost[node] > newCost){
                cost[node] = newCost;
                ways[node] = ways[neighbour];
            }else if(cost[node] == newCost){
                ways[node] += ways[neighbour];
            }
        }

        if(node == u){
            break;
        }
    }

    if(ways[u] == 0){
        std::cout << "There is no path from " << u << " to " << v << std::endl;
    }else{
        std::cout << "There are " << ways[u] << " lowest cost paths from " << u << " to " << v << " with the cost of " << cost[u]<< std::endl;
    }

    return 0;
}