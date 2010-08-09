#ifndef __UTP_H__
#define __UTP_H__

#include <iostream>   // ostream
#include <iterator>   // ostream_iterator, back_insert_iterator
#include <functional> // plus, minus, multiplies, divides
#include <algorithm>  // copy, transform
#include <vector>     // vector
#include <cassert>    // assert
#include <cmath>      // math functions
#include <tr1/math.h> // more math!

#include "utils.h" // convolve

namespace tada {

    namespace utp {

    // places to search for, for standard math functions
    namespace math {
        using std::floor; using std::ceil;

        using std::sqrt; using std::exp; using std::log;

        using std::sin; using std::cos; using std::tan;
        using std::asin; using std::acos; using std::atan;
        using std::sinh; using std::cosh; using std::tanh;
        using std::tr1::asinh; using std::tr1::acosh; using std::tr1::atanh;
    }

    /*
    * Implements the arithmetic for the truncated univariate
    * Taylor series using a scalar type parameter T
    */
    template<class T>
    class UTP
    {
    public:

        UTP(const typename std::vector<T>::size_type length);
        UTP(const typename std::vector<T>::size_type length, const T value);
        UTP(const UTP<T>& other);
        UTP(const T* begin, const T* end);

        typename std::vector<T>::size_type length() const {
            return coeff.size();
        }

        friend std::ostream& operator<<(std::ostream& out, const UTP<T>& utp)
        {
            out << "(";
            std::copy(utp.coeff.begin(), utp.coeff.end(), std::ostream_iterator<T>(out, ", "));
            out << "\b\b)";
            return out;
        }

        UTP<T>& operator=(const UTP<T>& other);

        /*
        * Get/Set Methods
        */
        const T& operator[](const typename std::vector<T>::size_type index) const {
            assert(index >=0 && index < coeff.size());
            return coeff[index];
        }
        void set(const typename std::vector<T>::size_type index, const T& value) {
            assert(index >=0 && index < coeff.size());
            coeff[index] = value;
        }

		// relational operators
		template<class U> friend const bool operator==(const UTP<U>& lhs, const UTP<U>& rhs);
		template<class U> friend const bool operator!=(const UTP<U>& lhs, const UTP<U>& rhs);
		template<class U> friend const bool operator< (const UTP<U>& lhs, const UTP<U>& rhs);
		template<class U> friend const bool operator> (const UTP<U>& lhs, const UTP<U>& rhs);
		template<class U> friend const bool operator<=(const UTP<U>& lhs, const UTP<U>& rhs);
		template<class U> friend const bool operator>=(const UTP<U>& lhs, const UTP<U>& rhs);

		template<class U> friend const bool operator==(U lhs, const UTP<U>& rhs);
		template<class U> friend const bool operator!=(U lhs, const UTP<U>& rhs);
		template<class U> friend const bool operator< (U lhs, const UTP<U>& rhs);
		template<class U> friend const bool operator> (U lhs, const UTP<U>& rhs);
		template<class U> friend const bool operator<=(U lhs, const UTP<U>& rhs);
		template<class U> friend const bool operator>=(U lhs, const UTP<U>& rhs);

		template<class U> friend const bool operator==(const UTP<U>& lhs, U rhs);
		template<class U> friend const bool operator!=(const UTP<U>& lhs, U rhs);
		template<class U> friend const bool operator< (const UTP<U>& lhs, U rhs);
		template<class U> friend const bool operator> (const UTP<U>& lhs, U rhs);
		template<class U> friend const bool operator<=(const UTP<U>& lhs, U rhs);
		template<class U> friend const bool operator>=(const UTP<U>& lhs, U rhs);

        // unary operators
        template<class U> friend const UTP<U> operator+(const UTP<U>& a);
        template<class U> friend const UTP<U> operator-(const UTP<U>& a);

        // binary operators for vconst ector types UTP<U>
        template<class U> friend const UTP<U> operator+(const UTP<U>& lhs, const UTP<U>& rhs);
        template<class U> friend const UTP<U> operator-(const UTP<U>& lhs, const UTP<U>& rhs);
        template<class U> friend const UTP<U> operator*(const UTP<U>& lhs, const UTP<U>& rhs);
        template<class U> friend const UTP<U> operator/(const UTP<U>& lhs, const UTP<U>& rhs);

