#include <iostream>
#include <vector>
#include <list>
using namespace std;

class HashTable {
    int size;
    vector<list<int>> table;

public:
    HashTable(int s) {
        size = s;
        table.resize(size);
    }

    int hashFunction(int key) {
        return key % size;
    }

    void insert(int key) {
        int index = hashFunction(key);

        table[index].push_back(key);

        cout << key << " inserted\n";
    }

    void search(int key) {
        int index = hashFunction(key);

        for (int x : table[index]) {
            if (x == key) {
                cout << "Element found\n";
                return;
            }
        }

        cout << "Element not found\n";
    }

    void display() {
        for (int i = 0; i < size; i++) {
            cout << i << " -> ";

            for (int x : table[i]) {
                cout << x << " -> ";
            }

            cout << "NULL\n";
        }
    }

    void deleteKey(int key) {
        int index = hashFunction(key);

        table[index].remove(key);

        cout << "Deletion operation completed\n";
    }
};

int main() {
    HashTable h(10);

    h.insert(23);
    h.insert(45);
    h.insert(35);
    h.insert(25);

    cout << "\nHash Table:\n";
    h.display();

    cout << "\nSearching 35:\n";
    h.search(35);

    cout << "\nDeleting 35:\n";
    h.deleteKey(35);

    h.display();

    return 0;
}
