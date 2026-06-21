#include "core/multidimensional/vector_2d.hpp"
#include "metaCore/lite/stream.hpp"

bool utest_1()
{
    bool result = true;
    udt::vector_2d<int> v1;
    result &= meta::lite::test::basic<bool>(v1.empty(), true);
    result &= meta::lite::test::basic<std::string>(v1.general_matrix_type(), "Empty Matrix");
    return result;
}

bool utest_2()
{
    bool result = true;
    udt::vector_2d<int> v2 = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}};
    result &= meta::lite::test::basic<std::string>(v2.general_matrix_type(), "Identity Matrix");
    result &= meta::lite::test::basic<int>(v2.determinant(), 1);
    result &= meta::lite::test::vector<int>(v2[1], {0, 1, 0});
    return result;
}

bool utest_3()
{
    bool result = true;
    udt::vector_2d<char> v3 = {2, 2, {{'c', 'i'}, {'o', 'p'}}};
    result &= meta::lite::test::basic<std::string>(v3.general_matrix_type(), "Square Matrix");
    result &= meta::lite::test::basic<bool>(v3.is_fixed_size(), true);
    result &= meta::lite::test::basic<char>(v3.get(1, 1), 'p');
    return result;
}

bool utest_4()
{
    bool result = true;
    udt::vector_2d<float> v4 = {
        {2, 0, 0},
        {0, 6, 0},
        {0, 0, 1}};
    result &= meta::lite::test::basic<std::string>(v4.general_matrix_type(), "Diagonal Matrix");
    result &= meta::lite::test::basic<float>(v4.determinant(), 12);
    return result;
}

bool utest_5()
{
    bool result = true;
    udt::vector_2d<int> v5 = {
        {1, 2, 8},
        {0, 8, 9},
        {0, 0, 5}};
    result &= meta::lite::test::basic<std::string>(v5.general_matrix_type(), "Upper Triangular Matrix");
    result &= meta::lite::test::basic<int>(v5.determinant(), 40);
    return result;
}

bool utest_6()
{
    bool result = true;
    udt::vector_2d<double> v6 = {
        {1.7, 0, 0},
        {2.8, 1.3, 0},
        {5.9, 4.6, 6.6},
    };
    result &= meta::lite::test::basic<std::string>(v6.general_matrix_type(), "Lower Triangular Matrix");
    result &= meta::lite::test::basic<int>(v6.determinant(), 14.586);
    return result;
}

bool utest_7()
{
    bool result = true;
    udt::vector_2d<int> v7 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 2, 9}};
    result &= meta::lite::test::basic<std::string>(v7.general_matrix_type(), "Square Matrix");
    result &= meta::lite::test::basic<int>(v7.determinant(), -36);
    return result;
}

bool utest_8()
{
    bool result = true;
    udt::vector_2d<int> v8 = {
        {12, 32, 23, 11},
        {55, 25, 62, 19},
        {34, 44, 88, 77},
        {65, 12, 14, 75}};
    result &= meta::lite::test::basic<std::string>(v8.general_matrix_type(), "Square Matrix");
    result &= meta::lite::test::basic<int>(v8.determinant(), -7770447);
    return result;
}

bool utest_9()
{
    bool result = true;
    udt::vector_2d<char> v9 = {
        {'c', ',', 'o'},
        {'u', 'o', 'w'},
        {'q', 'g', 'n'}};
    const std::vector<char> stdv9 = {'c', ',', 'o', 'u', 'o', 'w', 'q', 'g', 'n'};
    result &= meta::lite::test::vector<char>(v9.get_flatten(), stdv9);
    result &= meta::lite::test::basic<char>(v9.get_flatten(2), v9.get(0, 2));
    result &= meta::lite::test::vector<char>(v9.get(1), {'u', 'o', 'w'});
    return result;
}

bool utest_10()
{
    bool result = true;
    udt::vector_2d<int> v10 = {
        {10, 18, 12},
        {11, 97, 92}};
    std::vector<std::vector<int>> stdv10 = {
        {10, 11},
        {18, 97},
        {12, 92}};
    result &= meta::lite::test::vector_2d<int>(stdv10, v10.get_transpose());
    v10.clear(1);
    result &= meta::lite::test::basic<bool>(v10.empty(1), true);
    result &= meta::lite::test::basic<bool>(v10.empty(0), false);
    v10.clear();
    result &= meta::lite::test::basic<bool>(v10.empty(), true);
    return result;
}

