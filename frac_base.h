#ifndef _XFRACTION_FRAC_BASE_H_
#define _XFRACTION_FRAC_BASE_H_

#include <utility>
#include <iostream>
#include <vector>
#include "utility.h"

#if !defined(XFRACTION_AUTO_REDUCE)
#define XFRACTION_AUTO_REDUCE 1
#endif

using namespace std;

namespace fraction{
    template <class Type>
    class frac_base{
    public:
        constexpr frac_base(const Type &num = 0,
                            const Type &den = 1)
            :m_num(num * sign(den)),
             m_den(abs(den)){
            m_auto_reduce();     
        }
        frac_base(double ratio){
            std::vector<Type> sequence;
            sequence.push_back(static_cast<Type>(ratio));
            ratio = 1.0 / (ratio - sequence.back());
            for(double p0 = 1,q0 = 0,
                       p1 = sequence.back(),q1 = 1,
                       p2,q2,
                       err    = ratio - p1;
                !float_equal_zero(err);){
                sequence.push_back(static_cast<Type>(ratio));
                if(float_equal_zero(ratio - sequence.back())){
                    break;
                }
                ratio = 1.0 / (ratio - sequence.back());
                p2 = sequence.back() * p1 + p0;
                q2 = sequence.back() * q1 + q0;
                err = p2 / q2 - p1 / q1;
                p0 = p1;q0 = q1;
                p1 = p2;q1 = q2;
            }
            *this = frac_base<Type>(sequence.back(),1);
            for(auto itr = sequence.rbegin() + 1;itr != sequence.rend(); ++itr){
                *this = frac_base<Type>(*itr,1) + this->reciprocal();
            }
        }
        ~frac_base() noexcept = default;
        
        frac_base<Type> &operator=(double ratio){
            return (*this = frac_base<Type>(ratio));
        }
        
        Type &num()noexcept{
            return m_num;
        }
        const Type &num()const noexcept{
            return m_num;
        }
        Type &den()noexcept{
            return m_den;
        }
        const Type &den()const noexcept{
            return m_den;
        }
           
        frac_base<Type> &operator+=(const frac_base<Type> &rhs){
            Type l = lcm(m_den,rhs.m_den);
            m_num = m_num * l / m_den + rhs.m_num * l / rhs.m_den;
            m_den = l;
            m_auto_reduce();
            return *this;
        }
        frac_base<Type> &operator-=(const frac_base<Type> &rhs){
            Type l = lcm(m_den,rhs.m_den);
            m_num = m_num * l / m_den - rhs.m_num * l / rhs.m_den;
            m_den = l;
            m_auto_reduce();
            return *this;
        }
        frac_base<Type> &operator*=(const frac_base<Type> &rhs){
            m_num *= rhs.m_num;
            m_den *= rhs.m_den;
            m_auto_reduce();
            return *this;
        }
        frac_base<Type> &operator/=(const frac_base<Type> &rhs){
            return (*this *= rhs.reciprocal());
        }
        
        template<class RType>
        frac_base<Type> &operator+=(const RType &rhs)noexcept{
            return *this += frac_base<Type>(rhs);
        }
        template<class RType>
        frac_base<Type> &operator-=(const RType &rhs)noexcept{
            return *this -= frac_base<Type>(rhs);
        }
        template<class RType>
        frac_base<Type> &operator*=(const RType &rhs)noexcept{
            return *this *= frac_base<Type>(rhs);
        }
        template<class RType>
        frac_base<Type> &operator/=(const RType &rhs)noexcept{
            return *this /= frac_base<Type>(rhs);
        }
        
        frac_base<Type> operator+(const frac_base<Type> &rhs)const noexcept{
            auto tmp = *this;
            tmp += rhs;
            return tmp;
        }
        frac_base<Type> operator-(const frac_base<Type> &rhs)const noexcept{
            auto tmp = *this;
            tmp -= rhs;
            return tmp;
        }
        frac_base<Type> operator*(const frac_base<Type> &rhs)const noexcept{
            auto tmp = *this;
            tmp *= rhs;
            return tmp;
        }
        frac_base<Type> operator/(const frac_base<Type> &rhs)const noexcept{
            auto tmp = *this;
            tmp /= rhs;
            return tmp;
        }
        frac_base<Type> operator-()const noexcept{
            return frac_base<Type>(-m_num,m_den);
        }
        
