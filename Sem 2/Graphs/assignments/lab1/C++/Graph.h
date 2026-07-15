#pragma once

#include <filesystem>
#include <map>
#include <vector>
#include <set>

#include "IteratorRange.h"

using std::vector, std::map, std::pair, std::set;

class Graph{
private:
    //CHANGE HERE FOR O(1)
    map<int, vector<int>> inMap, outMap;
    map<pair<int, int>, int> costMap;
    set<int> vertices;

public:
    
    Graph(int noVertices);
    Graph(const Graph& g);

    int noVertices();
    int noEdges();

    IteratorRange<set<int>::const_iterator> getVertices();

    bool isEdge(int v1, int v2);

    int inDegree(int v);
    int outDegree(int v);

    IteratorRange<vector<int>::const_iterator> getOutboundNeighbours(int v);
    IteratorRange<vector<int>::const_iterator> getInboundNeighbours(int v);

    void setCost(int v1, int v2, int cost);
    int getCost(int v1, int v2);

    void addEdge(int v1, int v2, int cost = 0);
    void removeEdge(int v1, int v2);

    void addVertex(int v);
    void removeVertex(int v);

    Graph& operator=(const Graph& g);
};

Graph readGraph(std::istream& in);
void printGraph(Graph& g, std::ostream& out);
Graph generateRandomGraph(int noVertices, int noEdges, bool cost = false);