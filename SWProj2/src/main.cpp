#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <fstream>
#include <map>

using namespace std;

// Define a typedef for a pair of integers named PII
typedef pair<int, int> PII;

// Define a custom class Edge representing an edge in a graph
class Edge {
public:
    int u; // Source vertex of the edge
    int v; // Destination vertex of the edge
    int weight; // Weight of the edge

    // Constructor to initialize the attributes of the Edge object
    Edge(int u, int v, int weight) {
        this->u = u; // Assign the source vertex
        this->v = v; // Assign the destination vertex
        this->weight = weight; // Assign the weight of the edge
    }
};


class Graph {
private:
    int numVertices; // Number of vertices in the graph
    vector<vector<pair<int, int>>> adjacencyList; // Adjacency list representation of the graph
    map<pair<int, int>, pair<string, string>> edgeAttributes; // Store edge attributes

public:
    // Constructor to initialize the Graph object
    Graph() {
        numVertices = 0; // Initialize the number of vertices to 0
    }

    // Method to clear the graph by removing all vertices and edges
    void clearGraph() {
        adjacencyList.clear(); // Clear the adjacency list
        numVertices = 0; // Reset the number of vertices to 0
    }

    // Method to add an edge to the graph between vertices u and v with weight
    void addEdge(int u, int v, int weight) {
        // Check if the vertices specified are valid
        if (u < 0) {
            // If u is out of bounds, print an error message and return
            cout << "Invalid vertex u specified for edge addition." << endl;
            return;
        }
        if (v < 0) {
            // If v is out of bounds, print an error message and return
            cout << "Invalid vertex v specified for edge addition." << endl;
            return;
        }
        if (u >= numVertices) {
            // If u is out of bounds, print an error message and return
            cout << "Vertex u is out of bounds for edge addition." << endl;
            return;
        }
        if (v >= numVertices) {
            // If v is out of bounds, print an error message and return
            cout << "Vertex v is out of bounds for edge addition." << endl;
            return;
        }
        // Add edge (u, v) with weight to the adjacency list
        adjacencyList[u].push_back({v, weight});
        adjacencyList[v].push_back({u, weight}); // Assuming undirected graph, add edge (v, u) as well
    }

   // Method to find the shortest path from airports to other cities
void shortestPathFromAirports(vector<int>& distances, const vector<int>& airports, vector<vector<int>>& parents) {
    // Initialize visited array to track visited vertices
    vector<bool> visited(numVertices, false);
    // Priority queue to store vertices based on their distances
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Iterate through all airport cities
    for (int src : airports) {
        // Push the airport city into the priority queue with distance 0
        pq.push({0, src});
        // Set the distance to the airport city as 0
        distances[src] = 0;
    }

    // Loop until the priority queue is empty
    while (!pq.empty()) {
        // Extract the vertex with the smallest distance from the priority queue
        int u = pq.top().second;
        pq.pop();

        // If the vertex is already visited, skip processing its neighbors
        if (visited[u]) {
            continue;
        }

        // Mark the vertex as visited
        visited[u] = true;

        // Iterate through all neighbors of vertex u
        for (auto &neighbor : adjacencyList[u]) {
            int v = neighbor.first; // Neighbor vertex
            int weight = neighbor.second; // Weight of the edge between u and v

            // If vertex v is not visited and the distance to v through u is shorter than the current distance to v
            if (!visited[v]) {
                // Update the distance to vertex v
                int newDistance = distances[u] + weight;
                if (newDistance < distances[v]) {
                    // Clear previous parents of vertex v and add u as the new parent of v
                    parents[v].clear();
                    parents[v].push_back(u);
                    // Update the distance to vertex v
                    distances[v] = newDistance;
                    // Push vertex v into the priority queue with its updated distance
                    pq.push({distances[v], v});
                } else if (newDistance == distances[v]) {
                    // If there's another shortest path to v, add u as another parent
                    parents[v].push_back(u);
                }
            }
        }
    }
}



