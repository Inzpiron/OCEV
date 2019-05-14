#include <bits/stdc++.h>
using namespace std;

namespace ga {
    namespace mutation { 
        namespace int_perm {
            template<typename t>
            void swap (Population<t>& pop, double percentual) {
                int tam_chromo = pop.agent_buff[0].chromo_buff.size();
#pragma omp parallel for
                for (int i = 0; i < pop.pop_size; i++) {
                    for(int ii = 0; ii < tam_chromo; ii++) {
                        double perc = rand::real(0, 1);
                        if(perc <= percentual) {
                            int p1 = ii;
                            int p2 = p1;
                            while(p2 == p1) p2 = rand::integer(0, tam_chromo - 1);

                            int aux = pop.agent_buff[i].chromo_buff[p1];
                            pop.agent_buff[i].chromo_buff[p1] = pop.agent_buff[i].chromo_buff[p2];
                            pop.agent_buff[i].chromo_buff[p2] = aux;
                        }
                    }
                }
                
                /* TESTE DE CONSISTÊNCIA
#pragma omp parallel for
                for(int i = 0; i < pop.pop_size; i++) {
                    for(int j = 0; j < tam_chromo; j++) {
                        int total = count_if(pop.agent_buff[i].chromo_buff.begin(), pop.agent_buff[i].chromo_buff.end(), [&](int a) {
                            return a == j;
                        });

                        if(total != 1) {
                            cout << "deu merda " << total << endl;
                            cin.get();
                        }
                    }
                }
                */
            }
        }
    }
}