        template<class RType>
        frac_base<Type> operator+(const RType &rhs)const noexcept{
            return (*this + frac_base<Type>(rhs));
        }
        template<class RType>
        frac_base<Type> operator-(const RType &rhs)const noexcept{
            return (*this - frac_base<Type>(rhs));
        }
        template<class RType>
        frac_base<Type> operator*(const RType &rhs)const noexcept{
            return (*this * frac_base<Type>(rhs));
        }
        template<class RType>
        frac_base<Type> operator/(const RType &rhs)const noexcept{
            return (*this / frac_base<Type>(rhs));
        }
        
        frac_base<Type> reciprocal()const noexcept{
            return frac_base<Type>(m_den,m_num);
        }
        
        frac_base<Type> reduce()const noexcept{
            Type g = gcd(abs(m_num),m_den);
            return frac_base<Type>(m_num / g,m_den / g);
        }
        
        bool is_integer()const noexcept{
            #if XFRACTION_AUTO_REDUCE
                return m_den == 1;
            #else
                return this->reduce().den() == 1;
            #endif
        }
        
        bool is_proper()const noexcept{
            return abs(m_num) < m_den;
        }
        bool is_improper()const noexcept{
            return !is_proper();
        }
        
        bool operator==(const frac_base<Type> &rhs)const noexcept{
            #if XFRACTION_AUTO_REDUCE
                return m_num == rhs.m_num && m_den == rhs.m_den;
            #else
                auto tmp = reduce();
                return tmp.m_num == rhs.m_num && tmp.m_den == rhs.m_den; 
            #endif
        }
        bool operator!=(const frac_base<Type> &rhs)const noexcept{
            return !(*this == rhs);
        }
        bool operator<=(const frac_base<Type> &rhs)const noexcept{
            Type l = lcm(m_den,rhs.m_den);
            return (m_num * l / m_den) <= (rhs.m_num * l / rhs.m_den);
        }
        bool operator>=(const frac_base<Type> &rhs)const noexcept{
            Type l = lcm(m_den,rhs.m_den);
            return (m_num * l / m_den) >= (rhs.m_num * l / rhs.m_den);
        }
        bool operator<(const frac_base<Type> &rhs)const noexcept{
            Type l = lcm(m_den,rhs.m_den);
            return (m_num * l / m_den) < (rhs.m_num * l / rhs.m_den);
        }
        bool operator>(const frac_base<Type> &rhs)const noexcept{
            Type l = lcm(m_den,rhs.m_den);
            return (m_num * l / m_den) > (rhs.m_num * l / rhs.m_den);
        }
        
        template <class RType>
        bool operator<(const RType &rhs)const noexcept{
            return *this < frac_base<Type>(rhs);
        }
        template <class RType>
        bool operator<=(const RType &rhs)const noexcept{
            return *this <= frac_base<Type>(rhs);
        }
        template <class RType>
        bool operator>(const RType &rhs)const noexcept{
            return *this > frac_base<Type>(rhs);
        }
        template <class RType>
        bool operator>=(const RType &rhs)const noexcept{
            return *this >= frac_base<Type>(rhs);
        }
        template <class RType>
        bool operator==(const RType &rhs)const noexcept{
            return *this == frac_base<Type>(rhs);
        }
        template <class RType>
        bool operator!=(const RType &rhs)const noexcept{
            return *this != frac_base<Type>(rhs);
        }
        
        operator double()const noexcept{
            return static_cast<double>(m_num) / static_cast<double>(m_den);
        }
        
        friend std::ostream &operator<<(std::ostream &os,const frac_base<Type> &f){
            os << f.m_num;
            if(f.m_den != 1)
                os << '/' << f.m_den;
            return os;
        }
    protected:
    private:
        Type m_num;
        Type m_den;
        
        void m_auto_reduce(){
            #if XFRACTION_AUTO_REDUCE
            Type g = gcd(abs(m_num),m_den);
            m_num /= g;m_den /= g;
            #endif
        }
    };
    
    
    using frac = frac_base<int>;
    using fraci = frac_base<int>;
    using fracl = frac_base<long>;
    using fracll = frac_base<long long>;
}

#endif //_XFRACTION_FRAC_BASE_H_
