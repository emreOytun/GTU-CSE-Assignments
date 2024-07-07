# fromVertex and toVertex field are just vertexId's as integer.
class Edge:
    def __init__(this, fromVertex, toVertex, latency):
        this.fromVertex = fromVertex
        this.toVertex = toVertex
        this.latency = latency

    # Get the vertex at the other end of the edge.
    def otherVertex(self, vertex):
        if (self.fromVertex == vertex):
            return self.toVertex
        return self.fromVertex
    
class Graph:
    def __init__(self, numV):
        self.numV = numV
        self.numE = 0
        self.adjacencyList = []

        # Initialize the adjacencyList as the edge lists are empty.
        for i in range(0, numV):
            edges = []
            self.adjacencyList.append(edges)

    # Add the new edge in the edge list of the two vertexes. 
    # It doesn't matter if the graph is directed or undirected. It can be treated accordingly.
    def addEdge(self, edge):
        fromV = edge.fromVertex
        toV = edge.toVertex
        self.adjacencyList[fromV].append(edge)
        self.adjacencyList[toV].append(edge)
        self.numE = self.numE + 1

    def getAdjacencyList(self, vertex):
        return self.adjacencyList[vertex]
            
    def addVertex(self):
        edges = []
        self.adjacencyList.append(edges)
        self.numV = self.numV + 1
        return len(self.adjacencyList) - 1
    
minLatency = float('inf')
minPath = []
def findMinLatency(graph, sourceVertex, targetVertex):
    path = []
    visited = []
    for i in range(0, graph.numV):
        visited.append(False)

    global minLatency
    minLatency = float('inf')
    findMinLatencyHelper(graph, sourceVertex, targetVertex, visited, path, 0)
    minPath.append(targetVertex)
    return minPath, minLatency

# Recursive helper function that runs DFS to explore all possible paths.
def findMinLatencyHelper(graph, sourceVertex, targetVertex, visited, path, totalLatency):
    if (sourceVertex == targetVertex) :
        global minLatency
        if (totalLatency < minLatency) :
            global minPath
            minLatency = totalLatency
            minPath = path[:]
        return
    
    visited[sourceVertex] = True
    path.append(sourceVertex)

    adjacencyList = graph.adjacencyList[sourceVertex]
    for edge in adjacencyList:
        adjacentVertex = edge.otherVertex(sourceVertex)
        if (not visited[adjacentVertex]) :
            findMinLatencyHelper(graph, adjacentVertex, targetVertex, visited, path, totalLatency + edge.latency)

    visited[sourceVertex] = False
    path.pop()

def main() :
    # TEST1
    #graph = Graph(5)

    #edge1 = Edge(0, 2)
    #edge2 = Edge(1, 2)
    #edge3 = Edge(3, 4)

    #graph.addEdge(edge1)
    #graph.addEdge(edge2)
    #graph.addEdge(edge3)
    
    # TEST2
    graph = Graph(4)
    graph.addEdge(Edge(0, 1, 1))
    graph.addEdge(Edge(0, 2, 3))
    graph.addEdge(Edge(1, 3, 1))
    graph.addEdge(Edge(2, 3, 3))
    minPath, minLatency = findMinLatency(graph, 0, 3)
    print("Vertexes in min path: " + str(minPath) + " Min latency: " + str(minLatency))

main()
    
