#include "mathfuncs.h"
#include <boost/rational.hpp>

using std::cout;
using std::endl;

int main(int argc, char **argv)
{
    boost::rational<int> x0(1, 2);

    cout << "Differentiation with rational types around the point: "<< x0 << endl;

    cout << endl << str_f0 << endl;
    cout << f0(x0) << endl;
    cout << endl;

    return 0;
}
