#include <iostream>
#include <cmath>
#include <stdlib.h>
using namespace std;

int main(int argc, char* argv[]) {
    int N; 
    N = strtol(argv[1], NULL, 10); //convert the string from argv to number
    cout << pow(2, N) << endl; //prints the value of 2^N
    return 0;
}
