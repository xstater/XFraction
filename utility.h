#ifndef _XFRACTION_UTILITY_H_
#define _XFRACTION_UTILITY_H_

#include <utility>

#include <iostream>
using namespace std;

namespace fraction{
    template <class Type>
    constexpr int sign(const Type &value){
        return value < 0 ? -1 : 1;
    }
    template <class Type>
    constexpr Type abs(const Type &value){
        return value < 0 ? -value : value;
    }
    
    template <class Type>
    constexpr Type gcd(const Type &a,const Type &b){
        return b == 0 ? a : gcd(b,a % b);
    }
    
    template <class Type>
    constexpr Type lcm(const Type &a,const Type &b){
        return a * b / gcd(a,b);
    }
}

#endif //_XFRACTION_UTILITY_H_
