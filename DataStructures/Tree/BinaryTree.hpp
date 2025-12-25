#include "../Abstract/BinaryTreeADT.hpp"
#include <unordered_map>
#include <iostream>
using namespace std;

#pragma once

class BinaryTree : public BinaryTreeADT {
private:
    Node* root;
    unordered_map<int, Node*> nodes;

    // --------------------------------------------------
    //      HELPER FUNCTIONS
    // --------------------------------------------------

    Node* createNode(int n) {
        Node* node = new Node(n);
        nodes[n] = node;
        return node;
    }

    Node* getNode(int n) {
        auto pair = nodes.find(n);
        if(pair != nodes.end()) return pair->second;
        return nullptr;
    }

    void print(Node* node, int level) {
        if(!node) {
            cout << endl;
            return;
        }
        cout << "[" << node->val << "]" << endl;

        //print left
        printLine(level);
        cout << "`-- ";
        print(node->left, level + 1);

        //print right
        printLine(level);
        cout << "`-- ";
        print(node->right, level + 1);

        return;
    }

    void printLine(int level) {
        cout << "|";
        for(int i = 0; i < level; i++) cout << "    |";

        cout << endl;

        cout << "|";
        for(int i = 0; i < level; i++) cout << "    |";

        return;
    }

public:
    //constructor
    BinaryTree() : root(nullptr), nodes() {}

    //insert functions
    void addRoot(int n) {
        if(root) cout << "Binary Tree already has root!" << endl;
        else root = createNode(n);

        return;
    }

    void addLeft(int parent, int n) {
        Node* node = getNode(parent);

        if(!node) cout << "Parent doesn't exist!" << endl;
        else if(node->left) cout << "Parent already has left child!" << endl;
        else if(getNode(n)) cout << "A node with value " << n << " already exist!" << endl;
        else node->left = createNode(n);

        return;
    }
    
    void addRight(int parent, int n) {
        Node* node = getNode(parent);

        if(!node) cout << "Parent doesn't exist!" << endl;
        else if(node->right) cout << "Parent already has right child!" << endl;
        else if(getNode(n)) cout << "A node with value " << n << " already exist!" << endl;
        else node->right = createNode(n);

        return;
    }

    //get functions
    int getRoot() { return root->val; }
    int getSize() { return nodes.size(); }

    //search functions
    bool search(int n) { return getNode(n)? true : false; }

    // //traverse functions
    // virtual void preorder() = 0;
    // virtual void inorder() = 0;
    // virtual void postorder() = 0;
    // virtual void levelorder() = 0;

    // //remove functions
    // virtual bool remove(int n) = 0;

    //display functions
    void display() {
        if(!root) {
            cout << "No root found." << endl;
            return;
        }

        print(root, 0);
        return;
    }
};