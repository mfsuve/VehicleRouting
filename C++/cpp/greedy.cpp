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

Greedy::Greedy(int N, int V, bool verbose) : cost(0), N(N), V(V), numUnvisited(N - 1), verbose(verbose) {}

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
    // if (verbose) cout << "Called for Customer " << (*customer)->id << endl;
    if (customer == end) {
        // if (verbose) cout << "Returned true for Customer " << (*customer)->id << endl;
        return true;
    }
    bool success = false;
    for (int v = 0; v < vehicles.size(); ++v) {
        if (vehicles[v].fits(customer)) {
            // if (verbose) cout << "Added Customer " << (*customer)->id << " to Vehicle " << v << endl;
            // if (verbose) cout << "    Load of Vehicle " << v << ": " << vehicles[v].load << "/" << vehicles[v].capacity << endl;
            // if (verbose) cout << "        Demand of Customer " << (*customer)->id << ": " << (*customer)->demand << endl;
            vehicles[v].add(customer);
            // if (verbose) cout << "    Load of Vehicle " << v << ": " << vehicles[v].load << "/" << vehicles[v].capacity << endl;
            success = solve_recursive(next(customer), vehicles, end, begin);
            if (success)
                break;
            // if (verbose) cout << "Adding Customer " << (*customer)->id << " to Vehicle " << v << " didn't work" << endl;
            // if (verbose) cout << "Removed Customer " << (*customer)->id << " from Vehicle " << v << endl;
            // if (verbose) cout << "    Load of Vehicle " << v << ": " << vehicles[v].load << "/" << vehicles[v].capacity << endl;
            // if (verbose) cout << "        Demand of Customer " << (*customer)->id << ": " << (*customer)->demand << endl;
            vehicles[v].removeLast();
            // if (verbose) cout << "    Load of Vehicle " << v << ": " << vehicles[v].load << "/" << vehicles[v].capacity << endl;
        }
        // else
            // if (verbose) cout << "Customer " << (*customer)->id << " didn't fit to Vehicle " << v << endl;
    }
    // if (verbose) cout << " ** End of loop for Customer " << (*customer)->id << " with " << (success ? "success" : "fail") << endl;
    return success;
}

void Greedy::solve_guarantee(list<Customer*>& customers, vector<Vehicle>& vehicles) {
    for (Vehicle& v : vehicles) {
        v.clear(); // clearing the routes
        v.add(customers.front());
    }
    if (verbose) cout << "Cleared all vehicle routes" << endl;
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
    if (verbose)
        if (success)
            cout << "Solved with guaratee function! Cost: " << cost << endl;
        else
            cout << "Couldn't solve even with the guarantee function!" << endl;
}

Greedy& Greedy::solve(list<Customer*>& customers, vector<Vehicle>& vehicles, ofstream& output, bool save) {
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
            // cerr << "No customer fits to Vehicle " << vehicleIndex << ", ";
            if (verbose) cout << "No customer fits to Vehicle " << vehicleIndex << ", ";
            // No customer fits
            if (vehicleIndex + 1 < V) { // there are still vehicles
                if (!(*current)->isWarehouse()) {
                    vehicle.add(customers.front());
                    cost += (*current)->distance(0);
                    if (verbose) cout << "Vehicle " << vehicleIndex << " returns to warehouse and ";
                    // cerr << "Vehicle " << vehicleIndex << " returns to warehouse and ";
                }
                ++vehicleIndex;
                current = customers.begin();
                if (verbose) cout << "going to the next vehicle" << endl;
                // cerr << "going to the next vehicle" << endl;
            }
            else {
                // We DO NOT have any more vehicle to assign. The problem is unsolved under these parameters
                if (verbose) cout << "The rest customers do not fit in any Vehicle, the problem cannot be resolved under these constrains!" << endl;
                if (verbose) cout << "Trying with guarantee function." << endl;
                // cerr << "The rest customers do not fit in any Vehicle, the problem cannot be resolved under these constrains!" << endl;
                solve_guarantee(customers, vehicles);
                if (verbose) {
                    int i = 0;
                    for (Vehicle& v : vehicles) {
                        cout << "Vehicle " << i << ": ";
                        for (Customer* c : v.route) {
                            cout << c->id << " ";
                        }
                        cout << endl;
                        ++i;
                    }
                }
                return *this;
            }
        }
        else {
            if (save) {
                output << "loop=" << -1 << " iteration=" << -1 << " bestCost=" << cost << endl;
                for (int ii = 0; ii < V; ++ii) {
                    Vehicle& vehicle = vehicles[ii];
                    for (Customer* customer : vehicle.route) {
                        output << customer->id << " ";
                    }
                    output << endl;
                }
                output << "-" << endl;
            }
            if (verbose) cout << "Vehicle " << vehicleIndex << " goes to Customer " << (*candidate)->id << " at (" << (*candidate)->getX() << ", " << (*candidate)->getY() << ") with cost of " << minCost << endl;
            vehicle.add(candidate);
            current = candidate;
            (*candidate)->visited = true;
            cost += minCost;
            --numUnvisited;
            if (verbose) {
                cout << "       Load of Vehicle " << vehicleIndex << ": " << vehicle.getLoad() << endl;
                cout << "       " << numUnvisited << " customers remaining..." << endl;
            }
        }
    }
    if (verbose) cout << "Vehicle " << vehicleIndex << " returns to warehouse with cost " << (*current)->distance(0) << endl;
    cost += (*current)->distance(0);
    vehicles[vehicleIndex].add(customers.front());

    // Returning remaining vehicles to warehouse for tabusearch
    for (int i = vehicleIndex + 1; i < V; ++i)
        vehicles[i].add(customers.front());

    return *this;
}
