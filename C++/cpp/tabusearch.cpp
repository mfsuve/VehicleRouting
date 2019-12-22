#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <limits>
#include <fstream>
#include <sstream>
#include <string>
#include "../hpp/tabusearch.hpp"
#include "../hpp/vehicle.hpp"
#include "../hpp/customer.hpp"
#include "../hpp/greedy.hpp"

#include <iomanip>
#include <cassert>

TabuSearch::TabuSearch(const char* filename, bool verbose) : verbose(verbose) {
    ifstream file(filename);
    string line;
    getline(file, line);
    istringstream in(line);
    in >> N >> V >> c;
    if (verbose) cout << N << " customers, " << V << " vehicles with capacity " << c << endl;
    double x, y, demand;
    int id = 0;
    for(; getline(file, line); ++id) {
        if (line.empty() || line.find_first_not_of(' ') == string::npos) continue;
        in = istringstream(line);
        in >> demand >> x >> y;
        customers.emplace_back(id, demand, x, y);
        for (Customer& customer : customers) {
            customers.back().addNeighbor(customer);
        }
    }
    file.close();
}

double TabuSearch::calculateNeighborCost(list<Customer>::iterator fromNodeIndex, list<Customer>::iterator toNodeIndex) {
    return prev(fromNodeIndex)->distance(next(fromNodeIndex))
         + toNodeIndex->distance(fromNodeIndex)
         + fromNodeIndex->distance(next(toNodeIndex))
         - prev(fromNodeIndex)->distance(fromNodeIndex)
         - fromNodeIndex->distance(next(fromNodeIndex))
         - toNodeIndex->distance(next(toNodeIndex));
}

double TabuSearch::updateToBestNeighbor(vector<Vehicle>& vehicles, TabuList& tabulist) {
    if (verbose) {
        cout << "**** Started to update to the next best neighbor ****" << endl;
        for (int ii = 0; ii < V; ++ii) {
            Vehicle& vehicle = vehicles[ii];
            cout << "Vehicle " << ii << ": ";
            for (Customer* customer : vehicle.route) {
                cout << " " << customer->id;
            }
            cout << endl;
        }
    }
    bool found = false;
    double bestNeighborCost = numeric_limits<double>::max(), neighborCost;
    int bestFromIndex, bestToIndex;
    list<Customer>::iterator bestFromNodeIndex, bestToNodeIndex;
    // Iterate all vehicles (remove customer from)
    for (int fromIndex = 0; fromIndex < V; ++fromIndex) {
        Vehicle& from = vehicles[fromIndex];
        // Iterate all vehicles (add customer between index and index+1)
        for (int toIndex = 0; toIndex < V; ++toIndex) {
            cout << "   -> From  Vehicle " << fromIndex << endl;
            cout << "   -> To    Vehicle " << toIndex << endl;
            cout << "--------------------------------" << endl;
            Vehicle& to = vehicles[toIndex];
            // Iterate all customers on 'from' vehicle (Not removing the '0' node)
            for (auto fromNodeIndex = next(from.begin()), fromEnd = prev(from.end()); fromNodeIndex != fromEnd; ++fromNodeIndex) {
                // Iterate all customers on 'to' vehicle (Not adding after last '0' node)
                for (auto toNodeIndex = to.begin(), toEnd = prev(to.end()); toNodeIndex != toEnd; ++toNodeIndex) {
                    if (fromIndex == toIndex || to.fits(fromNodeIndex)) {
                        if (!(fromIndex == toIndex && (toNodeIndex == fromNodeIndex || toNodeIndex == prev(fromNodeIndex)))) {
                            // If not tabu
                            if (tabulist.isTabu(prev(fromNodeIndex), next(fromNodeIndex)) ||
                                tabulist.isTabu(toNodeIndex, fromNodeIndex) ||
                                tabulist.isTabu(fromNodeIndex, next(toNodeIndex))) {
                                    if (verbose) cout << "Moves are tabu. Continuing to next ones." << endl;                                    
                                continue;
                                }
                            // Calculate increase in cost
                            if (verbose) cout << "Checking cost when Customer " << (*fromNodeIndex)->id << " moves from Vehicle " << fromIndex << " to Customers between " << (*toNodeIndex)->id << " and " << (*next(toNodeIndex))->id << " of Vehicle " << toIndex << "." << endl;
                            neighborCost = calculateNeighborCost(fromNodeIndex, toNodeIndex);
                            if (verbose) cout << "neighborCost: " << neighborCost << endl;
                            // If better, save
                            if (neighborCost < bestNeighborCost) {
                                bestNeighborCost = neighborCost;
                                if (verbose) cout << "   Found a neighbor! Original Cost: " << cost << ". Best cost: " << cost + bestNeighborCost << "." << endl;
                                bestFromIndex = fromIndex;
                                bestToIndex = toIndex;
                                bestFromNodeIndex = fromNodeIndex;
                                bestToNodeIndex = toNodeIndex;
                                found = true;
                            }
                        }
                    }
                }
            }
        }
    }
    if (verbose) cout << "TabuList step" << endl;
    // lower the tabu tenures
    tabulist.step();
    // If not found, don't change anything
    if (!found) {
        if (verbose) cout << "Not found, returning old cost." << endl;
        return cost;
    }
    if (verbose) cout << "Making the moves tabu" << endl;
    // Update tabulist
    tabulist.makeTabu(prev(bestFromNodeIndex), bestFromNodeIndex);
    tabulist.makeTabu(bestFromNodeIndex, next(bestFromNodeIndex));
    tabulist.makeTabu(bestToNodeIndex, next(bestToNodeIndex));
    // Switch the node from 'from' to 'to'
    if (verbose) cout << "Removing from Vehicle " << bestFromIndex << " Customer " << (*bestFromNodeIndex)->id << " ";
    if (verbose) cout << "and moving it to Vehicle " << bestToIndex << " between " << (*bestToNodeIndex)->id << " and " << (*next(bestToNodeIndex))->id << endl;
    vehicles[bestToIndex].add(node, next(bestToNodeIndex));
    // Return the cost
    return cost + bestNeighborCost;
}

