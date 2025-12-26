#include "Tree/BinaryTree.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    BinaryTree* tree1 = new BinaryTree();
    BinaryTree* tree2 = new BinaryTree();
    BinaryTree* tree3 = new BinaryTree();
    vector<BinaryTree*> tree = {tree1, tree2, tree3};
    int i = 0;
    int n, par;
    char choice;
    bool condition, cont = true;
    
    //addRoot: a
    //addLeft: L
    //addRight: R
    //size: s
    //search: f
    //preorder: e
    //inorder: i
    //postorder: o
    //levelorder: l
    //remove: r
    //display: d
    //quit: q

    do {
        cout << "Op: "; cin >> choice;

        switch(choice) {
            case('a'):
                cin >> n;
                tree[i]->addRoot(n);
                break;
            case('L'):
                cin >> par;
                cin >> n;
                tree[i]->addLeft(par,n);
                break;
            case('R'):
                cin >> par;
                cin >> n;
                tree[i]->addRight(par,n);
                break;
            case('s'):
                tree[i]->size();
            case('f'):
                cin >> n;
                condition = tree[i]->search(n);
                if(condition) cout << n << " found in tree.";
                else cout << n << " not found in tree.";
                cout << endl;
            case('e'):
                tree[i]->preorder();
                break;
            case('i'):
                tree[i]->inorder();
                break;
            case('o'):
                tree[i]->postorder();
                break;
            case('l'):
                tree[i]->levelorder();
                break;
            case('r'):
                cin >> n;
                condition = tree[i]->remove(n);
                if(condition) cout << n << " successfully removed.";
                else cout << n << " was not removed.";
                cout << endl;
                break;
            case('d'):
                tree[i]->display();
                break;
            case('q'):
                cont = false;
                break;
            default:
                cout << "incorrect command." << endl;
                break;
        }
    }while(cont);
    return 0;
}