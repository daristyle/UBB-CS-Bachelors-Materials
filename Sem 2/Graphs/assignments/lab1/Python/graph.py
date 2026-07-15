from random import randint

class Graph:
    def __init__(self, no_vertices):
        self._out_neighbors = dict()
        self._in_neighbors = dict()
        self._vertices = set()
        self._cost = dict()
        for i in range(no_vertices):
            self._out_neighbors[i] = set()
            self._in_neighbors[i] = set()
            self._vertices.add(i)

    def addEdge(self, x, y, cost = 0):
        if y not in self._out_neighbors[x]:
            self._out_neighbors[x].add(y)
            self._in_neighbors[y].add(x)
            self._cost[x, y] = cost

    def getVertices(self):
        return iter(self._vertices)

    def getOutNeighbours(self, vertex):
        return iter(self._out_neighbors[vertex])

    def getInNeighbours(self, vertex):
        return iter(self._in_neighbors[vertex])

    def noEdges(self):
        return len(self._cost)

    def noVertices(self):
        return len(self._vertices)

    def isEdge(self, x, y):
        return y in self._out_neighbors[x]

    def inDegree(self, vertex):
        return len(self._in_neighbors[vertex])

    def outDegree(self, vertex):
        return len(self._out_neighbors[vertex])

    def setCost(self, x, y, cost):
        if not self.isEdge(x, y):
            return
        self._cost[x, y] = cost

    def getCost(self, x, y):
        return self._cost[x, y]

    def removeEdge(self, x, y):
        if not self.isEdge(x, y):
            return
        self._out_neighbors[x].remove(y)
        self._in_neighbors[y].remove(x)
        del self._cost[x, y]

    def addVertex(self, vertex):
        self._vertices.add(vertex)
        self._out_neighbors[vertex] = set()
        self._in_neighbors[vertex] = set()

    def removeVertex(self, vertex):
        self._vertices.remove(vertex)
        for x in self._out_neighbors[vertex]:
            self._in_neighbors[x].remove(vertex)
            del self._cost[vertex, x]
        for x in self._in_neighbors[vertex]:
            self._out_neighbors[x].remove(vertex)
            del self._cost[x, vertex]
        del self._out_neighbors[vertex]
        del self._in_neighbors[vertex]

    def copy(self):
        other = Graph(self.noVertices())
        other._out_neighbors = self._out_neighbors.copy()
        other._in_neighbors = self._in_neighbors.copy()
        other._vertices = self._vertices.copy()
        other._cost = self._cost.copy()
        return other


def readGraph(filename):
    with open(filename, "r") as f:
        print("Reading graph...")
        line = f.readline()
        n, m = map(int, line.split())
        g = Graph(n)
        for i in range(m):
            line = f.readline()
            x, y, cost = map(int, line.split())
            g.addEdge(x, y, cost)
            if (i + 1) % 100000 == 0:
                print(f"Read {i + 1} edges")

        print("Graph read!")
        return g

    return Graph(0)

def printGraph(g, filename):
    with open(filename, "w") as f:
        f.write(f"{g.noVertices()} {g.noEdges()}\n")
        for x in g.getVertices():
            for y in g.getOutNeighbours(x):
                f.write(f"{x} {y} {g.getCost(x, y)}\n")

def randomGraph(n, m, cost = False):
    g = Graph(n)
    edges_to_be_added = m
    edges_slots_left = n * n
    for i in range(0, n):
        for j in range(0, n):
            prob = randint(0, edges_slots_left - 1)
            if prob < edges_to_be_added:
                val = randint(0, 100) if cost else 0
                g.addEdge(i, j, val)
                edges_to_be_added -= 1
                if edges_to_be_added == 0:
                    return g
            edges_slots_left -= 1

    return g
