#include "udt/core/multidimensional/vector_3d.hpp"
#include "meta/lite/stream.hpp"

bool utest_1()
{
    bool result = true;
    udt::vector_3d<int> v1;
    meta::lite::test::basic<bool>(v1.empty(), true);
    v1 = {
        {{1, 2, 3},
         {4, 5, 6}},
        {{7, 8, 9},
         {10, 11, 12}}};
    result &= meta::lite::test::basic<int>(v1.get(1, 0, 2), 9);
    result &= meta::lite::test::basic<size_t>(v1.size(), 2);
    result &= meta::lite::test::basic<size_t>(v1.size(0), 2);
    result &= meta::lite::test::basic<size_t>(v1.size(1, 1), 3);
    return result;
}

bool utest_2()
{
    bool result = true;
    udt::vector_3d<char> v2 = {
        {{'c', 'i'},
         {'o', 'p'}},
        {{'p', 'y'},
         {'t', 'h'}},
        {{'o', 'n'},
         {'-', '-'}}};
    std::vector<std::vector<std::vector<char>>> stdv2 = {
        {{'c', 'i'},
         {'o', 'p'}},
        {{'p', 'y'},
         {'t', 'h'}},
        {{'o', 'n'},
         {'-', '-'}}};
    result &= meta::lite::test::basic<bool>(v2 == stdv2, true);
    stdv2[1][1][1] = 'o';
    result &= meta::lite::test::basic<bool>(v2 == stdv2, false);
    result &= meta::lite::test::basic<char>(v2.at(2, 0, 1), 'n');
    result &= meta::lite::test::vector<char>(v2.at(2, 1), stdv2[2][1]);
    result &= meta::lite::test::vector_2d<char>(v2.at(0), stdv2[0]);
    return result;
}

bool utest_3()
{
    bool result = true;
    udt::vector_3d<double> v3 = {
        {{1.1, 2.2, 3.3},
         {4.4, 5.5, 6.6}},
        {{7.7, 8.8, 9.9},
         {10.1, 11.11, 12.12}}};
    std::vector<std::vector<std::vector<double>>> stdv3 = {
        {{1.1, 2.2, 3.3},
         {4.4, 5.5, 6.6}},
        {{7.7, 8.8, 9.9},
         {10.1, 11.11, 12.12}}};
    result &= meta::lite::test::basic<bool>(v3 == stdv3, true);
    result &= meta::lite::test::basic<double>(v3.at(0, 1, 2), 6.6);
    result &= meta::lite::test::basic<size_t>(v3.size(1), 2);
    result &= meta::lite::test::vector<double>(v3.at(1, 0), stdv3[1][0]);
    result &= meta::lite::test::vector_2d<double>(v3.at(0), stdv3[0]);
    return result;
}

bool utest_4()
{
    bool result = true;
    udt::vector_3d<int> v4 = {
        {{1, 2, 3},
         {4, 5, 6}},
        {{7, 8, 9},
         {10, 11, 12}}};
    result &= meta::lite::test::basic<size_t>(v4.size(1), 2);
    v4.pop(1);
    result &= meta::lite::test::basic<size_t>(v4.size(1), 1);
    v4.push(1, {13, 18, 99});
    result &= meta::lite::test::basic<size_t>(v4.size(1), 2);
    result &= meta::lite::test::basic<int>(v4.at(1, 1, 2), 99);
    v4.clear();
    result &= meta::lite::test::basic<bool>(v4.empty(), true);
    return result;
}

bool utest_5()
{
    bool result = true;
    udt::vector_3d<int> v5(3, 3, 3);
    v5 = {
        {{1, 2, 3},
         {4, 5, 6},
         {7, 8, 9}},
        {{10, 11, 12},
         {13, 14, 15},
         {16, 17, 18}},
        {{19, 20, 21},
         {22, 23, 24},
         {25, 26, 27}}};
    result &= meta::lite::test::basic<bool>(v5.empty(), false);
    result &= meta::lite::test::basic<size_t>(v5.size(), 3);
    result &= meta::lite::test::basic<size_t>(v5.size(0), 3);
    result &= meta::lite::test::basic<size_t>(v5.size(1, 1), 3);
    result &= meta::lite::test::basic<bool>(v5.is_fixed_size(), true);
    return result;
}

