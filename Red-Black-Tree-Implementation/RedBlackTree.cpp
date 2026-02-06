#include <iostream>
#include <stdexcept>
/*for handling exceptions*/
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;

    Node(int newdata) {
        data = newdata;
        color = RED;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

class RedBlackTree {
private:
    Node* root;

protected:
    void rotateLeft(Node* z) {
        if (z == nullptr || z->right == nullptr) 
            throw invalid_argument("left rotation not available");
        Node* y = z->right;
        z->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = z;
        }
        y->parent = z->parent;
        if (z->parent == nullptr) {
            root = y;
        } else if (z == z->parent->left) {
            z->parent->left = y;
        } else {
            z->parent->right = y;
        }
        y->left = z;
        z->parent = y;
    }

    void rotateRight(Node* z) {
        if (z == nullptr || z->left == nullptr)
           throw invalid_argument("right rotation not available");
 
        Node* y = z->left;
        z->left = y->right;

        if (y->right != nullptr) 
            y->right->parent = z;
        y->parent = z->parent;
        if (z->parent == nullptr) {
            root = y;
        }
        else if (z->parent->left == z) {
            z->parent->left = y;
        } else {
            z->parent->right = y;
        }
        y->right = z;
        z->parent = y;
    }

public:
    RedBlackTree() {
        root = nullptr;
    }

    void insertRB(int data) {
        Node* z = new Node(data);
        Node* y = nullptr;
        Node* temp = root;

        while (temp != nullptr) 
        /*traversing the tree, finding
        the right spot for the inserted node*/
        {
            y = temp;
            if (z->data < temp->data) {
                temp = temp->left;
                /*go left if the node is smaller*/
            } else {
                temp = temp->right;
            }
        }
        z->parent = y;/*setting the parent of the new node*/
        if (y == nullptr) {
            root = z;
        } else if (z->data < y->data) {
            y->left = z;
        } else {
            y->right = z;
        }
        z->color = RED;

        RBInsertFixUp(z); 
    }

    void RBInsertFixUp(Node* z) {
        while (z->parent != nullptr && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;

                if (y != nullptr && y->color == RED) 
                /*case 1: unlce is red*/
                {
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    y->color = BLACK;
                    z = z->parent->parent;
                    /*move up the tree*/
                } else {
                    if (z == z->parent->right) 
                    /*case 2: z is the right child*/
                    {
                        z = z->parent;
                        rotateLeft(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateRight(z->parent->parent);
                }
            } else {
                Node* y = z->parent->parent->left;
                if (y != nullptr && y->color == RED)
                /*case 3: uncle is red*/
                {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left)
                    /*case 4: z is the left child*/
                    {
                        z = z->parent;
                        rotateRight(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateLeft(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
        /*ensure the root is always black*/
    }

    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr) 
        /*if u is the root*/
        {
            root = v;/*make v the root*/
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v != nullptr) {
            v->parent = u->parent;/*set parent of v to be parent of u*/
        }
    }

    void deleteRB(Node* z) {
        if (z == nullptr) {
            throw runtime_error("cannot delete null node");
        }

        Node* y = z; /* node to be deleted/moved */
        Node* ychild; /* child to replace y in the tree */
        Color yOgColor = y->color;

        if (z->left == nullptr) {
            ychild = z->right;
            transplant(z, z->right); /* replace z with its right child */
        } else if (z->right == nullptr) {
            ychild = z->left;
            transplant(z, z->left); /* replace z with its left child */
        } else {
            y = subtreeMinimum(z->right);
            yOgColor = y->color;
            ychild = y->right;

            if (y->parent == z) {
                if (ychild != nullptr)
                    ychild->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                if (y->right != nullptr)
                    y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            if (y->left != nullptr)
                y->left->parent = y;

            y->color = z->color;
        }
        if (yOgColor == BLACK) {
            if (ychild != nullptr) {
                deleteFixUp(ychild);
            }
        }
    }

    void deleteFixUp(Node* z) {
        while (z != root && z->color == BLACK) {
            Node* w;/*will hold sibling of z*/
            if (z == z->parent->right)
            /*case 1: if z is the right child of its parent,
            then w is the left sibling*/
            {
                w = z->parent->left; /* left sibling */
                if (w != nullptr && w->color == RED) 
                /*case 1a: if w is red, w perform a right
                rotation on z's parent*/
                {
                    w->color = BLACK;
                    z->parent->color = RED;
                    rotateRight(z->parent);
                    w = z->parent->left;
                }

                if (w == nullptr || (w->left == nullptr && w->right == nullptr) 
                || ((w->left != nullptr && w->left->color == BLACK) && 
                     (w->right != nullptr && w->right->color == BLACK))) 
                /*case 1b: if w is BLACK and both children are either null
                 or BLACK*/     
                     {
                    if (w != nullptr) w->color = RED;
                    z = z->parent;
                } else {
                    if (w->left == nullptr || w->left->color == BLACK) 
                    /*case 1c: if w has a red child, we need rotation 
                    to balance*/
                    {
                        if (w->right != nullptr) {
                            w->right->color = BLACK;
                        }
                        w->color = RED;
                        rotateLeft(w);
                        w = z->parent->left;
                    }
                    /*case 1d: now w's left child is red, we can perform
                    the final fix*/
                    w->color = z->parent->color;/*inherit the color 
                    of the parent*/
                    z->parent->color = BLACK;
                    if (w->left != nullptr) w->left->color = BLACK;
                    rotateRight(z->parent);
                    z = root;
                }
            } else {
                /*case 2: if z is the left child of its parent,
                then w is tthe right sibling*/
                w = z->parent->right;
                if (w != nullptr && w->color == RED)
                /*case 2a: if w is red, we perform left rotation
                on z's parent*/
                {
                    w->color = BLACK;
                    z->parent->color = RED;
                    rotateLeft(z->parent);
                    w = z->parent->right;
                }

                if (w == nullptr || (w->left == nullptr && w->right == nullptr)
                || ((w->left != nullptr && w->left->color == BLACK) && 
                     (w->right != nullptr && w->right->color == BLACK))) 
                /*case 2b: is w is black and both children are either null 
                or black*/     
                     {
                    if (w != nullptr) w->color = RED;
                    z = z->parent;
                } else {
                    if (w->right == nullptr || w->right->color == BLACK)
                    /*case 2c: if w has a red child, we need to rotate
                    to balance*/
                    {
                        if (w->left != nullptr) {
                            w->left->color = BLACK;
                        }
                        w->color = RED;
                        rotateRight(w);
                        w = z->parent->right;
                    }
                    /*case 2d: now w's right child is red, we
                    can perform the final fix*/
                    w->color = z->parent->color;
                    z->parent->color = BLACK;
                    if (w->right != nullptr) w->right->color = BLACK;
                    rotateLeft(z->parent);
                    z = root;
                }
            }
        }
        z->color = BLACK;
    }
    Node* predecessor(const Node* &node) {
        if (node == nullptr)
            throw invalid_argument("no predecessor found");
    
        Node* x = const_cast<Node*>(node);
        /*cast away const(=> allows modifictaions + traversal)*/
    
        if (x->left != nullptr) 
        /*case 1: if left child exists, go to left
        subtree*/
        {
            Node* current = x->left;
            while (current->right != nullptr)
                current = current->right;
                /*find the leftmost node in he left subtree*/
            return current;
            /*the rightmost node is the predecessor*/
        }
    
        Node* y = x->parent;
        /*case 2: no left subtree*/
        while (y != nullptr && x == y->left)
        /*go up until we move from a right 
        child to its parent*/
        {
            x = y;/*move up one level*/
            y = y->parent;/*continue climbing*/
        }
    
        return y;/*could be nullptr if no predecessor exists*/
    } 
    Node* successor(const Node* &node) {
        if (node == nullptr)
            throw invalid_argument("no succesor found");
    
        Node* x = const_cast<Node*>(node);
    
        if (x->right != nullptr) {
            Node* current = x->right;
            while (current->left != nullptr)
                current = current->left;
            return current;
        }
    
        Node* y = x->parent;
        while (y != nullptr && x == y->right) {
            x = y;
            y = y->parent;
        }
    
        return y;
    }       
    Node* getMinimum() {
        if (root == nullptr) throw runtime_error("empty tree");
        Node* current = root;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }
    Node* subtreeMinimum(Node* node) {
        if (node == nullptr) throw invalid_argument("null subtree");
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    Node* getMaximum() {
        if (root == nullptr) throw runtime_error("empty tree");
        Node* current = root;
        while (current->right != nullptr) {
            current = current->right;
        }
        return current;
    }
    Node* search(int data) {
        Node* z = root;
        while (z != nullptr && data != z->data) {
            if (data < z->data) {
                z = z->left;
            } else {
                z = z->right;
            }
        }
        return z;
    }
};

int main() {
    RedBlackTree rbt;

    cout << "inserting elements into the Red-Black Tree" << endl;
    rbt.insertRB(23);
    rbt.insertRB(16);
    rbt.insertRB(78);
    rbt.insertRB(21);
    rbt.insertRB(45);
    rbt.insertRB(15);
    rbt.insertRB(4);
    rbt.insertRB(29);

    cout << "searching for element 45 " << endl;
    Node* node = rbt.search(45);
    if (node != nullptr) {
        cout << "node with data: " << node->data << " found" << endl;
    } else {
        cout << "Node with data 15 not found" << endl;
    }

    cout << "deleting node with data 45" << endl;
    rbt.deleteRB(node);

    cout << "searching for the element 15 after deletion" << endl;
    node = rbt.search(45);
    if (node != nullptr) {
        cout << "node with the data " << node->data << " found" << endl;
    } else {
        cout << "Node with data 15 not found after deletion" << endl;
    }

    return 0;
}
