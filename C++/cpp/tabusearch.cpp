#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <limits>
#include <fstream>
#include "../hpp/tabusearch.hpp"
#include "../hpp/vehicle.hpp"
#include "../hpp/customer.hpp"

// TODO: initialize cost with greedy solver
TabuSearch::TabuSearch(const char* filename) : cost(0) {
    ifstream file(filename);
    file >> N >> V >> c;
    cout << N << " customers, " << V << " vehicles with capacity " << c << endl;
    int demand, x, y;
    for (int id = 0; id < N; ++id) {
        file >> demand >> x >> y;
        Customer newCustomer(id, demand, x, y);
        for (Customer customer : customers)
            newCustomer.addNeighbor(customer);
        customers.push_back(newCustomer);
        
        // for (Customer customer : customers)
        //     cout << "id: " << customer.id << " distance size: " << customer.distances.size() << endl;
    }
    file.close();

    cout << "Sizes:" << endl;
    for (Customer customer : customers)
        cout << "id: " << customer.id << " distance size: " << customer.distances.size() << endl;

    cout << "Distances:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Customer from = customers[i], to = customers[j];
            cout << from.distance(to) << " ";
        }
        cout << endl;
    }
}

int TabuSearch::updateToBestNeighbor(Vehicle vehicles[], TabuList& tabulist) { /*
    bool found = false;
    int bestNeighborCost = numeric_limits<int>::max(), neighborCost;
    int bestFromIndex, bestToIndex;
    list<int>::iterator bestFromNodeIndex, bestToNodeIndex;
    // Iterate all vehicles (remove customer from)
    for (int fromIndex = 0; fromIndex < N; ++fromIndex) {
        Vehicle from = vehicles[fromIndex];
        // Iterate all vehicles (add customer between index and index+1)
        for (int toIndex = 0; toIndex < N; ++toIndex) {
            Vehicle to = vehicles[toIndex];
            // Iterate all customers on 'from' vehicle (Not removing the '0' node)
            for (auto fromNodeIndex = next(from.begin()), fromEnd = prev(from.end()); fromNodeIndex != fromEnd; ++fromNodeIndex) {
                // Iterate all customers on 'to' vehicle (Not adding after last '0' node)
                for (auto toNodeIndex = to.begin(), toEnd = prev(to.end()); toNodeIndex != toEnd; ++toNodeIndex) {
                    if (fromIndex == toIndex || to.fits(demands[*fromNodeIndex])) {
                        if (!(fromIndex == toIndex && (toNodeIndex == fromNodeIndex || toNodeIndex == prev(fromNodeIndex)))) {
                            // If not tabu
                            if (tabulist.isTabu(*prev(fromNodeIndex), *next(fromNodeIndex)) ||
                                tabulist.isTabu(*toNodeIndex, *fromNodeIndex) ||
                                tabulist.isTabu(*fromNodeIndex, *next(toNodeIndex)))
                                continue;
                            // Calculate increase in cost
                            neighborCost = distance(*prev(fromNodeIndex), *next(fromNodeIndex))
                                         + distance(*toNodeIndex, *fromNodeIndex)
                                         + distance(*fromNodeIndex, *next(toNodeIndex))
                                         - distance(*prev(fromNodeIndex), *fromNodeIndex)
                                         - distance(*fromNodeIndex, *next(fromNodeIndex))
                                         - distance(*toNodeIndex, *next(toNodeIndex));
                            // If better, save
                            if (neighborCost < bestNeighborCost) {
                                bestNeighborCost = neighborCost;
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
    // lower the tabu tenures
    tabulist.step();
    // If not found, don't change anything
    if (!found)
        return cost;
    // Update tabulist
    tabulist.makeTabu(*prev(bestFromNodeIndex), *bestFromNodeIndex);
    tabulist.makeTabu(*bestFromNodeIndex, *next(bestFromNodeIndex));
    tabulist.makeTabu(*bestToNodeIndex, *next(bestToNodeIndex));
    // Switch the node from 'from' to 'to'
    int node = vehicles[bestFromIndex].remove(bestFromNodeIndex);
    vehicles[bestToIndex].add(node, bestToNodeIndex);
    // Return the cost
    return cost + bestNeighborCost;*/
    return 0;
}

void TabuSearch::solve(int maxIteration, int tenure) {/*
    TabuList tabulist(N, tenure);
    Vehicle vehicles[N]; // TODO Initialize this with greedy solution
    int bestCost = numeric_limits<int>::max();

    int iteration = 0;
    while (iteration < maxIteration) {
        cost = updateToBestNeighbor(vehicles, tabulist);
        if (cost < bestCost) {
            iteration = 0;
            // TODO Save best solution
        }
        else
            iteration++;
    }
*/
}