bool utest_11()
{
    bool result = true;
    udt::vector_2d<char> v11 = {
        {'c', 'p', 'p'},
        {'g', '+', '+'},
        {'2', 'h', 'o'}};
    size_t before_size = v11.size(2);
    v11.pop(2);
    result &= meta::lite::test::basic<size_t>(v11.size(2), before_size - 1);
    before_size = v11.size();
    v11.pop();
    result &= meta::lite::test::basic<size_t>(v11.size(), before_size - 1);
    std::vector<char> stdv11 = {'o', '-', '-'};
    v11.push(stdv11);
    result &= meta::lite::test::vector<char>(v11.get(2), stdv11);
    v11.push(1, 'i');
    result &= meta::lite::test::basic<size_t>(v11.last_index(1), 3);
    result &= meta::lite::test::basic<size_t>(v11.last_index(), 2);
    return result;
}

bool utest_12()
{
    bool result = true;
    udt::vector_2d<int> v12 = {
        {1, 8, 9},
        {2, 9}};
    std::vector<std::vector<int>> stdv12 = {
        {1, 8, 9},
        {2, 9}};
    result &= meta::lite::test::basic<bool>(v12 == stdv12, true);
    stdv12[1].push_back(11);
    result &= meta::lite::test::basic<bool>(v12 == stdv12, false);
    return result;
}

bool utest_13()
{
    udt::vector_2d<short> v13 = {
        {8, 9, 12},
        {10, 2, 3},
        {9, 11, 3}};
    std::vector<std::vector<short>> stdv13 = {
        {16, 17, 20},
        {18, 10, 11},
        {17, 19, 11}};
    v13 += 8;
    return meta::lite::test::vector_2d<short>(v13.get(), stdv13);
}

bool utest_14()
{
    udt::vector_2d<short> v14 = {
        {8, 9, 12},
        {10, 2, 3},
        {9, 11, 3}};
    std::vector<std::vector<short>> stdv14 = {
        {6, 7, 10},
        {8, 0, 1},
        {7, 9, 1}};
    v14 -= 2;
    return meta::lite::test::vector_2d<short>(v14.get(), stdv14);
}

bool utest_15()
{
    udt::vector_2d<short> v15 = {
        {8, 9, 12},
        {10, 2, 3},
        {9, 11, 3}};
    std::vector<std::vector<short>> stdv15 = {
        {80, 90, 120},
        {100, 20, 30},
        {90, 110, 30}};
    v15 *= 10;
    return meta::lite::test::vector_2d<short>(v15.get(), stdv15);
}

bool utest_16()
{
    udt::vector_2d<float> v16 = {
        {8, 9, 12},
        {10, 2, 3},
        {9, 11, 3}};
    std::vector<std::vector<float>> stdv16 = {
        {4, 4.5, 6},
        {5, 1, 1.5},
        {4.5, 5.5, 1.5}};
    v16 /= 2;
    return meta::lite::test::vector_2d<float>(v16.get(), stdv16);
}

bool utest_17()
{
    udt::vector_2d<char> v17 = {
        {'c', 'i'},
        {'o', ','}};
    std::vector<char> stdv17 = {'c', 'i'};
    return meta::lite::test::vector<char>(v17[0], stdv17);
}

bool utest_18()
{
    udt::vector_2d<char> v18 = {
        {'c', 'i'},
        {'o', ','}};
    int d = v18.determinant();
    return meta::lite::test::basic<int>(d, -7299);
}

bool utest_19()
{
    udt::vector_2d<short> v19 = {
        {8, 9, 12},
        {10, 2, 3},
        {9, 11, 3}};
    std::vector<std::vector<short>> stdv19 = {
        {6, 7, 10},
        {8, 0, 1},
        {7, 9, 1}};
    std::vector<std::vector<short>> stdv19_1 = {
        {14, 16, 22},
        {18, 2, 4},
        {16, 20, 4}};
    v19 += stdv19;
    return meta::lite::test::vector_2d<short>(v19.get(), stdv19_1);
}

