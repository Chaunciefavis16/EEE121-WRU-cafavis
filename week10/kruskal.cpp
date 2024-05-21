#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <algorithm>
#include <queue>
#include <limits>
#include <functional>
using namespace std;

class Graph
{
private:
    vector<char> vertices;
    bool isDirected; // Flag to track if the graph is directed or undirected
    int edgeCount;
    vector<int> predecessor;
    vector<vector<int>> mstAdjacencyList;
    vector<int> mstParent;

public:
    vector<int> parent;
    int numVertices;
    vector<vector<int>> adjacencyList;

    Graph()
    {
        numVertices = 0;
        isDirected = false; // Initialize as undirected by default
        edgeCount = 0;      // Initialize edge count to 0
        parent.clear();
        parent.resize(numVertices, -1);
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
    bool mstGenerated = false;

    void generateKruskalMST()
{
    vector<pair<int, pair<int, int>>> edges;

    // Collect all edges along with their weights
    for (int i = 0; i < numVertices; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (adjacencyList[i][j] != 0)
            {
                edges.push_back({adjacencyList[i][j], {i, j}});
            }
        }
    }

    // Sort edges by their weights
    sort(edges.begin(), edges.end());

    vector<int> parent(numVertices, -1);
    vector<int> rank(numVertices, 0);

    // Find function for union-find structure
    function<int(int)> find = [&](int u)
    {
        if (parent[u] == -1)
            return u;
        return parent[u] = find(parent[u]);
    };

    // Union function for union-find structure
    auto unionSets = [&](int u, int v)
    {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV)
        {
            if (rank[rootU] > rank[rootV])
                parent[rootV] = rootU;
            else if (rank[rootU] < rank[rootV])
                parent[rootU] = rootV;
            else
            {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    };

    mstAdjacencyList.clear();
    mstAdjacencyList.resize(numVertices, vector<int>(numVertices, 0));

    vector<pair<int, pair<int, int>>> mst;
    vector<bool> mstFlag(edges.size(), false);

    for (int k = 0; k < edges.size(); ++k)
    {
        auto [weight, edge] = edges[k];
        auto [u, v] = edge;

        if (find(u) != find(v))
        {
            mst.push_back({weight, {u, v}});
            mstAdjacencyList[u][v] = weight;
            mstAdjacencyList[v][u] = weight;
            unionSets(u, v);
            mstFlag[k] = true;
        }

        // Print intermediate disjoint sets
        cout << "DS: [";
        bool first = true;
        for (int i = 0; i < numVertices; ++i)
        {
            if (!first)
                cout << ", ";
            first = false;
            cout << "{";
            bool firstInSet = true;
            for (int j = 0; j < numVertices; ++j)
            {
                if (find(j) == i)
                {
                    if (!firstInSet)
                        cout << ", ";
                    firstInSet = false;
                    cout << vertices[j];
                }
            }
            cout << "}";
        }
        cout << "]" << endl;

        // Print priority queue status
        cout << "PQ: " << endl;
        cout << "Edge  Key  MST-flag" << endl;
        for (int i = 0; i < edges.size(); ++i)
        {
            auto [w, e] = edges[i];
            auto [x, y] = e;
            cout << "(" << vertices[x] << ", " << vertices[y] << ") " << w << " " << (mstFlag[i] ? "True" : "False") << endl;
        }
        cout << endl;
    }

    mstGenerated = true;
}


    void printKruskalMSTMatrix()
    {
        if (!mstGenerated)
        {
            cout << "KMST command must be invoked first before KMST-MPRINT." << endl;
            return;
        }
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
                cout << setw(5) << mstAdjacencyList[i][j] << " ";
            }
            cout << endl;
        }
    }

    void printKruskalMSTAdjacencyList()
    {
        if (!mstGenerated)
        {
            cout << "KMST command must be invoked first before KMST-APRINT." << endl;
            return;
        }
        cout << "Number of vertices: " << numVertices << endl;
        cout << "Number of edges: " << countEdges() << endl;
        cout << "Adjacency list representation:" << endl;
        for (int i = 0; i < numVertices; ++i)
        {
            cout << vertices[i] << " -> ";
            for (int j = 0; j < numVertices; ++j)
            {
                if (mstAdjacencyList[i][j] != 0)
                {
                    cout << vertices[j] << "(" << mstAdjacencyList[i][j] << ") ";
                }
            }
            cout << endl;
        }
    }
};

int main()
{
    Graph graph;
    string command;

    while (true)
    {
        cout << "Enter command: ";
        getline(cin, command);
        istringstream iss(command);
        string cmd;
        iss >> cmd;

        if (cmd == "DINIT")
        {
            int vertices;
            iss >> vertices;
            graph.directedInit(vertices);
        }
        else if (cmd == "UINIT")
        {
            int vertices;
            iss >> vertices;
            graph.undirectedInit(vertices);
        }
        else if (cmd == "VADD")
        {
            char name;
            iss >> name;
            graph.addVertex(name);
        }
        else if (cmd == "VDEL")
        {
            char name;
            iss >> name;
            graph.deleteVertex(name);
        }
        else if (cmd == "APRINT")
        {
            graph.printAdjacencyList();
        }
        else if (cmd == "EADD")
        {
            char v1, v2;
            int weight;
            iss >> v1 >> v2 >> weight;
            graph.addEdge(v1, v2, weight);
        }
        else if (cmd == "EDEL")
        {
            char v1, v2;
            iss >> v1 >> v2;
            graph.deleteEdge(v1, v2);
        }
        else if (cmd == "MPRINT")
        {
            graph.printMatrixRepresentation();
        }
        else if (cmd == "SPATH")
        {
            char source, destination;
            iss >> source >> destination;
            graph.shortestPath(source, destination);
        }
        else if (cmd == "KMST")
        {
            graph.generateKruskalMST();
        }
        else if (cmd == "KMST-MPRINT")
        {
            graph.printKruskalMSTMatrix();
        }
        else if (cmd == "KMST-APRINT")
        {
            graph.printKruskalMSTAdjacencyList();
        }
        else if (cmd == "EXIT")
        {
            break;
        }
        else
        {
            cout << "Invalid command." << endl;
        }
    }

    return 0;
}
