#include <iostream>
#include <vector>
#include "../hpp/customer.hpp"
#include "../hpp/vehicle.hpp"

using namespace std;

class Greedy {
public:
    int cost;
    Greedy(int N, int V, vector<Customer>& customers, Vehicle vehicle[]);
    Greedy& solve();
    double bestNeighbor(const Customer** candidate, const Customer& current, const Vehicle& vehicle);
private:
    int numUnvisited, N, V;
    Vehicle* vehicles;
    vector<Customer>* customers;
};
