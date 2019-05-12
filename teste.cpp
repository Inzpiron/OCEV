#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int t[] = {0, 1, 2, 3, 0};

    cout << std::count(t, t+5, 1) << endl;
    return 0;
}