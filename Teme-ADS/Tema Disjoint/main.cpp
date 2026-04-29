#include <iostream>
#include <vector>

using namespace std;

// Folosim array-uri pt simplitate
int tata[1001];
int rang[1001];
int nrComponente;

void initializare(int n) {
    for (int i = 0; i < n; i++) {
        tata[i] = i;
        rang[i] = 0;
    }
    nrComponente = n;
}

// find cu path compression (recursiv simplu)
int cauta(int i) {
    if (tata[i] == i) return i;
    return tata[i] = cauta(tata[i]);
}

// union prin rang
bool uneste(int i, int j) {
    int rad_i = cauta(i);
    int rad_j = cauta(j);

    if (rad_i != rad_j) {
        if (rang[rad_i] < rang[rad_j]) {
            tata[rad_i] = rad_j;
        } else if (rang[rad_i] > rang[rad_j]) {
            tata[rad_j] = rad_i;
        } else {
            tata[rad_i] = rad_j;
            rang[rad_j]++;
        }
        nrComponente--;
        return true;
    }
    return false;
}

void solveConnectedComponents(int n, vector<pair<int, int>> edges) {
    initializare(n);
    for (auto edge : edges) {
        uneste(edge.first, edge.second);
    }
    cout << "Componente conexe: " << nrComponente << endl;
}

void detectCycles(int n, vector<pair<int, int>> edges) {
    initializare(n);
    bool hasCycle = false;
    for (auto edge : edges) {
        if (!uneste(edge.first, edge.second)) {
            hasCycle = true;
            cout << "Ciclu detectat la muchia (" << edge.first << ", " << edge.second << ")" << endl;
        }
    }
    if (!hasCycle) cout << "Nu s-au detectat cicluri." << endl;
}

void solveProvinces(vector<vector<int>> matrix) {
    int n = matrix.size();
    initializare(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (matrix[i][j] == 1) uneste(i, j);
        }
    }
    cout << "Numar provincii: " << nrComponente << endl;
}

void solveSocialNetwork(int n, vector<pair<int, int>> friendships) {
    initializare(n);
    for (auto f : friendships) {
        uneste(f.first, f.second);
    }

    cout << nrComponente << " Groups" << endl;
    
    // pt fiecare radacina posibila, gasim membrii
    int gIdx = 1;
    bool vizitat[1001] = {false};
    
    for (int i = 0; i < n; i++) {
        int radacina = cauta(i);
        if (!vizitat[radacina]) {
            vizitat[radacina] = true;
            cout << "Group " << gIdx++ << ": {";
            
            bool prim = true;
            int count = 0;
            for (int j = 0; j < n; j++) {
                if (cauta(j) == radacina) {
                    if (!prim) cout << ",";
                    cout << j;
                    prim = false;
                    count++;
                }
            }
            cout << "} size " << count << endl;
        }
    }
}

int main() {
    // 1 & 2. Connected Components & Cycles
    cout << "--- Task 1 & 2 ---" << endl;
    int n1 = 5;
    vector<pair<int, int>> edges1 = {{0, 1}, {1, 2}, {3, 4}, {0, 2}};
    solveConnectedComponents(n1, edges1);
    detectCycles(n1, edges1);

    // 3. Provinces
    cout << "\n--- Task 3 (Provinces) ---" << endl;
    vector<vector<int>> matrix = {{1, 1, 0}, {1, 1, 0}, {0, 0, 1}};
    solveProvinces(matrix);

    // 4. Social Network
    cout << "\n--- Task 4 (Social Network) ---" << endl;
    int n2 = 7;
    vector<pair<int, int>> friendships = {{0, 1}, {1, 2}, {3, 4}, {5, 6}};
    solveSocialNetwork(n2, friendships);

    return 0;
}