bool utest_6()
{
    bool result = true;
    udt::vector_3d<int> v6 = {
        {{1, 2},
         {3, 4}},
        {{5, 6},
         {7, 8}},
        {{9, 10},
         {11, 12}}};
    std::vector<std::vector<std::vector<int>>> transposed = v6.get_transpose();
    std::vector<std::vector<std::vector<int>>> expected = {
        {{1, 2},
         {5, 6},
         {9, 10}},
        {{3, 4},
         {7, 8},
         {11, 12}}};
    result &= meta::lite::test::basic<bool>(transposed == expected, true);
    std::vector<std::vector<int>> flattened;
    v6.get_flatten(flattened);
    std::vector<std::vector<int>> expected_flattened = {
        {1, 2},
        {3, 4},
        {5, 6},
        {7, 8},
        {9, 10},
        {11, 12}};
    result &= meta::lite::test::basic<bool>(flattened == expected_flattened, true);
    return result;
}

bool utest_7()
{
    bool result = true;
    udt::vector_3d<int> v7 = {
        {{1, 2, 3},
         {4, 5, 6}},
        {{7, 8, 9},
         {10, 11, 12}}};
    result &= meta::lite::test::basic<int>(v7.last_index(), 1);
    result &= meta::lite::test::basic<int>(v7.last_index(0), 1);
    v7.pop(0);
    result &= meta::lite::test::basic<int>(v7.last_index(0), 0);
    result &= meta::lite::test::basic<int>(v7.last_index(0, 0), 2);
    v7.push(0, {16, 17, 18});
    result &= meta::lite::test::basic<int>(v7.last_index(0), 1);
    return result;
}

bool utest_8()
{
    bool result = true;
    udt::vector_3d<double> v8 = {
        {{4.0, 3.0},
         {6.0, 3.0}},
        {{1.0, 2.0},
         {1.0, 4.0}}};
    result &= meta::lite::test::basic<size_t>(v8.size(), 2);
    result &= meta::lite::test::basic<size_t>(v8.size(0), 2);
    result &= meta::lite::test::basic<size_t>(v8.size(1, 0), 2);
    v8.clear();
    result &= meta::lite::test::basic<bool>(v8.empty(), true);
    v8 = {
        {{4.0, 3.0},
         {6.0, 3.0}},
        {{1.0, 2.0},
         {1.0, 4.0}}};
    v8.clear(1);
    result &= meta::lite::test::basic<bool>(v8.empty(1), true);
    result &= meta::lite::test::basic<bool>(v8.empty(), false);
    return result;
}

bool utest_9()
{
    bool result = true;
    udt::vector_3d<int> v9 = {
        {{1, 2, 3},
         {4, 5, 6}},
        {{7, 8, 9},
         {10, 11, 12}}};
    v9 += 9;
    std::vector<std::vector<std::vector<int>>> expected = {
        {{10, 11, 12},
         {13, 14, 15}},
        {{16, 17, 18},
         {19, 20, 21}}};
    std::vector<std::vector<int>> v1 = expected[0];
    result &= meta::lite::test::vector_3d<int>(v9.get(), expected);
    result &= meta::lite::test::vector_2d<int>(v9[0], v1);
    return result;
}

bool utest_10()
{
    bool result = true;
    udt::vector_3d<double> v10 = {
        {{4.0, 3.0},
         {6.0, 3.0}},
        {{1.0, 2.0},
         {1.0, 4.0}}};
    v10 *= 2.0;
    std::vector<std::vector<std::vector<double>>> expected = {
        {{8.0, 6.0},
         {12.0, 6.0}},
        {{2.0, 4.0},
         {2.0, 8.0}}};
    result &= meta::lite::test::vector_3d<double>(v10.get(), expected);
    result &= meta::lite::test::vector_2d<double>(v10[1], expected[1]);
    return result;
}

bool utest_11()
{
    bool result = true;
    udt::vector_3d<int> v11 = {
        {{1, 2, 3},
         {4, 5, 6}},
        {{7, 8, 9},
         {10, 11, 12}}};
    v11 -= 1;
    std::vector<std::vector<std::vector<int>>> expected = {
        {{0, 1, 2},
         {3, 4, 5}},
        {{6, 7, 8},
         {9, 10, 11}}};
    result &= meta::lite::test::vector_3d<int>(v11.get(), expected);
    result &= meta::lite::test::vector_2d<int>(v11[1], expected[1]);
    return result;
}