void TabuSearch::solve(int maxIteration, int tenure) {
    TabuList tabulist(N, tenure);

    vector<Vehicle> vehicles;
    for (int i = 0; i < V; ++i)
        vehicles.emplace_back(c);
    Greedy greedy(N, V);
    cost = greedy.solve(customers, vehicles).cost;
    double bestCost = cost;

    if (verbose) cout << "**** Greedy Done ****" << endl;

    if (verbose) {
    int i = -1;
    cout << "vehicles.size(): " << vehicles.size() << endl;
    for (Vehicle& vehicle : vehicles) {
        cout << ++i << ". vehicle route: ";
            for (Customer* customer : vehicle.route) {
                cout << " " << customer->id;
        }
        cout << endl;
    }

        cout << "**** Started TabuSearch | maxIteration: " << maxIteration << " ****" << endl;
    cout << "Best cost: " << bestCost << endl;
    }

    int iteration = 0;
    while (iteration < maxIteration) {
        if (verbose) cout << " -> iteration: " << iteration << endl;
        cost = updateToBestNeighbor(vehicles, tabulist);
        if (verbose) cout << "After updating to best neighbor, the cost is " << cost << "." << endl;
        if (cost < bestCost) {
            bestCost = cost;
            bestVehicles = vehicles;
            iteration = 0;
        }
        else
            ++iteration;
        if (verbose) {
            cout << "********* Best Vehicles so far *********" << endl;
            for (int ii = 0; ii < V; ++ii) {
                Vehicle& vehicle = vehicles[ii];
                cout << "          Vehicle " << ii << ": ";
                for (Customer* customer : vehicle.route) {
                    cout << " " << customer->id;
                }
                cout << endl;
            }
            output.close();
        }
    }
    return bestCost;
}