#include <iostream>
#include <cmath>
#include "../hpp/customer.hpp"

using namespace std;

Customer::Customer(int id, int demand, double x, double y) : id(id), demand(demand), x(x), y(y) {}

double Customer::distance(Customer& to) {
    return distances[to.id];
}

double Customer::distance(int i) {
    return distances[i];
}

void Customer::addNeighbor(Customer& neighbor) {
    double distance = hypot(x - neighbor.x, y - neighbor.y);
    distances.push_back(distance);
    neighbor.distances.push_back(distance);

    if (neighbor.id == id - 1)
        distances.push_back(0);
    // for (double dist : distances)
    //     cout << "id: " << id << " distance: " << dist << endl;
    // cout << "----------------------------------" << endl;
}