        // binary operators for sconst calar types U
        template<class U> friend const UTP<U> operator+(const UTP<U>& lhs, const U rhs);
        template<class U> friend const UTP<U> operator-(const UTP<U>& lhs, const U rhs);
        template<class U> friend const UTP<U> operator*(const UTP<U>& lhs, const U rhs);
        template<class U> friend const UTP<U> operator/(const UTP<U>& lhs, const U rhs);

        template<class U> friend const UTP<U> operator+(const UTP<U>& lhs, const UTP<U>& rhs);
        template<class U> friend const UTP<U> operator+(const U lhs, const UTP<U>& rhs);
        template<class U> friend const UTP<U> operator-(const U lhs, const UTP<U>& rhs);
        template<class U> friend const UTP<U> operator*(const U lhs, const UTP<U>& rhs);
        template<class U> friend const UTP<U> operator/(const U lhs, const UTP<U>& rhs);

        // combined assignment operators
        template<class U> friend UTP<U>& operator+=(const UTP<U>& lhs, const UTP<U>& rhs);
        template<class U> friend UTP<U>& operator-=(const UTP<U>& lhs, const UTP<U>& rhs);
        template<class U> friend UTP<U>& operator*=(const UTP<U>& lhs, const UTP<U>& rhs);
        template<class U> friend UTP<U>& operator/=(const UTP<U>& lhs, const UTP<U>& rhs);

        template<class U> friend UTP<U>& operator+=(const UTP<U>& lhs, const U rhs);
        template<class U> friend UTP<U>& operator-=(const UTP<U>& lhs, const U rhs);
        template<class U> friend UTP<U>& operator*=(const UTP<U>& lhs, const U rhs);
        template<class U> friend UTP<U>& operator/=(const UTP<U>& lhs, const U rhs);

        // <math.h> functions (except for dlexp, frexp, modf and fmod)
        template<class U> friend const UTP<U> exp(const UTP<U>& a);
        template<class U> friend const UTP<U> log(const UTP<U>& a);
        template<class U> friend const UTP<U> log10(const UTP<U>& a);

        template<class U> friend const UTP<U> sin(const UTP<U>& a);
        template<class U> friend const UTP<U> cos(const UTP<U>& a);
        template<class U> friend const UTP<U> tan(const UTP<U>& a);
        template<class U> friend const UTP<U> asin(const UTP<U>& a);
        template<class U> friend const UTP<U> acos(const UTP<U>& a);
        template<class U> friend const UTP<U> atan(const UTP<U>& a);
        template<class U> friend const UTP<U> sinh(const UTP<U>& a);
        template<class U> friend const UTP<U> cosh(const UTP<U>& a);
        template<class U> friend const UTP<U> tanh(const UTP<U>& a);
        template<class U> friend const UTP<U> asinh(const UTP<U>& a);
        template<class U> friend const UTP<U> acosh(const UTP<U>& a);
        template<class U> friend const UTP<U> atanh(const UTP<U>& a);

        template<class U> friend const UTP<U> sqrt(const UTP<U>& a);
        template<class U> friend const UTP<U> pow(const UTP<U>&, const UTP<U>& a);
        template<class U> friend const UTP<U> pow(const UTP<U>&, const U& a);
        template<class U> friend const UTP<U> pow(const U&, const UTP<U>& a);

        template<class U> friend const UTP<U> fabs(const UTP<U>& a);
        template<class U> friend const UTP<U> ceil(const UTP<U>& a);
        template<class U> friend const UTP<U> floor(const UTP<U>& a);

    private:
        std::vector<T> coeff; // taylor coefficients
    };


    /*
    * Constructors
    */
    template<class T>
    UTP<T>::UTP(const typename std::vector<T>::size_type length)
    {
        assert(length >= 1);
        coeff.assign(length, T(0.0));
    }

    template<class T>
    UTP<T>::UTP(const typename std::vector<T>::size_type length, const T value)
    {
        assert(length >= 1);
        coeff.assign(length, T(0.0));
        coeff[0] = value;
    }

    template<class T>
    UTP<T>::UTP(const UTP<T>& other)
    {
        *this = other;
    }

    template<class T>
    UTP<T>::UTP(const T* begin, const T* end)
    {
        assert(end > begin);
        coeff.reserve(end - begin);
        std::copy(begin, end, std::back_insert_iterator< std::vector<T> >(coeff));
    }

