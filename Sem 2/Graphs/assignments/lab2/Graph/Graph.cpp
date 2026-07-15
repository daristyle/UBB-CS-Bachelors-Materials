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

int Graph::noVertices() const{
    return vertices.size();
}

int Graph::noEdges() const{
    return costMap.size();
}

IteratorRange<set<int>::const_iterator> Graph::getVertices() const{
    return {vertices.begin(), vertices.end()};
}

bool Graph::isEdge(int v1, int v2) const{
    return costMap.contains({v1, v2});
}

bool Graph::isVertex(int v) const{
    return vertices.contains(v);
}

int Graph::inDegree(int v) const{
    return inMap.at(v).size();
}

int Graph::outDegree(int v) const{
    return outMap.at(v).size();
}

IteratorRange<vector<int>::const_iterator> Graph::getOutboundNeighbours(int v) const{
    return {outMap.at(v).begin(), outMap.at(v).end()};
}

IteratorRange<vector<int>::const_iterator> Graph::getInboundNeighbours(int v) const{
    return {inMap.at(v).begin(), inMap.at(v).end()};
}

void Graph::setCost(int v1, int v2, int cost){
    if(!isEdge(v1, v2)) return;
    costMap[{v1, v2}] = cost;
}

int Graph::getCost(int v1, int v2) const{
    if(!isEdge(v1, v2)) return -1;
    return costMap.at({v1, v2});
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

Graph readGraph(std::istream& in, bool weighted, bool directed){
    std::cout << "Reading graph...\n";
    int vertices, edges;
    in >> vertices >> edges;
    Graph g(vertices);
    for(int i = 0; i < edges; i++){
        int v1, v2, cost = 0;
        in >> v1 >> v2;
        if(weighted){
            in >> cost;
        }
        g.addEdge(v1, v2, cost);
        if(!directed){
            g.addEdge(v2, v1, cost);
        }
        if((i + 1) % 100000 == 0) std::cout << (i + 1) << " edges read.\n";
    }
    std::cout << "Graph read.\n";
    return g;
}

void printGraph(const Graph& g, std::ostream& out, bool weighted, bool directed){
    int coef = (directed ? 1: 2);
    out << g.noVertices() << ' ' << g.noEdges()/coef << '\n';
    for(auto i : g.getVertices()){
        for(auto j : g.getOutboundNeighbours(i)){
            if(!directed && i > j) continue;
            out << i << ' ' << j;
            if(weighted){
                out << ' ' << g.getCost(i, j);
            }
            out << '\n';
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
                --noEdges;
            }
            --edgesLeft;
        }
    }

    return g;
}