#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Problem 1: Dynamic Leaderboard
struct Player {
    string name;
    int score;
};

class Leaderboard {
    vector<Player> players;

public:
    void add(string name, int score) {
        players.push_back({name, score});
    }

    void update(string name, int delta) {
        for (int i = 0; i < players.size(); i++) {
            if (players[i].name == name) {
                players[i].score += delta;
                return;
            }
        }
    }

    void remove(string name) {
        for (int i = 0; i < players.size(); i++) {
            if (players[i].name == name) {
                players.erase(players.begin() + i);
                return;
            }
        }
    }

    // comparator pt sortare descrescatoare
    static bool comparePlayers(Player a, Player b) {
        if (a.score != b.score) return a.score > b.score;
        return a.name < b.name;
    }

    void top(int k) {
        vector<Player> sortedPlayers = players;
        sort(sortedPlayers.begin(), sortedPlayers.end(), comparePlayers);

        for (int i = 0; i < k && i < sortedPlayers.size(); i++) {
            cout << sortedPlayers[i].name << " " << sortedPlayers[i].score << endl;
        }
        cout << endl;
    }
};

// Problem 2: Dynamic Median
class MedianFinder {
    vector<int> numbers;

public:
    void add(int x) {
        numbers.push_back(x);
        sort(numbers.begin(), numbers.end()); // sortam la fiecare adaugare
    }

    void remove(int x) {
        for (int i = 0; i < numbers.size(); i++) {
            if (numbers[i] == x) {
                numbers.erase(numbers.begin() + i);
                return; // scoatem doar o aparitie
            }
        }
    }

    void getMedian() {
        if (numbers.empty()) return;
        
        int n = numbers.size();
        // daca e par, n/2 - 1 e "lower median" pt indexare de la 0
        // exemplu: [2, 5, 7, 10] (n=4) -> medianul e 5 (index 1)
        if (n % 2 == 1) {
            cout << "Median: " << numbers[n / 2] << endl;
        } else {
            cout << "Median: " << numbers[n / 2 - 1] << endl;
        }
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