    /*
    * Assignment Operator: =
    */
    template<class T>
    UTP<T>& UTP<T>::operator=(const UTP<T>& other)
    {
        coeff = other.coeff;
        return *this;
    }

    /* define the friend methods */

    // relational operators
    template<class T> const bool operator==(const UTP<T>& lhs, const UTP<T>& rhs) { return lhs.coeff[0] == rhs.coeff[0]; }
    template<class T> const bool operator!=(const UTP<T>& lhs, const UTP<T>& rhs) { return lhs.coeff[0] != rhs.coeff[0]; }
    template<class T> const bool operator< (const UTP<T>& lhs, const UTP<T>& rhs) { return lhs.coeff[0] <  rhs.coeff[0]; }
    template<class T> const bool operator> (const UTP<T>& lhs, const UTP<T>& rhs) { return lhs.coeff[0] >  rhs.coeff[0]; }
    template<class T> const bool operator<=(const UTP<T>& lhs, const UTP<T>& rhs) { return lhs.coeff[0] <= rhs.coeff[0]; }
    template<class T> const bool operator>=(const UTP<T>& lhs, const UTP<T>& rhs) { return lhs.coeff[0] >= rhs.coeff[0]; }

    template<class T> const bool operator==(T lhs, const UTP<T>& rhs) { return lhs == rhs.coeff[0]; }
    template<class T> const bool operator!=(T lhs, const UTP<T>& rhs) { return lhs != rhs.coeff[0]; }
    template<class T> const bool operator< (T lhs, const UTP<T>& rhs) { return lhs <  rhs.coeff[0]; }
    template<class T> const bool operator> (T lhs, const UTP<T>& rhs) { return lhs >  rhs.coeff[0]; }
    template<class T> const bool operator<=(T lhs, const UTP<T>& rhs) { return lhs <= rhs.coeff[0]; }
    template<class T> const bool operator>=(T lhs, const UTP<T>& rhs) { return lhs >= rhs.coeff[0]; }

    template<class T> const bool operator==(const UTP<T>& lhs, T rhs) { return lhs.coeff[0] == rhs; }
    template<class T> const bool operator!=(const UTP<T>& lhs, T rhs) { return lhs.coeff[0] != rhs; }
    template<class T> const bool operator< (const UTP<T>& lhs, T rhs) { return lhs.coeff[0] <  rhs; }
    template<class T> const bool operator> (const UTP<T>& lhs, T rhs) { return lhs.coeff[0] >  rhs; }
    template<class T> const bool operator<=(const UTP<T>& lhs, T rhs) { return lhs.coeff[0] <= rhs; }
    template<class T> const bool operator>=(const UTP<T>& lhs, T rhs) { return lhs.coeff[0] >= rhs; }

    /* unary operators: +, - */
    template<class T> const UTP<T> operator+(const UTP<T>& a) { return a; }
    template<class T> const UTP<T> operator-(const UTP<T>& a)
    {
        UTP<T> temp(a.length());
        std::transform(a.coeff.begin(), a.coeff.end(), temp.coeff.begin(), bind1st(std::multiplies<T>(), -1));
        return temp;
    }

    /* binary operators: +, -, *, / */
    template<class T> const UTP<T> operator+(const UTP<T>& lhs, const UTP<T>& rhs)
    {
        assert(lhs.length() == rhs.length());
        UTP<T> temp(lhs.length());
        std::transform(lhs.coeff.begin(), lhs.coeff.end(), rhs.coeff.begin(), temp.coeff.begin(), std::plus<T>());
        return temp;
    }

    template<class T> const UTP<T> operator-(const UTP<T>& lhs, const UTP<T>& rhs)
    {
        assert(lhs.length() == rhs.length());
        UTP<T> temp(lhs.length());
        std::transform(lhs.coeff.begin(), lhs.coeff.end(), rhs.coeff.begin(), temp.coeff.begin(), std::minus<T>());
        return temp;
    }

    template<class T> const UTP<T> operator*(const UTP<T>& lhs, const UTP<T>& rhs)
    {
        assert(lhs.length() == rhs.length());
        UTP<T> temp(lhs.length());
        for (typename std::vector<T>::size_type k = 0; k < lhs.length(); ++k)
            temp.coeff[k] = utils::convolve(lhs.coeff.begin(), rhs.coeff.begin(), k, T(0.0));
        return temp;
    }

