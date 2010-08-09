#include "mathfuncs.h"
#include "mp_printer.h"
#include "mpreal.h"

using std::cout;
using std::endl;

int main(int argc, char **argv)
{
    mpfr::mpreal::set_default_prec(128);
    mpfr::mpreal x0(0.5);

    cout << "Differentiation with multiprecision types (128-bit) around the point: "<< x0 << endl;

    std::cout << std::endl << str_f0 << std::endl;
    print(f0(x0));
    std::cout << std::endl;

    std::cout << std::endl << str_f1 << std::endl;
    print(f1(x0));
    std::cout << std::endl;

    std::cout << std::endl << str_f2 << std::endl;
    print(f2(x0));
    std::cout << std::endl;

    std::cout << std::endl << str_f3 << std::endl;
    print(f3(x0));
    std::cout << std::endl;

    return 0;
}
