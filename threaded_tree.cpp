
#include <iostream>
#include <vector>
using namespace std;

class ThreadedTree {
    struct Node {
        int data;
        Node *left, *right;
        bool lthread, rthread;

        Node(int val) {
            data = val;
            left = right = NULL;
            lthread = rthread = false;
        }
    };

    Node* root;

    // Store nodes in inorder sequence
    void storeInorder(Node* node, vector<Node*>& nodes) {
        if (node == NULL)
            return;

        storeInorder(node->left, nodes);
        nodes.push_back(node);
        storeInorder(node->right, nodes);
    }

public:
    ThreadedTree() {
        root = NULL;
    }

    // Create sample binary tree
    void createTree() {
        root = new Node(1);

        root->left = new Node(2);
        root->right = new Node(3);

        root->left->left = new Node(4);
        root->left->right = new Node(5);

        root->right->left = new Node(6);
    }

    // Convert binary tree into threaded tree
    void createThreads() {
        vector<Node*> nodes;

        storeInorder(root, nodes);

        for (int i = 0; i < nodes.size(); i++) {

            if (nodes[i]->left == NULL) {
                nodes[i]->lthread = true;

                if (i > 0)
                    nodes[i]->left = nodes[i-1];
            }

            if (nodes[i]->right == NULL) {
                nodes[i]->rthread = true;

                if (i < nodes.size()-1)
                    nodes[i]->right = nodes[i+1];
            }
        }
    }

    // Inorder Traversal using threads
    void inorder() {
        Node* curr = root;

        while (curr != NULL && !curr->lthread)
            curr = curr->left;

        cout << "\nInorder Traversal: ";

        while (curr != NULL) {
            cout << curr->data << " ";

            if (curr->rthread) {
                curr = curr->right;
            }
            else {
                curr = curr->right;

                while (curr != NULL && !curr->lthread)
                    curr = curr->left;
            }
        }

        cout << endl;
    }

    // Preorder Traversal
    void preorder(Node* node) {
        if (node == NULL)
            return;

        cout << node->data << " ";

        if (!node->lthread)
            preorder(node->left);

        if (!node->rthread)
            preorder(node->right);
    }

    void displayPreorder() {
        cout << "\nPreorder Traversal: ";
        preorder(root);
        cout << endl;
    }
};

int main() {
    ThreadedTree t;

    t.createTree();
    t.createThreads();

    t.inorder();
    t.displayPreorder();

    return 0;
}
