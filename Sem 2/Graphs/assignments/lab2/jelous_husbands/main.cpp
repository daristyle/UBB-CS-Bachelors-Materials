#include "../Graph/Graph.h"

#include <iostream>
#include <queue>

using std::map, std::queue, std::cout;

const int STATES = 1 << 7;

bool isBankSafe(int bank){
    if((bank >> 3) == 0 || (bank & 0x7) == 0) return true;
    int m_mask = 0x20, w_mask = 0x4;
    for(int i = 0; i < 3; ++i){
        if((bank & w_mask)){
            if(!(bank & m_mask)){
                return false;
            }
        }
        m_mask >>= 1;
        w_mask >>= 1;
    }
    return true;
}

bool isValid(int state){
    int sourceBank = state >> 1;
    int destBank = (~sourceBank)&0x3F;
    return isBankSafe(sourceBank) && isBankSafe(destBank);
}

Graph createGraph(){
    //m1m2m3w1w2w3b
    Graph g(STATES);

    for(int state = 0; state < STATES; ++state){
        if(state == 127){
            cout << "";
        }
        if(isValid(state)){
            for(int i = 1; i < 7; ++i){
                if(((state >> i) & 1) == (state & 1)){
                    for(int j = i + 1; j < 7; ++j){
                        if(((state >> j) & 1) == (state & 1)){
                            int newState = state ^ (1 << i) ^ (1 << j) ^ 1;
                            if(isValid(newState)){
                                g.addEdge(state, newState);
                            }
                        }
                    }
                    int newState = state ^ (1 << i) ^ 1;
                    if(isValid(newState)){
                        g.addEdge(state, newState);
                    }
                }
            }
        }
    }

    return g;
}

map<int, int> BFS(int start, int end, Graph& g){
    map<int, int> parent, dist;
    queue<int> q;
    q.push(start);
    dist[start] = 1;
    while(!q.empty() && dist[end] == 0){
        int state = q.front();
        q.pop();
        for(int neighbour : g.getOutboundNeighbours(state)){
            if(dist[neighbour] == 0){
                dist[neighbour] = dist[state] + 1;
                parent[neighbour] = state;
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
    char type = 'M';
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
            type = 'W';
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
    auto g = createGraph();
    auto parent = BFS(STATES - 1, 0, g);

    cout << isValid(0b0110000);
    printPathRec(STATES - 1, 0, parent);

    return 0;
}