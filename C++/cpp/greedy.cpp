#include <iostream>
#include <vector>
#include <list>
#include <limits>
#include <fstream>
#include "../hpp/greedy.hpp"
#include "../hpp/customer.hpp"
#include "../hpp/vehicle.hpp"

#include <iomanip>

using namespace std;

Greedy::Greedy(int N, int V) : cost(0), N(N), V(V), numUnvisited(N - 1) {}

pair<double, list<Customer*>::iterator> Greedy::bestNeighbor(list<Customer*>& customers, const Customer* current, Vehicle& vehicle) {
    double minCost = numeric_limits<double>::max(), candidateCost;
    pair<double, list<Customer*>::iterator> result(minCost, customers.end());
    for (auto it = customers.begin(); it != customers.end(); ++it) {
        Customer* customer = *it;
        if (!customer->visited && vehicle.fits(customer)) {
            candidateCost = current->distance(customer);
            if (candidateCost < minCost) {
                minCost = candidateCost;
                result = make_pair(minCost, it);
            }
        }
    }
    return result;
}

bool Greedy::solve_recursive(list<Customer*>::iterator customer, vector<Vehicle>& vehicles, list<Customer*>::iterator end, list<Customer*>::iterator begin) {
    if (customer == end) {
        return true;
    }
    bool success = false;
    for (int v = 0; v < vehicles.size(); ++v) {
        if (vehicles[v].fits(customer)) {
            vehicles[v].add(customer);
            success = solve_recursive(next(customer), vehicles, end, begin);
            if (success)
                break;
            vehicles[v].removeLast();
        }
    }
    return success;
}

void Greedy::solve_guarantee(list<Customer*>& customers, vector<Vehicle>& vehicles) {
    for (Vehicle& v : vehicles) {
        v.clear(); // clearing the routes
        v.add(customers.front());
    }
    bool success = solve_recursive(next(customers.begin()), vehicles, customers.end(), customers.begin());
    cost = 0;
    for (Vehicle& v : vehicles) {
        v.add(customers.front());
        auto end = prev(v.end());
        for (auto it = v.begin(); it != end; ++it) {
            Customer* c = *it;
            cost += c->distance(next(it));
        }
    }
}

Greedy& Greedy::solve(list<Customer*>& customers, vector<Vehicle>& vehicles) {
    int i = 0;
    for (Vehicle& vehicle : vehicles)
        if (vehicle.empty())
            vehicle.add(customers.front());
    customers.front()->visited = true;

    int vehicleIndex = 0;
    list<Customer*>::iterator current = customers.begin();  // currentLocation is warehouse
    while (numUnvisited > 0) {
        Vehicle& vehicle = vehicles[vehicleIndex];

        auto cost_customer = bestNeighbor(customers, *current, vehicle);
        double minCost = cost_customer.first;
        auto candidate = cost_customer.second;

        if (candidate == customers.end()) {
            // No customer fits
            if (vehicleIndex + 1 < V) { // there are still vehicles
                if (!(*current)->isWarehouse()) {
                    vehicle.add(customers.front());
                    cost += (*current)->distance(0);
                }
                ++vehicleIndex;
                current = customers.begin();
            }
            else {
                // We DO NOT have any more vehicle to assign
                solve_guarantee(customers, vehicles);
                return *this;
            }
        }
        else {
            vehicle.add(candidate);
            current = candidate;
            (*candidate)->visited = true;
            cost += minCost;
            --numUnvisited;
        }
    }
    cost += (*current)->distance(0);
    vehicles[vehicleIndex].add(customers.front());

    // Returning remaining vehicles to warehouse for tabusearch
    for (int i = vehicleIndex + 1; i < V; ++i)
        vehicles[i].add(customers.front());

    return *this;
}
