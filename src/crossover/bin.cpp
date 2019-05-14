#include <bits/stdc++.h>
using namespace std;

namespace ga {
    namespace crossover { 
        namespace bin {
            template<typename t>
            void section(Population<t>& pop, double percentual) {
                int tam_chromo = pop.agent_buff[0].chromo_buff.size();
                for(int i = 0; i < pop.pop_size; i += 2) {
                    int p1, p2;
                    p1 = rand::integer(0, tam_chromo);
                    do {
                        p2 = rand::integer(0, tam_chromo);
                    } while(p2 == p1);

                    if(p1 > p2) {
                        int aux = p1;
                        p1 = p2;
                        p2 = aux;
                    }
                    
                    //cout << p1 << " " << p2 << endl;
                    //pop.agent_buff[i].print(); cout << endl;
                    //pop.agent_buff[i+1].print(); cout << endl;
                    double chance = rand::real(0, 1);
                    if(chance < percentual) {
                        for(int ii = p1; ii <= p2; ii++) {
                            int aux = pop.agent_buff[i].chromo_buff[ii];
                            pop.agent_buff[i].chromo_buff[ii]   = pop.agent_buff[i+1].chromo_buff[ii];
                            pop.agent_buff[i+1].chromo_buff[ii] = aux;   
                        }
                        //cout << " ---- " << endl;
                    }
                    //pop.agent_buff[i].print(); cout << endl;
                    //pop.agent_buff[i+1].print(); cout << endl;
                }

                //cout << endl << endl;
            }
        }
    }
}