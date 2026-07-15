#include <algorithm>

#include "../Graph/Graph.h"
#include <iostream>
#include <fstream>
//ASSUMES NODES ARE FROM 0 TO N - 1
vector<int> findCycle(const Graph& g){
    int n = g.noVertices();
    vector<vector<bool>> accessible((1 << n), vector<bool>(n, false));
    vector<vector<int>> from((1 << n), vector<int>(n, -1));
    vector<int> cycle;
    accessible[1][0] = true;
    for(int msk = 2; msk < (1 << n); ++msk){
        for(int node = 0; node < n; ++node){
            if(!(msk & (1 << node))) continue;
            for(auto neighbour: g.getInboundNeighbours(node)){
                if(!(msk & (1 << neighbour))) continue;
                if(accessible[msk ^ (1 << node)][neighbour]){
                    accessible[msk][node] = true;
                    from[msk][node] = neighbour;
                }
            }
        }
    }

    int node = 0, msk = (1 << n) - 1;
    for(int i = 0; i < n; ++i){
        if(accessible[msk][i] && g.isEdge(i, 0)){
            node = i;
        }
    }

    while(msk){
        if(!accessible[msk][node]){
            return vector<int>();
        }
        cycle.push_back(node);
        msk ^= (1 << node);
        node = from[msk ^ (1 << node)][node];
    }

    std::reverse(cycle.begin(), cycle.end());

    return cycle;
}

int main(){
    std::ifstream fin{"graph2.in"};
    Graph g = readGraph(fin, false, false);

    vector<int> cycle = findCycle(g);
    if(!cycle.empty()){
        std::cout << "An Hamiltonian cycle in the given graph is: ";
        for(auto node: cycle){
            std::cout << node << ", ";
        }
        std::cout << 0 << std::endl;
    }else{
        std::cout << "There is no Hamiltonian cycle in the given graph" << std::endl;
    }

    return 0;
}