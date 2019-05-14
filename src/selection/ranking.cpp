#include <bits/stdc++.h>
using namespace std;

namespace ga {
    namespace selection {
        template<typename t>
        void ranking(Population<t>& pop) {
            std::sort(pop.agent_buff, pop.agent_buff + pop.pop_size, [](Agent<t> a, Agent<t> b) {
                return a.fitness < b.fitness;
            });

            int roleta[pop.pop_size + 1] = {0};
            int sum = 0;
            int total = 0;
            for(int i = 0; i < pop.pop_size + 1; i++) {
                roleta[i] = sum;
                total     = sum;
                sum += i+1;
            }
        
            vector< Agent<t> > chosen_by_god;
            int last = -1;
            while(chosen_by_god.size() < pop.pop_size) {
                int target = rand::integer(0, total);
                for(int i = 0; i < pop.pop_size; i++) {
                    if(roleta[i] >= target && roleta[i] < target && i != last) {
                        chosen_by_god.push_back(pop.agent_buff[i]);
                        last = i;
                        break;
                    }
                }
            }

            for(int i = 0; i < pop.pop_size; i++) {
                pop.agent_buff[i] = chosen_by_god[i];
            }
        }
    }
}
