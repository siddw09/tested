
#include <iostream>
#include <vector>
using namespace std;

class HashTable {
    int size;
    vector<int> table;
    vector<int> state;

public:
    HashTable(int s) {
        size = s;
        table.resize(size);
        state.resize(size, 0);
    }

    int hashFunction(int key) {
        return key % size;
    }

    void insert(int key) {
        int index = hashFunction(key);

        for (int i = 0; i < size; i++) {
            int pos = (index + i * i) % size;

            if (state[pos] == 1 && table[pos] == key) {
                cout << "Duplicate key\n";
                return;
            }

            if (state[pos] == 0 || state[pos] == 2) {
                table[pos] = key;
                state[pos] = 1;

                cout << key << " inserted\n";
                return;
            }
        }

        cout << "Insertion failed: No available position\n";
    }

    void search(int key) {
        int index = hashFunction(key);

        for (int i = 0; i < size; i++) {
            int pos = (index + i * i) % size;

            if (state[pos] == 0)
                break;

            if (state[pos] == 1 && table[pos] == key) {
                cout << "Element found at index "
                     << pos << endl;
                return;
            }
        }

        cout << "Element not found\n";
    }

    void deleteKey(int key) {
        int index = hashFunction(key);

        for (int i = 0; i < size; i++) {
            int pos = (index + i * i) % size;

            if (state[pos] == 0)
                break;

            if (state[pos] == 1 && table[pos] == key) {
                state[pos] = 2;
                cout << "Element deleted\n";
                return;
            }
        }

        cout << "Element not found\n";
    }

    void display() {
        for (int i = 0; i < size; i++) {
            cout << i << " -> ";

            if (state[i] == 1)
                cout << table[i];
            else if (state[i] == 2)
                cout << "DELETED";
            else
                cout << "EMPTY";

            cout << endl;
        }
    }
};

int main() {
    HashTable h(11);

    h.insert(22);
    h.insert(33);
    h.insert(44);
    h.insert(55);

    cout << "\nHash Table:\n";
    h.display();

    cout << "\nSearching 44:\n";
    h.search(44);

    cout << "\nDeleting 44:\n";
    h.deleteKey(44);

    cout << "\nAfter Deletion:\n";
    h.display();

    return 0;
}
