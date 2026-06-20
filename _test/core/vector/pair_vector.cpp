#include "core/multidimensional/vector_2d.hpp"
#include "core/pair/pair_v.hpp"
#include "core/pair/pair__v.hpp"
#include "metaCore/lite.hpp"

bool utest_1()
{
    bool result = true;
    std::vector<int> v1 = {10, 28, 22, 12};
    std::vector<int> v2 = {88, 98, 89, 29};
    udt::pair_v<int> pv1(v1, v2);
    result &= meta::lite::test::basic<bool>(pv1.empty(), false);
    result &= meta::lite::test::basic<bool>(pv1.empty_v1(), false);
    result &= meta::lite::test::basic<bool>(pv1.empty_v2(), false);
    result &= meta::lite::test::basic<int>(pv1.at_v1(1), 28);
    result &= meta::lite::test::basic<int>(pv1.at_v2(2), 89);
    result &= meta::lite::test::vector<int>(pv1.get_vec1(), v1);
    result &= meta::lite::test::vector<int>(pv1.get_vec2(), v2);
    return result;
}
bool utest_2()
{
    bool result = true;
    std::vector<int> v1 = {4, 6};
    std::vector<int> v2 = {7, 3, 8, 2};
    udt::pair_v<int> pv2(v1, v2);
    result &= meta::lite::test::basic<int>(pv2.Divi_v1(std::pow(10, 3)), 41);
    result &= meta::lite::test::basic<int>(pv2.Divi_v2(std::pow(10, 6)), 2976);
    result &= meta::lite::test::basic<long double>(pv2.Mult_v1(), 24);
    result &= meta::lite::test::basic<long double>(pv2.Mult_v2(), 336);
    result &= meta::lite::test::basic<long double>(pv2.sum_v1(), 10);
    result &= meta::lite::test::basic<long double>(pv2.sum_v2(), 20);
    result &= meta::lite::test::basic<long double>(pv2.average_v1(), 5);
    result &= meta::lite::test::basic<long double>(pv2.average_v2(), 5);
    result &= meta::lite::test::basic<size_t>(pv2.size_v1(), 2);
    result &= meta::lite::test::basic<size_t>(pv2.size_v2(), 4);
    pv2.clear_v1();
    result &= meta::lite::test::basic<bool>(pv2.empty_v1(), true);
    result &= meta::lite::test::basic<bool>(pv2.empty_v2(), false);
    return result;
}
bool utest_3()
{
    bool result = true;
    std::vector<short> v1 = {95, 98};
    std::vector<short> v2 = {10, 12};
    udt::pair_v<short> pv3(v1, v2);
    pv3.clear_v2();
    result &= meta::lite::test::basic<bool>(pv3.empty_v2(), true);
    result &= meta::lite::test::basic<bool>(pv3.empty_v1(), false);
    result &= meta::lite::test::basic<bool>(pv3.empty(), false);
    pv3.clear_v1();
    result &= meta::lite::test::basic<bool>(pv3.empty(), true);
    return result;
}
bool utest_4()
{
    bool result = true;
    std::vector<char> v1 = {'l', 'i'};
    std::vector<char> v2 = {'v', 'o'};
    udt::pair_v<char> pv4(v1, v2);
    pv4.swap_vecs();
    result &= meta::lite::test::vector<char>(pv4.get_vec1(), v2);
    result &= meta::lite::test::vector<char>(pv4.get_vec2(), v1);
    pv4.clear_all();
    result &= meta::lite::test::basic<char>(pv4.empty(), true);
    return result;
}
bool utest_5()
{
    bool result = true;
    udt::pair_v<float> pv5 = {1.8, 1.9, 2.8, 3.9};
    result &= meta::lite::test::basic<bool>(pv5.empty_v1(), false);
    result &= meta::lite::test::basic<bool>(pv5.empty_v2(), true);
    pv5 = {1.2, 8.9, 3.8, 2.0};
    result &= meta::lite::test::basic<bool>(pv5.empty(), false);
    result &= meta::lite::test::basic<int>(pv5.sum_v1(), 10.4);
    result &= meta::lite::test::basic<int>(pv5.sum_v2(), 15.9);
    result &= meta::lite::test::basic<int>(pv5.Mult_v1(), 37.3464);
    result &= meta::lite::test::basic<int>(pv5.Mult_v2(), 81.168);
    result &= meta::lite::test::basic<int>(pv5.average_v1(), 2.6);
    result &= meta::lite::test::basic<int>(pv5.average_v2(), 3.975);
    return result;
}
bool utest_6()
{
    bool result = true;
    udt::vector_2d<char> v = {
        {'o', 'i'},
        {'u', 'w', 'q'}};
    udt::pair_v<char> pv6 = {'o', 'i'};
    pv6 = {'u', 'w', 'q'};
    result &= meta::lite::test::basic<bool>(pv6 == v.get(0), true);
    pv6 + 3;
    v += 3;
    result &= meta::lite::test::vector<char>(pv6.get_vec1(), v.get(0));
    result &= meta::lite::test::vector<char>(pv6.get_vec2(), v.get(1));
    return result;
}
bool utest_7()
{
    bool result = true;
    std::vector<std::vector<int>> vs = {
        {2, 17, 2, 17},
        {3, 17, 7, 18}};
    udt::pair_v<int> pv7;
    pv7 = {1, 9, 0, 8};
    pv7 = {2, 9, 5, 9};
    std::vector<int> v = {1, 8, 2, 9};
    pv7 + v;
    result &= meta::lite::test::vector<int>(pv7.get_vec1(), vs[0]);
    result &= meta::lite::test::vector<int>(pv7.get_vec2(), vs[1]);
    return result;
}
bool utest_8()
{
    bool result = true;
    std::vector<std::vector<short>> v = {
        {8, 29, 19, 23},
        {2, 88, 21, 0}};
    udt::pair_v<short> pv8;
    pv8 = {18, 39, 29, 33};
    pv8 = {12, 98, 31, 10};
    pv8 - 10;
    result &= meta::lite::test::vector<short>(pv8.get_vec1(), v[0]);
    result &= meta::lite::test::vector<short>(pv8.get_vec2(), v[1]);
    return result;
}
bool utest_9()
{
    bool result = true;
    std::vector<std::vector<int>> vs = {
        {0, 1, -2, -1},
        {1, 1, 3, 0}};
    udt::pair_v<int> pv9;
    pv9 = {1, 9, 0, 8};
    pv9 = {2, 9, 5, 9};
    std::vector<int> v = {1, 8, 2, 9};
    pv9 - v;
    result &= meta::lite::test::vector<int>(pv9.get_vec1(), vs[0]);
    result &= meta::lite::test::vector<int>(pv9.get_vec2(), vs[1]);
    return result;
}
bool utest_10()
{
    bool result = true;
    std::vector<std::vector<int>> vs = {
        {5, 45, 0, 40},
        {10, 45, 25, 45}};
    udt::pair_v<int> pv10;
    pv10 = {1, 9, 0, 8};
    pv10 = {2, 9, 5, 9};
    pv10 * 5;
    result &= meta::lite::test::vector<int>(pv10.get_vec1(), vs[0]);
    result &= meta::lite::test::vector<int>(pv10.get_vec2(), vs[1]);
    return result;
}
bool utest_11()
{
    bool result = true;
    std::vector<std::vector<int>> vs = {
        {2, 5, 0, 4},
        {1, 6, 12, 3}};
    udt::pair_v<int> pv11;
    pv11 = {4, 10, 0, 8};
    pv11 = {2, 12, 24, 6};
    pv11 / 2;
    result &= meta::lite::test::vector<int>(pv11.get_vec1(), vs[0]);
    result &= meta::lite::test::vector<int>(pv11.get_vec2(), vs[1]);
    return result;
}
bool utest_12()
{
    bool result = true;
    udt::pair_v<int> pv12 = {{12, 98, 23}, {78, 88, 32, 29}};
    result &= meta::lite::test::basic<size_t>(pv12.size_v1(), 3);
    result &= meta::lite::test::basic<size_t>(pv12.size_v2(), 4);
    pv12.set_v1({98, 28, 38});
    result &= meta::lite::test::basic<int>(pv12.at_v1(0), 98);
    result &= meta::lite::test::basic<int>(pv12.at_v2(1), 88);
    return result = true;
}
bool utest_13()
{
    bool result = true;
    udt::pair__v<int, char> pv13 = {{18, 29, 39}, {'w', 'o', 'i', 'l'}};
    result &= meta::lite::test::basic<int>(pv13.at_v1(1), 29);
    result &= meta::lite::test::basic<char>(pv13.at_v2(2), 'i');
    result &= meta::lite::test::basic<size_t>(pv13.size_v1(), 3);
    result &= meta::lite::test::basic<size_t>(pv13.size_v2(), 4);
    return result;
}
bool utest_14()
{
    bool result = true;
    udt::pair__v<short, float> pv14 = {{19, 99, 38}, {1.7, 2.3, 8.9}};
    result &= meta::lite::test::basic<int>(pv14.sum_v1(), 156);
    result &= meta::lite::test::basic<int>(pv14.sum_v2(), 12.9);
    result &= meta::lite::test::basic<int>(pv14.Mult_v1(), 71478);
    result &= meta::lite::test::basic<int>(pv14.Mult_v2(std::pow(10, 3)), 34798);
    result &= meta::lite::test::basic<int>(pv14.Divi_v1(std::pow(10, 8)), 1399);
    result &= meta::lite::test::basic<int>(pv14.Divi_v2(std::pow(10, 3)), 28.73);
    return result;
}
bool utest_15()
{
    bool result = true;
    udt::pair__v<int, char> pv15;
    pv15 = {{19, 28, 39}, {'o', '2', 'o'}};
    result &= meta::lite::test::basic<bool>(pv15.empty(), false);
    pv15.clear_v1();
    result &= meta::lite::test::basic<bool>(pv15.empty_v1(), true);
    result &= meta::lite::test::basic<bool>(pv15.empty_v2(), false);
    pv15.clear_v2();
    result &= meta::lite::test::basic<bool>(pv15.empty_v2(), true);
    result &= meta::lite::test::basic<bool>(pv15.empty(), true);
    return result;
}
bool utest_16()
{
    bool result = true;
    std::vector<int> v1 = {10, 29, 39};
    std::vector<char> v2 = {'o', 'z', 'w'};
    int sum = 0;
    for (char c : v2)
        sum += int(c);
    udt::pair__v<int, char> pv16;
    result &= meta::lite::test::basic<bool>(pv16.empty(), true);
    pv16.set_v1(v1);
    result &= meta::lite::test::basic<bool>(pv16.empty_v1(), false);
    result &= meta::lite::test::basic<bool>(pv16.empty_v2(), true);
    pv16.set_v2(v2);
    result &= meta::lite::test::basic<bool>(pv16.empty_v2(), false);
    result &= meta::lite::test::basic<bool>(pv16.empty(), false);
    result &= meta::lite::test::basic<int>(pv16.sum_v1(), 78);
    result &= meta::lite::test::basic<int>(pv16.sum_v2(), sum);
    pv16.clear_all();
    result &= meta::lite::test::basic<bool>(pv16.empty(), true);
    return result;
}
bool utest_17()
{
    bool result = true;
    udt::pair__v<float, int> pv17 = {{19.8, 12.9, 11.7}, {99, 29, 29, 20}};
    result &= meta::lite::test::basic<size_t>(pv17.size_v1(), 3);
    result &= meta::lite::test::basic<size_t>(pv17.size_v2(), 4);
    result &= meta::lite::test::basic<int>(static_cast<int>(pv17.average_v1()), 14);
    result &= meta::lite::test::basic<int>(static_cast<int>(pv17.average_v2()), 44);
    return result;
}
bool utest_18()
{
    bool result = true;
    std::vector<int> v1 = {89, 99, 102, 129};
    std::vector<char> v2 = {'o', 'a', 'z', 'p', 'c'};
    udt::pair__v<int, char> pv18(v1, v2);
    result &= meta::lite::test::vector<int>(pv18.get_vec1(), v1);
    result &= meta::lite::test::vector<char>(pv18.get_vec2(), v2);
    return result;
}
bool utest_19()
{
    bool result = true;
    std::vector<int> v1 = {111, 97, 122, 112, 99};
    std::vector<char> v2 = {'Y', 'c', 'f', '~'};
    udt::pair__v<int, char> pv18 = {{89, 99, 102, 126}, {{'o', 'a', 'z', 'p', 'c'}}};
    pv18.swap_vecs();
    result &= meta::lite::test::vector<int>(pv18.get_vec1(), v1);
    result &= meta::lite::test::vector<char>(pv18.get_vec2(), v2);
    return result;
}
bool utest_20()
{
    bool result = true;
    udt::pair__v<double, int> pv20 = {{2.8, 3.8, 8.8, 0.8}, {9, 12, 29, 38, 20}};
    int num = 3;
    double dnum = 1.2;
    pv20 + num;
    pv20 + dnum;
    std::vector<double> v1 = {4.0, 5.0, 10.0, 2.0};
    std::vector<int> v2 = {12, 15, 32, 41, 23};
    result &= meta::lite::test::vector<double>(pv20.get_vec1(), v1);
    result &= meta::lite::test::vector<int>(pv20.get_vec2(), v2);
    return result;
}
bool utest_21()
{
    bool result = true;
    udt::pair__v<short, int> pv21 = {{3, 9, 8, 3, 2}, {90, 39, 28, 39, 29, 29}};
    short num1 = 3;
    int num2 = 9;
    pv21 *num1;
    pv21 *num2;
    std::vector<short> v1 = {9, 27, 24, 9, 6};
    std::vector<int> v2 = {810, 351, 252, 351, 261, 261};
    result &= meta::lite::test::vector<short>(pv21.get_vec1(), v1);
    result &= meta::lite::test::vector<int>(pv21.get_vec2(), v2);
    return result;
}
bool utest_22()
{
    bool result = true;
    udt::pair__v<char, short> pv22 = {{'z', 'x', 'u'}, {88, 98, 29, 33}};
    pv22 - '0';
    pv22 - short(88);
    std::vector<char> v1 = {'J', 'H', 'E'};
    std::vector<short> v2 = {0, 10, -59, -55};
    result &= meta::lite::test::vector<char>(pv22.get_vec1(), v1);
    result &= meta::lite::test::vector<short>(pv22.get_vec2(), v2);
    return result;
}
bool utest_23()
{
    bool result = true;
    udt::pair__v<int, char> pv23 = {{88, 29, 38, 39}, {'~', '|', 'x'}};
    pv23 / int(4);
    pv23 / char(2);
    std::vector<int> v1 = {22, 7, 9, 9};
    std::vector<char> v2 = {'?', '>', '<'};
    result &= meta::lite::test::vector<int>(pv23.get_vec1(), v1);
    result &= meta::lite::test::vector<char>(pv23.get_vec2(), v2);
    return result;
}
bool utest_24()
{
    bool result = true;
    udt::pair__v<int, char> pv24 = {{9, 27, 24, 9, 6}, {'~', '|', 'x'}};
    std::vector<int> v1 = {3, 9, 2, 9, 3};
    std::vector<char> v2 = {'!', '*', '0'};
    pv24 - v1;
    pv24 - v2;
    std::vector<int> v3 = {6, 18, 22, 0, 3};
    std::vector<char> v4 = {']', 'R', 'H'};
    result &= meta::lite::test::vector<int>(pv24.get_vec1(), v3);
    result &= meta::lite::test::vector<char>(pv24.get_vec2(), v4);
    return result;
}
bool utest_25()
{
    bool result = true;
    udt::pair__v<int, double> pv25;
    pv25 = {{29, 38, 39, 23}, {2.9, 3.3, 2.3}};
    std::vector<int> v1 = {1, 2, 1, 7};
    std::vector<double> v2 = {1.1, 1.7, 0.7};
    pv25 + v1;
    pv25 + v2;
    std::vector<int> v3 = {30, 40, 40, 30};
    std::vector<double> v4 = {4, 5, 3};
    result &= meta::lite::test::vector<int>(pv25.get_vec1(), v3);
    result &= meta::lite::test::vector<double>(pv25.get_vec2(), v4);
    return result;
}
int main()
{
    meta::lite::io::NewLines(5);
    meta::lite::io::NewLines(5);
    bool bresult;
    float fresult;
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
    UTS >> bresult;
    meta::lite::io::print<std::string>("All test result: ");
    meta::lite::io::println(meta::lite::test::test_message(bresult));
    udt::pair_v<int> v1 = {{77, 49, 388}, {392, 389, 209}};
    udt::pair__v<int, char> v2 = {{88, 92, 39}, {'i', ',', '.'}};
    meta::lite::io::print("The size of the pair_v data type in bytes: ");
    meta::lite::io::println(meta::lite::benchmark::mata_data(v1));
    meta::lite::io::print("The size of the pair__v data type in bytes: ");
    meta::lite::io::println(meta::lite::benchmark::mata_data(v2));
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
    UTB >> fresult;
    meta::lite::io::print<std::string>(
        "The average time for all unit test: " +
        std::to_string(fresult) + " us");
    return 0;
}