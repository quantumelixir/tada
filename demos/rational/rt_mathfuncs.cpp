#include "mathfuncs.h"
#include <gmpxx.h>

using std::cout;
using std::endl;

int main(int argc, char **argv)
{
    mpq_class x0(355, 113);

    cout << "Differentiation with rational types around the point: "<< x0 << endl;

    cout << endl << str_f0 << endl;
    cout << f0(x0) << endl;
    cout << endl;

    return 0;
}
