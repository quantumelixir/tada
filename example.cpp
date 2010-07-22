#include <iostream>

#include "tada.h"

using namespace std;

using tada::utp::UTP;
using tada::utp::operator*;

int main(int argc, char **argv)
{
    const int ord = 5;
    const int N = ord + 1;

    UTP<double> x(N), y(N), z(N);

    x[0] = 2; y[0]  = 3;
    x[1] = 1; y[1]  = 1;

    cout << "Testing with order " << ord << ": ";
    cout << "(Using Operator Overloading)" << endl;
    z = (1.0 - x + y)/(3.0 * x - x / 4.0 * y);
    cout << z << endl;

    return 0;
}