bool utest_12()
{
    bool result = true;
    udt::vector_3d<double> v12 = {
        {{4.0, 3.0},
         {6.0, 3.0}},
        {{1.0, 2.0},
         {1.0, 4.0}}};
    v12 /= 2.0;
    std::vector<std::vector<std::vector<double>>> expected = {
        {{2.0, 1.5},
         {3.0, 1.5}},
        {{0.5, 1.0},
         {0.5, 2.0}}};
    result &= meta::lite::test::vector_3d<double>(v12.get(), expected);
    result &= meta::lite::test::vector_2d<double>(v12[1], expected[1]);
    return result;
}

bool utest_13()
{
    udt::vector_3d<int> v13 = {
        {{1, 2, 3},
         {4, 5, 6}},
        {{7, 8, 9},
         {10, 11, 12}}};
    v13 ^= 2;
    std::vector<std::vector<std::vector<int>>> expected = {
        {{1, 4, 9},
         {16, 25, 36}},
        {{49, 64, 81},
         {100, 121, 144}}};
    return meta::lite::test::vector_3d<int>(v13.get(), expected);
}

bool utest_14()
{
    udt::vector_3d<double> v14 = {
        {{4.0, 3.0},
         {6.0, 3.0}},
        {{1.0, 2.0},
         {1.0, 4.0}}};
    std::vector<std::vector<std::vector<double>>> sumvec = {
        {{1.0, 1.0},
         {1.0, 1.0}},
        {{1.0, 1.0},
         {1.0, 1.0}}};
    v14 += sumvec;
    std::vector<std::vector<std::vector<double>>> expected = {
        {{5.0, 4.0},
         {7.0, 4.0}},
        {{2.0, 3.0},
         {2.0, 5.0}}};
    return meta::lite::test::vector_3d<double>(v14.get(), expected);
}

bool utest_15()
{
    udt::vector_3d<int> v15 = {
        {{1, 2, 3},
         {4, 5, 6}},
        {{7, 8, 9},
         {10, 11, 12}}};
    std::vector<std::vector<std::vector<int>>> mulvec = {
        {{1, 0, 1},
         {0, 1, 0}},
        {{1, 1, 1},
         {0, 0, 0}}};
    v15 *= mulvec;
    std::vector<std::vector<std::vector<int>>> expected = {
        {{1, 0, 3},
         {0, 5, 0}},
        {{7, 8, 9},
         {0, 0, 0}}};
    return meta::lite::test::vector_3d<int>(v15.get(), expected);
}

bool utest_16()
{
    udt::vector_3d<double> v16 = {
        {{4.0, 3.0},
         {6.0, 3.0}},
        {{1.0, 2.0},
         {1.0, 4.0}}};
    std::vector<std::vector<std::vector<double>>> divvec = {
        {{2.0, 1.0},
         {3.0, 1.0}},
        {{1.0, 2.0},
         {1.0, 2.0}}};
    v16 /= divvec;
    std::vector<std::vector<std::vector<double>>> expected = {
        {{2.0, 3.0},
         {2.0, 3.0}},
        {{1.0, 1.0},
         {1.0, 2.0}}};
    return meta::lite::test::vector_3d<double>(v16.get(), expected);
}

bool utest_17()
{
    udt::vector_3d<int> v17 = {
        {{1, 2, 3},
         {4, 5, 6}},
        {{7, 8, 9},
         {10, 11, 12}}};
    std::vector<std::vector<std::vector<int>>> expvec = {
        {{1, 4, 9},
         {16, 25, 36}},
        {{49, 64, 81},
         {100, 121, 144}}};
    v17 ^= 2;
    return meta::lite::test::vector_3d<int>(v17.get(), expvec);
}

bool utest_18()
{
    udt::vector_3d<double> v18 = {
        {{4.0, 3.0},
         {6.0, 3.0}},
        {{1.0, 2.0},
         {1.0, 4.0}}};
    std::vector<std::vector<std::vector<double>>> matrices = {
        {{4.0, 3.0},
         {6.0, 3.0}},
        {{1.0, 2.0},
         {1.0, 4.0}}};
    v18 -= matrices;
    std::vector<std::vector<std::vector<double>>> expected = {
        {{0.0, 0.0},
         {0.0, 0.0}},
        {{0.0, 0.0},
         {0.0, 0.0}}};
    return meta::lite::test::vector_3d<double>(v18.get(), expected);
}

