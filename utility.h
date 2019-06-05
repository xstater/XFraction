#ifndef _XFRACTION_UTILITY_H_
#define _XFRACTION_UTILITY_H_

#define XFRACTION_EPS 1e-8

namespace fraction{
    template <class Type>
    constexpr int sign(const Type &value)noexcept{
        return value < 0 ? -1 : 1;
    }
    template <class Type>
    constexpr Type abs(const Type &value)noexcept{
        return value < 0 ? -value : value;
    }
    
    template <class Type>
    constexpr Type gcd(const Type &a,const Type &b)noexcept{
        return b == 0 ? a : gcd(b,a % b);
    }
    
    template <class Type>
    constexpr Type lcm(const Type &a,const Type &b)noexcept{
        return a * b / gcd(a,b);
    }

    bool float_equal_zero(double data)noexcept{
        return abs(data) < XFRACTION_EPS;
    }
}

#undef XFRACTION_EPS

#endif //_XFRACTION_UTILITY_H_
