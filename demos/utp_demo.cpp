#include <iostream>
#include <iomanip>

#include "tada.h"
#include "mpreal.h"

using namespace std;

using tada::utp::UTP;
using tada::utp::operator*;
using tada::utp::operator-;

int main(int argc, char **argv)
{
    const int ord = 5;
    const int N = ord + 1;

    cout << "Testing with order " << ord << ": ";
    cout << "(Using Operator Overloading)" << endl;

    cout << fixed; // set format flag

    UTP<float> xf(N), yf(N), zf(N); // single precision
    xf[0] = 2; yf[0]  = 3;
    xf[1] = 1; yf[1]  = 1;
    zf = (xf - 1.0 - xf + yf)/(3.0 * xf - xf / 4.0 * yf);
    cout << setprecision(20) << "Single precision: " << zf << endl;

    UTP<double> xd(N), yd(N), zd(N); // double precision
    xd[0] = 2; yd[0]  = 3;
    xd[1] = 1; yd[1]  = 1;
    zd = (xd - 1.0 - xd + yd)/(3.0 * xd - xd / 4.0 * yd);
    cout << setprecision(20) << "Double precision: " << zd << endl;

    mpfr::mpreal::set_default_prec(128); // quad precision
    UTP<mpfr::mpreal> xq(N), yq(N), zq(N);
    xq[0] = 2; yq[0]  = 3;
    xq[1] = 1; yq[1]  = 1;
    cout << setprecision(20) << "Quad precision  : " << xq + yq << endl;
//     zq = (xq + yq)/(xq - xq* yq);
//    cout << "Quad   precision: " << zq << endl;
//    cout << "Details:" << endl;
//    cout << "Machine Epsilon = " << mpfr::machine_epsilon(zq[0].get_prec()) << endl;
//    cout << "Min = " << mpfr::mpreal_min(zq[0].get_prec()) << endl;
//    cout << "Max = " << mpfr::mpreal_max(zq[0].get_prec()) <<endl;

    return 0;
}
