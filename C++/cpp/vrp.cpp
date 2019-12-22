#include <iostream>
#include <cstdlib>
#include "../hpp/tabusearch.hpp"
#include "../hpp/vehicle.hpp"
#include "../hpp/customer.hpp"

#include <bits/stdc++.h>
#include <exception>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " filename";
        return 0;
    }
    srand(0);
    TabuSearch solver(argv[1], false);
    // cerr << "Created tabu search" << endl;
    double bestCost = solver.solve(1000, 30, false);
    // cerr << "solved" << endl;
    
    cout << bestCost << endl;
    int i = 0;
    for (Vehicle& vehicle : solver.bestVehicles) {
        for (Customer* customer : vehicle.route) {
            cout << customer->id << " ";
        }
        cout << endl;
    }
}
