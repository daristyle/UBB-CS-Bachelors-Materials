#include "Graph.h"

#include <iostream>
#include <random>


Graph::Graph(int noVertices){
    for(int i = 0; i < noVertices; i++){
        inMap[i] = vector<int>();
        outMap[i] = vector<int>();
        vertices.insert(i);
    }
}

Graph::Graph(const Graph& g){
    this->inMap = g.inMap;
    this->outMap = g.outMap;
    this->costMap = g.costMap;
    this->vertices = g.vertices;
}

int Graph::noVertices(){
    return vertices.size();
}

int Graph::noEdges(){
    return costMap.size();
}

IteratorRange<set<int>::const_iterator> Graph::getVertices(){
    return {vertices.begin(), vertices.end()};
}

bool Graph::isEdge(int v1, int v2){
    return costMap.contains({v1, v2});
}

int Graph::inDegree(int v){
    return inMap[v].size();
}

int Graph::outDegree(int v){
    return outMap[v].size();
}

IteratorRange<vector<int>::const_iterator> Graph::getOutboundNeighbours(int v){
    return {outMap[v].begin(), outMap[v].end()};
}

IteratorRange<vector<int>::const_iterator> Graph::getInboundNeighbours(int v){
    return {inMap[v].begin(), inMap[v].end()};
}

void Graph::setCost(int v1, int v2, int cost){
    if(!isEdge(v1, v2)) return;
    costMap[{v1, v2}] = cost;
}

int Graph::getCost(int v1, int v2){
    if(!isEdge(v1, v2)) return -1;
    return costMap[{v1, v2}];
}

void Graph::addEdge(int v1, int v2, int cost){
    if(!this->vertices.contains(v1) || !this->vertices.contains(v2) || isEdge(v1, v2)) return;
    inMap[v2].push_back(v1);
    outMap[v1].push_back(v2);
    costMap[{v1, v2}] = cost;
}

void Graph::removeEdge(int v1, int v2){
    if(!isEdge(v1, v2)) return;
    int i = 0;
    while(outMap[v1][i] != v2) i++;
    std::swap(outMap[v1][i], outMap[v1][outMap[v1].size()-1]);
    outMap[v1].pop_back();
    i = 0;
    while(inMap[v2][i] != v1) i++;
    std::swap(inMap[v2][i], inMap[v2][inMap[v2].size()-1]);
    inMap[v2].pop_back();
    costMap.erase({v1, v2});
}

void Graph::addVertex(int v){
    vertices.insert(v);
    inMap[v] = vector<int>();
    outMap[v] = vector<int>();
}

void Graph::removeVertex(int v){
    for(auto w: getVertices()){
        removeEdge(v, w);
        removeEdge(w, v);
    }
    vertices.erase(v);
}

Graph& Graph::operator=(const Graph& g){
    this->inMap = g.inMap;
    this->outMap = g.outMap;
    this->costMap = g.costMap;
    this->vertices = g.vertices;
    return *this;
}

Graph readGraph(std::istream& in){
    std::cout << "Reading graph...\n";
    int vertices, edges;
    in >> vertices >> edges;
    Graph g(vertices);
    for(int i = 0; i < edges; i++){
        int v1, v2, cost;
        in >> v1 >> v2 >> cost;
        g.addEdge(v1, v2, cost);
        if((i + 1) % 100000 == 0) std::cout << (i + 1) << " edges read.\n";
    }
    std::cout << "Graph read.\n";
    return g;
}

void printGraph(Graph& g, std::ostream& out){
    out << g.noVertices() << ' ' << g.noEdges() << '\n';
    for(auto i : g.getVertices()){
        for(auto j : g.getOutboundNeighbours(i)){
            out << i << ' ' << j << ' ' << g.getCost(i, j) << '\n';
        }
    }
}

Graph generateRandomGraph(int noVertices, int noEdges, bool cost){
    Graph g(noVertices);
    int edgesLeft = noVertices*noVertices;
    for(auto i : g.getVertices()){
        for(auto j : g.getVertices()){
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distrib(0, edgesLeft - 1);
            int randomValue = distrib(gen);
            if(randomValue < noEdges){
                std::uniform_int_distribution<> distribCost(0, 100);
                int randomCost = distribCost(gen) * cost;
                g.addEdge(i, j, randomCost);
                --noEdges;3
            }
            --edgesLeft;
        }
    }

    return g;
}