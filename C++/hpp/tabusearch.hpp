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
    TabuSearch(const char* filename, bool verbose=false);
private:
    double cost;
    bool verbose;
    double updateToBestNeighbor(vector<Vehicle>& vehicles, TabuList& tabulist);
    double calculateNeighborCost(list<Customer>::iterator fromNodeIndex, list<Customer>::iterator toNodeIndex);
};
#endif