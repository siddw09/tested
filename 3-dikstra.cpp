#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

class Graph {
    int V;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int v) {
        V = v;
        adj.resize(V);
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void dijkstra(int src) {
        vector<int> dist(V, INT_MAX);
        vector<int> parent(V, -1);

        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > pq;

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto edge : adj[u]) {
                int v = edge.first;
                int w = edge.second;

                if (dist[u] != INT_MAX &&
                    dist[u] + w < dist[v]) {

                    dist[v] = dist[u] + w;
                    parent[v] = u;

                    pq.push({dist[v], v});
                }
            }
        }

        cout << "\nShortest Distances:\n";

        for (int i = 0; i < V; i++) {
            cout << src << " to " << i << " = ";

            if (dist[i] == INT_MAX) {
                cout << "Unreachable\n";
            } else {
                cout << dist[i] << "\n";
            }
        }

        cout << "\nShortest Paths:\n";

        for (int i = 0; i < V; i++) {
            if (dist[i] == INT_MAX) {
                cout << i << ": No path\n";
                continue;
            }

            vector<int> path;
            int curr = i;

            while (curr != -1) {
                path.push_back(curr);
                curr = parent[curr];
            }

            reverse(path.begin(), path.end());

            for (int node : path) {
                cout << node << " ";
            }

            cout << "\n";
        }
    }
};

int main() {
    Graph g(5);

    g.addEdge(0, 1, 4);
    g.addEdge(0, 4, 7);
    g.addEdge(0, 2, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(2, 3, 2);
    g.addEdge(3, 4, 3);

    int source;

    cout << "Enter source vertex (0-4): ";
    cin >> source;

    g.dijkstra(source);

    return 0;
}