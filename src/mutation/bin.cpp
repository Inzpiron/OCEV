#include <bits/stdc++.h>
using namespace std;

namespace ga {
    namespace mutation { 
        namespace bin {
            template<typename t>
            void bitflip (Population<t>& pop, double percentual) {
                int tam_chromo = pop.agent_buff[0].chromo_buff.size();
                
#pragma omp parallel for
                for (int i = 0; i < pop.pop_size; i++) {
                    for(int ii = 0; ii < tam_chromo; ii++) {
                        double perc = rand::real(0, 1);
                        if(perc <= percentual) {
                            pop.agent_buff[i].chromo_buff[ii] = !pop.agent_buff[i].chromo_buff[ii];
                        }
                    }
                }
            }
        }
    }
}