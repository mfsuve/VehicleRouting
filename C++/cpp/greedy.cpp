#include <iostream>
#include <vector>
#include <limits>
#include "../hpp/greedy.hpp"
#include "../hpp/customer.hpp"
#include "../hpp/vehicle.hpp"

using namespace std;

Greedy::Greedy(int N, int V, vector<Customer>& customers, Vehicle vehicles[])
    : cost(0), N(N), V(V), numUnvisited(N), customers(&customers), vehicles(vehicles) {}

double Greedy::bestNeighbor(const Customer** candidate, const Customer& current, const Vehicle& vehicle) {
    double minCost = numeric_limits<double>::max(), candidateCost;
    for (const Customer& customer : *customers) {
        if (!customer.visited) {
            if (vehicle.fits(customer.demand)) {
                candidateCost = current.distance(customer);
                if (candidateCost < minCost) {
                    minCost = candidateCost;
                    *candidate = &customer;
                }
            }
        }
    }
}

Greedy& Greedy::solve() {
    for (int i = 0; i < V; ++i) {
        Vehicle& vehicle = vehicles[i];
        if (vehicle.empty())
            vehicle.add((*customers)[0], vehicle.begin());
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

    int vehicleIndex = 0, candidate;
    while (numUnvisited > 0) {
        Customer** candidate = nullptr;             // best candidate
        const Customer& current = (*customers)[0];  // currentLocation
        Vehicle& vehicle = vehicles[vehicleIndex];

        bestNeighbor(candidate, current, vehicle);

        if (!candidate) {
            // No customer fits
            if (vehicleIndex + 1 < V) { // there are still vehicles
                if (!current.isWarehouse()) {
                    vehicle.add((*customers)[0]);
                }
            }
        }

    }
}
