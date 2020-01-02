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

    size_t pos = 0;
    std::string token;
    string s(filename);
    while ((pos = s.find("\\")) != std::string::npos) {
        token = s.substr(0, pos);
        s.erase(0, pos + 1);
    }
    if (verbose) cout << "s: " << s << endl;
    outputFilename = s;

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
        Customer* newCustomer = new Customer(id, demand, x, y);
        customers.push_back(newCustomer);
        for (Customer* customer : customers)
            newCustomer->addNeighbor(customer);
    }
    file.close();
}

TabuSearch::~TabuSearch() {
    for (Customer* customer : customers)
        delete customer;
}

double TabuSearch::calculateNeighborCost(list<Customer*>::const_iterator fromNodeIndex, list<Customer*>::const_iterator toNodeIndex) {
    Customer* prevFrom = *prev(fromNodeIndex);
    Customer* nextFrom = *next(fromNodeIndex);
    Customer* to = *toNodeIndex;
    Customer* from = *fromNodeIndex;
    Customer* nextTo = *next(toNodeIndex);

    return prevFrom->distance(nextFrom)
         + to->distance(from)
         + from->distance(nextTo)
         - prevFrom->distance(from)
         - from->distance(nextFrom)
         - to->distance(nextTo);
}

double TabuSearch::updateToBestNeighbor(vector<Vehicle>& vehicles, TabuList& tabulist, double bestCost) {
    bool found = false;
    double bestNeighborCost = numeric_limits<double>::max(), neighborCost;
    int bestFromIndex, bestToIndex;
    list<Customer*>::const_iterator bestFromNodeIndex, bestToNodeIndex;
    // Iterate all vehicles (remove customer from)
    for (int fromIndex = 0; fromIndex < V; ++fromIndex) {
        Vehicle& from = vehicles[fromIndex];
        // Iterate all vehicles (add customer between index and index+1)
        for (int toIndex = 0; toIndex < V; ++toIndex) {
            Vehicle& to = vehicles[toIndex];
            // Iterate all customers on 'from' vehicle (Not removing the '0' node)
            for (auto fromNodeIndex = next(from.begin()), fromEnd = prev(from.end()); fromNodeIndex != fromEnd; ++fromNodeIndex) {
                // Iterate all customers on 'to' vehicle (Not adding after last '0' node)
                for (auto toNodeIndex = to.begin(), toEnd = prev(to.end()); toNodeIndex != toEnd; ++toNodeIndex) {
                    if (fromIndex == toIndex || to.fits(fromNodeIndex)) {
                        if (!(fromIndex == toIndex && (toNodeIndex == fromNodeIndex || toNodeIndex == prev(fromNodeIndex)))) {
                            // Calculate the change in cost                            
                            neighborCost = calculateNeighborCost(fromNodeIndex, toNodeIndex);
                            // If not tabu
                            if ((!tabulist.isTabu(prev(fromNodeIndex), next(fromNodeIndex)) &&  // If adding this edge is not tabu and
                                 !tabulist.isTabu(toNodeIndex, fromNodeIndex) &&                // If adding this edge is not tabu and
                                 !tabulist.isTabu(fromNodeIndex, next(toNodeIndex))) ||         // If adding this edge is not tabu
                                 cost + neighborCost < bestCost) {                                 // OR we found a solution even better than the best one


                                // if ((tabulist.isTabu(prev(fromNodeIndex), next(fromNodeIndex)) ||
                                //      tabulist.isTabu(toNodeIndex, fromNodeIndex) ||
                                //      tabulist.isTabu(fromNodeIndex, next(toNodeIndex))))
                                //     cout << "Tabu but found even better solution" << endl;


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
    }
    // lower the tabu tenures
    tabulist.step();
    // If not found, don't change anything
    if (!found)
        return cost;
    // Update tabulist (I make tabu to go back previous state)
    tabulist.makeTabu(prev(bestFromNodeIndex), bestFromNodeIndex);
    tabulist.makeTabu(bestFromNodeIndex, next(bestFromNodeIndex));
    tabulist.makeTabu(bestToNodeIndex, next(bestToNodeIndex));
    // Switch the node from 'from' to 'to'
    Customer* node = vehicles[bestFromIndex].remove(bestFromNodeIndex);
    vehicles[bestToIndex].add(node, next(bestToNodeIndex));
    // Return the cost
    return cost + bestNeighborCost;
}

double TabuSearch::solve(int maxIteration, int tenure, bool save) {
    TabuList tabulist(N, tenure);

    vector<Vehicle> vehicles;
    for (int i = 0; i < V; ++i) {
        bestVehicles.emplace_back(c);
        vehicles.emplace_back(c);
    }

    ofstream output;
    if (save) {
        string outputFilepath = "../../solution/" + outputFilename + "/output.txt";
        output.open(outputFilepath);
        output << "loop=" << -1 << " iteration=" << -1 << " bestCost=" << -1 << endl;
        for (int ii = 0; ii < V; ++ii) {
            Vehicle& vehicle = vehicles[ii];
            for (Customer* customer : vehicle.route) {
                output << customer->id << " ";
            }
            output << endl;
        }
        output << "-" << endl;
    }

    Greedy greedy(N, V, verbose);
    cost = greedy.solve(customers, vehicles, output, save).cost;
    double bestCost = cost;

    cout << "Greedy done with the cost " << bestCost << endl;

    int iteration = 0, loop = 0;
    while (iteration < maxIteration) {
        if (loop % 100000 == 0) {
            ostringstream ss;
            ss << "Loop: " << loop;
            cout << setw(20) << left << ss.str() << " Best Cost: " << bestCost << endl;
        }
        cost = updateToBestNeighbor(vehicles, tabulist, bestCost);
        if (cost < bestCost) {
            bestCost = cost;
            bestVehicles = vehicles;
            iteration = 0;
            cout << "Changed!" << endl;
        }
        else
            ++iteration;

        iteration = 0;
        if (bestCost <= 540)
            break;

        ++loop;

        if (save) {
            output << "loop=" << loop << " iteration=" << iteration << " bestCost=" << cost << endl;
            for (int ii = 0; ii < V; ++ii) {
                Vehicle& vehicle = vehicles[ii];
                for (Customer* customer : vehicle.route) {
                    output << customer->id << " ";
                }
                output << endl;
            }
            output << "-" << endl;
        }
    }
    return bestCost;
}