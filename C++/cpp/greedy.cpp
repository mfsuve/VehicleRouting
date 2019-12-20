#include <iostream>
#include <vector>
#include <list>
#include <limits>
#include "../hpp/greedy.hpp"
#include "../hpp/customer.hpp"
#include "../hpp/vehicle.hpp"

#include <iomanip>

using namespace std;

Greedy::Greedy(int N, int V) : cost(0), N(N), V(V), numUnvisited(N - 1) {}

pair<double, list<Customer>::iterator> Greedy::bestNeighbor(list<Customer>& customers, Customer& current, Vehicle& vehicle) {
    double minCost = numeric_limits<double>::max(), candidateCost;
    pair<double, list<Customer>::iterator> result(minCost, customers.end());
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
    for (Vehicle& vehicle : vehicles)
        if (vehicle.empty())
            vehicle.add(customers.front());
    customers.front().visited = true;

    int vehicleIndex = 0;
    list<Customer>::iterator current = customers.begin();  // currentLocation is warehouse
    while (numUnvisited > 0) {
        Vehicle& vehicle = vehicles[vehicleIndex];

        auto cost_customer = bestNeighbor(customers, *current, vehicle);
        double minCost = cost_customer.first;
        auto candidate = cost_customer.second;

        if (candidate == customers.end()) {
            cout << "No customer fits to Vehicle " << vehicleIndex << ", ";
            // No customer fits
            if (vehicleIndex + 1 < V) { // there are still vehicles
                if (!current->isWarehouse()) {
                    vehicle.add(customers.front());
                    cost += current->distance(0);
                    cout << "Vehicle " << vehicleIndex << " returns to warehouse and ";
                }
                ++vehicleIndex;
                current = customers.begin();
                cout << "going to the next vehicle" << endl;
            }
            else {
                // We DO NOT have any more vehicle to assign. The problem is unsolved under these parameters
                cout << "The rest customers do not fit in any Vehicle, the problem cannot be resolved under these constrains!" << endl;
                exit(EXIT_FAILURE);
            }
        }
        else {
            cout << "Vehicle " << vehicleIndex << " goes to Customer " << candidate->id << " at (" << candidate->x << ", " << candidate->y << ") with cost of " << minCost << endl;
            vehicle.add(candidate);
            current = candidate;
            candidate->visited = true;
            cost += minCost;
            --numUnvisited;
            cout << "       Load of Vehicle " << vehicleIndex << ": " << vehicle.getLoad() << endl;
            cout << "       " << numUnvisited << " customers remaining..." << endl;
        }

        // cout << "               customers.size(): " << customers.size() << endl;
        // for (Customer& customer : customers) {
        //     if (customer.visited)
        //         cout << "               Customer " << customer.id << " is visited" << endl;
        //     else
        //         cout << "               Customer " << customer.id << " is not visited" << endl;
        // }

    }
    cout << "Vehicle " << vehicleIndex << " returns to warehouse with cost " << current->distance(0) << endl;
    cost += current->distance(0);
    vehicles[vehicleIndex].add(customers.front());
    return *this;
}
