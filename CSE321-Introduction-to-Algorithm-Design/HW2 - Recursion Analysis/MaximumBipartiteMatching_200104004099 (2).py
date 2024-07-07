# fromVertex and toVertex field are just vertexId's as integer.
class Edge:
    def __init__(this, fromVertex, toVertex):
        this.fromVertex = fromVertex
        this.toVertex = toVertex
        this.capacity = 1
        this.flow = 0

    def toString(self):
        return self.fromVertex + "-" + self.targetVertex + "-" + self.flow + "--" + self.capacity

    # Get the vertex at the other end of the edge.
    def otherVertex(self, vertex):
        if (self.fromVertex == vertex):
            return self.toVertex
        return self.fromVertex
    
    def residualCapacity(self, vertex):
        if (self.fromVertex == vertex):
            return self.capacity - self.flow
        return self.flow
    
    def addFlow(self, vertex, newFlow):
        # If newFlow is come in the forward way, then decrease the flow since flow in the Edge is the remaining flows in forward way.
        if (self.fromVertex == vertex):
            self.flow = self.flow + newFlow
        else:
            self.flow = self.flow - newFlow 

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

class MaximumBipartiteMatching:
    def __init__(self, graph):
        self.graph = graph

    def findMaximumBipartiteMatching(self):
        # Create the flow graph.
        self.addSourceAndTargetVertexes()
        source = self.graph.numV - 2
        target = self.graph.numV - 1

        # Find the maximum flow in the flow graph.
        maxFlow = 0

        # Initialize the parents array.
        parents = []
        for i in range(0, self.graph.numV):
            parents.append(None)

        while (self.checkAugmentingPath(parents, source, target)):
            # It's same for all edges in bipartite graph.
            minResidualFlow = 1

            curVertex = target
            while (curVertex != source):
                edge = parents[curVertex]
                otherVertex = edge.otherVertex(curVertex)

                edge.addFlow(otherVertex, minResidualFlow)

                curVertex = otherVertex
    
            maxFlow = maxFlow + minResidualFlow

        return maxFlow


    def checkAugmentingPath(self, parents, source, target):
         # Initialize the visited array.
        visited = []
        for i in range(0, self.graph.numV):
            visited.append(False)

        queue = []
        queue.append(source)
        visited[source] = True
        while not (len(queue) == 0) and not (visited[target]):
            curVertex = queue.pop(0)

            # Iterate through the edges on this vertex.
            for edge in self.graph.adjacencyList[curVertex]:
                if (edge.residualCapacity(curVertex) > 0) and not(visited[edge.otherVertex(curVertex)]):
                    parents[edge.otherVertex(curVertex)] = edge
                    queue.append(edge.otherVertex(curVertex))
                    visited[edge.otherVertex(curVertex)] = True

        return visited[target]
                
    # This method finds the two sets of vertexes in the bipartite graph.
    # Then create edges from source to set1 vertexes.
    # And edges from set2 vertexes to target.
    # Finally, a flow graph is created.
    def addSourceAndTargetVertexes(self):
        sets = []
        set1 = []
        set2 = []
        sets.append(set1)
        sets.append(set2)
        
        # Initialize the colors array.
        # Initialize the colors as -1 as none of them has color at first.
        colors = []
        for i in range(0, self.graph.numV):
            colors.append(-1)

        # Initialize the visited array.
        visited = []
        for i in range(0, self.graph.numV):
            visited.append(False)

        for i in range(0, self.graph.numV):
            if (not visited[i]):
                self.runBfsAndColorConnectedVertexes(sets, colors, visited, i)

        # Print two sets for testing.
        print("Set0: ")
        for vertex in sets[0]:
            print(vertex)
        
        print("Set1: ")
        for vertex in sets[1]:
            print(vertex)

        # Add source and target vertex. And edges from source -> set1's vertex, set2 vertex -> target.
        sourceVertex = self.graph.addVertex()
        targetVertex = self.graph.addVertex()

        for set1Vertex in set1:
            edge = Edge(sourceVertex, set1Vertex)
            self.graph.addEdge(edge)
        
        for set2Vertex in set2:
            edge = Edge(set2Vertex, targetVertex)
            self.graph.addEdge(edge)

    # Run bfs starting from the given vertex. 
    # Assumption: The vertex is not visited so it's not colored before.
    def runBfsAndColorConnectedVertexes(self, sets, colors, visited, i):
        queue = []
        queue.append(i)
        colors[i] = 0   # Initialize the color of the first vertex as 0.
        sets[0].append(i)     # Put the current vertex into the set0.
        while not (len(queue) == 0):
            vertexId = queue.pop(0)
            visited[vertexId] = True

            # Find the opposite color
            oppositeColor = 1
            if (colors[vertexId] == oppositeColor):
                oppositeColor = 0
            

            # Iterate through the adjacent vertexes and set their colors.
            adjacencyList = self.graph.adjacencyList[vertexId]
            for edge in adjacencyList:
                adjacentVertex = edge.otherVertex(vertexId)
                if (not visited[adjacentVertex]):
                    colors[adjacentVertex] = oppositeColor
                    sets[oppositeColor].append(adjacentVertex)
                    queue.append(adjacentVertex)

def main():
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
    graph.addEdge(Edge(0, 2))
    graph.addEdge(Edge(0, 3))
    graph.addEdge(Edge(1, 2))

    maximumBipartiteMatching = MaximumBipartiteMatching(graph)
    print("RESULT: " + str(maximumBipartiteMatching.findMaximumBipartiteMatching()))

main()