bool utest_20()
{
    udt::vector_2d<short> v20 = {
        {8, 9, 12},
        {10, 2, 3},
        {9, 11, 3}};
    std::vector<std::vector<short>> stdv20 = {
        {6, 7, 3},
        {7, 3, 1},
        {7, 9, 1}};
    std::vector<std::vector<short>> stdv20_1 = {
        {2, 2, 9},
        {3, -1, 2},
        {2, 2, 2}};
    v20 -= stdv20;
    return meta::lite::test::vector_2d<short>(v20.get(), stdv20_1);
}

bool utest_21()
{
    bool result = true;
    udt::vector_2d<short> v21 = {
        {18, 88, 12},
        {10, 28},
        {19},
        {29, 33, 55, 32}};
    result &= meta::lite::test::basic<std::string>(v21.general_matrix_type(), "Invalid Matrix");
    v21.push(0, 98);
    v21.push(1, 78);
    v21.push(1, 62);
    v21.push(2, 12);
    v21.push(2, 36);
    v21.push(2, 51);
    result &= meta::lite::test::basic<std::string>(v21.general_matrix_type(), "Square Matrix");
    result &= meta::lite::test::basic<long double>(v21.determinant(), -5396064);
    return result;
}

bool utest_22()
{
    udt::vector_2d<short> v22 = {
        {8, 8, 2, 9},
        {0, 2, 8, 6},
        {9, 1, 6, 5},
        {9, 3, 5, 2}};
    std::vector<std::vector<short>> stdv22 = {
        {64, 64, 4, 81},
        {0, 4, 64, 36},
        {81, 1, 36, 25},
        {81, 9, 25, 4}};
    v22 ^= 2;
    return meta::lite::test::vector_2d<short>(v22.get(), stdv22);
}

bool utest_23()
{
    udt::vector_2d<short> v23 = {
        {8, 8, 2, 9},
        {0, 2, 8, 6},
        {9, 1, 6, 5},
        {9, 3, 5, 2}};
    std::vector<std::vector<short>> stdv23_1 = {
        {1, 1, 2, 2},
        {8, 3, 2, 3},
        {1, 4, 4, 3},
        {3, 6, 5, 9}};
    v23 ^= stdv23_1;
    std::vector<std::vector<short>> stdv23_2 = {
        {8, 8, 4, 81},
        {0, 8, 64, 216},
        {9, 1, 1296, 125},
        {729, 729, 3125, 512}};
    return meta::lite::test::vector_2d<short>(v23.get(), stdv23_2);
}

bool utest_24()
{
    udt::vector_2d<int> v24 = {
        {8, 8, 2, 9},
        {0, 2, 8, 6},
        {9, 1, 6, 5},
        {9, 3, 5, 2}};
    udt::vector_2d<int> v24_1 = {
        {1, 1, 2, 2},
        {8, 3, 2, 3},
        {1, 4, 4, 3},
        {3, 6, 5, 9}};
    v24 ^= v24_1;
    std::vector<std::vector<int>> v24_2 = {
        {8, 8, 4, 81},
        {0, 8, 64, 216},
        {9, 1, 1296, 125},
        {729, 729, 3125, 512}};
    return meta::lite::test::vector_2d<int>(v24.get(), v24_2);
}

bool utest_25()
{

    udt::vector_2d<int> v25 = {
        {8, 9, 12},
        {10, 2, 3},
        {9, 11, 3}};
    udt::vector_2d<int> v25_1 = {
        {6, 7, 3},
        {7, 3, 1},
        {7, 9, 1}};
    std::vector<std::vector<int>> v25_2 = {
        {2, 2, 9},
        {3, -1, 2},
        {2, 2, 2}};
    v25 -= v25_1;
    return meta::lite::test::vector_2d<int>(v25.get(), v25_2);
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
    UTS << utest_21;
    UTS << utest_22;
    UTS << utest_23;
    UTS << utest_24;
    UTS << utest_25;
    UTS.print_summary();
    udt::vector_2d<int> v = {{77, 49, 388}, {392, 389, 209}};
    meta::lite::io::println(
        "The size of the udt::vector_2d data type in bytes using mata data: ",
        meta::lite::benchmark::mata_data(v));
    meta::lite::io::println(
        "The size of the udt::vector_2d data type in bytes using heap data: ",
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
    UTB << utest_21;
    UTB << utest_22;
    UTB << utest_23;
    UTB << utest_24;
    UTB << utest_25;
    UTB.print_summary();
    return 0;
}