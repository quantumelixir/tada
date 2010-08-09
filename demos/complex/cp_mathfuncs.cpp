#include "mathfuncs.h"
#include <complex>

using std::cout;
using std::endl;

int main(int argc, char **argv)
{
    std::complex<double> x0(1.0, 1.0);

    cout << "Differentiation with complex types around the point: "<< x0 << endl;

    cout << endl << str_f0 << endl;
    cout << f0(x0) << endl;
    cout << endl;

/*
 *    cout << endl << str_f1 << endl;
 *    cout << f1(x0) << endl;
 *    cout << endl;
 *
 *    cout << endl << str_f2 << endl;
 *    cout << f2(x0) << endl;
 *    cout << endl;
 *
 *    cout << endl << str_f3 << endl;
 *    cout << f3(x0) << endl;
 *    cout << endl;
 */

    return 0;
}
