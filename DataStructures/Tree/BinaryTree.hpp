#include <unordered_map>
#include <queue>
#include <iostream>
using namespace std;

#pragma once

class BinaryTree {
public:
    //constructor
    BinaryTree() : root(nullptr), nodes() {}

    //insert functions
    void addRoot(int n) {
        if(root) cout << "Binary Tree already has root!" << endl;
        else root = create_node(n);

        return;
    }

    void addLeft(int parent, int n) {
        Node* node = get_node(parent);

        if(!node) cout << "Parent doesn't exist!" << endl;
        else if(node->left) cout << "Parent already has left child!" << endl;
        else if(get_node(n)) cout << "A node with value " << n << " already exist!" << endl;
        else node->left = create_node(n);

        return;
    }
    
    void addRight(int parent, int n) {
        Node* node = get_node(parent);

        if(!node) cout << "Parent doesn't exist!" << endl;
        else if(node->right) cout << "Parent already has right child!" << endl;
        else if(get_node(n)) cout << "A node with value " << n << " already exist!" << endl;
        else node->right = create_node(n);

        return;
    }

    //get functions
    int size() { return nodes.size(); }

    //search functions (NOT YET RIPE ENOUGH, i think)
    bool search(int n) { return get_node(n)? true : false; }

    //traverse functions
    void preorder() {
        int count = 0;
        pre_traverse(root, count);
    }

    void inorder() {
        int count = 0;
        in_traverse(root, count);
    }

    void postorder() {
        int count = 0;
        post_traverse(root, count);
    }

    void levelorder() {
        if(!root) {
            cout << "root not found." << endl;
            return;
        }
        queue<Node*> q;
        int level = 0;

        cout << level << ": " << root->val << endl;
        q.push(root->left);
        q.push(root->right);

        while(q.size()) {
            level++;
            cout << level << ": ";
            int size = q.size();

            for(int i = 0; i < q.size(); i++) {
                Node* curr = q.front();
                q.pop();

                if(!curr) continue;
                q.push(curr->left);
                q.push(curr->right);
                cout << curr->val << " ";
            }

            cout << endl;
        }

        return;
    }

    //remove functions
    bool remove(int n) {
        Node* node = get_node(n);

        if(!node) return false;
        delete_node(node);

        return true;
    }

    //display functions
    void display() {
        print(root, 0);
        return;
    }

private:
    struct Node {
        int val;
        Node *left;
        Node *right;

        Node(int v) : val(v), left(nullptr), right(nullptr) {}
    };

    Node* root;
    unordered_map<int, Node*> nodes;

    Node* create_node(int n) {
        Node* node = new Node(n);
        nodes[n] = node;
        return node;
    }

    Node* get_node(int n) {
        auto pair = nodes.find(n);
        if(pair != nodes.end()) return pair->second;
        return nullptr;
    }

    void delete_node(Node* node) {
        if (!node) return;

        delete_node(node->left);
        delete_node(node->right);
        nodes.erase(node->val);

        Node* parent = find_parent(root, node);

        if(!parent) root = nullptr;
        else if (parent->left == node) parent->left = nullptr;
        else if (parent->right == node) parent->right = nullptr;

        delete node;
        return;
    }

    Node* find_parent(Node* start, Node* node) {
        if(!start) return nullptr;

        if(start->left == node || start->right == node) return start;
        Node* left = find_parent(start->left, node);
        Node* right = find_parent(start->right, node);

        if(left) return left;
        if(right) return right;
        return nullptr;
    }

    
    void pre_traverse(Node* node, int& count) {
        if(!node) return;

        cout << "[" << node->val << "] ";
        count++;
        if(count % 10 == 0) cout << endl;

        pre_traverse(node->left, count);
        pre_traverse(node->right, count);
        return;
    }

    void in_traverse(Node* node, int& count) {
        if(!node) return;

        in_traverse(node->left, count);

        cout << "[" << node->val << "] ";
        count++;
        if(count % 10 == 0) cout << endl;

        in_traverse(node->right, count);
        return;
    }

    void post_traverse(Node* node, int& count) {
        if(!node) return;

        post_traverse(node->left, count);
        post_traverse(node->right, count);

        cout << "[" << node->val << "] ";
        count++;
        if(count % 10 == 0) cout << endl;

        return;
    }

    void print(Node* node, int level) {
        if(!node) {
            cout << "[]" << endl;
            return;
        }
        cout << "[" << node->val << "]" << endl;

        //print left
        print_line(level);
        cout << "`--<";
        print(node->left, level + 1);

        //print right
        print_line(level);
        cout << "`-->";
        print(node->right, level + 1);

        return;
    }

    void print_line(int level) {
        cout << "|";
        for(int i = 0; i < level; i++) cout << "    |";

        cout << endl;

        cout << "|";
        for(int i = 0; i < level; i++) cout << "    |";

        return;
    }

};