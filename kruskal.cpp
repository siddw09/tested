
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Graph {

    struct Edge {
        int u, v, w;
    };

    int V;
    vector<Edge> edges;

    vector<int> parent, rank;

    // Find parent of a vertex
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);

        return parent[x];
    }

    // Join two sets
    void unite(int u, int v) {
        int a = find(u);
        int b = find(v);

        if (a == b)
            return;

        if (rank[a] < rank[b]) {
            parent[a] = b;
        }
        else if (rank[a] > rank[b]) {
            parent[b] = a;
        }
        else {
            parent[b] = a;
            rank[a]++;
        }
    }

public:

    Graph(int v) {
        V = v;
    }

    void addEdge(int u, int v, int w) {
        edges.push_back({u, v, w});
    }

    void kruskal() {

        // Sort edges by weight
        sort(edges.begin(), edges.end(),
             [](Edge a, Edge b) {
                 return a.w < b.w;
             });

        parent.resize(V);
        rank.resize(V, 0);

        for (int i = 0; i < V; i++)
            parent[i] = i;

        int totalCost = 0;
        int count = 0;

        cout << "Edges in MST:\n";

        for (auto edge : edges) {

            int u = edge.u;
            int v = edge.v;
            int w = edge.w;

            // Check whether edge forms a cycle
            if (find(u) != find(v)) {

                cout << u << " - " << v
                     << " : " << w << endl;

                totalCost += w;
                unite(u, v);
                count++;

                if (count == V - 1)
                    break;
            }
        }

        if (count != V - 1) {
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

    g.kruskal();

    return 0;
}