    template<class T> const UTP<T> operator/(const UTP<T>& lhs, const UTP<T>& rhs)
    {
        assert(lhs.length() == rhs.length());
        UTP<T> temp(lhs.length());
        for (typename std::vector<T>::size_type k = 0; k < lhs.length(); ++k)
            temp.coeff[k] = (T(1.0)/rhs.coeff[0]) * (lhs.coeff[k] - utils::convolve(temp.coeff.begin(), rhs.coeff.begin(), k, T(0.0)));
        return temp;
    }

    template<class T> const UTP<T> operator+(const UTP<T>& lhs, const T rhs)
    {
        UTP<T> temp(lhs);
        temp.coeff[0] = temp.coeff[0] + rhs;
        return temp;
    }

    template<class T> const UTP<T> operator-(const UTP<T>& lhs, const T rhs)
    {
        UTP<T> temp(lhs);
        temp.coeff[0] = temp.coeff[0] - rhs;
        return temp;
    }

    template<class T> const UTP<T> operator*(const UTP<T>& lhs, const T rhs)
    {
        UTP<T> temp(lhs);
        std::transform(lhs.coeff.begin(), lhs.coeff.end(), temp.coeff.begin(), bind2nd(std::multiplies<T>(), rhs));
        return temp;
    }

    template<class T> const UTP<T> operator/(const UTP<T>& lhs, const T rhs)
    {
        UTP<T> temp(lhs);
        std::transform(lhs.coeff.begin(), lhs.coeff.end(), temp.coeff.begin(), bind2nd(std::divides<T>(), rhs));
        return temp;
    }

    template<class T> const UTP<T> operator+(const T lhs, const UTP<T>& rhs) { return rhs + lhs; }
    template<class T> const UTP<T> operator-(const T lhs, const UTP<T>& rhs) { return -rhs + lhs; }
    template<class T> const UTP<T> operator*(const T lhs, const UTP<T>& rhs) { return rhs * lhs; }
    template<class T> const UTP<T> operator/(const T lhs, const UTP<T>& rhs) { return UTP<T>(rhs.length(), lhs) / rhs; }

    /* combined assignment operators */
    template<class T> UTP<T>& operator+=(const UTP<T>& lhs, const UTP<T>& rhs) { return lhs = lhs + rhs; }
    template<class T> UTP<T>& operator-=(const UTP<T>& lhs, const UTP<T>& rhs) { return lhs = lhs - rhs; }
    template<class T> UTP<T>& operator*=(const UTP<T>& lhs, const UTP<T>& rhs) { return lhs = lhs * rhs; }
    template<class T> UTP<T>& operator/=(const UTP<T>& lhs, const UTP<T>& rhs) { return lhs = lhs / rhs; }

    template<class T> UTP<T>& operator+=(const UTP<T>& lhs, const T rhs) { return lhs = lhs + rhs;}
    template<class T> UTP<T>& operator-=(const UTP<T>& lhs, const T rhs) { return lhs = lhs - rhs;}
    template<class T> UTP<T>& operator*=(const UTP<T>& lhs, const T rhs) { return lhs = lhs * rhs;}
    template<class T> UTP<T>& operator/=(const UTP<T>& lhs, const T rhs) { return lhs = lhs / rhs;}

    template<class T> const UTP<T> fabs (const UTP<T>& a)
    {
        return (a.coeff[0] > 0) ? a : -a;
    }

    template<class T> const UTP<T> ceil (const UTP<T>& a)
    {
        using math::ceil;

        return UTP<T>(a.length(), ceil(a.coeff[0]));
    }

    template<class T> const UTP<T> floor(const UTP<T>& a)
    {
        using math::floor;

        return UTP<T>(a.length(), floor(a.coeff[0]));
    }

    template<class T> const UTP<T> sin(const UTP<T>& a)
    {
        using math::sin;
        using math::cos;

        UTP<T> u(a.length()), v(a.length());

        // u' =  va' (u = sin(a))
        // v' = -ua' (v = cos(a))
        u.set(0, sin(a[0])); v.set(0, cos(a[0]));
        tada::utils::solve_simul(u.coeff.begin(),  T(1.0), a.coeff.begin(), v.coeff.begin(),
                                 v.coeff.begin(), T(-1.0), a.coeff.begin(), u.coeff.begin(),
                                 u.length() ,  1);

        return u;
    }

