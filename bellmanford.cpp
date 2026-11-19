#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> edges;

public:
    Graph(int v) {
        V = v;
    }

    void addEdge(int u, int v, int w) {
        edges.push_back({u, v, w});
    }

    void bellmanFord(int src) {
        vector<int> dist(V, INT_MAX);

        dist[src] = 0;

        // Relax all edges V-1 times
        for (int i = 1; i < V; i++) {
            for (auto edge : edges) {
                int u = edge[0];
                int v = edge[1];
                int w = edge[2];

                if (dist[u] != INT_MAX &&
                    dist[u] + w < dist[v]) {

                    dist[v] = dist[u] + w;
                }
            }
        }

        // Check negative weight cycle
        for (auto edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];

            if (dist[u] != INT_MAX &&
                dist[u] + w < dist[v]) {

                cout << "Negative weight cycle found\n";
                return;
            }
        }

        cout << "Shortest distances:\n";

        for (int i = 0; i < V; i++) {
            cout << src << " to " << i << " = ";

            if (dist[i] == INT_MAX)
                cout << "Unreachable";
            else
                cout << dist[i];

            cout << endl;
        }
    }
};

int main() {
    Graph g(5);

    g.addEdge(0, 1, -1);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 2);
    g.addEdge(1, 4, 2);
    g.addEdge(3, 2, 5);
    g.addEdge(3, 1, 1);
    g.addEdge(4, 3, -3);

    g.bellmanFord(0);

    return 0;
}
