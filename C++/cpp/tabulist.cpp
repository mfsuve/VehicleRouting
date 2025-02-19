#include <iostream>
#include <list>
#include "../hpp/random.hpp"
#include "../hpp/tabulist.hpp"
#include "../hpp/customer.hpp"

using namespace std;

TabuList::TabuList(int N, int tenure, Random* rng) : N(N), tenure(tenure), rng(rng) {
    for (int i = 0; i < N * N; ++i)
        tabulist.push_back(0);
}

void TabuList::makeTabu(int i, int j, int maxDelay) {
    int randomDelay = rng->randint(maxDelay);
    tabulist[index(i, j)] = tenure + randomDelay;
}

void TabuList::makeTabu(const Customer* i, const Customer* j, int maxDelay) {
    makeTabu(i->id, j->id, maxDelay);
}

void TabuList::makeTabu(list<Customer*>::const_iterator i, list<Customer*>::const_iterator j, int maxDelay) {
    makeTabu(*i, *j, maxDelay);
}

bool TabuList::isTabu(int i, int j) {
    return tabulist[index(i, j)] != 0;
}

bool TabuList::isTabu(const Customer* i, const Customer* j) {
    return isTabu(i->id, j->id);
}

bool TabuList::isTabu(list<Customer*>::const_iterator i, list<Customer*>::const_iterator j) {
    return isTabu(*i, *j);
}

void TabuList::step() {
    for (int i = 0; i < N * N; ++i) 
        if (tabulist[i] > 0)
            --tabulist[i];
}

int TabuList::index(int i, int j) {
    return i * N + j;
}