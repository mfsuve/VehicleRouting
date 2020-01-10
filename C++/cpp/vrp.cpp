#include <iostream>
#include <cstdlib>
#include <fstream>
// #include "../mingw_hpp/mingw.thread.h"
#include "../hpp/random.hpp"
#include "../hpp/tabusearch.hpp"
#include "../hpp/vehicle.hpp"
#include "../hpp/customer.hpp"

#include <bits/stdc++.h>

using namespace std;

// thread function
// void runVRP(int TID, char* filename, int maxIteration, int tenure, double initMutationRate, double deltaMutationRate, int seed) {
//     Random rng(seed);
//     TabuSearch solver(filename, &rng, false);
//     cout << "Created Thread " << TID << endl;
//     double bestCost = solver.solve(TID, maxIteration, tenure, initMutationRate, deltaMutationRate, true);

//     cout << TID << ": " << bestCost << endl;
//     int i = 0;
//     for (Vehicle& vehicle : solver.bestVehicles) {
//         for (Customer* customer : vehicle.route) {
//             cout << customer->id << " ";
//         }
//         cout << endl;
//     }
// }

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " filename";
        return 0;
    }

    // thread T1(runVRP, 1, argv[1], 100000000, 40, 3000000, 0.985, 10);
    // thread T2(runVRP, 2, argv[1], 100000000, 40, 3000000, 0.985, 43);
    // thread T3(runVRP, 3, argv[1], 100000000, 30, 3000000, 0.985, 123);  // 542.763 - 266M iteration
    // thread T4(runVRP, 4, argv[1], 100000000, 30, 3000000, 0.98, 1234);
    // thread T5(runVRP, 5, argv[1], 100000000, 30, 3000000, 0.985, 223);  // 542.763 - 10M iteration
    // thread T6(runVRP, 6, argv[1], 100000000, 30, 3000000, 0.98, 34);    // 542.763 - 381M iteration

    // thread T1(runVRP, 1, argv[1], 100000000, 20, 3000000, 0.98, 10);
    // thread T2(runVRP, 2, argv[1], 100000000, 20, 3000000, 0.98, 43);
    // thread T3(runVRP, 3, argv[1], 100000000, 20, 3000000, 0.99, 123);
    // thread T4(runVRP, 4, argv[1], 100000000, 30, 3000000, 0.99, 76);
    // thread T5(runVRP, 5, argv[1], 100000000, 30, 2000000, 0.98, 223);
    // thread T6(runVRP, 6, argv[1], 100000000, 30, 2000000, 0.99, 34);

    // T1.join();
    // T2.join();
    // T3.join();
    // T4.join();
    // T5.join();
    // T6.join();

    Random rng(223);
    TabuSearch solver(argv[1], &rng, false);
    double bestCost = solver.solve(0, 5000000, 50, 3000000, 0.985, false);
    // double bestCost = solver.solve(5000000, 50, 3000000, 0.99, true);
    // double bestCost = solver.solve(5000000, 50, 1000000, 0.98, true); // 543.197


    
    cout << bestCost << endl;
    int i = 0;
    for (Vehicle& vehicle : solver.bestVehicles) {
        for (Customer* customer : vehicle.route) {
            cout << customer->id << " ";
        }
        cout << endl;
    }
}
