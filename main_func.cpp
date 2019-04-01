#include <bits/stdc++.h>
#include "source.hpp"

using namespace std;

int main() {
    ga::rand::reset();

    auto fitness = [](ga::Agent<auto>& agent) {
        std::bitset<16> bin;
        int i, j;
        for(i = agent.chromo_buff.size()-1, j = 0; i >= 0; i--, j++) {
            bin[j] = agent.chromo_buff[i];
        }

        long int dec = bin.to_ulong();
        --j;


        if(dec > 40001)
            cout << bin << " -> ";
        do {
            bin[j] = 0;
            dec = bin.to_ulong();
            --j;
        } while(dec > 40001);

        cout << bin << " ";

        double x = (dec/10000.0 - 2);
        double res = ((cos(20*x) - abs(x)/2 + (pow(x, 3))/4.0) + 4)/6.0;

        return res;
    };

    cout << "População BIN" << endl;
    ga::Population<int> pop1(10, ga::chromo_config<int>(ga::BIN,
    []()->vector<int>{
        return ga::rand::vec_int(16, 0, 1);
    }),
    fitness);

    pop1.run_fitness();
    cout << endl << endl;

    return 0;
}
