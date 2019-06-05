#include <iostream>
#include "utility.h"
#include "frac_base.h"

using namespace std;
using namespace fraction;

int main(){
    cout << fraction::gcd(8,12) << endl;
    cout << -lcm(11,8) << endl;
    cout << frac(1,-4).reciprocal() << endl;
    cout << (frac(12,14) -= frac(-2,7)).reciprocal() << endl;
    cout << -(frac(12,14) / frac(7,-2)) << endl;
    cout << static_cast<double>(frac(-1,3)) << endl;
    cout << (frac(1,3) < 2) << endl;
    cout << (frac(1,3) + frac(2,3)).is_integer() << endl;
    cout << frac(3.245) << endl; //3.245 == 649/200
    auto f = frac(3.1415926535897);
    cout << f << endl;
    cout << static_cast<double>(f) << endl;
    return 0;
}
