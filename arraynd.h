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
        typedef typename inner_type::native_type native_type[s];

        static constexpr size_type size()
        {
            return join_array(std::array<size_t, 1>({ s }), inner_type::size());
        }

        constexpr arraynd()
            : inner() // TODO Not sure why this is needed but it keeps the compiler happy
        {
        }

        constexpr arraynd(const native_type& init)
            : inner(to_array_inner(init, std::make_index_sequence<s> {}))
        {
        }

    private:
        template <std::size_t... I>
        static constexpr std::array<inner_type, s> to_array_inner(const native_type& init, std::index_sequence<I...>)
        {
            return { inner_type(init[I])... };
        }

        std::array<inner_type, s>   inner;
    };

    template <class T, int s>
    class arraynd<T, s> // : public std::array<T, s>
    {
    public:
        typedef T inner_type;
        static const int dimension = 1;
        typedef std::array<size_t, dimension> size_type;
        typedef T native_type[s];

        static constexpr size_type size()
        {
            return { s };
        }

        constexpr arraynd()
            : inner() // TODO Not sure why this is needed but it keeps the compiler happy
        {
        }

        constexpr arraynd(const native_type& init)
            : inner(to_array_inner(init, std::make_index_sequence<s> {}))
        {
        }

    private:
        template <std::size_t... I>
        static constexpr std::array<inner_type, s> to_array_inner(const native_type& init, std::index_sequence<I...>)
        {
            return { inner_type(init[I])... };
        }

        std::array<inner_type, s>   inner;
    };
}
