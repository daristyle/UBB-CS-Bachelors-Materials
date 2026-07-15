#include "../Graph/Graph.h"
#include <iostream>
#include <fstream>
#include <map>
#include <queue>

using std::map;

map<int, int> forwardBFS(int start, int end, Graph& g){
    map<int, int> parent;
    std::queue<int> q;
    parent[start] = start;
    q.push(start);
    while(!q.empty() && !parent.contains(end)){
        int node = q.front();
        q.pop();
        for(auto neighbour: g.getOutboundNeighbours(node)){
            if(!parent.contains(neighbour)){
                parent[neighbour] = node;
                q.push(neighbour);
            }
        }
    }

    return parent;
}

void printPathRec(int start, int end, int length, map<int, int>& parent, std::ostream& out, bool first = true){
    if(start == end){
        out << length + 1 << '\n';
        out << start;
    }else{
        printPathRec(start, parent[end], length + 1, parent, out, false);
        out << end;
    }
    if(!first){
        out << " -> ";
    }else{
        out << '\n';
    }
}

void printPath(int start, int end, Graph& g, std::ostream& out){
    auto parent = forwardBFS(start, end, g);

    if(!parent.contains(end)){
        out << "There is no path from " << start << " to " << end << "!\n";
        return;
    }

    printPathRec(start, end, 0, parent, out);
}

void testBasicGraph(std::string name){
    std::ifstream fin{name +".in"};
    std::ofstream fout{name +".out"};

    Graph g = readGraph(fin, true, true);

    printPath(1, 100, g, fout);
    printPath(100, 1, g, fout);
}

void testGraph1(){
    std::ifstream fin{"graph1.in"};
    std::ofstream fout{"graph1.out"};

    Graph g = readGraph(fin, false, true);

    printPath(3, 4, g, fout);}

void testGraph2(){
    std::ifstream fin{"graph2.in"};
    std::ofstream fout{"graph2.out"};

    Graph g = readGraph(fin, false, true);

    printPath(0, 1, g, fout);
}

int main(){
    /*testBasicGraph("graph1k");
    testBasicGraph("graph10k");
    testBasicGraph("graph100k");
    testBasicGraph("graph1m");
*/
    testGraph1();
    testGraph2();

    return 0;
}
//Ciorbe George