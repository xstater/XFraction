#include <iostream>
#include "utility.h"
#include "frac_base.h"

using namespace std;
using namespace fraction;

int main(){
    cout << gcd(11,8) << endl;
    cout << -lcm(11,8) << endl;
    cout << frac(1,-4).reciprocal() << endl;
    cout << (frac(12,14) -= frac(-2,7)).reciprocal() << endl;
    cout << -(frac(12,14) / frac(7,-2)) << endl;
    cout << static_cast<double>(frac(-1,3)) << endl;
    cout << (frac(1,3) < 2) << endl;
    return 0;
}
