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

     return 0;
}
