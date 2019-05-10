#include <bits/stdc++.h>
using namespace std;

namespace ga {
    namespace crossover { 
        namespace int_perm {
            template<typename t>
            void pmx(Population<t>& pop, double percentual) {
                int tam_chromo = pop.agent_buff[0].chromo_buff.size();

                for(int i = 0; i < pop.pop_size; i += 2) {
                    int p1, p2;
                    p1 = rand::integer(0, tam_chromo - 1);
                    do {
                        p2 = rand::integer(0, tam_chromo - 1);
                        cout << "lol" << endl;
                    } while(p2 == p1);

                    if(p1 > p2) {
                        int aux = p1;
                        p1 = p2;
                        p2 = aux;
                    } 

                    double chance = rand::real(0, 1);
                    int * map1 = new int[tam_chromo];
                    int * map2 = new int[tam_chromo];
                    std::fill(map1, map1+tam_chromo, -1);
                    std::fill(map2, map2+tam_chromo, -1);
                    cout << "Pontos " << p1 << " " << p2 << endl;
                    cout << "AG1: "; pop.agent_buff[i].print(); cout << endl;
                    cout << "AG2: "; pop.agent_buff[i+1].print(); cout << endl;
                    cout << "----" << endl;

                    if(chance < percentual) {
                        
                        for(int ii = p1; ii <= p2; ii++) {
                            int * c1 = &(pop.agent_buff[i].chromo_buff[ii]);
                            int * c2 = &(pop.agent_buff[i+1].chromo_buff[ii]);

                            map1[*c2] = *c1; //Mapeamento ...
                            map2[*c1] = *c2;
                            int aux = *c1; // Swaping ...
                            *c1 = *c2;
                            *c2 = aux;  
                        }
                        
                        auto func_map = [&](int idx) {
                            int * c1 = &(pop.agent_buff[i].chromo_buff[idx]);
                            int * c2 = &(pop.agent_buff[i+1].chromo_buff[idx]);

                            if(map1[*c1] != -1)
                                *c1 = map1[*c1];

                            if(map2[*c2] != -1)
                                *c2 = map2[*c2];
                        };

                        for(int ii = 0; ii < p1; ii++)
                            func_map(ii);

                        for(int ii = p2 + 1; ii < tam_chromo; ii++)
                            func_map(ii);

                        cout << "AG1: "; pop.agent_buff[i].print(); cout << endl;
                        cout << "AG2: "; pop.agent_buff[i+1].print(); cout << endl;
                    }
                    cout << endl << endl;
                }
            }
        }
    }
}