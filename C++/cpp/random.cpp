#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <list>
#include "../hpp/random.hpp"

Random::Random(int seed) : eng(seed) {}

int Random::randint(int end) {
    if (end == 0) return 0;
    if (end < 0)
        return randint(end, 0);
    else
        return randint(0, end);
}

int Random::randint(int start, int end) {
    return uniform_int_distribution<int>{start, end}(eng);
}

double Random::rand(double end) {
    if (end == 0) return 0;
    if (end < 0) {
        double r = rand(end, 0);
        // cout << "random returned " << r << endl;
        return r;
    }
    else {
        double r = rand(0, end);
        // cout << "random returned " << r << endl;
        return r;
    }
}

double Random::rand(double start, double end) {
    return uniform_real_distribution<double>{start, end}(eng);
}

// template<typename T>
// list<T> Random::shuffle(list<T>& l) {
//     list<T> s(l);
//     std::shuffle(s.begin(), s.end(), eng);
//     return s;
// }
