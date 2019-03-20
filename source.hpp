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
        int * vec_int(int, int, int);
        double * vec_real(int, double, double);
        int * vec_intperm(int);
    }

    template <typename t>
    struct chromo_config {
        Cod cod_type;
        int chromo_size;
        std::function<t*()> chromo_gen;

        chromo_config(){}
        chromo_config(Cod cod, int s, auto func){
            this->cod_type = cod;
            this->chromo_size = s;
            this->chromo_gen = func;
        }
    };

    
    template <typename t>
    class Agent {
        t * chromo_buff;
        chromo_config<t> feature;

    public:
        Agent<t>() {}
        Agent<t>(chromo_config<t> feature) {
            this->feature = feature;
            this->chromo_buff = this->feature.chromo_gen();
            print();
        }

        void print() {
            cout << "[";
            for(int i = 0; i < this->feature.chromo_size; i++) {
                cout << this->chromo_buff[i];
                if(i != this->feature.chromo_size - 1)
                    cout << ",";
            }
            cout << "]" << endl;
        }
    };

    template <typename t>
    class Population {
        int pop_size;
        pair<t, t> bounds;
        chromo_config<t> chromo_style;
        Agent<t> * agent_buff;
    public:
        Population();
        Population(int pop_size, pair<t,t> bounds, chromo_config<t> chromo_style) {
            this->chromo_style = chromo_style;
            this->bounds = bounds;
            this->pop_size = pop_size;
            agent_buff = new Agent<t>[this->pop_size];

            for(int i = 0; i < this->pop_size; i++) {
                if(chromo_style.cod_type == BIN || chromo_style.cod_type == INT_PERM)
                    agent_buff[i] = Agent<t>(chromo_style);
                else {
                    agent_buff[i] = Agent<t>(chromo_style);
                }
            }
        }
    };
}

#endif