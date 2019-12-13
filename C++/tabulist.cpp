#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

class TabuList {
public:
    int N, tenure;
    vector<int> tabulist;

    TabuList(int N, int tenure) : N(N), tenure(tenure) {
        srand(0);
        for (int i = 0; i < N * N; ++i)
            tabulist.push_back(0);
    }
    
    void makeTabu(int i, int j, int maxDelay=5) {
        int randomDelay = rand() % maxDelay;
        tabulist[index(i, j)] = tenure + randomDelay;
    }

    bool isTabu(int i, int j) {
        return tabulist[index(i, j)] != 0;
    }

    void step() {
        for (int i = 0; i < N * N; ++i) 
            if (tabulist[i] > 0)
                --tabulist[i];
    }

private:
    int index(int i, int j) {
        return i * N + j;
    }
};