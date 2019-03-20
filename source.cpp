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

        int * vec_int(int size, int in, int fi) {
            int * ret = new int[size];
            for(int i = 0; i < size; i++)
                ret[i] = integer(in, fi);
            
            return ret;
        }

        double * vec_real(int size, double in, double fi) {
            double * ret = new double[size];
            for(int i = 0; i < size; i++)
                ret[i] = real(in, fi);

            return ret;
        }

        int * vec_intperm(int size) {
            vector<int> tmp(size); 
            int * ret = new int[size];
            for(int i = 0; i < tmp.size(); i++) 
                tmp[i] = i;
            int max = size -1;

            for(int i = 0; i < size; i++) {
                int offset = rand::integer(0, max);
                ret[i] = tmp[offset];
                tmp.erase(tmp.begin() + offset);
                --max;
            }

            return ret;
        }
    }
}




