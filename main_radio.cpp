#include <bits/stdc++.h>
#include "source.hpp"

using namespace std;

int main() {
    ga::rand::reset();

    int st, lx;
    auto fitness = [&](ga::Agent<auto>& agent) {
        std::bitset<5> st_bin;
        std::bitset<5> lx_bin;
        
        for(int i = agent.chromo_buff.size()-1, j = 0; j < 5; i--, j++) {
            lx_bin[j] = agent.chromo_buff[i];
        }

        for(int i = agent.chromo_buff.size()-6, j = 0; j < 5; i--, j++) {
            st_bin[j] = agent.chromo_buff[i];
        }

        long int st_dec = st_bin.to_ulong();
        long int lx_dec = lx_bin.to_ulong();

        int st_map = (24.0/(32 - 1)) * st_dec;
        int lx_map = (16.0/(32 - 1)) * lx_dec;

        double pen = max(0.0, ((st_map + 2*lx_map) - 40)/16.0);
        
        cout << st_bin << "=" << setw(2) << st_map << setw(0) << " | " << lx_bin << "=" << setw(2) << lx_map << setw(0) << " | pen=" << pen;    
        //long int dec = bin.to_ulong();
        //cout << "bin ";
        return 0;
    };

    cout << "População BIN" << endl;
    ga::Population<int> pop1(10, ga::chromo_config<int>(ga::BIN, 
    []()->vector<int>{
        return ga::rand::vec_int(10, 0, 1);
    }), 
    fitness);

    pop1.run_fitness();
    cout << endl << endl;

    return 0;
}