    void primMaxMST(int K, vector<pair<int, pair<int, int>>>& maxProfitEdges) {
    // Initialize a boolean array to track whether vertices are in the MST
    vector<bool> inMST(numVertices, false);
    // Priority queue to store edges based on their weights (max-heap for Prim's algorithm)
    priority_queue<pair<int, pair<int, int>>> pq;

    // Iterate through all edges from the first airport city
    for (auto &edge : adjacencyList[0]) {
        // Only consider edges among the first K cities
        if (edge.first < K) {
            // Push the edge weight along with its vertices into the priority queue
            pq.push({edge.second, {0, edge.first}});
        }
    }
    // Mark the first airport city as included in the MST
    inMST[0] = true;

    // Iterate until the priority queue is empty or the MST contains K - 1 edges
    while (!pq.empty() && maxProfitEdges.size() < K - 1) {
        // Extract the edge with the maximum weight from the priority queue
        int weight = pq.top().first;
        int u = pq.top().second.first; // Vertex u of the edge
        int v = pq.top().second.second; // Vertex v of the edge
        pq.pop();

        // If vertex v is already in the MST, skip processing its adjacent edges
        if (inMST[v]) {
            continue;
        }

        // Mark vertex v as included in the MST
        inMST[v] = true;
        // Add the edge to the maximum profit edges vector
        maxProfitEdges.push_back({weight, {u, v}});

        // Iterate through all edges adjacent to vertex v
        for (auto &neighbor : adjacencyList[v]) {
            int nextVertex = neighbor.first; // Next adjacent vertex
            int edgeWeight = neighbor.second; // Weight of the adjacent edge

            // If the adjacent vertex is not in the MST and within the first K cities
            if (!inMST[nextVertex] && nextVertex < K) {
                // Push the edge weight along with its vertices into the priority queue
                pq.push({edgeWeight, {v, nextVertex}});
            }
        }
    }
}



    // Method to set the number of vertices in the graph and resize the adjacency list
void setNumVertices(int vertices) {
    // Set the number of vertices to the specified value
    numVertices = vertices;
    // Resize the adjacency list to accommodate the specified number of vertices
    adjacencyList.resize(numVertices);
}

void generateGraphDiagramDOT(int testCaseNumber, int numCities, int numAirports, const vector<pair<int, pair<int, int>>>& maxProfitFlights, const vector<int>& cityDistances, const vector<vector<int>>& parents) {
    ofstream outFile("graph-diagram-testcase-" + to_string(testCaseNumber) + ".dot");
    if (!outFile.is_open()) {
        cerr << "Failed to open output file." << endl;
        return;
    }

    outFile << "graph G {" << endl;
    outFile << "    graph [bgcolor=white];" << endl;
    outFile << "    node [style=filled];" << endl;

    // Write the nodes of the graph
    for (int i = 0; i < numCities; ++i) {
        string fillColor = (i < numAirports) ? "darkgreen" : "lightgreen";
        outFile << "    City" << i << " [fillcolor=" << fillColor << ", style=filled];" << endl;
    }

    // Highlight the maximum profit flights by updating edge attributes
    for (const auto& flight : maxProfitFlights) {
        int u = flight.second.first, v = flight.second.second;
        if (u > v) swap(u, v);
        edgeAttributes[{u, v}] = {"dashed", "blue"}; // Update edge attribute for max profit flights
    }

    // Highlight the shortest paths to cities with airports by updating edge attributes
    for (int i = numAirports; i < numCities; ++i) {
        for (int j = 0; j < parents[i].size(); ++j) {
            int u = parents[i][j], v = i;
            if (u > v) swap(u, v);
            edgeAttributes[{u, v}] = {"solid", "blue"}; // Update edge attribute for shortest paths to airports
        }
    }

    // Classify other edges by updating edge attributes
    for (int u = 0; u < numCities; ++u) {
        for (const auto& neighbor : adjacencyList[u]) {
            int v = neighbor.first;
            if (u >= v) continue;
            if (edgeAttributes.find({u, v}) == edgeAttributes.end()) {
                string style = "solid", color = "black";
                if ((u < numAirports && v < numAirports) || (u >= numAirports && v >= numAirports)) {
                    style = "dashed"; // Update edge attribute for edges between airport cities or non-airport cities
                }
                edgeAttributes[{u, v}] = {style, color};
            }
        }
    }

    // Write edges to the DOT file after updating edge attributes
    for (const auto& edge : edgeAttributes) {
        int u = edge.first.first, v = edge.first.second;
        string style = edge.second.first, color = edge.second.second;
        int weight = 0;
        for (const auto& adjEdge : adjacencyList[u]) {
            if (adjEdge.first == v) {
                weight = adjEdge.second;
                break;
            }
        }
        outFile << "    City" << u << " -- City" << v << " [style=" << style << ", color=" << color << ", label=\"" << weight << "\"];" << endl;
    }

    // Write the footer of the DOT file
    outFile << "}" << endl;

    // Close the output file
    outFile.close();
}


 
};

