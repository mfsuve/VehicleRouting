#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP
#include <iostream>
#include <vector>

using namespace std;

class Customer {
public:
    int id, demand, x, y;
    Customer(int id, int demand, int x, int y);
    Customer(const Customer& customer);
    int distance(Customer& to);
    int distance(int i);
    void addNeighbor(Customer& neighbor);
    vector<double> distances;
private:
};
#endif