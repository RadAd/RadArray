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
    constexpr rad::arraynd<int, 6> a1;
    static_assert(decltype(a1)::dimension == 1, "dimension fail");
    static_assert(rad::equal(a1.size(), std::array<size_t, 1> { 6 }), "size fail");

    constexpr int a2array[] = { 7, 3, 6 };
    constexpr rad::arraynd<int, 3> a2 = a2array;
    //static_assert(rad::equal(a2, a2array), "equal fail");
    static_assert(a2[0] == 7, "comparison fail");
    static_assert(a2[1] == 3, "comparison fail");
    static_assert(a2[2] == 6, "comparison fail");
}

void Test2DArray()
{
    puts("--- " __FUNCTION__);
    constexpr const rad::arraynd<int, 2, 3> a1;
    static_assert(decltype(a1)::dimension == 2, "dimension fail");
    static_assert(rad::equal(a1.size(), std::array<size_t, 2> { 2, 3 }), "size fail");

    constexpr int a2array[3][2] = { { 5, 7 }, { 2, 9 }, { 8, 3 } };
    constexpr rad::arraynd<int, 3, 2> a2 = a2array;
    //static_assert(rad::equal(a2, a2array), "equal fail");
    static_assert(a2[0][0] == 5, "comparison fail");
    static_assert(a2[0][1] == 7, "comparison fail");
    static_assert(a2[1][0] == 2, "comparison fail");
    static_assert(a2[1][1] == 9, "comparison fail");
    static_assert(a2[2][0] == 8, "comparison fail");
    static_assert(a2[2][1] == 3, "comparison fail");
}

int main()
{
    puts("*** ArrayND Test ***");
    TestLexicographicalCompare();
    TestMakeArray();
    Test1DArray();
    Test2DArray();
}
