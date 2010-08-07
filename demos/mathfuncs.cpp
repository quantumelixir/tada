#include <iostream>
#include <iomanip>

#include "mathfuncs.h"

using namespace std;

int main(int argc, char **argv)
{
    double x0 = 0.5;

    cout << fixed << setprecision(20);
    std::cout << "Single and Double Precision" << std::endl;

    cout << endl << str_f0 << endl;
    cout << "Single precision: " << f0(float(x0)) << endl;
    cout << "Double precision: " << f0(double(x0)) << endl;

    cout << endl << str_f1 << endl;
    cout << "Single precision: " << f1(float(x0)) << endl;
    cout << "Double precision: " << f1(double(x0)) << endl;

    cout << endl << str_f2 << endl;
    cout << "Single precision: " << f2(float(x0)) << endl;
    cout << "Double precision: " << f2(double(x0)) << endl;

    cout << endl << str_f3 << endl;
    cout << "Single precision: " << f3(float(x0)) << endl;
    cout << "Double precision: " << f3(double(x0)) << endl;

    return 0;
}
