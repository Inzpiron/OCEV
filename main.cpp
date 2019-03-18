#include <bits/stdc++.h>
#include "source.hpp"

using namespace std;

int main() {
    ga::rand::reset();

    cout << "População BIN" << endl;
    ga::Population pop(ga::BIN, 10, 10, 0,0);
    cout << endl << endl;

    cout << "População INT-PERM" << endl;
    ga::Population pop1(ga::INT_PERM, 10, 10, 0, 0);
    cout << endl << endl;

    cout << "População REAL" << endl;
    ga::Population pop2(ga::REAL, 10, 10, -5.0, 10.0);
    cout << endl << endl;

    cout << "População INT" << endl;
    ga::Population pop3(ga::INT, 10, 10, -10, 10);



    return 0;
}