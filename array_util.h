#pragma once

// std::make_array - an array complement to std::make_tuple
// std::lexicographical_compare
// std::equal
// rel::join - join two arrays into a single array

#include <array>
#include <utility>

namespace rad
{
    template <typename... T>
    constexpr auto make_array(T&&... values)
        // -> std::array<typename std::decay<typename std::common_type<T...>::type>::type, sizeof...(T)>
    {
        typedef typename std::decay_t<typename std::common_type_t<T...>> decay_type;
        // TODO I did this to auto cast say an int to a double, is this the right way to so it for all types???
        //return std::array<decay_type, sizeof...(T)> { std::forward<T>(values)... };
        return std::array<decay_type, sizeof...(T)> { decay_type(std::forward<T>(values))... };
    }

    namespace impl
    {
        // internal functions, user api appear below

        template <class T, size_t S, class F>
        constexpr bool lexicographical_compare(const std::array<T, S>& arr1, const std::array<T, S>& arr2, size_t i, F f)
        {
            return (i == (S - 1)) ? f(arr1[i], arr2[i]) : lexicographical_compare(arr1, arr2, i + 1, f) & f(arr1[i], arr2[i]);
        }

        template <class T, class U, size_t S>
        constexpr bool equal(const std::array<T, S>& arr1, const std::array<U, S>& arr2, size_t i)
        {
            return (i == (S - 1)) ? arr1[i] == arr2[i] : impl::equal(arr1, arr2, i + 1) & (arr1[i] == arr2[i]);
        }

        // TODO Can this work for vararg classes (as well as vararg size_t array)
        template <class T, class U, std::size_t... I1, std::size_t... I2>
        constexpr auto join_array(const T& arr1, const U& arr2, std::index_sequence<I1...>, std::index_sequence<I2...>)
        {
            return make_array(std::get<I1>(arr1)..., std::get<I2>(arr2)...);
        }

        template<class T>
        using make_tuple_sequence = std::make_index_sequence<std::tuple_size<T>::value>;
    }

    template <class T, size_t S, class F = std::equal_to<T>>
    constexpr bool lexicographical_compare(const std::array<T, S>& arr1, const std::array<T, S>& arr2, F f = F())
    {
        return impl::lexicographical_compare(arr1, arr2, 0, f);
    }

    // operator== for std::array is not constexpr until C++20
    template <class T, class U, size_t S>
    constexpr bool equal(const std::array<T, S>& arr1, const std::array<U, S>& arr2)
    {
        // TODO Which method is better?
        return true
            ? impl::equal(arr1, arr2, 0)
            : lexicographical_compare(arr1, arr2);
    }

    template <class T, class U>
    constexpr auto join_array(const T& a1, const U& a2)
    {
        return impl::join_array(a1, a2, impl::make_tuple_sequence<T> {}, impl::make_tuple_sequence<U> {});
    }
}
