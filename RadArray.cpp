#include "arraynd.h"
#include <cstdio>
#include <cassert>

template<class T, class U>
constexpr bool is_same(T, U)
{
    return std::is_same<T, U>::value;
}

void TestMakeArray()
{
    puts("--- " __FUNCTION__);
    static_assert(rad::equal(std::array<int, 4> { 1, 2, 6, 7 }, rad::make_array(1, 2, 6, 7)), "make_array fail");
    static_assert(rad::equal(std::array<double, 2> { 1, 3.0 }, rad::make_array(1, 3.0)), "make_array fail");    // Testing int promotion to double
}

void TestLexicographicalCompare()
{
    puts("--- " __FUNCTION__);
    constexpr std::array<int, 4> arr1 = { 78, 23, 65, 72 };
    constexpr std::array<int, 4> arr2 = { 78, 23, 65, 72 };
    constexpr std::array<int, 4> arr3 = { 6, 3, 5, 2 };

    static_assert(rad::lexicographical_compare(arr1, arr2), "lexicographical_compare fail");
    static_assert(!rad::lexicographical_compare(arr1, arr3), "lexicographical_compare fail");
    static_assert(!rad::lexicographical_compare(arr1, arr2, std::not_equal_to<>()), "lexicographical_compare fail");
    static_assert(rad::lexicographical_compare(arr1, arr3, std::not_equal_to<>()), "lexicographical_compare fail");
}

void TestEqual()
{
    puts("--- " __FUNCTION__);
    constexpr std::array<int, 4> arr1 = { 78, 23, 65, 72 };
    constexpr std::array<int, 4> arr2 = { 78, 23, 65, 72 };
    constexpr std::array<int, 4> arr3 = { 6, 3, 5, 2 };

    static_assert(rad::equal(arr1, arr2), "equal fail");
    static_assert(!rad::equal(arr1, arr3), "equal fail");
}

void Test1DArray()
{
    puts("--- " __FUNCTION__);
    rad::arraynd<int, 6> ab1;
    static_assert(decltype(ab1)::dimension == 1, "dimension fail");
    static_assert(rad::equal(ab1.size(), std::array<size_t, 1> { 6 }), "size fail");
}

void Test2DArray()
{
    puts("--- " __FUNCTION__);
    constexpr const rad::arraynd<int, 2, 3> a;
    static_assert(decltype(a)::dimension == 2, "dimension fail");
    static_assert(rad::equal(a.size(), std::array<size_t, 2> { 2, 3 }), "size fail");
}

int main()
{
    puts("*** ArrayND Test ***");
    TestLexicographicalCompare();
    TestMakeArray();
    Test1DArray();
    Test2DArray();
}
