#include <iostream>
#include <fstream>

#include "Graph.h"

using namespace std;

void printMenu(){
    cout << "1.Read graph 1k\n"
         << "2.Read graph 10k\n"
         << "3.Read graph 100k\n"
         << "4.Read graph 1m\n"
         << "5.Add vertex\n"
         << "6.Remove vertex\n"
         << "7.Add edge\n"
         << "8.Remove edge\n"
         << "9.Update edge\n"
         << "10.Generate random graph with 6 vertices and 20 edges\n"
         << "11.Generate random graph with 7 vertices and 40 edges\n"
         << "12.Display the outbound edges of a vertex\n"
         << "13.Display the inbound edges of a vertex\n"
         << "14.Display the cost of an edge\n"
         << "15.Display the number of vertices\n"
         << "16.Display the number of edges\n"
         << "17.Save graph\n"
         << "0.Exit\n";
}

void saveGraph(Graph& g, string file){
    if(file == "") return;
    ofstream fout(file);
    printGraph(g, fout);
}

Graph readGraph(string file){
    ifstream fin(file);
    return readGraph(fin);
}

int main(){
    bool exited = false;
    string file = "", command = "";
    Graph g(0);
    while(!exited){
        printMenu();
        cout << "Enter command: ";
        cin >> command;
        if(command == "1"){
            saveGraph(g, file);
            g = readGraph("graph1k.txt");
            file = "graph1k_modif.txt";
        }else if(command == "2"){
            saveGraph(g, file);
            g = readGraph("graph10k.txt");
            file = "graph10k_modif.txt";
        }else if(command == "3"){
            saveGraph(g, file);
            g = readGraph("graph100k.txt");
            file = "graph100k_modif.txt";
        }else if(command == "4"){
            saveGraph(g, file);
            g = readGraph("graph1m.txt");
            file = "graph1m_modif.txt";
        }else if(command == "5"){
            int v;
            cout << "Enter vertex: ";
            cin >> v;
            g.addVertex(v);
        }else if(command == "6"){
            int v;
            cout << "Enter vertex: ";
            cin >> v;
            g.removeVertex(v);
        }else if(command == "7"){
            int v1, v2, cost;
            cout << "Enter vertex 1: ";
            cin >> v1;
            cout << "Enter vertex 2: ";
            cin >> v2;
            cout << "Enter cost: ";
            cin >> cost;
            g.addEdge(v1, v2, cost);
        }else if(command == "8"){
            int v1, v2;
            cout << "Enter vertex 1: ";
            cin >> v1;
            cout << "Enter vertex 2: ";
            cin >> v2;
            g.removeEdge(v1, v2);
        }else if(command == "9"){
            int v1, v2, cost;
            cout << "Enter vertex 1: ";
            cin >> v1;
            cout << "Enter vertex 2: ";
            cin >> v2;
            cout << "Enter cost: ";
            cin >> cost;
            g.setCost(v1, v2, cost);
        }else if(command == "10"){
            saveGraph(g, file);
            g = generateRandomGraph(6, 20, true);
            file = "random_graph1.txt";
            saveGraph(g, file);
        }else if(command == "11"){
            saveGraph(g, file);
            g = generateRandomGraph(7, 40, true);
            file = "random_graph2.txt";
            saveGraph(g, file);
        }else if(command == "12"){
            int v;
            cout << "Enter vertex: ";
            cin >> v;
            cout << "Outbound edges: ";
            for(auto i : g.getOutboundNeighbours(v)){
                cout << i << ", ";
            }
            cout << '\n';
        }else if(command == "13"){
            int v;
            cout << "Enter vertex: ";
            cin >> v;
            cout << "Inbound edges: ";
            for(auto i : g.getInboundNeighbours(v)){
                cout << i << ", ";
            }
            cout << '\n';
        }else if(command == "14"){
            int v1, v2;
            cout << "Enter vertex 1: ";
            cin >> v1;
            cout << "Enter vertex 2: ";
            cin >> v2;
            cout << g.getCost(v1, v2) << '\n';
        }else if(command == "15"){
            cout << "Number of vertices: " << g.noVertices() << '\n';
        }else if(command == "16"){
            cout << "Number of edges: " << g.noEdges() << '\n';
        }else if(command == "17"){
            saveGraph(g, file);
        }else if(command == "0"){
            saveGraph(g, file);
            cout << "Bye bye!";
            exited = true;
        }else{
            cout << "Invalid command\n";
        }
    }

    return 0;
}