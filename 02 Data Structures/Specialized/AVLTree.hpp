#include "mybintree.hpp"
#include <iostream>
using namespace std;

class AVLTree {
	MyBinaryTree* tree = new MyBinaryTree();
    
    bool isBalanced(node* curr) {
        int left = curr->left ? curr->left->height() : 0;
        int right = curr->right ? curr->right->height() : 0;
        return abs(left - right) <= 1;
    }
    
	public:
	bool search(int num) {
		return search_node(tree->getRoot(), num);
	}

	bool search_node(node* n, int num) {
		if (n == NULL) {
			return false;
		}
		if (n->elem == num) {
			return true;
		}
		if (num > n->elem) {
			// proceed to right
			return search_node(n->right, num);
		} else {
			return search_node(n->left, num);
		}
	}

    // TODO perform post-processing by checking for violation after insertion
    // from the node inserted (or from its parent) until the root
	node* insert(int num) {
		node* n = tree->getRoot();
		if (n == NULL) {
			return tree->addRoot(num);
		}
		return insert_node(n, num);
	}

	node* insert_node(node* n, int num) {
		if (n == NULL) {
			return NULL;
		}
		if (n->elem == num) {
			return NULL;
		}
		if (num > n->elem) {
			if (!n->right) {
				node* ret = tree->addRight(n, num);
				
				node* curr = ret->parent;
				while(curr) {
				    if(!isBalanced(curr)) restructure(curr);
				    curr = curr->parent;
				}
				
				return ret;
			} else {
				return insert_node(n->right, num);
			}
		} else {
			if (!n->left) {
				node* ret = tree->addLeft(n, num);
				
				node* curr = ret->parent;
				while(curr) {
				    if(!isBalanced(curr)) restructure(curr);
				    curr = curr->parent;
				}
				
				return ret;
			} else {
				return insert_node(n->left, num);
			}
		}
	}


    // TODO perform post-processing by checking for violation after deletion
    // from the parent of the node removed until the root
    bool remove(int num) {
        return remove_node(tree->getRoot(), num);
    }

	bool remove_node(node* n, int num) {
		if (n == NULL) {
			return false;
		}
		if (n->elem == num) {
		    node* curr;
            if (n->left && n->right) {
                node* r = n->right;
                while (r->left) {
                    r = r->left;
                }
                curr = r->parent;
                int rem = tree->remove(r);
                n->elem = rem;
            } else {
                curr = n->parent;
    			tree->remove(n);
            }
            
            while(curr) {
			    if(!isBalanced(curr)) restructure(curr);
			    curr = curr->parent;
			}
            return true;
		}
		if (num > n->elem) {
			return remove_node(n->right, num);
		} else {
			return remove_node(n->left, num);
		}
	}

    // TODO copy and paste your completed restructure method here
     bool restructure(node* gp) {
        node* par; // parent
        // TODO find parent
        int gpleft = gp->left ? gp->left->height() : 0;
        int gpright = gp->right? gp->right->height() : 0;
        par = gpleft > gpright ?
        gp->left : gp->right;
        // This is an indicator of the placement of grandparent to parent (gtop)
        bool gtop_right = false;
        if (gp->right == par) {
            gtop_right = true;
        }

        node* child;
        // TODO find child
        int parleft = par->left ? par->left->height() : 0;
        int parright = par->right? par->right->height() : 0;
        if(parleft == parright) {
            if(gtop_right) child = par->right;
            else child = par->left;
        }
        else child = parleft > parright ?
        par->left : par->right;
        // This is an indicator of the placement of parent to child (ptoc)
        bool ptoc_right = false;
        if (par->right == child) {
            ptoc_right = true;
        }

        // FOR THE FOLLOWING: Write in each of the if statements a console output
        // on its corresponding operation (ZIGLEFT, ZIGRIGHT, ZIGZAGLEFT, or ZIGZAGRIGHT)

        // z
        //  \
        //   y
        //    \
        //     x
        if (gtop_right && ptoc_right) {
            // TODO call to either zigleft or zigright or both
            cout << "ZIGLEFT" << endl;
            zigleft(par);
        }

        // z
        //   \
        //     y
        //    /
        //   x
        else if (gtop_right && !ptoc_right) {
            // TODO call to either zigleft or zigright or both
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
            // TODO call to either zigleft or zigright or both
            cout << "ZIGRIGHT" << endl;
            zigright(par);
        }

        //      z
        //    /
        //  y
        //   \
        //    x
        else {
            // TODO call to either zigleft or zigright or both
            cout << "ZIGZAGRIGHT" << endl;
            zigleft(child);
            zigright(child);
        }

        return true;
    }

    void zigleft(node* curr) {
        tree->zigleft(curr);
    }

    void zigright(node* curr) {
        tree->zigright(curr);
    }

	void print() {
		tree->print();
	}
};