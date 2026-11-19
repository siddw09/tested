
#include <iostream>
#include <vector>
#include <queue>
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

    void prims(int src) {
        vector<bool> visited(V, false);

        // {weight, vertex}
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > pq;

        pq.push({0, src});

        int totalCost = 0;
        int count = 0;

        cout << "Edges in MST:\n";

        while (!pq.empty()) {
            int weight = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (visited[u])
                continue;

            visited[u] = true;
            totalCost += weight;
            count++;

            if (u != src) {
                cout << "Vertex " << u
                     << " Weight " << weight << endl;
            }

            for (auto edge : adj[u]) {
                int v = edge.first;
                int w = edge.second;

                if (!visited[v]) {
                    pq.push({w, v});
                }
            }
        }

        if (count != V) {
            cout << "Graph is disconnected. MST not possible.\n";
            return;
        }

        cout << "Minimum Cost of MST: "
             << totalCost << endl;
    }
};

int main() {
    Graph g(5);

    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    g.prims(0);

    return 0;
}
