#ifndef TABUSEARCH_HPP
#define TABUSEARCH_HPP
#include <iostream>
#include <list>
#include "../hpp/tabulist.hpp"
#include "../hpp/vehicle.hpp"
#include "../hpp/customer.hpp"

using namespace std;

class TabuSearch {
public:
    int N, V, c;
    list<Customer> customers; // TODO can this be private?
    TabuSearch(const char* filename);
    void solve(int iterations, int tenure);
private:
    int cost;
    int updateToBestNeighbor(vector<Vehicle>& vehicles, TabuList& tabulist);
    int calculateNeighborCost(list<Customer>::iterator fromNodeIndex, list<Customer>::iterator toNodeIndex);
};
#endif