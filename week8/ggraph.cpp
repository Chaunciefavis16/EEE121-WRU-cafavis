#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <algorithm>
#include <queue>
#include <limits>

using namespace std;

class Graph
{
private:
    vector<vector<int>> adjacencyList;
    vector<char> vertices;
    int numVertices;
    bool isDirected; // Flag to track if the graph is directed or undirected
    int edgeCount;

public:
    Graph()
    {
        numVertices = 0;
        isDirected = false; // Initialize as undirected by default
        edgeCount = 0;      // Initialize edge count to 0
    }

    void clearGraph()
    {
        adjacencyList.clear();
        vertices.clear();
        numVertices = 0;
    }

    void directedInit(int vertices)
    {
        clearGraph();
        numVertices = vertices;
        adjacencyList.resize(numVertices, vector<int>(numVertices, 0));
        cout << "Directed graph initialized with " << numVertices << " vertices." << endl;
        for (int i = 0; i < numVertices; ++i)
        {
            this->vertices.push_back('A' + i);
        }
        isDirected = true;
    }

    void undirectedInit(int vertices)
    {
        clearGraph();
        numVertices = vertices;
        adjacencyList.resize(numVertices, vector<int>(numVertices, 0));
        cout << "Undirected graph initialized with " << numVertices << " vertices." << endl;
        for (int i = 0; i < numVertices; ++i)
        {
            this->vertices.push_back('A' + i);
        }
        isDirected = false;
    }

    void printMatrixRepresentation()
    {
        cout << "Number of vertices: " << numVertices << endl;
        cout << "Number of edges: " << countEdges() << endl;

        cout << setw(4) << " ";
        for (int i = 0; i < numVertices; ++i)
        {
            cout << setw(3) << "[" << vertices[i] << "] ";
        }
        cout << endl;

        for (int i = 0; i < numVertices; ++i)
        {
            cout << "[" << vertices[i] << "] ";
            for (int j = 0; j < numVertices; ++j)
            {
                cout << setw(5) << adjacencyList[i][j] << " ";
            }
            cout << endl;
        }
    }

    int countEdges()
    {
        return edgeCount;
    }

    void addVertex(char name)
    {
        if (find(vertices.begin(), vertices.end(), name) != vertices.end())
        {
            cout << "Vertex " << name << " already exists." << endl;
        }
        else
        {
            vertices.push_back(name);
            numVertices++;
            adjacencyList.push_back(vector<int>(numVertices, 0));
            for (int i = 0; i < numVertices; ++i)
            {
                adjacencyList[i].push_back(0);
            }
            cout << "Vertex " << name << " added." << endl;
        }
    }

    void deleteVertex(char name)
    {
        auto it = find(vertices.begin(), vertices.end(), name);
        if (it != vertices.end())
        {
            int index = it - vertices.begin();
            vertices.erase(it);
            numVertices--;
            adjacencyList.erase(adjacencyList.begin() + index);
            cout << "Vertex " << name << " deleted." << endl;
        }
        else
        {
            cout << "Vertex " << name << " does not exist." << endl;
        }
    }

    void addEdge(char v1, char v2, int weight = -1)
    {
        if (weight <= 0)
        {
            cout << "Error: Invalid weight specified for edge addition." << endl;
            return;
        }

        int index1 = find(vertices.begin(), vertices.end(), v1) - vertices.begin();
        int index2 = find(vertices.begin(), vertices.end(), v2) - vertices.begin();
        if (index1 >= numVertices || index2 >= numVertices)
        {
            cout << "Invalid vertices specified for edge addition." << endl;
            return;
        }

        if (weight == -1)
        {
            cout << "Error: No weight specified for edge addition." << endl;
            return;
        }
        adjacencyList[index1][index2] = weight;
        if (!isDirected)
        {
            adjacencyList[index2][index1] = weight;
        }
        cout << "Edge added between vertices " << v1 << " and " << v2 << " with weight " << weight << "." << endl;
        // Increment the edge count
        edgeCount++;
    }

    void deleteEdge(char v1, char v2)
    {
        int index1 = find(vertices.begin(), vertices.end(), v1) - vertices.begin();
        int index2 = find(vertices.begin(), vertices.end(), v2) - vertices.begin();
        if (index1 >= numVertices || index2 >= numVertices)
        {
            cout << "Invalid vertices specified for edge deletion." << endl;
            return;
        }
        adjacencyList[index1][index2] = 0;
        if (!isDirected)
        {
            adjacencyList[index2][index1] = 0;
        }
        cout << "Edge deleted between vertices " << v1 << " and " << v2 << "." << endl;
        // Decrement the edge count
        edgeCount--;
    }

