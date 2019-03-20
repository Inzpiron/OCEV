#include <bits/stdc++.h>

using namespace std;

int main() {
    #pragma omp parallel
    {
    // Code inside this region runs in parallel.
    printf("Hello!\n");
    }
}