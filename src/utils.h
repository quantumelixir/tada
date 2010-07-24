#ifndef __UTILS_H__
#define __UTILS_H__

namespace tada {

    namespace utils {

    template <class InputIterator1, class InputIterator2, class T>
    T convolve(InputIterator1 first1, InputIterator1 last1, InputIterator2 last2, T init = T())
    {
        while (first1 != last1)
            init = init + (*first1++) * (*last2--);
        return init;
    }

    }

}

#endif /* __UTILS_H__ */
