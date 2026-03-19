#ifndef BST_HPP
#define BST_HPP

#include <iostream>

class BST {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;

        Node(int k) : key(k), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Insert helper
    Node* insert(Node* node, int key) {
        if (node == nullptr) {
            return new Node(key);
        }

        if (key < node->key) {
            node->left = insert(node->left, key);
        } else {
            node->right = insert(node->right, key);
        }

        return node;
    }

    // Search helper
    bool search(Node* node, int key) const {
        if (node == nullptr) return false;

        if (node->key == key) return true;

        if (key < node->key)
            return search(node->left, key);
        else
            return search(node->right, key);
    }

    // Cleanup
    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}

    ~BST() {
        destroy(root);
    }

    void insert(int key) {
        root = insert(root, key);
    }

    bool search(int key) const {
        return search(root, key);
    }
};

#endif