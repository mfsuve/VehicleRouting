#ifndef RANDOM_HPP
#define RANDOM_HPP
#include <iostream>
#include <vector>
#include <random>
#include <iterator>

using namespace std;

class Random {
public:
    int seed;
    Random(int seed=123);
    int randint(int end);
    int randint(int start, int end);
    double rand(double end=1.0);
    double rand(double start, double end);
    template<typename T>
    typename T::iterator sample(T& v, int s, int e) {
        if (s < 0) s += v.size();
        if (e < 0) e += v.size();
        int index = s + randint(e - s - 1);
        auto begin = v.begin();
        std::advance(begin, index);
        return begin;
    }
    template<typename T>
    typename T::iterator sample(T& v, int s) {
        return sample(v, s, v.size());
    }
    template<typename T>
    typename T::iterator sample(T& v) {
        return sample(v, 0);
    }
private:
    std::mt19937 eng;
};
#endif