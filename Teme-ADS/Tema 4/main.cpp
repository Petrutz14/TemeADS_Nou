#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

struct Node {
    int data, degree;
    Node *child, *sibling, *parent;

    Node(int val) : data(val), degree(0), 
                   child(nullptr), sibling(nullptr), parent(nullptr) {}
};

class BinomialHeap {
    // lista de radacini a arborilor binomiali
    list<Node*> head;

    // functie auxiliara pentru a uni doi arbori de acelasi grad
    Node* linkTrees(Node* b1, Node* b2) {
        if (b1->data > b2->data) swap(b1, b2);
        b2->parent = b1;
        b2->sibling = b1->child;
        b1->child = b2;
        b1->degree++;
        return b1;
    }

    // functia principala de merge a doua liste de radacini
    list<Node*> mergeRootLists(list<Node*>& l1, list<Node*>& l2) {
        list<Node*> res;
        auto it1 = l1.begin(), it2 = l2.begin();
        while (it1 != l1.end() && it2 != l2.end()) {
            if ((*it1)->degree <= (*it2)->degree) {
                res.push_back(*it1);
                it1++;
            } else {
                res.push_back(*it2);
                it2++;
            }
        }
        while (it1 != l1.end()) res.push_back(*it1++);
        while (it2 != l2.end()) res.push_back(*it2++);
        return res;
    }

public:
    BinomialHeap() {}

    void insert(int key) {
        BinomialHeap tempHeap;
        tempHeap.head.push_back(new Node(key));
        unionWith(tempHeap);
    }

    void unionWith(BinomialHeap& other) {
        head = mergeRootLists(head, other.head);
        other.head.clear(); // golim cealalta lista

        if (head.empty()) return;

        auto curr = head.begin();
        auto next = std::next(curr);
        auto next_next = (next != head.end()) ? std::next(next) : head.end();

        while (next != head.end()) {
            // caz 1: grade diferite SAU 3 de acelasi grad (pastram primul, combinam restul la pasul urmator)
            if ((*curr)->degree != (*next)->degree || 
               (next_next != head.end() && (*next_next)->degree == (*curr)->degree)) {
                curr++;
                next++;
            } 
            // caz 2: grad curr == grad next, decidem care devine parinte
            else if ((*curr)->data <= (*next)->data) {
                (*curr) = linkTrees(*curr, *next);
                next = head.erase(next);
            } else {
                (*next) = linkTrees(*next, *curr);
                curr = head.erase(curr);
            }
            if (next != head.end()) next_next = std::next(next);
            else next_next = head.end();
        }
    }

    int getMin() {
        if (head.empty()) return -1;
        Node* minNode = nullptr;
        for (auto node : head) {
            if (minNode == nullptr || node->data < minNode->data) {
                minNode = node;
            }
        }
        return minNode->data;
    }

    void extractMin() {
        if (head.empty()) return;

        // 1. Gasim radacina minima
        auto minIt = head.begin();
        Node* minNode = *minIt;
        for (auto it = head.begin(); it != head.end(); ++it) {
            if ((*it)->data < minNode->data) {
                minNode = *it;
                minIt = it;
            }
        }

        // 2. Scoatem din lista de radacini
        head.erase(minIt);

        // 3. Inversam lista copiilor (copiii sunt tinuti de la grad mare la mic)
        BinomialHeap childrenHeap;
        Node* child = minNode->child;
        while (child) {
            Node* nextChild = child->sibling;
            child->sibling = nullptr;
            child->parent = nullptr;
            childrenHeap.head.push_front(child);
            child = nextChild;
        }

        // 4. Union cu heap-ul copiilor
        unionWith(childrenHeap);
        delete minNode;
    }

    void printRoots() {
        cout << "Radacini: ";
        for (auto node : head) {
            cout << "(" << node->data << ", deg:" << node->degree << ") ";
        }
        cout << endl;
    }
};

int main() {
    BinomialHeap h;

    // testari
    h.insert(10);
    h.insert(20);
    h.insert(5);

    cout << "Minimul curent: " << h.getMin() << endl;
    h.extractMin(); // de schimbat
    
    h.printRoots();

    return 0;
}
