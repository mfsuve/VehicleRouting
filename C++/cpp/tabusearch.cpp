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

// TODO: initialize cost with greedy solver
TabuSearch::TabuSearch(const char* filename) {
    ifstream file(filename);
    string line;
    getline(file, line);
    istringstream in(line);
    in >> N >> V >> c;
    cout << N << " customers, " << V << " vehicles with capacity " << c << endl;
    double x, y, demand;
    int id = 0;
    for(; getline(file, line); ++id) {
        in = istringstream(line);
        in >> demand >> x >> y;
        customers.emplace_back(id, demand, x, y);
        for (Customer& customer : customers) { // TODO read customers into list (not a vector)
            customers[id].addNeighbor(customer);
        }
    }
    file.close();
    Vehicle::capacity = c;
    Vehicle vehicles[N];
    Greedy greedy(N, V);
    cost = greedy.solve(customers, vehicles).cost;
}

int TabuSearch::calculateNeighborCost(list<Customer>::iterator fromNodeIndex, list<Customer>::iterator toNodeIndex) {
    return (*prev(fromNodeIndex)).distance(*next(fromNodeIndex))
         + (*toNodeIndex).distance(*fromNodeIndex)
         + (*fromNodeIndex).distance(*next(toNodeIndex))
         - (*prev(fromNodeIndex)).distance(*fromNodeIndex)
         - (*fromNodeIndex).distance(*next(fromNodeIndex))
         - (*toNodeIndex).distance(*next(toNodeIndex));
}

int TabuSearch::updateToBestNeighbor(Vehicle vehicles[], TabuList& tabulist) {
    bool found = false;
    int bestNeighborCost = numeric_limits<int>::max(), neighborCost;
    int bestFromIndex, bestToIndex;
    list<Customer>::iterator bestFromNodeIndex, bestToNodeIndex;
    // Iterate all vehicles (remove customer from)
    for (int fromIndex = 0; fromIndex < N; ++fromIndex) {
        Vehicle& from = vehicles[fromIndex];
        // Iterate all vehicles (add customer between index and index+1)
        for (int toIndex = 0; toIndex < N; ++toIndex) {
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
                                tabulist.isTabu(fromNodeIndex, next(toNodeIndex)))
                                continue;
                            // Calculate increase in cost
                            neighborCost = calculateNeighborCost(fromNodeIndex, toNodeIndex);
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
    tabulist.makeTabu(prev(bestFromNodeIndex), bestFromNodeIndex);
    tabulist.makeTabu(bestFromNodeIndex, next(bestFromNodeIndex));
    tabulist.makeTabu(bestToNodeIndex, next(bestToNodeIndex));
    // Switch the node from 'from' to 'to'
    Customer node = vehicles[bestFromIndex].remove(bestFromNodeIndex);
    vehicles[bestToIndex].add(node, next(bestToNodeIndex));
    // Return the cost
    return cost + bestNeighborCost;
}

void TabuSearch::solve(int maxIteration, int tenure) {
    TabuList tabulist(N, tenure);
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
}