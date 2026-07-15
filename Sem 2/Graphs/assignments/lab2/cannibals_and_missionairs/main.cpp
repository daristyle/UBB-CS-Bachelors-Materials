#include "../Graph/Graph.h"
#include <iostream>
#include <map>
#include <queue>

using std::map, std::cout;

const int STATES = 1 << 7;

bool isSafe(int bank){
    if(!(bank & 0b111)) return true;
    int missionairs = 0, cannibals = 0;
    for(int i = 0; i < 3; i++){
        missionairs += bank & 1;
        bank >>= 1;
    }
    for(int i = 0; i < 3; i++){
        cannibals += bank & 1;
        bank >>= 1;
    }
    return missionairs >= cannibals;
}

bool isValid(int state){
    int sourceBank = state >> 1;
    int destBank = (~sourceBank) & 0x3F;

    return isSafe(sourceBank) && isSafe(destBank);
}

Graph makeGraph(){
    //c1c2c3m1m2m3b
    Graph g(STATES);
    for(int state = 0; state < STATES; state++){
        if(!isValid(state)) continue;
        for(int i = 1; i < 7; ++i){
            if(((state >> i) & 1) != (state & 1)) continue;
            for(int j = i + 1; j < 7; ++j){
                if(((state >> j) & 1) != (state & 1)) continue;
                int newState = state ^ (1 << i) ^ (1 << j) ^ 1;
                if(isValid(newState)){
                    g.addEdge(state, newState);
                }
            }
            int newState = state ^ (1 << i) ^ 1;
            if(isValid(newState)){
                g.addEdge(state, newState);
            }
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
        for(int neighbour : g.getOutboundNeighbours(node)){
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
    int mask = 0x40;
    int i = 1;
    char type = 'C';
    for(int j = 0; j < 6; j++){
        if(state & mask){
            source += type;
            source += std::to_string(i);
            source += ' ';
        }else{
            dest += type;
            dest += std::to_string(i);
            dest += ' ';
        }
        ++i;
        mask >>= 1;
        if(mask == 0x8){
            type = 'M';
            i = 1;
        }
    }
    if(state & 1){
        source += "B ";
    }else{
        dest = "B " + dest;
    }
    cout << source << "| "  << dest << '\n';
}

void printPathRec(int start, int end, map<int, int>& parent){
    if(start == end){
        printState(end);
        return;
    }
    printPathRec(start, parent[end], parent);
    cout << "\t\t|\n\t\t|\n\t\tV\n";
    printState(end);
}

int main(){
    auto g= makeGraph();
    auto parent = BFS(STATES - 1, 0, g);
    printPathRec(STATES - 1, 0, parent);

    return 0;
}