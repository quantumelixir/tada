#include <iostream>

#include "tada.h"
#include "mpreal.h"

using namespace std;

using tada::utp::UTP;

// our test function: f(x) = x/(1 + x)
template<class T>
UTP<T> f(T x0, unsigned int N = 5)
{
    UTP<T> x(N);
    x.set(0, x0);
    x.set(1, T(1.0));
    return x/(T(1.0) + x);
}

int main(int argc, char **argv)
{
    double x0 = 1.0;

    mpfr::mpreal::set_default_prec(128);
    cout << f(mpfr::mpreal(x0)) << endl;

    return 0;
}
