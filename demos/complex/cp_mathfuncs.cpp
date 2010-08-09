#include <complex>
#include <boost/math/complex.hpp>

// => first include the definition of asin(complex<double>&)
// For most types this is not necessary because the compiler is smart enough to
// figure out the correct function to call through ADL. However, because
// std::complex<T> doesn't come with definitions for inverse trigonometric
// (they're part of TR1) functions we have to manually include them.
namespace tada { namespace utp { namespace math {
    using boost::math::asin;
}}}

// => then include the headers
#include "mathfuncs.h"

using std::cout;
using std::endl;

int main(int argc, char **argv)
{
    std::complex<double> x0(1.0, 1.0);

    cout << "Differentiation with complex types around the point: "<< x0 << endl;

    cout << endl << str_f0 << endl;
    cout << f0(x0) << endl;
    cout << endl;

    cout << endl << str_f1 << endl;
    cout << f1(x0) << endl;
    cout << endl;

    cout << endl << str_f2 << endl;
    cout << f2(x0) << endl;
    cout << endl;

    cout << endl << str_f3 << endl;
    cout << f3(x0) << endl;
    cout << endl;

    return 0;
}
