#include <iostream>
using namespace std;

struct node {
    node* parent;
    node* right;
    node* left;
    int element;
};

class SplayTree {
    node* root;
    int size;

    node* create_node(int num, node* parent) {
        node* n = new node{parent, nullptr, nullptr, num};
        return n;
    }

    bool search(node* curr, int num) {
        if (!curr) {
            return false;
        }
        if (num == curr->element) {
            return true;
        }

        if (num < curr->element) {
            return search(curr->left, num);
        }
        return search(curr->right, num);
    }

    node* search_node(node* curr, int num) {
        if (num == curr->element) {
            return curr;
        }

        if (num < curr->element) {
            if (curr->left) {
                return search_node(curr->left, num);
            }
            return curr;
        }
        if (curr->right) {
            return search_node(curr->right, num);
        }
        return curr;
    }
    
    void splay(node* n) {
        while(n != root) restructure(n);
    }

    public:
    SplayTree() {
        root = NULL;
        size = 0;
    }

    bool search(int num) {
        bool status = search(root, num);
        splay(search_node(root, num));
        return status;
    }

    bool insert(int num) {
        if (root == NULL) {
            root = create_node(num, NULL);
            size++;
            return true;
        } else {
            node* parent = search_node(root, num);
            if (parent->element != num) {
                node* newest = create_node(num, parent);
                if (parent->element < num) {
                    parent->right = newest;
                } else {
                    parent->left = newest;
                }
                size++;
                splay(newest);
                return true;
            }
        }
        return false;
    }

    bool remove(int num) {
        if (isEmpty()) return false;
        node* rem_node = search_node(root, num);

        if (rem_node->element != num) return false;

        //1. splay the node to root
        splay(rem_node);

        //2. save left and right subtree and disconnect
        node* left = rem_node->left;
        node* right = rem_node->right;
        if(left) left->parent = nullptr;
        if(right) right->parent = nullptr;

        //3. delete rem_node
        delete rem_node;
        size--;

        //4. find successor (leftmost of right subtree)
        if(!right) {
            root = left;
            return true;
        }
        root = right;
        node* successor = right;
        while(successor->left) successor = successor->left;

        //5. splay successor
        splay(successor);
        root->left = left;
        if(left) left->parent = root;

        return true;
    }

    //  |
    //  y
    //   \
    //    x <- curr
    void zigleft(node* curr) {
        if(!curr->parent) return;
        node *x = curr, *y = x->parent, *z = y->parent;
        node* left = x->left;
        
        y->parent = x;
        x->left = y;
        y->right = left;
        if(left) left->parent = y;
        
        if(z) {
            y == z->right ?
            z->right = x : z->left = x;
            x->parent = z;
        }
        else {
            root = x;
            x->parent = NULL;
        }
    }

    //   |
    //   y
    //  /
    // x <- curr
    void zigright(node* curr) {
        if(!curr->parent) return;
        node *x = curr, *y = x->parent, *z = y->parent;
        node* right = x->right;
        
        y->parent = x;
        x->right = y;
        y->left = right;
        if(right) right->parent = y;
        
        if(z) {
            y == z->right ?
            z->right = x : z->left = x;
            x->parent = z;
        }
        else {
            root = x;
            x->parent = NULL;
        }
    }

    // GIVEN the child (or x), find the parent (or y), and the grandparent if any (or z).
    // Splay the child to the root recursively or iteratively.
    void restructure(node* child) {
        node* par;
        par = child->parent;

        bool ptoc_right = false;
        if (par->right == child) {
            ptoc_right = true;
        }

        node* gp;
        // If gp does not exist, proceed to doing ZIGLEFT or ZIGRIGHT.
        gp = par->parent;
        if(!gp) {
            if(ptoc_right) {
                cout << "ZIGLEFT" << endl;
                zigleft(child);
            } else {
                cout << "ZIGRIGHT" << endl;
                zigright(child);
            }
            return;
        }

        bool gtop_right = false;
        if (gp->right == par) {
            gtop_right = true;
        }

        // FOR THE FOLLOWING: Write in each of the if statements a console output
        // on its corresponding operation (ZIGZIGLEFT, ZIGZIGRIGHT, ZIGZAGLEFT, or ZIGZAGRIGHT)

        // z
        //  \
        //   y
        //    \
        //     x
        if (gtop_right && ptoc_right) {
        cout << "ZIGZIGLEFT" << endl;
        zigleft(par);
        zigleft(child);
        }

        // z
        //   \
        //     y
        //    /
        //   x
        else if (gtop_right && !ptoc_right) {
        cout << "ZIGZAGLEFT" << endl;
        zigright(child);
        zigleft(child);
        }

        //     z
        //    /
        //   y
        //  /
        // x
        else if (!gtop_right && !ptoc_right) {
        cout << "ZIGZIGRIGHT" << endl;
        zigright(par);
        zigright(child);
        }

        //      z
        //    /
        //  y
        //   \
        //    x
        else {
        cout << "ZIGZAGRIGHT" << endl;
        zigleft(child);
        zigright(child);
        }

        return;
    }

    //FOR DEBUGGING
    void print() {
        if (isEmpty()) {
            cout << "EMPTY" << endl;
            return;
        }
        cout << "PRE-ORDER: ";
        print_preorder(root);
        cout << endl << "IN-ORDER: ";
        print_inorder(root);
        cout << endl << "POST-ORDER: ";
        print_postorder(root);
        cout << endl << "STATUS: " << check_parent(root, NULL) << endl;
    }

    bool isEmpty() {
        return size == 0;
    }

    void print_preorder(node* curr) {
        cout << curr->element << " ";
        if (curr->left != NULL) {
            print_preorder(curr->left);
        }
        if (curr->right != NULL) {
            print_preorder(curr->right);
        }
    }

    void print_inorder(node* curr) {
        if (curr->left != NULL) {
            print_inorder(curr->left);
        }
        cout << curr->element << " ";
        if (curr->right != NULL) {
            print_inorder(curr->right);
        }
    }

    void print_postorder(node* curr) {
        if (curr->left != NULL) {
            print_postorder(curr->left);
        }
        if (curr->right != NULL) {
            print_postorder(curr->right);
        }
        cout << curr->element << " ";
    }

    bool check_parent(node* curr, node* par) {
        if (!curr) {
            return true;
        }
        if (curr->parent != par) {
            if (!curr->parent) {
                cout << "Illegal parent of " << curr->element << ": NULL -- must be " << par->element << endl;
            } else if (!par) {
                cout << "Illegal parent of " << curr->element << ": " << curr->parent->element << "must be NULL" << endl;
            } else {
                cout << "Illegal parent of " << curr->element << ": " << curr->parent->element << " -- must be " << par->element << endl;
            }
            return false;
        }
        return check_parent(curr->left, curr) && check_parent(curr->right, curr);
    }
};