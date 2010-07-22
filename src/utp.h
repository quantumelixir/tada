#ifndef __UTP_H__
#define __UTP_H__

#include <iostream>   // ostream
#include <iterator>   // ostream_iterator, back_insert_iterator
#include <functional> // plus, minus, multiplies, divides
#include <algorithm>  // copy, transform
#include <vector>     // vector
#include <cassert>    // assert

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
        UTP();

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
        T& operator[](const typename std::vector<T>::size_type index);

        UTP<T> operator+() const;
        UTP<T> operator-() const;

        UTP<T> operator+(const UTP<T>& other) const;
        UTP<T> operator-(const UTP<T>& other) const;
        UTP<T> operator*(const UTP<T>& other) const;
        UTP<T> operator/(const UTP<T>& other) const;

        UTP<T> operator+(const T other) const;
        UTP<T> operator-(const T other) const;
        UTP<T> operator*(const T other) const;
        UTP<T> operator/(const T other) const;

        UTP<T>& operator+=(const UTP<T>& other);
        UTP<T>& operator-=(const UTP<T>& other);
        UTP<T>& operator*=(const UTP<T>& other);
        UTP<T>& operator/=(const UTP<T>& other);

        UTP<T>& operator+=(const T other);
        UTP<T>& operator-=(const T other);
        UTP<T>& operator*=(const T other);
        UTP<T>& operator/=(const T other);

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
        coeff.assign(length, 0.0);
    }

    template<class T>
    UTP<T>::UTP(const typename std::vector<T>::size_type length, const T value)
    {
        assert(length >= 1);
        coeff.assign(length, value);
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

    template<class T>
    UTP<T>::UTP()
    {
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
    * Unary Operators: +, -
    */
    template<class T>
    UTP<T> UTP<T>::operator+() const
    {
        return *this;
    }

    template<class T>
    UTP<T> UTP<T>::operator-() const
    {
        UTP<T> temp(this->length());
        std::transform(coeff.begin(), coeff.end(), temp.coeff.begin(), bind1st(std::multiplies<T>(), -1));
        return temp;
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

    /*
    * Binary Operators: +, -, *, /
    */
    template<class T>
    UTP<T> UTP<T>::operator+(const UTP<T>& other) const
    {
        assert(this->length() == other.length());
        UTP<T> temp(this->length());
        std::transform(coeff.begin(), coeff.end(), other.coeff.begin(), temp.coeff.begin(), std::plus<T>());
        return temp;
    }

    template<class T>
    UTP<T> UTP<T>::operator-(const UTP<T>& other) const
    {
        assert(this->length() == other.length());
        UTP<T> temp(this->length());
        std::transform(coeff.begin(), coeff.end(), other.coeff.begin(), temp.coeff.begin(), std::minus<T>());
        return temp;
    }

    template<class T>
    UTP<T> UTP<T>::operator*(const UTP<T>& other) const
    {
        assert(this->length() == other.length());
        UTP<T> temp(this->length());
        for (typename std::vector<T>::size_type k = 0; k < this->length(); ++k) 
            temp.coeff[k] = utils::convolve(coeff.begin(), coeff.begin() + k + 1, other.coeff.begin() + k, 0.0);
        return temp;
    }

    template<class T>
    UTP<T> UTP<T>::operator/(const UTP<T>& other) const
    {
        assert(this->length() == other.length());
        UTP<T> temp(this->length());
        for (typename std::vector<T>::size_type k = 0; k < this->length(); ++k) 
        {
            temp.coeff[k] = (1/other.coeff[0]) * (coeff[k] - utils::convolve(temp.coeff.begin(), temp.coeff.begin() + k, other.coeff.begin() + k, 0.0));
        }
        return temp;
    }

    template<class T>
    UTP<T> UTP<T>::operator+(const T other) const
    {
        UTP<T> temp(*this);
        temp.coeff[0] += other;
        return temp;
    }

    template<class T>
    UTP<T> UTP<T>::operator-(const T other) const
    {
        UTP<T> temp(*this);
        temp.coeff[0] -= other;
        return temp;
    }

    template<class T>
    UTP<T> UTP<T>::operator*(const T other) const
    {
        UTP<T> temp(this->length());
        std::transform(coeff.begin(), coeff.end(), temp.coeff.begin(), bind2nd(std::multiplies<T>(), other));
        return temp;
    }

    template<class T>
    UTP<T> UTP<T>::operator/(const T other) const
    {
        UTP<T> temp(this->length());
        std::transform(coeff.begin(), coeff.end(), temp.coeff.begin(), bind2nd(std::divides<T>(), other));
        return temp;
    }

    /*
    * Combined Assignment Operators: +=, -=, *=, /=
    */
    template<class T>
    UTP<T>& UTP<T>::operator+=(const UTP<T>& other)
    {
        *this = *this + other;
        return *this;
    }

    template<class T>
    UTP<T>& UTP<T>::operator-=(const UTP<T>& other)
    {
        *this = *this - other;
        return *this;
    }

    template<class T>
    UTP<T>& UTP<T>::operator*=(const UTP<T>& other)
    {
        *this = *this * other;
        return *this;
    }

    template<class T>
    UTP<T>& UTP<T>::operator/=(const UTP<T>& other)
    {
        *this = *this / other;
        return *this;
    }

    template<class T>
    UTP<T>& UTP<T>::operator+=(const T other)
    {
        *this = *this + other;
        return *this;
    }

    template<class T>
    UTP<T>& UTP<T>::operator-=(const T other)
    {
        *this = *this - other;
        return *this;
    }

    template<class T>
    UTP<T>& UTP<T>::operator*=(const T other)
    {
        *this = *this * other;
        return *this;
    }

    template<class T>
    UTP<T>& UTP<T>::operator/=(const T other)
    {
        *this = *this / other;
        return *this;
    }

    /*
    * Binary Operators: +, -, *, / (for non UTP objects on LHS)
    */

    template<class T>
    UTP<T> operator+(const T lhs, const UTP<T>& rhs)
    {
        UTP<T> temp(rhs);
        temp += lhs;
        return temp;
    }

    template<class T>
    UTP<T> operator-(const T lhs, const UTP<T>& rhs)
    {
        UTP<T> temp(-rhs);
        temp += lhs;
        return temp;
    }

    template<class T>
    UTP<T> operator*(const T lhs, const UTP<T>& rhs)
    {
        UTP<T> temp(rhs);
        temp *= lhs;
        return temp;
    }

    template<class T>
    UTP<T> operator/(const T lhs, const UTP<T>& rhs)
    {
        UTP<T> temp(rhs);
        temp /= lhs;
        return temp;
    }

    }

}

#endif /* __UTP_H__ */