int main() { // Main function
    int numTestCases; // Variable to store the number of test cases
    cin >> numTestCases; // Read the number of test cases from input

    for (int currentCase = 1; currentCase <= numTestCases; ++currentCase) { // Loop through each test case
        int numCities, numAirports, numFlights; // Variables to store the number of cities, airports, and flights
        cin >> numCities >> numAirports >> numFlights; // Read the number of cities, airports, and flights

        Graph graph; // Create an instance of the Graph class
        graph.setNumVertices(numCities); // Set the number of vertices in the graph

        for (int i = 0; i < numFlights; ++i) { // Loop through each flight
            int city1, city2, flightCost; // Variables to store information about the flight
            cin >> city1 >> city2 >> flightCost; // Read the information about the flight
            graph.addEdge(city1, city2, flightCost); // Add the flight as an edge in the graph
        }

        vector<pair<int, pair<int, int>>> maxProfitFlights; // Vector to store the flights with maximum profit
        vector<vector<int>> parents(numCities); // Vector to store the parents of each city in the shortest paths

        graph.primMaxMST(numAirports, maxProfitFlights); // Find the maximum profit flights using Prim's algorithm

        // Calculate total airline profit
        int totalProfit = 0; // Variable to store the total airline profit
        for (auto &flight : maxProfitFlights) { // Loop through each maximum profit flight
            totalProfit += flight.first; // Add the profit of the flight to the total profit
        }

        // Sort the flights by cost in descending order
        sort(maxProfitFlights.begin(), maxProfitFlights.end(), [](const pair<int, pair<int, int>>& a, const pair<int, pair<int, int>>& b) {
            return a.first > b.first; // Compare flights by cost in descending order
        });

        // Calculate distances from cities to the nearest airport
        vector<int> distancesFromAirport(numCities, numeric_limits<int>::max()); // Vector to store distances from cities to the nearest airport
        vector<int> airportCities(numAirports); // Vector to store indices of airport cities
        for (int i = 0; i < numAirports; ++i) { // Loop through each airport
            airportCities[i] = i; // Store the index of the airport city
        }
        graph.shortestPathFromAirports(distancesFromAirport, airportCities, parents); // Find shortest paths from airports to cities

        // Print output
        cout << "Test case #" << currentCase << ":" << endl; // Print the test case number
        cout << "Airline Profit: " << totalProfit << endl; // Print the total airline profit
        cout << "Flights:" << endl; // Print flights with maximum profit
        for (auto &flight : maxProfitFlights) { // Loop through each maximum profit flight
            int city1 = flight.second.first; // Get the index of the first city
            int city2 = flight.second.second; // Get the index of the second city
            if (city1 > city2) { // Ensure city1 index is less than city2 index
                swap(city1, city2); // Swap city indices if necessary
            }
            cout << city1 << " " << city2 << " " << flight.first << endl; // Print flight information
        }
        cout << "Distance of cities from the nearest airport:" << endl; // Print distances of cities from nearest airport
        for (int i = numAirports; i < numCities; ++i) { // Loop through each city (excluding airports)
            cout << i << ": " << distancesFromAirport[i] << endl; // Print city index and its distance from the nearest airport
        }
        cout << endl; // Print an empty line for separation

        // Generate DOT file for visualization
        graph.generateGraphDiagramDOT(currentCase, numCities, numAirports, maxProfitFlights, distancesFromAirport, parents);

        // Clear the graph for the next test case
        graph.clearGraph();
    }

    return 0; // Return 0 to indicate successful execution
}
