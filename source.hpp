#ifndef __CAL_H_INCLUDED__
#define __CAL_H_INCLUDED__

using namespace std;

namespace ga {
    enum Cod {
        BIN,
        INT,
        INT_PERM,
        REAL
    };

    namespace rand {
        namespace {
            std::random_device rd;
            std::mt19937 gen;
            std::uniform_real_distribution<> r_dist;
            std::uniform_int_distribution<> i_dist;
        }

        void reset();
        int integer(int i, int j);
        double real(double i, double j);
        bool boolean();
        vector<int> vec_int(int, int, int);
        vector<double> vec_real(int, double, double);
        vector<int> vec_intperm(int);
    }

    template <typename t>
    struct chromo_config {
        Cod cod_type;
        std::function<vector<t>()> chromo_gen;

        chromo_config(){}
        chromo_config(Cod cod, auto func){
            this->cod_type = cod;
            this->chromo_gen = func;
        }
    };


    template <typename t>
    class Agent {
        chromo_config<t> feature;

    public:
        vector<t> chromo_buff;
        double fitness;

        Agent<t>() {}
        Agent<t>(chromo_config<t> feature) {
            this->feature = feature;
            this->chromo_buff = this->feature.chromo_gen();
            this->fitness = -1;
        }

        void print() {
            cout << "[";
            for(int i = 0; i < this->chromo_buff.size(); i++) {
                cout << this->chromo_buff[i];
                if(i != this->chromo_buff.size() - 1)
                    cout << ",";
            }
            cout << "] ";
        }
    };

    template <typename t>
    class Population {
    public:
        int pop_size;
        pair<t, t> bounds;
        chromo_config<t> chromo_style;
        Agent<t> * agent_buff;

        std::function<double(Agent<t>&)> func_fitness;
        std::function<void(Population&)> func_selection;
        std::function<void(Population&, int, double)> func_crossover;
        
        Population();
        Population(int pop_size, pair<t,t> bounds, chromo_config<t> chromo_style, auto func_fitness,
                   auto func_selection, auto func_crossover) {
            this->chromo_style = chromo_style;
            this->bounds = bounds;
            this->pop_size = pop_size;
            this->func_fitness = func_fitness;
            this->func_selection = func_selection;
            agent_buff = new Agent<t>[this->pop_size];

            for(int i = 0; i < this->pop_size; i++) {
                agent_buff[i] = Agent<t>(chromo_style);
            }
        }

        Population(int pop_size, chromo_config<t> chromo_style, auto func_fitness, auto func_roulette,
                   auto func_crossover) {
            this->chromo_style = chromo_style;
            this->bounds = {0,0};
            this->pop_size = pop_size;
            this->func_fitness = func_fitness;
            this->func_selection = func_roulette;
            this->func_crossover = func_crossover;
            agent_buff = new Agent<t>[this->pop_size];

            //#pragma omp parallel for
            for(int i = 0; i < this->pop_size; i++) {
                agent_buff[i] = Agent<t>(chromo_style);
            }
        }

        void run_fitness() {
            #pragma omp parallel for
            for(int i = 0; i < pop_size; i++) {
                agent_buff[i].fitness = func_fitness(agent_buff[i]);
                //cout << agent_buff[i].fitness << endl;
            }
        }

        void run_selection() {
            this->func_selection(*this);
        }

        void run_crossover(int np, double percentual) {
            this->func_crossover(*this, np, percentual);
        }
    };

    namespace crossover { 
        namespace bin {
            template<typename t>
            void points(Population<t>& pop, int np, double percentual) {
                int * points = new int[np];
                cout << pop.agent_buff[0].fitness << endl;
                int tam_chromo = pop.agent_buff[0].chromo_buff.size();
                cout << tam_chromo << endl;
                /*
                bool * visitados = new bool[tam_chromo];
                for(int i = 0; i < np; i++) {       
                    int pos = rand::integer(0, tam_chromo);
                    
                    if(!visitados[pos]) {
                        visitados[pos] = true;
                        points[i] = pos;
                    }

                    cout << pos << endl;
                }

                /*
                for(int i = 0; i < pop.pop_size; i++) {
                    double chance = rand::real(0, 1);
                    if(chance < percentual) {

                    }
                }*/
            }
        }
    }

    namespace selection {
        template<typename t>
        void roulette(Population<t>& pop) {
            double last = -1;
            double fit_rel[pop.pop_size] = {0};
            double fit_total = 0;

            for(int i = 0; i <  pop.pop_size; i++) 
                fit_total += pop.agent_buff[i].fitness;

            cout << "roleta: " << endl;
            double roleta[pop.pop_size + 1] = {0};
            double fit_rel_sum = 0;
            for(int i = 0; i < pop.pop_size; i++) {
                fit_rel[i] = pop.agent_buff[i].fitness/fit_total;
                fit_rel_sum += fit_rel[i];
                roleta[i+1] = fit_rel_sum;
            }

            for(int i = 0; i < pop.pop_size + 1; i++) {
                cout << roleta[i] << endl;
            }

            cout << endl;
            vector< Agent<t> > chosen_by_god;
            while(chosen_by_god.size() < pop.pop_size) {
                double target = rand::real(0, 1);
                for(int i = 0; i < pop.pop_size; i++) {
                    if(roleta[i] <= target && roleta[i+1] > target && i != last) {
                        last = i;
                        chosen_by_god.push_back(pop.agent_buff[i]);
                        cout << i << " " << pop.agent_buff[i].fitness << endl;
                        break;
                    }
                }
            }

            //pop.agent_buff = chosen_by_god.data();
        }
    }   
}

#endif
