#ifndef TABUSEARCH_HPP
#define TABUSEARCH_HPP
#include <iostream>
#include <list>
#include <string>
#include "../hpp/random.hpp"
#include "../hpp/tabulist.hpp"
#include "../hpp/vehicle.hpp"
#include "../hpp/customer.hpp"

using namespace std;

class TabuSearch {
public:
    int N, V, c;
    Random* rng;
    vector<Vehicle> bestVehicles;
    list<Customer*> customers; // TODO can this be private?
    TabuSearch(const char* filename, Random* rng, bool verbose=false);
    ~TabuSearch();
    double solve(int TID, int iterations, int tenure, double initMutationRate=1000000, double deltaMutationRate=0.98, bool save=false);
private:
    double cost;
    double updateToBestNeighbor(vector<Vehicle>& vehicles, TabuList& tabulist, double bestCost);
    double calculateNeighborCost(list<Customer*>::const_iterator fromNodeIndex, list<Customer*>::const_iterator toNodeIndex);
    double mutate(vector<Vehicle>& vehicles);
};
#endif