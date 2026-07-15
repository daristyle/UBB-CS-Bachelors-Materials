#include "../Graph/Graph.h"
#include <fstream>
#include <map>
#include <set>
#include <stack>
#include <iostream>

using std::map, std::set, std::cout, std::stack, std::pair;

void HopcroftTarjanBCC(int node, int currentDepth, int parent, Graph& g, map<int, int>& depth, map<int, int>& lowlink,
                    stack<pair<int, int>>& edgeStack, vector<Graph>& BCCs){
    lowlink[node] = depth[node] = currentDepth;
    for(auto neighbour: g.getOutboundNeighbours(node)){
        if(neighbour == parent) continue;
        if(!depth.contains(neighbour)){
            edgeStack.push({node, neighbour});

            HopcroftTarjanBCC(neighbour, currentDepth + 1, node, g, depth, lowlink,edgeStack, BCCs);
            lowlink[node] = std::min(lowlink[node], lowlink[neighbour]);

            if(lowlink[neighbour] >= depth[node]){
                Graph BCC;
                pair<int, int> edge;
                do{
                    edge = edgeStack.top();
                    edgeStack.pop();
                    if(!BCC.isVertex(edge.first)){
                        BCC.addVertex(edge.first);
                    }
                    if(!BCC.isVertex(edge.second)){
                        BCC.addVertex(edge.second);
                    }
                    BCC.addEdge(edge.first, edge.second);
                    BCC.addEdge(edge.second, edge.first);
                }while(edge != std::make_pair(node, neighbour));

                BCCs.push_back(BCC);
            }
        }else if(depth[node] > depth[neighbour]){
            edgeStack.push({node, neighbour});

            lowlink[node] = std::min(lowlink[node], depth[neighbour]);
        }
    }
}

int main(){
    std::ifstream fin{"graph5.in"};
    std::ofstream fout{"graph5.out"};

    Graph g = readGraph(fin, false, false);
    map<int, int> depth, lowlink;
    stack<pair<int, int>> edgeStack;
    vector<Graph> BCCs;

    for(auto v: g.getVertices()){
        if(!depth.contains(v)){
            HopcroftTarjanBCC(v, 0, -1, g, depth, lowlink, edgeStack, BCCs);
        }
    }

    for(const auto& bcc: BCCs){
        printGraph(bcc, fout, false,false);
        fout << "------------------------------------------------------------------------------------" << std::endl;
    }

    return 0;
}