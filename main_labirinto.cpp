#include <bits/stdc++.h>
#include "src/source.hpp"
#include "src/selection/roulette.cpp"
#include "src/selection/ranking.cpp"
#include "src/crossover/int_perm.cpp"
#include "src/crossover/bin.cpp"
#include "src/mutation/int_perm.cpp"

using namespace std;

int main() {
    int total = 100;
    ga::rand::reset();
    
    int mapa[][25] =   {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,3,1,1,0,0},
                        {0,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,1,0},
                        {0,1,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0},
                        {0,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,1,0},
                        {0,1,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,1,0},
                        {0,1,0,0,0,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0},
                        {0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,1,0},
                        {0,1,1,1,1,1,1,1,0,1,1,0,1,1,1,0,1,0,1,0,1,0,1,1,0},
                        {0,0,0,0,0,0,1,1,0,1,1,0,1,1,1,0,1,0,1,0,1,0,0,1,0},
                        {0,2,1,1,1,0,1,0,0,1,1,0,1,0,0,0,1,0,1,0,1,0,1,1,0},
                        {0,1,0,0,1,0,1,0,0,1,1,0,1,0,0,0,1,0,1,0,1,1,1,1,0},
                        {0,1,0,0,1,0,1,0,0,1,0,0,1,0,0,0,1,0,1,0,0,0,0,1,0},
                        {0,1,0,0,1,0,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,0},
                        {0,1,0,0,1,0,1,1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,0,1,0},
                        {0,1,1,0,1,0,0,1,1,1,0,0,0,0,0,1,1,1,1,0,1,0,0,1,0},
                        {0,1,1,0,1,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,1,0},
                        {0,0,1,0,1,0,1,1,0,0,0,0,0,0,0,1,1,1,1,0,1,0,1,0,0},
                        {0,1,1,0,0,0,1,1,0,1,1,1,1,0,0,0,0,0,1,0,1,1,1,1,0},
                        {0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,0,0,1,0},
                        {0,0,0,0,1,0,0,0,0,1,1,0,1,1,1,0,1,0,1,0,1,1,0,1,0},
                        {0,1,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,0,0,1,0,1,0},
                        {0,1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0},
                        {0,1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,1,0},
                        {0,1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0},
                        {0,1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,0,1,0,1,0},
                        {0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,0,1,1,1,1,1,0},
                        {0,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0},
                        {0,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

    
    
    auto fitness = [&](ga::Population<int>& pop, ga::Agent<auto>& agent) {
        //std::this_thread::sleep_for(0.05s);
        int x  = 1, y = 10;
        int xf = 1, yf = 20;
        int col = 0;

        auto free = [&](int i, int j) {
            if(i >= 25 || i < 0) { col++; return false; }
            if(j >= 29 || j < 0) { col++; return false; }
            if(mapa[i][j] == 0)  { col++; return false; }
            return true;
        };

        for(int i = 0; i < agent.chromo_buff.size(); i++) {
            int opc = agent.chromo_buff[i];
            switch(agent.chromo_buff[i]) {
                case 0:
                    if(free(x+1, y))
                        x++;
                    break;

                case 1:
                    if(free(x-1, y))
                        y++;
                    break;
                
                case 2: 
                    if(free(x, y-1))  
                        y--;
                    break;
                
                case 3:
                    if(free(x, y+1))
                        y++;
                    break;
            }
        }

        int max  = 29 + 25;
        int dist = abs(x - xf) + abs(y - yf); 
        return 1 - (dist/(double) max);
    };

    ga::chromo_config<int> chromo(                 // Estrutura que define o agente
        ga::INT,                                   // Tipo de codificação: BIN, INT-PERM, REAL, INT
        {0, 3},                                    // Limites do gene
        [&]()->vector<int> {                       // Função para gerar os individuos iniciais
            return ga::rand::vec_int(total, 0, 3); // Parametro = quantidade de genes
        }
    );

    ga::Population<int> pop1(               // Classe população
        10,                                 // Quantidade de individuos
        chromo,                             // Configuração do cromossomo
        fitness,                            // Função fitness associada
        ga::selection::roulette<int>,        // Método de seleção
        ga::crossover::bin::section<int>,   // Método crossover
        ga::mutation::int_perm::swap<int>   // Método mutação
    );

    pop1.start_worker(
        2.5e6,    // Quantidade máxima de gerações
        0.80,      // Percentual de crossover
        0.05       // Percentual de Mutação
    );

    return 0;
}
