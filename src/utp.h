#ifndef __UTP_H__
#define __UTP_H__

#include <iostream>   // ostream
#include <iterator>   // ostream_iterator, back_insert_iterator
#include <functional> // plus, minus, multiplies, divides
#include <algorithm>  // copy, transform
#include <vector>     // vector
#include <cassert>    // assert
#include <cmath>      // math functions

#include "utils.h" // convolve

namespace tada {

    namespace utp {

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
        template<class U> friend const UTP<U> operator+(const UTP<U>& obj);
        template<class U> friend const UTP<U> operator-(const UTP<U>& obj);

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

        template<class U> friend const UTP<U> fabs(const UTP<U>& obj);
        template<class U> friend const UTP<U> ceil(const UTP<U>& obj);
        template<class U> friend const UTP<U> floor(const UTP<U>& obj);
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
    * Get/Set Method
    */
    template<class T>
    T& UTP<T>::operator[](const typename std::vector<T>::size_type index)
    {
        assert(index >=0 && index < coeff.size());
        return coeff[index];
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
    template<class T> const UTP<T> operator+(const UTP<T>& obj) { return obj; }
    template<class T> const UTP<T> operator-(const UTP<T>& obj)
    {
        UTP<T> temp(obj.length());
        std::transform(obj.coeff.begin(), obj.coeff.end(), temp.coeff.begin(), bind1st(std::multiplies<T>(), -1));
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
            temp.coeff[k] = (1/rhs.coeff[0]) * (lhs.coeff[k] - utils::convolve(temp.coeff.begin(), rhs.coeff.begin(), k, T(0.0)));
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

    template<class T> const UTP<T> fabs (const UTP<T>& obj) { return (obj.coeff[0] > 0) ? obj : -obj; }
    template<class T> const UTP<T> ceil (const UTP<T>& obj) { return UTP<T>(obj.length(), std::ceil(obj.coeff[0])); }
    template<class T> const UTP<T> floor(const UTP<T>& obj) { return UTP<T>(obj.length(), std::floor(obj.coeff[0])); }
    } // namespace utp

} // namespace tada

#endif /* __UTP_H__ */
