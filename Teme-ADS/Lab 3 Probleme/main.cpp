#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

// Problem 1: Dynamic Leaderboard
class Leaderboard {
    unordered_map<string, int> playerScores;
    // set pt sortare automata, (score, name)
    set<pair<int, string>> board;

public:
    void add(string name, int score) {
        playerScores[name] = score;
        board.insert({score, name});
    }

    void update(string name, int delta) {
        if (playerScores.find(name) != playerScores.end()) {
            // scoatem din set ca sa il putem actualiza
            board.erase({playerScores[name], name});
            playerScores[name] += delta;
            board.insert({playerScores[name], name});
        }
    }

    void remove(string name) {
        if (playerScores.find(name) != playerScores.end()) {
            board.erase({playerScores[name], name});
            playerScores.erase(name);
        }
    }

    void top(int k) {
        int count = 0;
        // parcurgere inversa pt cele mai mari scoruri
        for (auto it = board.rbegin(); it != board.rend() && count < k; ++it) {
            cout << it->second << " " << it->first << endl;
            count++;
        }
        cout << endl;
    }
};

// Problem 2: Dynamic Median
class MedianFinder {
    // impartim numerele in doua jumatati pt eficienta
    multiset<int> left;  // jumatatea mica (max element)
    multiset<int> right; // jumatatea mare (min element)

    // reechilibrare: left poate avea maxim 1 element in plus fata de right
    void balance() {
        if (left.size() > right.size() + 1) {
            auto it = prev(left.end());
            right.insert(*it);
            left.erase(it);
        } else if (right.size() > left.size()) {
            auto it = right.begin();
            left.insert(*it);
            right.erase(it);
        }
    }

public:
    void add(int x) {
        if (left.empty() || x <= *left.rbegin()) {
            left.insert(x);
        } else {
            right.insert(x);
        }
        balance();
    }

    void remove(int x) {
        auto it = left.find(x);
        if (it != left.end()) {
            left.erase(it);
        } else {
            it = right.find(x);
            if (it != right.end()) {
                right.erase(it);
            }
        }
        balance();
    }

    void getMedian() {
        if (left.empty()) return;
        // daca nr total e par sau impar, returnam *left.rbegin() 
        // conform cerintei "lower median"
        cout << "Median: " << *left.rbegin() << endl;
    }
};

int main() {
    // test problem 1
    cout << "--- Leaderboard Test ---" << endl;
    Leaderboard lb;
    lb.add("Alice", 120);
    lb.add("Bob", 90);
    lb.add("Carol", 150);
    lb.update("Bob", 50); 
    lb.top(2);
    lb.remove("Carol");
    lb.top(2);

    // test problem 2
    cout << "--- Median Test ---" << endl;
    MedianFinder mf;
    mf.add(5);
    mf.add(2);
    mf.add(10);
    mf.getMedian(); 
    mf.add(7);
    mf.getMedian(); 
    mf.remove(5);   
    mf.getMedian(); 

    return 0;
}
