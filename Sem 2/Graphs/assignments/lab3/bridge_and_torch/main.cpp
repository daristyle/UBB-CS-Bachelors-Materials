#include "../Graph/Graph.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>

using std::cin, std::cout, std::vector;

Graph createGraph(const vector<int>& v){
    int n = v.size();
    int states = (1 << (n + 1));
    Graph g(states);
    for(int state = 0; state < states; ++state){
        for(int i = 1; i <= n; ++i){
            if(((state >> i) & 1) == (state & 1)){
                for(int j = i + 1; j <= n; ++j){
                    if(((state >> j) & 1) == (state & 1)){
                        int newState = state ^ (1 << i) ^ (1 << j) ^ 1;
                        g.addEdge(state, newState, std::max(v[i - 1], v[j - 1]));
                    }
                }
                int newState = state ^ (1 << i) ^ 1;
                g.addEdge(state, newState, v[i - 1]);
            }
        }
    }

    return g;
}

pair<map<int, int>, map<int, int>> Dijkstra(int start, int end, Graph& g){
    map<int, int> dist, parent;
    std::priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int, int>>> pq;
    dist[start] = 0;
    parent[start] = start;
    pq.push({0, start});
    bool discovered = false;
    while(!pq.empty() && !discovered){
        auto [distance, node] = pq.top();
        pq.pop();
        discovered = node == end;
        if(dist[node] < distance) continue;
        for(auto neighbour: g.getOutboundNeighbours(node)){
            if(!dist.contains(neighbour) || dist[neighbour] > dist[node] + g.getCost(node, neighbour)){
                dist[neighbour] = dist[node] + g.getCost(node, neighbour);
                parent[neighbour] = node;
                pq.push({dist[neighbour], neighbour});
            }
        }
    }

    return {parent, dist};
}

void printState(int state, int n){
    std::string left, right;
    for(int i = 1; i <= n; ++i){
        if((state >> i) & 1){
            right += std::to_string(i);
            right += " ";
        }else{
            left += std::to_string(i);
            left += " ";
        }
    }
    if(state & 1){
        right = "F " + right;
    }else{
        left += "F ";
    }

    cout << left << "| " << right << '\n';
}

void printPathRec(int start, int end, map<int, int>& parent, map<int, int>& dist, int n){
    if(start == end){
        printState(start, n);
        return;
    }
    printPathRec(start, parent[end], parent, dist, n);
    int time = dist[end] - dist[parent[end]];
    std::string s = "";
    for(int i = 0; i < n / 5 + 1; ++i){
        s += "\t";
    }
    std::cout << s + "|\n" + s + "| " << time << "\n" + s + "V\n";
    printState(end, n);
}

int main(){
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; ++i){
        cin >> v[i];
    }

    Graph g = createGraph(v);
    cout<<"created\n";
    auto [parent, dist] = Dijkstra(0, (1 << (n + 1)) - 1, g);
    printPathRec(0, (1 << (n + 1)) - 1, parent, dist, n);
    cout << "The total time is " << dist[(1 << (n + 1)) - 1] << '\n';

    return 0;
}