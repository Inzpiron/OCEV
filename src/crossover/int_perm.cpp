#include <bits/stdc++.h>
using namespace std;

namespace ga {
    namespace crossover { 
        namespace int_perm {
            template<typename t>
            void pmx(Population<t>& pop, double percentual) {
                int tam_chromo = pop.agent_buff[0].chromo_buff.size();
                #pragma omp parallel for
                for(int i = 0; i < pop.pop_size; i += 2) {
                    int p1, p2;
                    p1 = rand::integer(0, tam_chromo - 1);
                    do {
                        p2 = rand::integer(0, tam_chromo - 1);
                    } while(p2 == p1);

                    if (p1 > p2) {
                        int aux = p1;
                        p1 = p2;
                        p2 = aux;
                    } 

                    double chance = rand::real(0, 1);
                    //cout << "Pontos " << p1 << " " << p2 << endl;
                    //cout << "AG1: "; pop.agent_buff[i].print(); cout << endl;
                    //cout << "AG2: "; pop.agent_buff[i+1].print(); cout << endl;
                    //cout << "----" << endl;

                    if(chance < percentual) {
                        vector<int> * map = new vector<int>[tam_chromo];
                        bool * visitado[2];
                        visitado[0] = new bool[tam_chromo];
                        visitado[1] = new bool[tam_chromo];

                        std::fill(map, map + tam_chromo, vector<int>());
                        std::fill(visitado[0], visitado[0] + tam_chromo, false);
                        std::fill(visitado[1], visitado[1] + tam_chromo, false);

                        for(int ii = p1; ii <= p2; ii++) {
                            int * c1 = &(pop.agent_buff[i].chromo_buff[ii]);
                            int * c2 = &(pop.agent_buff[i+1].chromo_buff[ii]);
                            
                            map[*c2].push_back(*c1); //Mapeamento ...
                            map[*c1].push_back(*c2);
                            int aux = *c1; // Swaping ...
                            *c1 = *c2;
                            *c2 = aux; 
                            visitado[0][*c1] = true;
                            visitado[1][*c2] = true; 
                        }
                        
                        auto func_map = [&](int idx) {
                            for(int l = 0; l < 2; l++) {
                                int * c = &(pop.agent_buff[i+l].chromo_buff[idx]);
                                
                                bool * v_aux = new bool[tam_chromo];
                                std::fill(v_aux, v_aux + tam_chromo, false);
                                v_aux[*c] = true;
                                
                                while(visitado[l][*c]) { 
                                    for(auto x : map[*c]) {
                                        if(!v_aux[x]) {
                                            *c = x;
                                            v_aux[*c] = true;
                                            break;
                                        }
                                    }
                                }

                                delete[] v_aux;
                                visitado[l][*c] = true;
                            }
                        };
                        
                        for(int ii = 0; ii < tam_chromo; ii++)
                            if(ii < p1 || ii > p2)
                                func_map(ii);

                        delete[] map;
                        delete[] visitado[0];
                        delete[] visitado[1];
                        //cout << "AG1: "; pop.agent_buff[i].print(); cout << endl;
                        //cout << "AG2: "; pop.agent_buff[i+1].print(); cout << endl;
                    }
                    //cout << endl << endl;
                }
            }
        }
    }
}