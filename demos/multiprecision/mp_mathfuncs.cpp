#include "mathfuncs.h"
#include "mp_printer.h"
#include "mpreal.h"

using mpfr::mpreal;

int main(int argc, char **argv)
{
    double x0 = 0.5;

    mpreal::set_default_prec(128);
    std::cout << "Multiprecision (128-bit)" << std::endl;

    std::cout << std::endl << str_f0 << std::endl;
    print(f0(mpreal(x0)));
    std::cout << std::endl;

    std::cout << std::endl << str_f1 << std::endl;
    print(f1(mpreal(x0)));
    std::cout << std::endl;

    std::cout << std::endl << str_f2 << std::endl;
    print(f2(mpreal(x0)));
    std::cout << std::endl;

    std::cout << std::endl << str_f3 << std::endl;
    print(f3(mpreal(x0)));
    std::cout << std::endl;

    return 0;
}
