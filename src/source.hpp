#ifndef __SRC_H_INCLUDED__
#define __SRC_H_INCLUDED__
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
        std::pair<t, t> bounds;

        chromo_config(){}
        chromo_config(Cod cod, std::pair<t,t> bounds, auto func){
            this->cod_type   = cod;
            this->bounds     = bounds;
            this->chromo_gen = func;
        }
    };


    template <typename t>
    class Agent {
        chromo_config<t> feature;

    public:
        vector<t> chromo_buff;
        double fitness;
        int id;

        Agent<t>() {}
        Agent<t>(chromo_config<t> feature, int id) {
            this->feature = feature;
            this->chromo_buff = this->feature.chromo_gen();
            this->fitness = -1;
            this->id = id;
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
        std::function<double(Population<t>&, Agent<t>&)> func_fitness;
        std::function<void(Population&)> func_selection;
        std::function<void(Population&, double)> func_crossover;
        std::function<void(Population&, double)> func_mutation;
    
    public:
        int pop_size;
        int gen;
        chromo_config<t> chromo_style;
        Agent<t> * agent_buff;
        Agent<t> god_agent;
        
        Population();
        Population(int pop_size, chromo_config<t> chromo_style, auto func_fitness,
                   auto func_selection, auto func_crossover, auto func_mutation) {
            this->pop_size = pop_size;
            this->gen = 0;
            this->chromo_style = chromo_style;
            this->func_fitness = func_fitness;
            this->func_selection = func_selection;
            this->func_crossover = func_crossover;
            this->func_mutation  = func_mutation;
            this->god_agent = Agent<t>(chromo_style, -1);
            this->god_agent.fitness = numeric_limits<double>::min();

            agent_buff = new Agent<t>[this->pop_size];
            for(int i = 0; i < this->pop_size; i++) {
                agent_buff[i] = Agent<t>(chromo_style, i);
            }
        }


        void run_fitness() {
            Agent<t> ag_worst (this->chromo_style, -1);
            ag_worst.fitness = numeric_limits<double>::max();
#pragma omp parallel for 
            for(int i = 0; i < pop_size; i++) {
                agent_buff[i].fitness = func_fitness(*this, agent_buff[i]);
#pragma omp critical 
                {
                    if(agent_buff[i].fitness < ag_worst.fitness) {
                        ag_worst = agent_buff[i];
                        ag_worst.id = i;
                    }

                    if(agent_buff[i].fitness > this->god_agent.fitness) {
                        this->god_agent = agent_buff[i];
                    }
                }
            }

            //ELITISMO
            if(this->god_agent.id != -1 && this->gen > 0){
                this->agent_buff[ag_worst.id] = god_agent;
            }
        }

        void run_selection() {
            this->func_selection(*this);
        }

        void run_crossover(double percentual) {
            this->func_crossover(*this, percentual);
        }

        void run_mutation(double percentual) {
            this->func_mutation(*this, percentual);
        }

        void start_worker(int n_gen, double p_crossover, double p_mutation) {
            int total = n_gen;
            double god_agent = 0;
            double ant = -1;
            do {
                this->run_fitness();
                this->run_selection();

                if(this->god_agent.fitness > ant) { 
                    cout << this->gen << " " << this->god_agent.fitness << endl;
                    ant = this->god_agent.fitness;

                    if(ant >= 1) break;
                }

                this->run_crossover(p_crossover);
                this->run_mutation(p_mutation);
                ++this->gen;
                //cin.get();
            } while(n_gen--);
        }
    };
}


#endif
