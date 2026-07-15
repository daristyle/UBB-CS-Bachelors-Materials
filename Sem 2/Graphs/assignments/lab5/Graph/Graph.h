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
    
    Graph(int noVertices = 0);
    Graph(const Graph& g);

    int noVertices() const;
    int noEdges() const;

    IteratorRange<set<int>::const_iterator> getVertices() const;

    bool isEdge(int v1, int v2) const;
    bool isVertex(int v) const;

    int inDegree(int v) const;
    int outDegree(int v) const;

    IteratorRange<vector<int>::const_iterator> getOutboundNeighbours(int v) const;
    IteratorRange<vector<int>::const_iterator> getInboundNeighbours(int v) const;

    void setCost(int v1, int v2, int cost);
    int getCost(int v1, int v2) const;

    void addEdge(int v1, int v2, int cost = 0);
    void removeEdge(int v1, int v2);

    void addVertex(int v);
    void removeVertex(int v);

    Graph& operator=(const Graph& g);

    bool operator==(const Graph&) const;
};

Graph readGraph(std::istream& in, bool weigthed = true, bool directed = true);
void printGraph(const Graph& g, std::ostream& out, bool weighted = true, bool directed = true);
Graph generateRandomGraph(int noVertices, int noEdges, bool cost = false);