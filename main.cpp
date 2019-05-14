#include <bits/stdc++.h>
#include "src/source.hpp"
#include "src/selection/roulette.cpp"
#include "src/selection/ranking.cpp"
#include "src/crossover/int_perm.cpp"
#include "src/mutation/int_perm.cpp"

using namespace std;

int main() {
    int total = 16;
    ga::rand::reset();
    
    auto fitness = [&](ga::Population<int>& pop, ga::Agent<auto>& agent) {
        vector<bool> colidiu (total, false);
        int sum = 0;
        for(int i = 0; i < agent.chromo_buff.size(); i++) {
            int y = i;
            int x = agent.chromo_buff[i];

            for(int j = i+1; j < agent.chromo_buff.size(); j++) {
                int _y = j;
                int _x = agent.chromo_buff[j];

                if(abs(x - _x) == abs(y - _y)) {
                    colidiu[i] = true;
                    colidiu[j] = true;
                }
            }
        }

        for(auto i : colidiu) {
            if(i) sum++;
        }

        return 1.0 - ((double)sum/(double)total);
    };

    ga::chromo_config<int> chromo(                 // Estrutura que define o agente
        ga::INT_PERM,                              // Tipo de codificação: BIN, INT-PERM, REAL, INT
        {-1, -1},                                  // Limites do gene
        [&]()->vector<int>{                        // Função para gerar os individuos iniciais
            return ga::rand::vec_intperm(total);   // Parametro = quantidade de genes
        }
    );

    ga::Population<int> pop1(               // Classe população
        10,                                 // Quantidade de individuos
        chromo,                             // Configuração do cromossomo
        fitness,                            // Função fitness associada
        ga::selection::ranking<int>,        // Método de seleção
        ga::crossover::int_perm::pmx<int>,  // Método crossover
        ga::mutation::int_perm::swap<int>   // Método mutação
    );

    pop1.start_worker(
        250000,    // Quantidade máxima de gerações
        0.525,     // Percentual de crossover
        1/96.0    // Percentual de Mutação
    );

    return 0;
}
