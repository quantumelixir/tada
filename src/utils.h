#ifndef __UTILS_H__
#define __UTILS_H__

#include <cassert>

namespace tada {

    namespace utils {

        // generator to count using type T
        template<class T>
        class Generator
        {
            public:
                Generator() : curr_(T(0.0)), step_(T(1.0)) { }
                Generator(const T& start, const T& step) : curr_(start), step_(step) { }

                const T next() { return (*this)++; } // alias for postfix increment
                const T operator()() { return curr_; } // return current state
                const T operator++() { return curr_ += step_; } // prefix
                const T operator++(int dummy) // postfix
                {
                    T ret = curr_;
                    curr_ += step_;
                    return ret;
                }

            private:
                T curr_;
                T step_;
        };

        // convolve: \sum_{i=0}^{k}  a_i * v_{k-i}
        template <class IterA, class IterB, class IndexType, class T>
            T convolve(IterA a, IterB v, IndexType k, T init)
            {
                assert(k >= 0);

                v = v + k;
                do {
                    init += (*a++) * (*v--);
                } while (k--);
                return init;
            }

        // tilde convolve: \sum_{i=0}^{k} i * a_i * v_{k-i} (skips the last `skiplastn' terms of the convolution)
        template <class IterA, class IterB, class IndexType, class T>
            T tconvolve(IterA a, IterB v, IndexType k, T init, int skiplastn = 0)
            {
                assert(k >= 0);

                v = v + k;
                Generator<T> inc;
                do {
                    init += (inc++) * (*a++) * (*v--);
                } while (k-- - skiplastn > 0);
                return init;
            }

        // solve u' = va' | solves for u (except for the constant term) i.e. n >= 1
        template <class IterA, class IterB, class IndexType, class T>
            void solve_ueqva(IterA u, IterB a, IterB v, IndexType n, T init)
            {
                assert(n >= 1);

                Generator<T> inc;
                IndexType k = 1; // skip the constant term
                while (k < n)
                {
                    ++inc;
                    *++u = tconvolve(a, v, k, init) / inc();
                    k++;
                }
            }

        // solve a' = vu' | solves for u (except for the constant term) i.e. n > 1
        template <class IterA, class IterB, class IndexType, class T>
            void solve_aeqvu(IterA u, IterB a, IterB v, IndexType n, T init)
            {
                assert(n >= 1);

                IterA ucurr = u;
                Generator<T> inc;
                IndexType k = 1; // skip the constant term
                while (k < n)
                {
                    inc++;
                    *++ucurr = (inc() * (*++a) - tconvolve(u, v, k, init, 1))/(*v * inc());
                    k++;
                }
            }

        // solve two linear differential equations simultaneously
        template <class IterA, class IterB, class IndexType, class T>
            void solve_simul(IterA u1, T alpha1, IterB a1, IterB v1,
                             IterA u2, T alpha2, IterB a2, IterB v2,
                             IndexType n, int kind)
            {
                assert(n >= 1);
                assert(kind >=1 && kind <= 4);

                T init(0.0);
                IterA _u1 = u1, _u2 = u2;
                Generator<T> inc;
                IndexType k = 1; // skip the constant term

                switch (kind)
                {
                    case 1 :
                        while (k < n)
                        {
                            inc++;
                            *++u1 = alpha1 * tconvolve(a1, v1, k, init) / inc();
                            *++u2 = alpha2 * tconvolve(a2, v2, k, init) / inc();
                            k++;
                        }
                        break;

                    case 2 :
                        while (k < n)
                        {
                            inc++;
                            *++u1 = alpha1 * tconvolve(a1, v1, k, init) / inc();
                            *++u2 = (inc() * (*++a2) - tconvolve(_u2, v2, k, init, 1))/(*v1 * inc());
                            k++;
                        }
                        break;

                    case 3 :
                        while (k < n)
                        {
                            inc++;
                            *++u1 = (inc() * (*++a1) - tconvolve(_u1, v1, k, init, 1))/(*v1 * inc());
                            *++u2 = alpha2 * tconvolve(a2, v2, k, init) / inc();
                            k++;
                        }
                        break;

                    case 4 :
                        while (k < n)
                        {
                            inc++;
                            *++u1 = (inc() * (*++a1) - tconvolve(_u1, v1, k, init, 1))/(*v1 * inc());
                            *++u2 = (inc() * (*++a2) - tconvolve(_u2, v2, k, init, 1))/(*v1 * inc());
                            k++;
                        }
                        break;
                }
            }

    } // namespace utils

} // namespace tada

#endif /* __UTILS_H__ */
