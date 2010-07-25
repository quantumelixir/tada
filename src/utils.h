#ifndef __UTILS_H__
#define __UTILS_H__

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
                Generator<T> inc;
                do {
                    init = init + (inc++) * (*a++) * (*v--);
                } while (k--);
                return init;
            }

        // solve u' = va' | solves for u (except for the constant term) i.e. n >= 1
        template <class OutputIter, class BidirectionalIter1, class BidirectionalIter2, class IndexType, class T>
            void solve_ueqva(OutputIter u, BidirectionalIter1 a, BidirectionalIter2 v, IndexType n, T init)
            {
                Generator<T> inc;
                IndexType k = 1; // skip the constant term
                while (k++ < n)
                    *++u = tconvolve(a, v, k, init) / (++inc);
            }

        // solve a' = vu' | solves for u (except for the constant term) i.e. n > 1
        template <class OutputIter, class BidirectionalIter1, class BidirectionalIter2, class IndexType, class T>
            void solve_aeqvu(OutputIter u, BidirectionalIter1 a, BidirectionalIter2 v, IndexType n, T init)
            {
                Generator<T> inc;
                IndexType k = 1; // skip the constant term
                while (k++ < n)
                    *++u = (*++a)/(*v) - tconvolve(u, v, k - 1, init)/(*v * (++inc));
            }

    } // namespace utils

} // namespace tada

#endif /* __UTILS_H__ */
