from parted import freeAllDevices

from graph import *

def printMenu():
    print("1.Read graph 1k")
    print("2.Read graph 10k")
    print("3.Read graph 100k")
    print("4.Read graph 1m")
    print("5.Add vertex")
    print("6.Remove vertex")
    print("7.Add edge")
    print("8.Remove edge")
    print("9.Update edge")
    print("10.Generate random graph with 6 vertices and 20 edges")
    print("11.Generate random graph with 7 vertices and 40 edges")
    print("12.Display the outbound edges of a vertex")
    print("13.Display the inbound edges of a vertex")
    print("14.Display the cost of an edge")
    print("15.Display the number of vertices")
    print("16.Display the number of edges")
    print("17.Save graph")
    print("0.Exit")

def saveGraph(g, filename):
    if filename == "":
        return;
    printGraph(g, filename)

def main():
    exited = False
    g = Graph(0)
    file = ""
    while not exited:
        printMenu()
        choice = input("Enter your choice: ")
        if choice == "1":
            saveGraph(g, file)
            g = readGraph("graph1k.txt")
            file = "graph1k_modif.txt"
        elif choice == "2":
            saveGraph(g, file)
            g = readGraph("graph10k.txt")
            file = "graph10k_modif.txt"
        elif choice == "3":
            saveGraph(g, file)
            g = readGraph("graph100k.txt")
            file = "graph100k_modif.txt"
        elif choice == "4":
            saveGraph(g, file)
            g = readGraph("graph1m.txt")
            file = "graph1m_modif.txt"
        elif choice == "5":
            v = int(input("Enter the vertex to add: "))
            g.addVertex(v)
        elif choice == "6":
            v = int(input("Enter the vertex to remove: "))
            g.removeVertex(v)
        elif choice == "7":
            x = int(input("Enter the source vertex: "))
            y = int(input("Enter the destination vertex: "))
            cost = int(input("Enter the cost: "))
            g.addEdge(x, y, cost)
        elif choice == "8":
            x = int(input("Enter the source vertex: "))
            y = int(input("Enter the destination vertex: "))
            g.removeEdge(x, y)
        elif choice == "9":
            x = int(input("Enter the source vertex: "))
            y = int(input("Enter the destination vertex: "))
            cost = int(input("Enter the new cost: "))
            g.setCost(x, y, cost)
        elif choice == "10":
            saveGraph(g, file)
            g = randomGraph(6, 20)
            file = "random_graph1.txt"
            saveGraph(g, file)
        elif choice == "11":
            saveGraph(g, file)
            g = randomGraph(7, 40)
            file = "random_graph2.txt"
            saveGraph(g, file)
        elif choice == "12":
            v = int(input("Enter the vertex: "))
            output = ""
            for u in g.getOutNeighbours(v):
                output += f"{u}, "
            output = output[:-2]
            print(output)
        elif choice == "13":
            v = int(input("Enter the vertex: "))
            output = ""
            for u in g.getInNeighbours(v):
                output += f"{u}, "
            output = output[:-2]
            print(output)
        elif choice == "14":
            x = int(input("Enter the source vertex: "))
            y = int(input("Enter the destination vertex: "))
            print(f"The cost of the edge from {x} to {y} is {g.getCost(x, y)}")
        elif choice == "15":
            print(f"The number of vertices is {g.noVertices()}")
        elif choice == "16":
            print(f"The number of edges is {g.noEdges()}")
        elif choice == "17":
            saveGraph(g, file)
        elif choice == "0":
            saveGraph(g, file)
            print("Bye bye!")
            exited = True
        else:
            print("Invalid choice")

if __name__ == "__main__":
    main()