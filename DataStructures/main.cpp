#include "Tree/BinaryTree.hpp"
#include <iostream>
using namespace std;

int main() {
    BinaryTreeADT* tree = new BinaryTree();

    // tree->addRoot(10);
    // tree->addLeft(10, 5);
    // tree->addRight(10, 6);
    // tree->addLeft(5, 4);
    // tree->display();

    // tree->addRight(5, 6);

    tree->addRoot(10);
    tree->addLeft(10,9);
    tree->addLeft(9,8);
    tree->addLeft(8,7);
    tree->addLeft(7,6);
    tree->display();
    return 0;
}