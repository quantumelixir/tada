#include <iostream>
#include <iomanip>

#include "tada.h"
#include "mpreal.h"

using namespace std;

using tada::utp::UTP;

// our test function: f(x) = x/(1 + x)
template<class T>
UTP<T> f(T x0, unsigned int N = 5)
{
    UTP<T> x(N);
    x[0] = x0; x[1] = T(1.0);
    return x/(T(1.0) + x);
}

int main(int argc, char **argv)
{
    double x0 = 1.0;

    cout << fixed << setprecision(20);

    cout << "Single precision: " << f(float(x0)) << endl;
    cout << "Double precision: " << f(double(x0)) << endl;
    mpfr::mpreal::set_default_prec(128);
    cout << "Multi  precision: " << f(mpfr::mpreal(x0)) << endl;

    return 0;
}
