#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP
#include <iostream>
#include <vector>

using namespace std;

class Customer {
public:
    int id, demand, visited;
    Customer(int id, int demand, double x, double y);
    double distance(Customer& to);
    double distance(int i);
    void addNeighbor(Customer& neighbor);
    bool operator==(const Customer& customer);
    bool isWarehouse() const;
private:
    vector<double> distances;
    double x, y;
};
#endif