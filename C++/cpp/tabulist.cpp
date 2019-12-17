#include <iostream>
#include <vector>
#include <cstdlib>
#include "../hpp/tabulist.hpp"

using namespace std;

TabuList::TabuList(int N, int tenure) : N(N), tenure(tenure) {
    cout << "N: " << N << ", tenure: " << tenure << endl;
    for (int i = 0; i < N * N; ++i)
        tabulist.push_back(0);
}

void TabuList::makeTabu(int i, int j, int maxDelay) {
    int randomDelay = rand() % maxDelay;
    tabulist[index(i, j)] = tenure + randomDelay;
}

bool TabuList::isTabu(int i, int j) {
    return tabulist[index(i, j)] != 0;
}

void TabuList::step() {
    for (int i = 0; i < N * N; ++i) 
        if (tabulist[i] > 0)
            --tabulist[i];
}

int TabuList::index(int i, int j) {
    return i * N + j;
}