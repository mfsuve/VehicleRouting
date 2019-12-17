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
    Vehicle::capacity = c;
    vector<int> xs, ys;
    int demand, x, y;
    for (int i = 0; i < N; ++i) {
        file >> demand >> x >> y;
        demands.push_back(demand);
        xs.push_back(x);
        ys.push_back(y);
    }
    file.close();
    for (int i = 1; i < N; ++i)
        for (int j = 0; j < i; ++j)
            distances.push_back(hypot(xs[i] - xs[j], ys[i] - ys[j]));
}

double TabuSearch::distance(const int& i, const int& j) {
    if (i == j) return 0;
    int idx;
    if (i > j)
        idx = (i * (i - 1)) / 2 + j;
    else
        idx = (j * (j - 1)) / 2 + i;
    return distances[idx];
}

int TabuSearch::updateToBestNeighbor(Vehicle vehicles[], TabuList& tabulist) {
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
    return cost + bestNeighborCost;
}

void TabuSearch::solve(int maxIteration, int tenure) {
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

}