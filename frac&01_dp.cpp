#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Knapsack {
public:
    struct Item {
        int weight, profit;
        double ratio;
    };

    void fractionalKnapsack(vector<Item> items, int capacity) {
        sort(items.begin(), items.end(),
             [](Item a, Item b) {
                 return a.ratio > b.ratio;
             });

        double totalProfit = 0;

        for (auto item : items) {
            if (capacity >= item.weight) {
                capacity -= item.weight;
                totalProfit += item.profit;
            }
            else {
                totalProfit += item.ratio * capacity;
                break;
            }
        }

        cout << "Fractional Knapsack Profit: "
             << totalProfit << endl;
    }

    void zeroOneKnapsack(vector<Item> items, int capacity) {
        int n = items.size();

        vector<vector<int>> dp(
            n + 1, vector<int>(capacity + 1, 0)
        );

        for (int i = 1; i <= n; i++) {
            for (int w = 0; w <= capacity; w++) {

                if (items[i-1].weight <= w) {
                    dp[i][w] = max(
                        items[i-1].profit +
                        dp[i-1][w - items[i-1].weight],

                        dp[i-1][w]
                    );
                }
                else {
                    dp[i][w] = dp[i-1][w];
                }
            }
        }

        cout << "0/1 Knapsack Profit: "
             << dp[n][capacity] << endl;
    }
};

int main() {
    Knapsack k;

    vector<Knapsack::Item> items = {
        {10, 60, 6.0},
        {20, 100, 5.0},
        {30, 120, 4.0}
    };

    int capacity = 50;

    k.fractionalKnapsack(items, capacity);
    k.zeroOneKnapsack(items, capacity);

    return 0;
}