    template<class T> const UTP<T> cos(const UTP<T>& a)
    {
        using math::sin;
        using math::cos;

        UTP<T> u(a.length()), v(a.length());

        // u' =  va' (u = sin(a))
        // v' = -ua' (v = cos(a))
        u.set(0, sin(a[0])); v.set(0, cos(a[0]));
        tada::utils::solve_simul(u.coeff.begin(),  T(1.0), a.coeff.begin(), v.coeff.begin(),
                                 v.coeff.begin(), T(-1.0), a.coeff.begin(), u.coeff.begin(),
                                 u.length() ,  1);

        return v;
    }

    template<class T> const UTP<T> tan(const UTP<T>& a)
    {
        using math::tan;

        UTP<T> u(a.length()), v(a.length());

        // u' =  va' (u = tan(a))
        // v' = 2uu' (v = 1 + a*a)
        u.set(0, tan(a[0])); v.set(0, T(1.0) + tan(a[0])*tan(a[0]));
        tada::utils::solve_simul(u.coeff.begin(),  T(1.0), a.coeff.begin(), v.coeff.begin(),
                                 v.coeff.begin(),  T(2.0), u.coeff.begin(), u.coeff.begin(),
                                 u.length() ,  1);

        return u;
    }

    template<class T> const UTP<T> asin(const UTP<T>& a)
    {
        using math::asin;
        using math::sqrt;

        UTP<T> u(a.length()), v(a.length());

        // a' =  vu' (u = asin(a))
        // v' = -au' (v = sqrt(1 - a*a))
        u.set(0, asin(a[0])); v.set(0, sqrt(T(1.0) - a[0]*a[0]));
        tada::utils::solve_simul(u.coeff.begin(),  T(1.0), a.coeff.begin(), v.coeff.begin(),
                                 v.coeff.begin(), T(-1.0), u.coeff.begin(), a.coeff.begin(),
                                 u.length() ,  3);

        return u;
    }

    template<class T> const UTP<T> acos(const UTP<T>& a)
    {
        using math::acos;
        using math::sqrt;

        UTP<T> u(a.length()), v(a.length());

        // a' =  vu' (u = acos(a))
        // v' = -au' (v = -sqrt(1 - a*a))
        u.set(0, acos(a[0])); v.set(0, - sqrt(T(1.0) - a[0]*a[0]));
        tada::utils::solve_simul(u.coeff.begin(),  T(1.0), a.coeff.begin(), v.coeff.begin(),
                                 v.coeff.begin(), T(-1.0), u.coeff.begin(), a.coeff.begin(),
                                 u.length() ,  3);

        return u;
    }

    template<class T> const UTP<T> atan(const UTP<T>& a)
    {
        using math::atan;

        UTP<T> u(a.length()), v(a.length());

        // a' =  vu' (u = atan(a))
        // v' = 2aa' (v = 1 + a*a)
        u.set(0, atan(a[0])); v.set(0, T(1.0) + a[0]*a[0]);
        tada::utils::solve_simul(u.coeff.begin(),  T(1.0), a.coeff.begin(), v.coeff.begin(),
                                 v.coeff.begin(),  T(2.0), a.coeff.begin(), a.coeff.begin(),
                                 u.length() ,  3);

        return u;
    }

    template<class T> const UTP<T> sinh(const UTP<T>& a)
    {
        using math::sinh;
        using math::cosh;

        UTP<T> u(a.length()), v(a.length());

        // u' = va' (u = sinh(a))
        // v' = ua' (v = cosh(a))
        u.set(0, sinh(a[0])); v.set(0, cosh(a[0]));
        tada::utils::solve_simul(u.coeff.begin(),  T(1.0), a.coeff.begin(), v.coeff.begin(),
                                 v.coeff.begin(),  T(1.0), a.coeff.begin(), u.coeff.begin(),
                                 u.length() ,  1);

        return u;
    }

    template<class T> const UTP<T> cosh(const UTP<T>& a)
    {
        using math::sinh;
        using math::cosh;

        UTP<T> u(a.length()), v(a.length());

        // u' = va' (u = sinh(a))
        // v' = ua' (v = cosh(a))
        u.set(0, sinh(a[0])); v.set(0, cosh(a[0]));
        tada::utils::solve_simul(u.coeff.begin(),  T(1.0), a.coeff.begin(), v.coeff.begin(),
                                 v.coeff.begin(),  T(1.0), a.coeff.begin(), u.coeff.begin(),
                                 u.length() ,  1);

        return v;
    }

