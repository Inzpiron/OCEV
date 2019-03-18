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
    }

    template <typename t>
    struct chromo_config {
        Cod cod_type;
        int chromo_size;
        pair<t,t> bounds;

        chromo_config(){}
        chromo_config(Cod cod, int s, t i, t f){
            this->cod_type = cod;
            this->chromo_size = s;
            this->bounds.first = i;
            this->bounds.second = f;
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
            this->chromo_buff = new t[this->feature.chromo_size];
            generate();
        }

        int generate() {
            vector<int> tmp(this->feature.chromo_size); 
            for(int i = 0; i < tmp.size(); i++) 
                tmp[i] = i;
            int max = this->feature.chromo_size -1;

            for(int i = 0; i < this->feature.chromo_size; i++) {
                switch(feature.cod_type) {
                    case BIN:
                        this->chromo_buff[i] = rand::boolean();
                        break;

                    case INT:
                        this->chromo_buff[i] = rand::integer(this->feature.bounds.first, this->feature.bounds.second);
                        break;

                    case REAL:
                        this->chromo_buff[i] = rand::real(this->feature.bounds.first, this->feature.bounds.second);
                        break;

                    case INT_PERM:
                        int offset = rand::integer(0, max);
                        this->chromo_buff[i] = tmp[offset];
                        tmp.erase(tmp.begin() + offset);
                        --max;
                        break;
                }
            }

            print();
            rand::reset();
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
        chromo_config<t> chromo_style;
        Agent<t> * agent_buff;
    public:
        Population();
        Population(int pop_size, chromo_config<t> chromo_style) {
            this->chromo_style = chromo_style;
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