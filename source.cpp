#include <bits/stdc++.h>
#include "source.hpp"
using namespace std;

namespace ga {
    namespace rand {
        void reset() {
            gen = std::mt19937(rd());
        }

        int integer(int i, int j){
            i_dist = std::uniform_int_distribution<>(i, j);
            return i_dist(gen);
        }

        double real(double i, double j){
            r_dist = std::uniform_real_distribution<>(i, j);
            return r_dist(gen);
        }

        bool boolean() {
            return integer(0, 1);
        }
    }
}




