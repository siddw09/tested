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
        int deletedIndex = -1;

        for (int i = 0; i < size; i++) {
            int pos = (index + i) % size;

            if (state[pos] == 1 && table[pos] == key) {
                cout << "Duplicate key\n";
                return;
            }

            if (state[pos] == 2 && deletedIndex == -1) {
                deletedIndex = pos;
            }

            if (state[pos] == 0) {
                if (deletedIndex != -1)
                    pos = deletedIndex;

                table[pos] = key;
                state[pos] = 1;

                cout << key << " inserted\n";
                return;
            }
        }

        if (deletedIndex != -1) {
            table[deletedIndex] = key;
            state[deletedIndex] = 1;
            cout << key << " inserted\n";
        }
        else {
            cout << "Hash Table is Full\n";
        }
    }

    void search(int key) {
        int index = hashFunction(key);

        for (int i = 0; i < size; i++) {
            int pos = (index + i) % size;

            if (state[pos] == 0)
                break;

            if (state[pos] == 1 && table[pos] == key) {
                cout << "Element found at index "
                     << pos << "\n";
                return;
            }
        }

        cout << "Element not found\n";
    }

    void deleteKey(int key) {
        int index = hashFunction(key);

        for (int i = 0; i < size; i++) {
            int pos = (index + i) % size;

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

            cout << "\n";
        }
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

    cout << "\nAfter Deletion:\n";
    h.display();

    return 0;
}
