#include "../Graph/Graph.h"
#include <queue>
#include <map>
#include <set>
#include <iostream>
#include <fstream>

using std::map, std::set;

map<int, int> BellmanFord(int start, Graph& g){
    map<int, int> cost;
    std::queue<int> q;
    set<int> queue;

    for(auto vertex: g.getVertices()){
        cost[vertex] = INT32_MAX;
    }

    q.push(start);
    queue.insert(start);
    cost[start] = 0;
    while(!q.empty()){
        int node = q.front();
        q.pop();
        queue.erase(node);
        for(auto neighbour: g.getOutboundNeighbours(node)){
            if(cost[neighbour] > cost[node] + g.getCost(node,neighbour)){
                cost[neighbour] = cost[node] + g.getCost(node, neighbour);
                if(!queue.contains(neighbour)){
                    q.push(neighbour);
                    queue.insert(neighbour);
                }
            }
        }
    }

    return cost;
}

Graph createMinCostSubgraph(int start, Graph& g){
    auto cost = BellmanFord(start, g);
    Graph minCostGraph(g.noVertices());
    for(auto vertex: g.getVertices()){
        for(auto neighbour: g.getOutboundNeighbours(vertex)){
            if(cost[neighbour] == cost[vertex] + g.getCost(vertex, neighbour))
                minCostGraph.addEdge(vertex, neighbour, g.getCost(vertex, neighbour));
        }
    }
    return minCostGraph;
}

int countMinCostWalks(int node, int end, set<int>& visited, map<int, int>& memo, Graph& g){
    if(memo.contains(node)){
        return memo[node];
    }

    visited.insert(node);
    int retval = (node == end) ? 1 : 0;
    for(auto neighbour: g.getOutboundNeighbours(node)){
        if(!visited.contains(neighbour)){
            int temp = countMinCostWalks(neighbour, end, visited, memo, g);
            if(temp == -1){
                return memo[node] = -1;
            }
            retval += temp;
        }else{
            return memo[node] = -1;
        }
    }
    visited.erase(node);

    return memo[node] = retval;
}

int main(){
    std::ifstream fin("graph4.in");
    Graph g = readGraph(fin, true, true);
    int u, v;
    fin >> u >> v;

    set<int> visited;
    map<int, int> memo;
    Graph minCostSubgraph = createMinCostSubgraph(u, g);
    int ans = countMinCostWalks(u, v, visited, memo, minCostSubgraph);
    if(ans == -1){
        std::cout << "There is an infinite number of minimum cost paths from " << u << " to " << v << std::endl;
    }else{
        std::cout << "There are " << ans << " minimum cost paths from " << u << " to " << v << std::endl;
    }

    return 0;
}
