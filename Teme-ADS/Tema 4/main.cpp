#include <iostream>
#include <algorithm>

using namespace std;

struct Node {
    int data, degree;
    Node *child, *sibling, *parent;

    Node(int val) : data(val), degree(0), 
                   child(nullptr), sibling(nullptr), parent(nullptr) {}
};

class BinomialHeap {
    // Folosim un array fix de radacini (maxim 32 arbori pt 2^32 elemente)
    Node* roots[32];

    // helper sa unim doi arbori de acelasi grad
    Node* linkTrees(Node* b1, Node* b2) {
        if (b1->data > b2->data) swap(b1, b2);
        b2->parent = b1;
        b2->sibling = b1->child;
        b1->child = b2;
        b1->degree++;
        return b1;
    }

public:
    BinomialHeap() {
        for (int i = 0; i < 32; i++) roots[i] = nullptr;
    }

    void unionWith(BinomialHeap& other) {
        Node* carry = nullptr;
        for (int i = 0; i < 32; i++) {
            int count = (roots[i] != nullptr) + (other.roots[i] != nullptr) + (carry != nullptr);
            
            if (count == 0) {
                // nimic de facut
            } else if (count == 1) {
                if (other.roots[i]) roots[i] = other.roots[i];
                else if (carry) roots[i] = carry;
                carry = nullptr;
            } else if (count == 2) {
                Node* a = roots[i];
                Node* b = other.roots[i];
                Node* c = carry;
                
                Node *t1 = nullptr, *t2 = nullptr;
                if (a && b) { t1 = a; t2 = b; roots[i] = nullptr; }
                else if (a && c) { t1 = a; t2 = c; roots[i] = nullptr; }
                else { t1 = b; t2 = c; }
                
                carry = linkTrees(t1, t2);
            } else { // count == 3
                Node* nextCarry = linkTrees(roots[i], other.roots[i]);
                roots[i] = carry;
                carry = nextCarry;
            }
            other.roots[i] = nullptr;
        }
    }

    void insert(int key) {
        BinomialHeap temp;
        temp.roots[0] = new Node(key);
        unionWith(temp);
    }

    int getMin() {
        int minVal = -1;
        bool found = false;
        for (int i = 0; i < 32; i++) {
            if (roots[i]) {
                if (!found || roots[i]->data < minVal) {
                    minVal = roots[i]->data;
                    found = true;
                }
            }
        }
        return minVal;
    }

    void extractMin() {
        int minIdx = -1;
        for (int i = 0; i < 32; i++) {
            if (roots[i]) {
                if (minIdx == -1 || roots[i]->data < roots[minIdx]->data) {
                    minIdx = i;
                }
            }
        }

        if (minIdx == -1) return;

        Node* minNode = roots[minIdx];
        roots[minIdx] = nullptr;

        // Punem copiii radacinii minime intr-un heap nou
        BinomialHeap childrenHeap;
        Node* curr = minNode->child;
        while (curr) {
            Node* next = curr->sibling;
            curr->sibling = nullptr;
            curr->parent = nullptr;
            childrenHeap.roots[curr->degree] = curr;
            curr = next;
        }

        delete minNode;
        unionWith(childrenHeap);
    }

    void printRoots() {
        cout << "Radacini: ";
        for (int i = 0; i < 32; i++) {
            if (roots[i]) cout << "(" << roots[i]->data << ", deg:" << i << ") ";
        }
        cout << endl;
    }
};

int main() {
    BinomialHeap h;
    h.insert(10);
    h.insert(20);
    h.insert(5);

    cout << "Minimul curent: " << h.getMin() << endl;
    h.extractMin();
    h.printRoots();

    return 0;
}

