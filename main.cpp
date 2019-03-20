#include <bits/stdc++.h>
#include "source.hpp"

using namespace std;

int main() {
    ga::rand::reset();

    
    cout << "População BIN" << endl;
    ga::Population<int> pop(10, {0,1}, ga::chromo_config<int>(ga::BIN, 10, []()->int*{
        return ga::rand::vec_int(10, 0, 1);
    }));
    cout << endl << endl;


    cout << "População INT_PERM" << endl;
    ga::Population<int> pop1(10, {0,0}, ga::chromo_config<int>(ga::INT_PERM, 10, []()->int*{
        return ga::rand::vec_intperm(10);
    }));
    cout << endl << endl;


    cout << "População INT" << endl;
    ga::Population<int> pop2(10, {0, 10}, ga::chromo_config<int>(ga::INT_PERM, 10, []()->int*{
        return ga::rand::vec_int(10, 0, 10);
    }));
    cout << endl << endl;


    cout << "População REAL" << endl;
    ga::Population<double> pop3(10, {0.0, 10.0}, ga::chromo_config<double>(ga::REAL, 10, []()->double*{
        return ga::rand::vec_real(10, 0, 10);
    }));
    cout << endl << endl;

    /*
    cout << "População INT-PERM" << endl;
    ga::Population<int> pop1(10, ga::chromo_config<int>(ga::INT_PERM, 10, 0, 0));
    cout << endl << endl;

    cout << "População REAL" << endl;
    ga::Population<double> pop2(10, ga::chromo_config<double>(ga::REAL, 10, -5, 10));
    cout << endl << endl;
    */
    return 0;
}