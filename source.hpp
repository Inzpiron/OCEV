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
    class Agent {
        Cod cod_type;
        t * chromo_buff;
        int chromo_size;
        pair<t, t> bounds;

    public:
        Agent<t>() {}
        Agent<t>(int size, Cod type, t b1, t b2) {
            this->chromo_size = size;
            this->cod_type = type;
            this->chromo_buff = new t[this->chromo_size];
            this->bounds = pair<t,t>(b1, b2);
            generate();
        }

        Agent<t>(int size, Cod type) {
            if(type == BIN || type == INT_PERM) {
                this->chromo_size = size;
                this->cod_type = type;
                this->chromo_buff = new t[this->chromo_size];
                this->bounds = pair<t,t>(0,0);
                generate();
            }
        }

        int generate() {
            switch(cod_type) {
                case BIN:
                    for(int i = 0; i < this->chromo_size; i++) {
                        this->chromo_buff[i] = rand::boolean();
                    }

                    break;

                case INT:
                    for(int i = 0; i < this->chromo_size; i++) {
                        this->chromo_buff[i] = rand::integer(this->bounds.first, this->bounds.second);
                    }
                    break;

                case REAL:
                    for(int i = 0; i < this->chromo_size; i++) {
                        this->chromo_buff[i] = rand::real(this->bounds.first, this->bounds.second);
                    }
                    break;

                case INT_PERM:
                    vector<int> tmp(this->chromo_size);   
                    for(int i = 0; i < tmp.size(); i++) 
                        tmp[i] = i;

                    int max = this->chromo_size -1;
                    for(int i = 0; i < this->chromo_size; i++) {
                        int offset = rand::integer(0, max);
                        this->chromo_buff[i] = tmp[offset];
                        tmp.erase(tmp.begin() + offset);
                        --max;
                    }
                    break;
            }

            print();
            rand::reset();
        }


        void print() {
            cout << "Agent : {" << endl;
            cout << "   type: " << this->cod_type << endl;
            cout << "   chromo_size: " << this->chromo_size << endl;
            cout << "   bounds: (" << this->bounds.first << ", " << this->bounds.second << ")" << endl;
            cout << "   chromo_buff: [";
            for(int i = 0; i < this->chromo_size; i++) {
                cout << this->chromo_buff[i];
                if(i != this->chromo_size - 1)
                    cout << ",";
            }
            cout << "]" << endl << "}" << endl;
        }
    };

    template <class t>
    class Population {
        Cod cod_type;
        int pop_size;
        int chromo_size;
        Agent<t> * agent_buff;
    public:
        Population();
        Population(Cod cod_type, int pop_size, int chromo_size, t in, t fi) {
            this->cod_type = cod_type;
            this->pop_size = pop_size;
            this->chromo_size = chromo_size;
            agent_buff = new Agent<t>[this->pop_size];

            for(int i = 0; i < this->pop_size; i++) {
                if((cod_type == BIN || cod_type == INT_PERM) && in==fi)
                    agent_buff[i] = Agent<t>(chromo_size, cod_type);
                else {
                    agent_buff[i] = Agent<t>(chromo_size, cod_type, in, fi);
                }
            }
        }
    };
}

#endif