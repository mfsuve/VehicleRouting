#include <iostream>
#include <vector>
#include <list>
#include "../hpp/customer.hpp"
#include "../hpp/vehicle.hpp"

using namespace std;

class Greedy {
public:
    double cost;
    Greedy(int N, int V);
    Greedy& solve(list<Customer>& customers, vector<Vehicle>& vehicles);
    pair<double, list<Customer>::iterator> bestNeighbor(list<Customer>& customers, Customer& current, Vehicle& vehicle);
private:
    int numUnvisited, N, V;
};
