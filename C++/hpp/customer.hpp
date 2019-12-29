#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP
#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Customer {
public:
    int id, demand;
    bool visited;
    vector<double> distances;   // TODO make this private
    Customer(int id, int demand, double x, double y);
    Customer(const Customer& other);
    double distance(list<Customer*>::const_iterator i) const;
    double distance(const Customer* to) const;
    double distance(int i) const;
    void addNeighbor(Customer* neighbor);
    bool operator==(const Customer& customer);
    bool isWarehouse() const;
    int getX() const;
    int getY() const;
private:
    double x, y;
};
#endif