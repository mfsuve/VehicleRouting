#ifndef TABUSEARCH_HPP
#define TABUSEARCH_HPP
#include <iostream>
#include <list>
#include <string>
#include "../hpp/tabulist.hpp"
#include "../hpp/vehicle.hpp"
#include "../hpp/customer.hpp"

using namespace std;

class TabuSearch {
public:
    int N, V, c;
    vector<Vehicle> bestVehicles;
    list<Customer*> customers; // TODO can this be private?
    TabuSearch(const char* filename, bool verbose=false);
    ~TabuSearch();
    double solve(int iterations, int tenure, bool save=false);
private:
    string outputFilename;
    double cost;
    bool verbose;
    double updateToBestNeighbor(vector<Vehicle>& vehicles, TabuList& tabulist, double bestCost);
    double calculateNeighborCost(list<Customer*>::const_iterator fromNodeIndex, list<Customer*>::const_iterator toNodeIndex);
};
#endif