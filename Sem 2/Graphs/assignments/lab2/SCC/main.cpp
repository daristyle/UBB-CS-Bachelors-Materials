#include "../Graph/Graph.h"
#include "../Graph/IteratorRange.h"
#include <iostream>
#include <fstream>
#include <functional>
#include <vector>
#include <set>

using std::function, std::vector, std::set, std::cout;

void dfs(int node,const function<IteratorRange<vector<int>::const_iterator>(int)>& getNeighbours,
    set<int>& visited, vector<int>& order){
    visited.insert(node);

    for(auto neighbour: getNeighbours(node)){
        if(!visited.contains(neighbour)){
            dfs(neighbour, getNeighbours, visited, order);
        }
    }

    order.push_back(node);
}

int main(){
    std::ifstream fin{"graph5.in"};
    std::ofstream fout{"graph5.out"};

    Graph g = readGraph(fin, false, true);
    set<int> visited;
    vector<int> orderStack;

    for(auto v: g.getVertices()){
        if(!visited.contains(v)){
            dfs(v, [&g](int node){return g.getOutboundNeighbours(node);},
                visited, orderStack);
        }
    }

    visited.clear();

    vector<vector<int>> SCCs;
    while(!orderStack.empty()){
        int node = orderStack.back();
        orderStack.pop_back();
        if(visited.contains(node)) continue;
        vector<int> scc;
        dfs(node, [&g](int node){return g.getInboundNeighbours(node);},
            visited, scc);
        sort(scc.begin(), scc.end());
        SCCs.push_back(scc);
    }

    sort(SCCs.begin(), SCCs.end());

    for(const auto& scc: SCCs){
        for(auto node: scc){
            fout << node << ' ';
        }
        fout << '\n';
    }

    return 0;
}