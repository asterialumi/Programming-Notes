#include "Specialized/BinaryTree.hpp"
#include "Primitive/Array.hpp"
#include <iostream>
#include <vector>
using namespace std;

void ds_array();
void ds_binary_tree();

int main() {
    ds_array();
    return 0;
}

void ds_array() {
    Array* a = new Array();
    char choice;
    int n, i;
    bool proceed = true;

    do {
        cout << "Op: ";
        cin >> choice;
        switch(choice) {
            case('a'): cin >> n; a->insert(n); break;
            case('r'): a->remove(); break;
            case('A'): cin >> i; cin >> n; a->insert(i,n); break;
            case('R'): cin >> i; a->remove(i); break;
            case('l'): a->clear(); break;
            case('f'): cout << a->first() << endl; break;
            case('b'): cout << a->last() << endl; break;
            case('p'): a->display(); cout << endl; break;
            case('u'): a->status(); break;
            case('q'): proceed = false; break;
            case('e'): cin >> n; a->expand(n); break;
            case('E'): cin >> n; cin >> i; a->expand(n,i); break;
            case('s'): cin >> n; a->erase(n); break;
            case('S'): cin >> i; cin >> n; a->erase(i,n); break;
            case('c'): cin >> n; a->reserve(n); break;
            case('z'): cin >> n; a->resize(n); break;
            default: cout << "invalid." << endl; break;
        }
    } while(proceed);
}

void ds_binary_tree() {
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
}