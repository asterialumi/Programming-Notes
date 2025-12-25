#pragma once

class BinaryTreeADT {
protected:
    struct Node {
        int val;
        Node *left;
        Node *right;

        Node(int v) : val(v), left(nullptr), right(nullptr) {}
    };

public:
    //insert functions
    virtual void addRoot(int n) = 0;
    virtual void addLeft(int parent, int n) = 0;
    virtual void addRight(int parent, int n) = 0;

    //get functions
    virtual int getRoot() = 0;
    virtual int getSize() = 0;

    //search functions
    virtual bool search(int n) = 0;

    // //traverse functions
    // virtual void preorder() = 0;
    // virtual void inorder() = 0;
    // virtual void postorder() = 0;
    // virtual void levelorder() = 0;

    // //remove functions
    // virtual bool remove(int n) = 0;

    //display functions
    virtual void display() = 0;
};