#include <iostream>
using namespace std;

struct Node {
    int data;
    bool isRed;
    Node *parent, *left, *right;

    //node constructor,nodurile sunt rosii cand intra in copac
    Node(int val, bool redStatus = true)
        : data(val), isRed(redStatus), parent(nullptr), left(nullptr), right(nullptr) {}
};

class RBTree {
    Node *NIL, *root;

    //0=left,1=right
    void rotate(Node* node, int direction) {
        Node* child = (direction == 0) ? node->right : node->left;

        //link node to child inner subtree
        if (direction == 0) {
            node->right = child->left;
            if (child->left != NIL) child->left->parent = node;
        } else {
            node->left = child->right;
            if (child->right != NIL) child->right->parent = node;
        }

        //link copil la paarinte
        child->parent = node->parent;
        if (node->parent == nullptr) {
            root = child;
        } else {
            if (node == node->parent->left) node->parent->left = child;
            else node->parent->right = child;
        }

        //nod sub copil
        if (direction == 0) child->left = node;
        else child->right = node;
        node->parent = child;
    }

    void fixInsert(Node* newNode) {
        while (newNode->parent->isRed) {
            bool parentIsLeft = (newNode->parent == newNode->parent->parent->left);
            Node* uncle = parentIsLeft ? newNode->parent->parent->right : newNode->parent->parent->left;

            if (uncle->isRed) {
                //unchi rosu,recolorare
                newNode->parent->isRed = uncle->isRed = false;
                newNode->parent->parent->isRed = true;
                newNode = newNode->parent->parent;
            } else {
                //triunghi,rotire sa se faca linie
                if (newNode == (parentIsLeft ? newNode->parent->right : newNode->parent->left)) {
                    newNode = newNode->parent;
                    rotate(newNode, parentIsLeft ? 0 : 1);
                }
                //linie,rotire bunic si recolorare
                newNode->parent->isRed = false;
                newNode->parent->parent->isRed = true;
                rotate(newNode->parent->parent, parentIsLeft ? 1 : 0);
            }
            if (newNode == root) break;
        }
        root->isRed = false; //root e negru mereu
    }

public:
    RBTree() {
        NIL = new Node(0, false); // nodurile NIL sunt negre
        root = NIL;
    }


    bool search(int key) {
        Node* current = root;
        while (current != NIL) {
            if (key == current->data) return true;
            current = (key < current->data) ? current->left : current->right;
        }
        return false;
    }

    int findMin() {
        if (root == NIL) return -1;
        Node* current = root;
        while (current->left != NIL) current = current->left;
        return current->data;
    }

    int findMax() {
        if (root == NIL) return -1;
        Node* current = root;
        while (current->right != NIL) current = current->right;
        return current->data;
    }

    void insert(int key) {
        Node *newNode = new Node(key);
        newNode->left = newNode->right = NIL;

        Node *trailing = nullptr;
        Node *current = root;

        while (current != NIL) {
            trailing = current;
            current = (newNode->data < current->data) ? current->left : current->right;
        }

        newNode->parent = trailing;
        if (trailing == nullptr) root = newNode;
        else if (newNode->data < trailing->data) trailing->left = newNode;
        else trailing->right = newNode;

        if (newNode->parent == nullptr) {
            newNode->isRed = false;
            return;
        }
        if (newNode->parent->parent != nullptr) fixInsert(newNode);
    }
};

int main() {
    RBTree tree;

    //inserari
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(100);
    tree.insert(22);
    tree.insert(33);
    tree.insert(80);

    //cautari
    cout << "E 70 in copac? " << (tree.search(70) ? "DA" : "NU") << endl;
    cout << "E 80 in copac? " << (tree.search(80) ? "DA" : "NU") << endl;
    cout << "E 1 in copac? "  << (tree.search(1) ? "DA" : "NU") << endl;

    //min si max
    cout << "Cel mai mic nod: " << tree.findMin() << endl;
    cout << "Cel mai mare nod: " << tree.findMax() << endl;

    return 0;
}
