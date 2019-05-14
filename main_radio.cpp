#include <bits/stdc++.h>
#include "src/source.hpp"
#include "src/selection/roulette.cpp"
#include "src/crossover/bin.cpp"
#include "src/mutation/bin.cpp"

using namespace std;

int main() {
    ga::rand::reset();

    int st, lx;
    auto fitness = [](ga::Population<auto>& pop, ga::Agent<auto>& agent) {
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

        int st_map = (24.0/(32.0 - 1.0)) * st_dec;
        int lx_map = (16.0/(32.0 - 1.0)) * lx_dec;

        double pen = max(0.0, ((st_map + 2*lx_map) - 40)/16.0);

        //cout << st_bin << "=" << setw(2) << st_map << setw(0) << " | " << lx_bin << "=" << setw(2) << lx_map << setw(0) << " | pen=" << pen << endl;
        //long int dec = bin.to_ulong();
        //cout << "bin ";
        return (30.0 * st_map + 40.0 * lx_map)/1360.0 - pen;
    };

    ga::chromo_config<int> chromo(                 // Estrutura que define o agente
        ga::BIN,                                   // Tipo de codificação: BIN, INT-PERM, REAL, INT
        {-1, -1},                                  // Limites do gene
        [&]()->vector<int>{                        // Função para gerar os individuos iniciais
            return ga::rand::vec_int(10, 0, 1); // Parametro = quantidade de genes
        }
    );

    ga::Population<int> pop(              // Classe população
        20,                               // Quantidade de individuos
        chromo,                           // Configuração do cromossomo
        fitness,                          // Função fitness associada
        ga::selection::roulette<int>,     // Método de seleção
        ga::crossover::bin::section<int>, // Método crossover
        ga::mutation::bin::bitflip<int>   // Método mutação
    );

    pop.start_worker(
        250000,    // Quantidade máxima de gerações
        0.90,      // Percentual de crossover
        0.05       // Percentual de Mutação
    );

    return 0;
}
