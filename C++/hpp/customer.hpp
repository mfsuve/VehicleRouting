#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP
#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Customer {
public:
    int id, demand, visited;
    Customer(int id, int demand, double x, double y);
    double distance(list<Customer>::iterator i) const;
    double distance(const Customer& to) const;
    double distance(int i) const;
    void addNeighbor(Customer& neighbor);
    bool operator==(const Customer& customer);
    bool isWarehouse() const;
    vector<double> distances;   // TODO make this private
    int getX();
    int getY();
private:
    double x, y;
};
#endif