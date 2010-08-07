#include "mpreal.h"
#include <string>

void
print(tada::utp::UTP<mpfr::mpreal> x, std::size_t precision = 0)
{
    if (!precision)
        precision  = mpfr::mpreal::get_default_prec();

    std::cout << "(";
    for (int i = 0; i < x.length(); ++i)
        std::cout << x[i].to_string() << ", ";
    std::cout << "\b\b)";
}
