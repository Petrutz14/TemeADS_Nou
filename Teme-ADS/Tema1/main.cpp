#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    } //Constructor simplu
};

//Insert() e deja functie in C++ si am pus insertit
Node* insertit(Node* root, int val) {
    if (root == nullptr) return new Node(val);
    if (val < root->data) root->left = insertit(root->left, val);
    else root->right = insertit(root->right, val);
    return root;
}

//Cautare
bool searchit(Node* root, int val) {
    if (root == nullptr) return false;
    if (root->data == val) return true;
    if (val < root->data) return searchit(root->left, val);
    return searchit(root->right, val);
}

//Min
Node* findMin(Node* root) {
    while (root && root->left) {root = root->left;}
    return root;
}


//Max
Node* findMax(Node* root) {
    while (root && root->right) {root = root->right;}
    return root;
}

//Stergere
Node* removeit(Node* root, int val) {
    if (root == nullptr) return nullptr;

    if (val < root->data) root->left = removeit(root->left, val);
    else if (val > root->data) root->right = removeit(root->right, val);
    else {
        //Caz nod gasit 1 copil
        if (root->left == nullptr) { Node* temp = root->right; delete root; return temp; }
        if (root->right == nullptr) { Node* temp = root->left; delete root; return temp; }

        //Caz nod gasit 2 copii,inlocuieste cu cel mai mic din dreapta
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = removeit(root->right, temp->data);
    }
    return root;
}

//Teste
int main() {
    //Inserari
    Node* root = nullptr;
    root = insertit(root, 50);
    insertit(root, 30);
    insertit(root, 70);
    insertit(root, 20);
    insertit(root, 100);
    insertit(root, 22);
    insertit(root, 33);
    insertit(root, 80);

    //Cautari
    cout << "E 70 in copac? " << (searchit(root, 70) ? "DA" : "NU") << endl;
    cout << "E 80 in copac? " << (searchit(root, 80) ? "DA" : "NU") << endl;
    cout << "E 1 in copac? " << (searchit(root, 1) ? "DA" : "NU") << endl;

    //Min si Max in copac
    cout << "Cel mai mic nod: " << findMin(root)->data << endl;
    cout << "Cel mai mare nod: " << findMax(root)->data << endl;

    //Stergere
    root = removeit(root, 70);
    cout << "A ramas 70 in copac? " << (searchit(root, 70) ? "DA" : "NU") << endl;
    root = removeit(root, 33);
    cout << "A ramas 33 in copac? " << (searchit(root, 33) ? "DA" : "NU") << endl;
    cout << "A ramas 80 in copac? " << (searchit(root, 80) ? "DA" : "NU") << endl;

    return 0;
}