    template<class T> const UTP<T> tanh(const UTP<T>& a)
    {
        using math::tanh;

        UTP<T> u(a.length()), v(a.length());

        // u' =   va' (u = tanh(a))
        // v' = -2uu' (v = 1 - u*u)
        u.set(0, tanh(a[0])); v.set(0, T(1.0) - u[0]*u[0]);
        tada::utils::solve_simul(u.coeff.begin(),  T(1.0), a.coeff.begin(), v.coeff.begin(),
                                 v.coeff.begin(), T(-2.0), u.coeff.begin(), u.coeff.begin(),
                                 u.length() ,  1);

        return u;
    }

    template<class T> const UTP<T> asinh(const UTP<T>& a)
    {
        using math::asinh;
        using math::sqrt;

        UTP<T> u(a.length()), v(a.length());

        // a' = vu' (u = asinh(a))
        // v' = au' (v = sqrt(1 + a*a))
        u.set(0, asinh(a[0])); v.set(0, sqrt(T(1.0) + a[0]*a[0]));
        tada::utils::solve_simul(u.coeff.begin(),  T(1.0), a.coeff.begin(), v.coeff.begin(),
                                 v.coeff.begin(),  T(1.0), u.coeff.begin(), a.coeff.begin(),
                                 u.length() ,  3);

        return u;
    }

    template<class T> const UTP<T> acosh(const UTP<T>& a)
    {
        using math::acosh;
        using math::sqrt;

        UTP<T> u(a.length()), v(a.length());

        // a' = vu' (u = acosh(a))
        // v' = au' (v = sqrt(a*a - 1))
        u.set(0, acosh(a[0])); v.set(0, sqrt(a[0]*a[0] - T(1.0)));
        tada::utils::solve_simul(u.coeff.begin(),  T(1.0), a.coeff.begin(), v.coeff.begin(),
                                 v.coeff.begin(),  T(1.0), u.coeff.begin(), a.coeff.begin(),
                                 u.length() ,  3);

        return u;
    }

    template<class T> const UTP<T> atanh(const UTP<T>& a)
    {
        using math::atanh;

        UTP<T> u(a.length()), v(a.length());

        // a' =   vu' (u = atanh(a))
        // v' = -2aa' (v = 1 - a*a)
        u.set(0, atanh(a[0])); v.set(0, T(1.0) - a[0]*a[0]);
        tada::utils::solve_simul(u.coeff.begin(),  T(1.0), a.coeff.begin(), v.coeff.begin(),
                                 v.coeff.begin(), T(-2.0), a.coeff.begin(), a.coeff.begin(),
                                 u.length() ,  3);

        return u;
    }

    template<class T> const UTP<T> exp(const UTP<T>& a)
    {
        using math::exp;

        UTP<T> u(a.length());

        // u' = ua (u = exp(a))
        u.set(0, exp(a.coeff[0]));
        tada::utils::solve_ueqva(u.coeff.begin(), a.coeff.begin(), u.coeff.begin(), a.length(), T(0.0));

        return u;
    }

    template<class T> const UTP<T> log(const UTP<T>& a)
    {
        using math::log;

        UTP<T> u(a.length());

        // a' = au' (u = log(a))
        u.set(0, log(a.coeff[0]));
        tada::utils::solve_aeqvu(u.coeff.begin(), a.coeff.begin(), a.coeff.begin(), a.length(), T(0.0));

        return u;
    }

    template<class T> const UTP<T> log10(const UTP<T>& a)
    {
        using math::log;

        return log(a)/log(T(10.0));
    }

    template<class T> const UTP<T> pow(const UTP<T>&, const UTP<T>& a);
    template<class T> const UTP<T> pow(const UTP<T>&, const T& a);
    template<class T> const UTP<T> pow(const T&, const UTP<T>& a);
    template<class T> const UTP<T> atan2(const UTP<T>&, const UTP<T>& a);
    template<class T> const UTP<T> sqrt(const UTP<T>& a);

    } // namespace utp

} // namespace tada

#endif /* __UTP_H__ */
