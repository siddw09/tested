#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

class TSP {
    int n;
    vector<vector<int>> cost;
    int bestCost;
    vector<int> bestPath;

    struct Node {
        int city;
        int level;
        int cost;
        int bound;
        vector<int> path;
        vector<bool> visited;
    };

    struct Compare {
        bool operator()(Node a, Node b) {
            return a.bound > b.bound;
        }
    };

    int calculateBound(Node node) {
        int bound = node.cost;

        // Find minimum outgoing edge
        // for current and unvisited cities
        for (int i = 0; i < n; i++) {

            if (node.visited[i] && i != node.city)
                continue;

            int minimum = INT_MAX;

            for (int j = 0; j < n; j++) {
                if (i != j && cost[i][j] < minimum)
                    minimum = cost[i][j];
            }

            if (minimum == INT_MAX)
                return INT_MAX;

            bound += minimum;
        }

        return bound;
    }

public:
    TSP(vector<vector<int>> c) {
        cost = c;
        n = c.size();
        bestCost = INT_MAX;
    }

    void solve() {
        priority_queue<Node, vector<Node>, Compare> pq;

        Node root;

        root.city = 0;
        root.level = 0;
        root.cost = 0;
        root.path.push_back(0);
        root.visited.assign(n, false);
        root.visited[0] = true;

        root.bound = calculateBound(root);

        pq.push(root);

        while (!pq.empty()) {
            Node current = pq.top();
            pq.pop();

            if (current.bound >= bestCost)
                continue;

            for (int i = 0; i < n; i++) {

                if (!current.visited[i] &&
                    cost[current.city][i] != INT_MAX) {

                    Node child = current;

                    child.city = i;
                    child.level++;
                    child.cost += cost[current.city][i];
                    child.visited[i] = true;
                    child.path.push_back(i);

                    if (child.level == n - 1) {

                        if (cost[i][0] != INT_MAX) {
                            int total = child.cost + cost[i][0];

                            if (total < bestCost) {
                                bestCost = total;
                                bestPath = child.path;
                                bestPath.push_back(0);
                            }
                        }
                    }
                    else {
                        child.bound = calculateBound(child);

                        if (child.bound < bestCost)
                            pq.push(child);
                    }
                }
            }
        }

        if (bestCost == INT_MAX) {
            cout << "No complete tour exists\n";
            return;
        }

        cout << "Minimum Cost: " << bestCost << endl;

        cout << "Shortest Tour: ";

        for (int city : bestPath)
            cout << city << " ";

        cout << endl;
    }
};

int main() {
    const int INF = INT_MAX;

    vector<vector<int>> cost = {
        {INF, 10, 15, 20},
        {10, INF, 35, 25},
        {15, 35, INF, 30},
        {20, 25, 30, INF}
    };

    TSP t(cost);
    t.solve();

    return 0;
}
