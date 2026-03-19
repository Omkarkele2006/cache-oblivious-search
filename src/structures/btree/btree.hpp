#ifndef BTREE_HPP
#define BTREE_HPP

#include <vector>

class BTree {
private:
    struct Node {
        std::vector<int> keys;
        std::vector<Node*> children;
        bool leaf;

        Node(bool leaf) : leaf(leaf) {}
    };

    Node* root;
    int t; // minimum degree

    void split_child(Node* parent, int i) {
        Node* y = parent->children[i];
        Node* z = new Node(y->leaf);

        // Move last t-1 keys to new node
        for (int j = 0; j < t - 1; j++)
            z->keys.push_back(y->keys[j + t]);

        // If not leaf, move children
        if (!y->leaf) {
            for (int j = 0; j < t; j++)
                z->children.push_back(y->children[j + t]);
        }

        int mid = y->keys[t - 1];

        // Resize original node
        y->keys.resize(t - 1);
        if (!y->leaf)
            y->children.resize(t);

        parent->children.insert(parent->children.begin() + i + 1, z);
        parent->keys.insert(parent->keys.begin() + i, mid);
    }

    void insert_non_full(Node* node, int key) {
        int i = node->keys.size() - 1;

        if (node->leaf) {
            node->keys.push_back(0);
            while (i >= 0 && key < node->keys[i]) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }
            node->keys[i + 1] = key;
        } else {
            while (i >= 0 && key < node->keys[i])
                i--;

            i++;

            if (node->children[i]->keys.size() == 2 * t - 1) {
                split_child(node, i);

                if (key > node->keys[i])
                    i++;
            }

            insert_non_full(node->children[i], key);
        }
    }

    bool search(Node* node, int key) const {
        int i = 0;

        while (i < node->keys.size() && key > node->keys[i])
            i++;

        if (i < node->keys.size() && key == node->keys[i])
            return true;

        if (node->leaf)
            return false;

        return search(node->children[i], key);
    }

public:
    BTree(int t = 3) : t(t) {
        root = new Node(true);
    }

    void insert(int key) {
        if (root->keys.size() == 2 * t - 1) {
            Node* s = new Node(false);
            s->children.push_back(root);

            split_child(s, 0);

            int i = (key > s->keys[0]) ? 1 : 0;
            insert_non_full(s->children[i], key);

            root = s;
        } else {
            insert_non_full(root, key);
        }
    }

    bool search(int key) const {
        return search(root, key);
    }
};

#endif