#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include "../hpp/customer.hpp"
#include "../hpp/vehicle.hpp"

using namespace std;

class Greedy {
public:
    double cost;
    Greedy(int N, int V);
    Greedy& solve(list<Customer*>& customers, vector<Vehicle>& vehicles);
    void solve_guarantee(list<Customer*>& customers, vector<Vehicle>& vehicles);
    bool solve_recursive(list<Customer*>::iterator customer, vector<Vehicle>& vehicles, list<Customer*>::iterator end, list<Customer*>::iterator begin);
    pair<double, list<Customer*>::iterator> bestNeighbor(list<Customer*>& customers, const Customer* current, Vehicle& vehicle);
private:
    int numUnvisited, N, V;
};
