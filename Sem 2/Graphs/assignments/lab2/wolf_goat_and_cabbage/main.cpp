#include "../Graph/Graph.h"
#include <iostream>
#include <map>
#include <queue>

using std::map, std::cout;

const int STATES = 1 << 4;

bool isSafe(int state){
    return ((state & 0b1100) != 0b1100) && ((state & 0b110) != 0b110) || (state & 1);
}

bool isValid(int state){
    int sourceBank = state;
    int destBank = (~sourceBank) & 0xF;

    return isSafe(sourceBank) && isSafe(destBank);
}

Graph createGraph(){
    Graph g(STATES);
    //wgcb

    for(int state = 0; state < STATES; ++state){
        if(!isValid(state)) continue;
        for(int i = 1; i < 4; ++i){
            if(((state >> i) & 1) == (state & 1)){
                int newState = state ^ (1 << i) ^ 1;
                if(isValid(newState)){
                    g.addEdge(state, newState);
                }
            }
        }
        int newState = state ^ 1;
        if(isValid(newState)){
            g.addEdge(state, newState);
        }
    }

    return g;
}

map<int, int> BFS(int start, int end, Graph& g){
    map<int, int> parent;
    set<int> visited;
    std::queue<int> q;
    visited.insert(start);
    q.push(start);
    while(!q.empty() && !visited.contains(end)){
        int node = q.front();
        q.pop();
        for(auto neighbour: g.getOutboundNeighbours(node)){
            if(!visited.contains(neighbour)){
                visited.insert(neighbour);
                parent[neighbour] = node;
                q.push(neighbour);
            }
        }
    }

    return parent;
}

void printState(int state){
    std::string source = "", dest = "";
    if(state & 0x8){
        source += "W ";
    }else{
        dest += "W ";
    }
    if(state & 0x4){
        source += "G ";
    }else{
        dest += "G ";
    }
    if(state & 0x2){
        source += "C ";
    }else{
        dest += "C ";
    }
    if(state & 1){
        source += "B ";
    }else{
        dest = "B " + dest;
    }

    cout << source << "| " << dest << '\n';
}

void printPathRec(int start, int end, map<int, int>& parent){
    if(start == end){
        printState(end);
        return;
    }
    printPathRec(start, parent[end], parent);
    cout << "\t|\n\t|\n\tV\n";
    printState(end);
}

int main(){
    auto g = createGraph();
    auto parent = BFS(STATES - 1, 0, g);
    printPathRec(STATES - 1, 0, parent);

    return 0;
}