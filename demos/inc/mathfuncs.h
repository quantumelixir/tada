#include "tada.h"
#include <iostream>

static const std::string str_f0("x/(1 - x + x*x)");
template<class T>
tada::utp::UTP<T> f0(T x0, unsigned int N = 5)
{
    tada::utp::UTP<T> x(N);
    x.set(0, x0);
    x.set(1, T(1.0));
    return x/(T(1.0) - x + x*x);
}

static const std::string str_f1("x*sin(x)/(1 + exp(x))");
template<class T>
tada::utp::UTP<T> f1(T x0, unsigned int N = 5)
{
    tada::utp::UTP<T> x(N);
    x.set(0, x0);
    x.set(1, T(1.0));
    return x*sin(x)/(T(1.0) + exp(x));
}

static const std::string str_f2("log(x)*tan(x) + asin(1/(1 + cosh(x)))");
template<class T>
tada::utp::UTP<T> f2(T x0, unsigned int N = 5)
{
    tada::utp::UTP<T> x(N);
    x.set(0, x0);
    x.set(1, T(1.0));
    return log(x)*tan(x) + asin(T(1.0)/(T(1.0) + cosh(x)));
}

static const std::string str_f3("sin(x*x)/(1 + log(x)) + " \
                           "asin(1/(1 + cosh(x)*tanh(x)))");
template<class T>
tada::utp::UTP<T> f3(T x0, unsigned int N = 5)
{
    tada::utp::UTP<T> x(N);
    x.set(0, x0);
    x.set(1, T(1.0));
    return sin(x*x)/(T(1.0) + log(x)) + asin(T(1.0)/(T(1.0) + cosh(x)*tanh(x)));
}
