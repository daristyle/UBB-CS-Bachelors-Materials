#include <algorithm>

#include "../Graph/Graph.h"
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <algorithm>

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
    map<int, int> duration;
    Graph g(0);
    int n, x, d, m, start = 0, end = 0;
    fin >> n;
    for(int i = 0; i < n; i++){
        fin >> x >> d >> m;
        duration[x] = d;

        g.addVertex(x);
        for(int j = 0; j < m; j++){
            fin >> d;
            g.addEdge(x, d);
        }

        if(x < start){
            start = x;
        }
        if(x > end){
            end = x;
        }
    }

    --start,++end;
    duration[start] = duration[end] = 0;
    g.addVertex(start);
    g.addVertex(end);

    for(auto vertex: g.getVertices()){
        if(vertex != start){
            g.addEdge(vertex, start);
        }
        if(vertex != end){
            g.addEdge(end, vertex);
        }
    }

    printGraph(g, std::cout, false, true);

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

    map<int, int> early, late;
    int totalTime = 0;

    for(auto node: order){
        early[node] = 0;
        for(auto neighbour: g.getOutboundNeighbours(node)){
            if(early[neighbour] > early[node]){
                early[node] = early[neighbour];
            }
        }
        early[node] += duration[node];

        totalTime += duration[node];
    }

    std::reverse(order.begin(), order.end());

    for(auto node: order){
        late[node] = node == end ? early[node] : totalTime;
        for(auto neighbour: g.getInboundNeighbours(node)){
            if(late[neighbour] - duration[neighbour] < late[node]){
                late[node] = late[neighbour] - duration[neighbour];
            }
        }
    }

    std::cout << "The toal time of the project is " << totalTime << std::endl;

    for(auto node: g.getVertices()){
        if(node != start && node != end){
            std::cout << "The earliest time for the node " << node << " is " << early[node] - duration[node] <<
                          " and the latest is " << late[node] - duration[node] << std::endl;
        }
    }

    vector<int> critical;
    for(auto node: g.getVertices()){
        if(node != start && node != end && early[node] == late[node]){
            critical.push_back(node);
        }
    }

    if(!critical.empty()){
        std::cout << "The critical nodes are: ";
        for(auto node: critical){
            std::cout << node << " ";
        }
        std::cout << std::endl;
    }else{
        std::cout << "There are no critical nodes" << std::endl;
    }

    return 0;
}