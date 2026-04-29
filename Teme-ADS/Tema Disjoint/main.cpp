#include <iostream>
#include <vector>
#include <numeric>
#include <unordered_map>
#include <set>

using namespace std;

// Structura pt Disjoint Set Union (DSU)
class DSU {
    vector<int> parent;
    vector<int> rank;
    int components;

public:
    DSU(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0); // initial, fiecare e propriul parinte
        rank.assign(n, 0);
        components = n;
    }

    // find cu path compression
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]); // scurtam drumul spre radacina
    }

    // union prin rank
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);

        if (root_i != root_j) {
            if (rank[root_i] < rank[root_j]) {
                parent[root_i] = root_j;
            } else if (rank[root_i] > rank[root_j]) {
                parent[root_j] = root_i;
            } else {
                parent[root_i] = root_j;
                rank[root_j]++;
            }
            components--; // am unit doua grupuri
            return true;
        }
        return false; // erau deja in acelasi grup (ciclu detectat)
    }

    int getNumComponents() {
        return components;
    }
};

void solveConnectedComponents(int n, vector<pair<int, int>> edges) {
    DSU dsu(n);
    for (auto edge : edges) {
        dsu.unite(edge.first, edge.second);
    }
    cout << "Componente conexe: " << dsu.getNumComponents() << endl;
}

void detectCycles(int n, vector<pair<int, int>> edges) {
    DSU dsu(n);
    bool hasCycle = false;
    for (auto edge : edges) {
        if (!dsu.unite(edge.first, edge.second)) {
            hasCycle = true;
            cout << "Ciclu detectat la muchia (" << edge.first << ", " << edge.second << ")" << endl;
        }
    }
    if (!hasCycle) cout << "Nu s-au detectat cicluri." << endl;
}

void solveProvinces(vector<vector<int>> isConnected) {
    int n = isConnected.size();
    DSU dsu(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (isConnected[i][j] == 1) {
                dsu.unite(i, j);
            }
        }
    }
    cout << "Numar provincii: " << dsu.getNumComponents() << endl;
}

void solveSocialNetwork(int n, vector<pair<int, int>> friendships) {
    DSU dsu(n);
    for (auto f : friendships) {
        dsu.unite(f.first, f.second);
    }

    // grupam membrii pt fiecare radacina
    unordered_map<int, vector<int>> groups;
    for (int i = 0; i < n; i++) {
        groups[dsu.find(i)].push_back(i);
    }

    cout << dsu.getNumComponents() << " Groups" << endl;
    int groupNum = 1;
    for (auto const& [root, members] : groups) {
        cout << "Group " << groupNum++ << ": {";
        for (int i = 0; i < members.size(); i++) {
            cout << members[i] << (i == members.size() - 1 ? "" : ",");
        }
        cout << "} size " << members.size() << endl;
    }
}

int main() {
    // 1 & 2. Connected Components & Cycles
    cout << "--- Task 1 & 2 ---" << endl;
    int n1 = 5;
    vector<pair<int, int>> edges1 = {{0, 1}, {1, 2}, {3, 4}, {0, 2}}; // 0-2 inchide ciclu
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
