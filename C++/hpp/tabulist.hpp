#ifndef TABULIST_HPP
#define TABULIST_HPP
#include <iostream>
#include <vector>
#include "../hpp/random.hpp"
#include "../hpp/customer.hpp"

using namespace std;

class TabuList {
public:
    int N, tenure;
    vector<int> tabulist;
    Random* rng;
    TabuList(int N, int tenure, Random* rng);
    void makeTabu(int i, int j, int maxDelay=5);
    void makeTabu(const Customer* i, const Customer* j, int maxDelay=5);
    void makeTabu(list<Customer*>::const_iterator i, list<Customer*>::const_iterator j, int maxDelay=5);
    bool isTabu(int i, int j);
    bool isTabu(const Customer* i, const Customer* j);
    bool isTabu(list<Customer*>::const_iterator i, list<Customer*>::const_iterator j);
    void step();
    int index(int i, int j);
};
#endif