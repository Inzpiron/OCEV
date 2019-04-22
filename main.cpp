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
        return 1.0 - ((double)sum/(double)total);
    };

    ga::chromo_config<int> chromo(              // Estrutura que define o agente
        ga::INT_PERM,                           // Tipo de codificação: BIN, INT-PERM, REAL, INT
        []()->vector<int>{                      // Função para gerar os individuos iniciais
            return ga::rand::vec_intperm(16);
        }
    );

    ga::Population<int> pop1(            // Classe população
        10,                              // Quantidade de individuos
        chromo,                          // Estilo do cromossomo
        fitness,                         // Função fitness associada
        ga::selection::roulette<int>,    // Método de seleção
        ga::crossover::bin::points<int>
    );

    pop1.run_fitness();
    pop1.run_selection();
    pop1.run_crossover(10, 0.80);

    return 0;
}
