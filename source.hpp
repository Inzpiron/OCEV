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
        int pop_size;
        pair<t, t> bounds;
        chromo_config<t> chromo_style;
        Agent<t> * agent_buff;
        std::function<double(Agent<t>&)> func_fitness;

    public:
        Population();
        Population(int pop_size, pair<t,t> bounds, chromo_config<t> chromo_style, auto func_fitness) {
            this->chromo_style = chromo_style;
            this->bounds = bounds;
            this->pop_size = pop_size;
            this->func_fitness = func_fitness;
            agent_buff = new Agent<t>[this->pop_size];

            for(int i = 0; i < this->pop_size; i++) {
                agent_buff[i] = Agent<t>(chromo_style);
            }
        }

        Population(int pop_size, chromo_config<t> chromo_style, auto func_fitness) {
            this->chromo_style = chromo_style;
            this->bounds = {0,0};
            this->pop_size = pop_size;
            this->func_fitness = func_fitness;
            agent_buff = new Agent<t>[this->pop_size];

            //#pragma omp parallel for
            for(int i = 0; i < this->pop_size; i++) {
                agent_buff[i] = Agent<t>(chromo_style);
            }
        }


        void run_fitness() {
            #pragma omp parallel for
            for(int i = 0; i < pop_size; i++) {
                agent_buff[i].print();
                agent_buff[i].fitness = func_fitness(agent_buff[i]);
                cout << agent_buff[i].fitness << endl;
            }
        }
    };
}

#endif