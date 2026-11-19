
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
    int V;
    vector<vector<pair<int, int>>> adj;
    vector<string> departments;

public:
    Graph(vector<string> names) {
        V = names.size();
        departments = names;
        adj.resize(V);
    }

    void addEdge(int u, int v, int distance) {
        adj[u].push_back({v, distance});
        adj[v].push_back({u, distance});
    }

    void display() {
        cout << "\nCampus Graph:\n";

        for (int i = 0; i < V; i++) {
            cout << departments[i] << " -> ";

            for (auto edge : adj[i]) {
                cout << departments[edge.first]
                     << "(" << edge.second << "m) -> ";
            }

            cout << "NULL\n";
        }
    }

    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "\nBFS Traversal: ";

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            cout << departments[u] << " ";

            for (auto edge : adj[u]) {
                int v = edge.first;

                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        cout << endl;
    }

    void DFSUtil(int u, vector<bool>& visited) {
        visited[u] = true;
        cout << departments[u] << " ";

        for (auto edge : adj[u]) {
            int v = edge.first;

            if (!visited[v]) {
                DFSUtil(v, visited);
            }
        }
    }

    void DFS(int start) {
        vector<bool> visited(V, false);

        cout << "\nDFS Traversal: ";
        DFSUtil(start, visited);

        cout << endl;
    }
};

int main() {
    vector<string> names = {
        "Computer",
        "Mechanical",
        "Civil",
        "ENTC",
        "Library",
        "Admin"
    };

    Graph g(names);

    g.addEdge(0, 1, 100);
    g.addEdge(0, 3, 50);
    g.addEdge(0, 4, 80);
    g.addEdge(1, 2, 60);
    g.addEdge(2, 5, 70);
    g.addEdge(3, 5, 90);
    g.addEdge(4, 5, 40);

    g.display();

    g.BFS(0);
    g.DFS(0);

    return 0;
}
