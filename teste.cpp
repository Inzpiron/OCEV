#include <iostream>

using namespace std;

int main() {
    int * vec = new int[10];
    fill(vec, vec+10, -1);

    int * ptr = &vec[5];
    *ptr = 0;

    for(int i = 0; i < 10; i++)
        cout << vec[i] << endl;
    return 0;
}