bool utest_19()
{
    bool result = true;
    udt::vector_3d<double> v19 = {
        {{4.0, 3.0},
         {6.0, 3.0}},
        {{1.0, 2.0},
         {1.0, 4.0}}};
    result &= meta::lite::test::basic<bool>(v19.is_cude2X2X2(), true);
    std::vector<std::vector<double>> push_vector2d = {{1.0, 2.0}, {3.0, 4.0}};
    v19.push(push_vector2d);
    result &= meta::lite::test::basic<bool>(v19.is_cude2X2X2(), false);
    v19 = {
        {{1.0, 2.0, 3.0},
         {4.0, 5.0, 6.0},
         {7.0, 8.0, 9.0}},
        {{10.0, 11.0, 12.0},
         {13.0, 14.0, 15.0},
         {16.0, 17.0, 18.0}},
        {{19.0, 20.0, 21.0},
         {22.0, 23.0, 24.0},
         {25.0, 26.0, 27.0}}};
    std::vector<long double> dets = v19.get_determinant_vec();
    std::vector<long double> expected_dets = {0.0, 0.0, 0.0};
    result &= meta::lite::test::vector<long double>(dets, expected_dets);
    result &= meta::lite::test::basic<bool>(v19.is_cude3X3X3(), true);
    result &= meta::lite::test::basic<double>(v19.get_determinant(0), 0.0);
    return result;
}

bool utest_20()
{
    bool result = true;
    udt::vector_3d<int> v20 = {
        {{1, 2, 3},
         {4, 5, 6}},
        {{7, 8, 9},
         {10, 11, 12}}};
    result &= meta::lite::test::basic<bool>(v20.is_sizeNXMXW(2, 2, 3), true);
    result &= meta::lite::test::basic<bool>(v20.is_sizeNXMXW(2, 3, 3), false);
    std::vector<std::vector<std::vector<int>>> checkvec = {
        {{1, 2, 3},
         {4, 5, 6}},
        {{7, 8, 9},
         {10, 11, 12}}};
    result &= meta::lite::test::basic<bool>(v20.is_sizeNXMXW(2, 2, 3, checkvec), true);
    result &= meta::lite::test::basic<bool>(v20.is_sizeNXMXW(2, 3, 3, checkvec), false);
    return result;
}

int main()
{
    meta::lite::test_stream UTS;
    UTS << utest_1;
    UTS << utest_2;
    UTS << utest_3;
    UTS << utest_4;
    UTS << utest_5;
    UTS << utest_6;
    UTS << utest_7;
    UTS << utest_8;
    UTS << utest_9;
    UTS << utest_10;
    UTS << utest_11;
    UTS << utest_12;
    UTS << utest_13;
    UTS << utest_14;
    UTS << utest_15;
    UTS << utest_16;
    UTS << utest_17;
    UTS << utest_18;
    UTS << utest_19;
    UTS << utest_20;
    UTS.print_summary();
    udt::vector_3d<int> v = {
        {{77, 49},
         {3, 98, 29},
         {928, 398, 39}},
        {{388, 392},
         {99, 23, 388},
         {2983, 283, 38}},
        {{389, 209},
         {8839, 338},
         {9982, 3889}}};
    meta::lite::io::println(
        "The size of the udt::vector data type in bytes using mata data: ",
        meta::lite::benchmark::mata_data(v));
    meta::lite::io::println(
        "The size of the udt::vector data type in bytes using heap data: ",
        meta::lite::benchmark::heap_data(v.get()));
    meta::lite::benchmark_stream<false> UTB = 6;
    UTB << utest_1;
    UTB << utest_2;
    UTB << utest_3;
    UTB << utest_4;
    UTB << utest_5;
    UTB << utest_6;
    UTB << utest_7;
    UTB << utest_8;
    UTB << utest_9;
    UTB << utest_10;
    UTB << utest_11;
    UTB << utest_12;
    UTB << utest_13;
    UTB << utest_14;
    UTB << utest_15;
    UTB << utest_16;
    UTB << utest_17;
    UTB << utest_18;
    UTB << utest_19;
    UTB << utest_20;
    UTB.print_summary();
    return 0;
}