#include "../Graph/Graph.h"
#include <iostream>
#include <fstream>

void findHamiltonianCycle(int node, bool& found, int target, set<int>& processing, vector<int>& cycle, const Graph& g){
    cycle.push_back(node);
    processing.insert(node);
    for(auto neighbour: g.getOutboundNeighbours(node)){
        if(!processing.contains(neighbour)){
            findHamiltonianCycle(neighbour, found, target, processing, cycle, g);
            if(found) return;
        }else if(neighbour == target && cycle.size() == g.noVertices()){
            found = true;
            return;
        }
    }
    processing.erase(node);
    cycle.pop_back();
}

int main(){
    std::ifstream fin{"graph2.in"};
    Graph g = readGraph(fin, false, false);

    int node = *g.getVertices().begin();
    bool found = false;
    set<int> processing;
    vector<int> cycle;
    findHamiltonianCycle(node, found, node, processing, cycle, g);

    if(found){
        std::cout << "An Hamiltonian cycle in the given graph is: ";
        for(auto node: cycle){
            std::cout << node << ", ";
        }
        std::cout << node << std::endl;
    }else{
        std::cout << "There is no Hamiltonian cycle in the given graph" << std::endl;
    }

    return 0;
}