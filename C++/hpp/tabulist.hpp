#ifndef TABULIST_HPP
#define TABULIST_HPP
#include <iostream>
#include <vector>
#include "../hpp/customer.hpp"

using namespace std;

class TabuList {
public:
    int N, tenure;
    vector<int> tabulist;
    TabuList(int N, int tenure);
    void makeTabu(int i, int j, int maxDelay=5);
    void makeTabu(Customer i, Customer j, int maxDelay=5);
    void makeTabu(list<Customer>::iterator i, list<Customer>::iterator j, int maxDelay=5);
    bool isTabu(int i, int j);
    bool isTabu(Customer i, Customer j);
    bool isTabu(list<Customer>::iterator i, list<Customer>::iterator j);
    void step();
    int index(int i, int j);
};
#endif