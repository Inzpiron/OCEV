#include <bits/stdc++.h>
using namespace std;

namespace ga {
    namespace selection {
        template<typename t>
        void roulette(Population<t>& pop) {
            double last = -1;
            double fit_rel[pop.pop_size] = {0};
            double fit_total = 0;

            for(int i = 0; i <  pop.pop_size; i++) 
                fit_total += pop.agent_buff[i].fitness;

            double roleta[pop.pop_size + 1] = {0};
            double fit_rel_sum = 0;
            for(int i = 0; i < pop.pop_size; i++) {
                fit_rel[i] = pop.agent_buff[i].fitness/fit_total;
                fit_rel_sum += fit_rel[i];
                roleta[i+1] = fit_rel_sum;
            }
            
            vector< Agent<t> > chosen_by_god;
            while(chosen_by_god.size() < pop.pop_size) {
                double target = rand::real(0, 1);
                for(int i = 0; i < pop.pop_size; i++) {
                    if(roleta[i] <= target && roleta[i+1] > target && i != last) {
                        last = i;
                        chosen_by_god.push_back(pop.agent_buff[i]);
                        break;
                    }
                }
            }

            //pop.agent_buff = chosen_by_god.data();
            for(int i = 0; i < pop.pop_size; i++) {
                pop.agent_buff[i] = chosen_by_god[i];
            }
        }
    }
}
