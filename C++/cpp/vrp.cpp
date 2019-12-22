#include <iostream>
#include <cstdlib>
#include "../hpp/tabusearch.hpp"
#include "../hpp/vehicle.hpp"
#include "../hpp/customer.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " filename";
        return 0;
    }
    srand(0);
    TabuSearch solver(argv[1], false);
    double bestCost = solver.solve(800, 100, true);
    
    cout << bestCost << endl;
    int i = 0;
    for (Vehicle& vehicle : solver.bestVehicles) {
        for (Customer* customer : vehicle.route) {
            cout << customer->id << " ";
        }
        cout << endl;
    }
}
