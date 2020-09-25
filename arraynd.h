#pragma once

#include <array>
#include "array_util.h"

namespace rad
{
    template <class T, int s, int... r>
    class arraynd // : public std::array<arraynd<T, r...>, s>
    {
    public:
        typedef arraynd<T, r...> inner_type;
        static const int dimension = sizeof...(r) + 1;
        typedef std::array<size_t, dimension> size_type;

        static constexpr size_type size()
        {
            return join_array(std::array<size_t, 1>({ s }), inner_type::size());
        }
    };

    template <class T, int s>
    class arraynd<T, s> // : public std::array<T, s>
    {
    public:
        typedef T inner_type;
        static const int dimension = 1;
        typedef std::array<size_t, dimension> size_type;

        static constexpr size_type size()
        {
            return { s };
        }
    };
}
