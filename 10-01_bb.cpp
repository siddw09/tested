
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Knapsack {

public:
    // Item structure must be public
    struct Item {
        int weight, profit;
        double ratio;
    };

private:
    struct Node {
        int level;
        int profit;
        int weight;
        double bound;
    };

    vector<Item> items;
    int n, capacity;

    // Calculate upper bound
    double calculateBound(Node u) {

        if (u.weight >= capacity)
            return 0;

        double profitBound = u.profit;
        int totalWeight = u.weight;
        int j = u.level + 1;

        // Add complete items
        while (j < n &&
               totalWeight + items[j].weight <= capacity) {

            totalWeight += items[j].weight;
            profitBound += items[j].profit;
            j++;
        }

        // Add fractional part
        if (j < n) {
            profitBound +=
                (capacity - totalWeight) * items[j].ratio;
        }

        return profitBound;
    }

    // Priority queue comparison
    struct Compare {
        bool operator()(Node a, Node b) {
            return a.bound < b.bound;
        }
    };

public:

    // Constructor
    Knapsack(vector<Item> input, int cap) {

        items = input;
        capacity = cap;
        n = items.size();

        // Calculate profit/weight ratio
        for (auto &item : items) {
            item.ratio =
                (double)item.profit / item.weight;
        }

        // Sort items by ratio
        sort(items.begin(), items.end(),
             [](Item a, Item b) {
                 return a.ratio > b.ratio;
             });
    }

    void solve() {

        priority_queue<Node, vector<Node>, Compare> pq;

        Node root;

        root.level = -1;
        root.profit = 0;
        root.weight = 0;
        root.bound = calculateBound(root);

        pq.push(root);

        int maxProfit = 0;

        while (!pq.empty()) {

            Node u = pq.top();
            pq.pop();

            // Pruning
            if (u.bound <= maxProfit)
                continue;

            int next = u.level + 1;

            if (next >= n)
                continue;

            // Branch 1: Include next item
            Node v;

            v.level = next;
            v.weight = u.weight + items[next].weight;
            v.profit = u.profit + items[next].profit;

            if (v.weight <= capacity &&
                v.profit > maxProfit) {

                maxProfit = v.profit;
            }

            v.bound = calculateBound(v);

            if (v.bound > maxProfit)
                pq.push(v);

            // Branch 2: Exclude next item
            Node exclude;

            exclude.level = next;
            exclude.weight = u.weight;
            exclude.profit = u.profit;

            exclude.bound = calculateBound(exclude);

            if (exclude.bound > maxProfit)
                pq.push(exclude);
        }

        cout << "Maximum Profit using Branch & Bound: "
             << maxProfit << endl;
    }
};

int main() {

    vector<Knapsack::Item> items = {
        {10, 60},
        {20, 100},
        {30, 120}
    };

    int capacity = 50;

    Knapsack k(items, capacity);

    k.solve();

    return 0;
}
