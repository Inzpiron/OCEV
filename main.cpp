#include <bits/stdc++.h>
#include "source.hpp"

using namespace std;

int main() {
    ga::rand::reset();


    auto fitness = [](ga::Agent<auto>& agent) {
        map<pair<int, int>, bool> mapa;
        int sum = 0;
        int total = 0;
        for(int i = 0; i < agent.chromo_buff.size(); i++) {
            int y = i;
            int x = agent.chromo_buff[i];

            for(int j = i+1; j < agent.chromo_buff.size(); j++) {
                ++total;
                int _y = j;
                int _x = agent.chromo_buff[j];

                if(_y == y || x == _x || abs(x - _x) == abs(y - _y)){
                    sum++;
                }
            }
        }

        return 1.0 - ((double) sum/ (double)total);
    };

    cout << "População INT_PERM" << endl;
    ga::Population<int> pop1(10, ga::chromo_config<int>(ga::INT_PERM, []()->vector<int>{
        return ga::rand::vec_intperm(10000);
    }), fitness);

    pop1.run_fitness();
    cout << endl << endl;

    /*
    cout << "População INT-PERM" << endl;
    ga::Population<int> pop1(10, ga::chromo_config<int>(ga::INT_PERM, 10, 0, 0));
    cout << endl << endl;

    cout << "População REAL" << endl;
    ga::Population<double> pop2(10, ga::chromo_config<double>(ga::REAL, 10, -5, 10));
    cout << endl << endl;
    */

    return 0;
}