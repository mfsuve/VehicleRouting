#include <iostream>
#include <vector>
#include <list>
#include <limits>
#include "../hpp/greedy.hpp"
#include "../hpp/customer.hpp"
#include "../hpp/vehicle.hpp"

using namespace std;

Greedy::Greedy(int N, int V) : cost(0), N(N), V(V), numUnvisited(N - 1) {}

pair<double, list<Customer>::iterator> Greedy::bestNeighbor(list<Customer>& customers, Customer& current, Vehicle& vehicle) {
    double minCost = numeric_limits<double>::max(), candidateCost;
    pair<double, list<Customer>::iterator> result(0, customers.end());
    for (auto it = customers.begin(); it != customers.end(); ++it) {
        Customer& customer = *it;
        if (!customer.visited && vehicle.fits(customer.demand)) {
            candidateCost = current.distance(customer);
            if (candidateCost < minCost) {
                minCost = candidateCost;
                result = make_pair(minCost, it);
            }
        }
    }
    return result;
}

Greedy& Greedy::solve(list<Customer>& customers, vector<Vehicle>& vehicles) {
    for (int i = 0; i < V; ++i) {
        Vehicle& vehicle = vehicles[i];
        if (vehicle.empty())
            vehicle.add(customers.front(), vehicle.begin());
    }

    // For debugging
    customers.front().visited = true;
    cout << "After setting warehouse as visited:" << endl;
    cout << "customers.front().visited: " << customers.front().visited << endl;

    cout << "After adding the first node to all vehicles:" << endl;
    for (int i = 0; i < V; ++i) {
        Vehicle& vehicle = vehicles[i];
        cout << "Vehicle size: " << vehicle.route.size() << endl;
    }
    // Remove after

    int vehicleIndex = 0;
    Customer& current = customers.front();  // currentLocation is warehouse
    while (numUnvisited > 0) {
        Vehicle& vehicle = vehicles[vehicleIndex];

        auto cost_customer = bestNeighbor(customers, current, vehicle);
        double minCost = cost_customer.first;
        auto candidate = cost_customer.second;

        if (candidate == customers.end()) {
            // No customer fits
            if (vehicleIndex + 1 < V) { // there are still vehicles
                if (!current.isWarehouse()) {
                    vehicle.add(customers.front(), vehicle.end());
                    cost += current.distance(0);
                }
                ++vehicleIndex;
            }
            else {
                // We DO NOT have any more vehicle to assign. The problem is unsolved under these parameters
                cout << "The rest customers do not fit in any Vehicle, the problem cannot be resolved under these constrains" << endl;
                exit(EXIT_FAILURE);
            }
        }
        else {
            vehicle.add(*candidate, vehicle.end())
        }

    }
}
