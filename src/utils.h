#ifndef __UTILS_H__
#define __UTILS_H__

namespace tada {

    namespace utils {

        // convolve: \sum_{i=0}^{k}  a_i * v_{k-i}
        template <class BidirectionalIter1, class BidirectionalIter2, class IndexType, class T>
            T convolve(BidirectionalIter1 a, BidirectionalIter2 v, IndexType k, T init)
            {
                v = v + k;
                do {
                    init = init + (*a++) * (*v--);
                } while (k--);
                return init;
            }

        // tilde convolve: \sum_{i=0}^{k} i * a_i * v_{k-i}
        template <class BidirectionalIter1, class BidirectionalIter2, class IndexType, class T>
            T tconvolve(BidirectionalIter1 a, BidirectionalIter2 v, IndexType k, T init)
            {
                v = v + k;
                T inc(0.0);
                do {
                    init = init + inc * (*a++) * (*v--);
                    inc = inc + T(1.0);
                } while (k--);
                return init;
            }

        // solve u' = va' | solves for u (except for the constant term) i.e. n >= 1
        template <class OutputIter, class BidirectionalIter1, class BidirectionalIter2, class IndexType, class T>
            void solve_ueqva(OutputIter u, BidirectionalIter1 a, BidirectionalIter2 v, IndexType n, T init)
            {
                T inc(1.0);
                IndexType k = 1; // skip the constant term
                while (k++ < n)
                {
                    *++u = tconvolve(a, v, k, init) / inc;
                    inc = inc + T(1.0);
                }
            }

        // solve a' = vu' | solves for u (except for the constant term) i.e. n > 1
        template <class OutputIter, class BidirectionalIter1, class BidirectionalIter2, class IndexType, class T>
            void solve_aeqvu(OutputIter u, BidirectionalIter1 a, BidirectionalIter2 v, IndexType n, T init)
            {
                T inc(1.0);
                IndexType k = 1; // skip the constant term
                while (k++ < n)
                {
                    *++u = (inc * (*++a) - tconvolve(u, v, k - 1, init)) / (*v * inc);
                    inc = inc + T(1.0);
                }
            }

    } // namespace utils

} // namespace tada

#endif /* __UTILS_H__ */
