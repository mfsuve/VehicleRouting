#ifndef TABUSEARCH_HPP
#define TABUSEARCH_HPP
#include <iostream>
#include <vector>
#include "../hpp/tabulist.hpp"
#include "../hpp/vehicle.hpp"
#include "../hpp/customer.hpp"

using namespace std;

class TabuSearch {
public:
    int N, V, c;
    vector<Customer> customers;
    TabuSearch(const char* filename);
    void solve(int iterations, int tenure);
private:
    int cost;
    int updateToBestNeighbor(Vehicle vehicles[], TabuList& tabulist);
    int TabuSearch::calculateNeighborCost(list<Customer>::iterator fromNodeIndex, list<Customer>::iterator toNodeIndex);
};
#endif