    void printAdjacencyList()
    {
        cout << "Number of vertices: " << numVertices << endl;
        cout << "Number of edges: " << countEdges() << endl;
        cout << "Adjacency list representation:" << endl;
        for (int i = 0; i < numVertices; ++i)
        {
            cout << vertices[i] << " -> ";
            for (int j = 0; j < numVertices; ++j)
            {
                if (adjacencyList[i][j] != 0)
                {
                    cout << vertices[j] << "(" << adjacencyList[i][j] << ") ";
                }
            }
            cout << endl;
        }
    }

    void shortestPath(char source, char destination)
    {
        int sourceIndex = find(vertices.begin(), vertices.end(), source) - vertices.begin();
        int destinationIndex = find(vertices.begin(), vertices.end(), destination) - vertices.begin();

        // Check if source and destination nodes exist
        if (sourceIndex >= numVertices || destinationIndex >= numVertices)
        {
            cout << "Invalid source or destination node." << endl;
            return;
        }

        // Initialize distances and predecessors
        vector<int> distance(numVertices, numeric_limits<int>::max());
        vector<int> predecessor(numVertices, -1);
        distance[sourceIndex] = 0;

        // Priority queue to store vertices and their distances
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, sourceIndex});

        // Process vertices using Dijkstra's algorithm
        while (!pq.empty())
        {
            // Print the current state of the table
            cout << "Vertex ds[v] pre[v]" << endl;
            for (int i = 0; i < numVertices; ++i)
            {
                cout << vertices[i] << setw(7) << distance[i];
                if (predecessor[i] != -1)
                    cout << setw(8) << vertices[predecessor[i]] << endl;
                else
                    cout << setw(8) << "-" << endl;
            }
            cout << endl;

            int u = pq.top().second;
            pq.pop();

            for (int v = 0; v < numVertices; ++v)
            {
                if (adjacencyList[u][v] != 0)
                {
                    int weight = adjacencyList[u][v];
                    if (distance[v] > distance[u] + weight)
                    {
                        distance[v] = distance[u] + weight;
                        predecessor[v] = u;
                        pq.push({distance[v], v});
                    }
                }
            }
        }

        // Print shortest path
        cout << "Shortest path from " << source << " to " << destination << ": ";
        vector<char> path;
        for (int v = destinationIndex; v != -1; v = predecessor[v])
        {
            path.push_back(vertices[v]);
        }
        reverse(path.begin(), path.end());
        for (char vertex : path)
        {
            cout << vertex << " ";
        }
        cout << endl;
    }
};

int main()
{
    Graph graph;

    string command_line;

    while (true)
    {
        cout << "Enter command: ";
        getline(cin, command_line);

        stringstream ss(command_line);
        string command;
        ss >> command;

        if (command == "DINIT")
        {
            int numVertices;
            ss >> numVertices;
            graph.directedInit(numVertices);
        }
        else if (command == "UINIT")
        {
            int numVertices;
            ss >> numVertices;
            graph.undirectedInit(numVertices);
        }
        else if (command == "VADD")
        {
            char name;
            ss >> name;
            graph.addVertex(name);
        }
        else if (command == "VDEL")
        {
            char name;
            ss >> name;
            graph.deleteVertex(name);
        }
        else if (command == "APRINT")
        {
            graph.printAdjacencyList();
        }
        else if (command == "EADD")
        {
            char v1, v2;
            int weight;
            ss >> v1 >> v2 >> weight;
            graph.addEdge(v1, v2, weight);
        }
        else if (command == "EDEL")
        {
            char v1, v2;
            ss >> v1 >> v2;
            graph.deleteEdge(v1, v2);
        }
        else if (command == "MPRINT")
        {
            graph.printMatrixRepresentation();
        }
        else if (command == "SPATH")
        {
            char source, destination;
            ss >> source >> destination;
            graph.shortestPath(source, destination);
        }
        else if (command == "EXIT")
        {
            cout << "Exiting program..." << endl;
            exit(0);
        }
        else
        {
            cout << "Unsupported command: " << command << endl;
        }
    }

    return 0;
}
