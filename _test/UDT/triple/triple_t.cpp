#include "lite.hpp"
#include "UDT/triple.hpp"
/// @brief This function test the function get_first in the object triple_t.
/// @return The basic test value (should be true).
bool utest_1()
{
    udt::triple_t<int> tt = {10, 29, 33};
    return lite::test::basic<int>(tt.get_first(), 10);
}
/// @brief This function test the function get_second in the object triple_t.
/// @return The basic test value (should be true).
bool utest_2()
{
    udt::triple_t<short> tt = {29, 38, 58};
    return lite::test::basic<short>(tt.get_second(), 38);
}
/// @brief This function test the function get_third in the object triple_t.
/// @return The basic test value (should be true).
bool utest_3()
{
    udt::triple_t<char> tt = {'o', 'z', 'v'};
    return lite::test::basic<char>(tt.get_third(), 'v');
}
/// @brief This function test the empty constructor in the object triple_t.
/// @return The basic test value (should be true).
bool utest_4()
{
    udt::triple_t<double> tt;
    return lite::test::basic<double>(tt.get_second(), 0.0);
}
/// @brief This function test the operator = {float, float, float} in the object triple_t.
/// @return The basic test value (should be true).
bool utest_5()
{
    udt::triple_t<float> tt;
    tt = {1.2f, 2.8f, 39.3f};
    return lite::test::basic<float>(tt.get_first(), 1.2f);
}
/// @brief This function test the function set_first and set_second and set_third in the object triple_t.
/// @return The basic test value (should be true).
bool utest_6()
{
    udt::triple_t<int> tt;
    tt.set_first(100);
    tt.set_second(113);
    tt.set_third(332);
    return lite::test::basic<int>(tt.max(), 332);
}
/// @brief This function test the function set in the object triple_t.
/// @return The basic test value (should be true).
bool utest_7()
{
    udt::triple_t<int> tt;
    tt.set(19, 18, 33);
    return lite::test::basic<int>(tt.min(), 18);
}
/// @brief This function test the operator = triple_t in the object triple_t.
/// @return The basic test value (should be true).
bool utest_8()
{
    udt::triple_t<char> tt1 = {'-', '*', '2'};
    udt::triple_t<char> tt2 = tt1;
    return lite::test::basic<char>(tt2.get_second(), '*');
}
/// @brief This function test the function swap in the object triple_t.
/// @return The basic test value (should be true).
bool utest_9()
{
    udt::triple_t<short> tt1 = {10, 28, 33};
    udt::triple_t<short> tt2 = {99, 38, 29};
    tt1.swap(tt2);
    return lite::test::basic<short>(tt1.get_second(), 38);
}
/// @brief This function test the function average in the object triple_t.
/// @return The basic test value (should be true).
bool utest_10()
{
    udt::triple_t<double> tt = {2.3, 5.4, 51.2};
    return lite::test::basic<int>(tt.average() * 100, 1963);
}
/// @brief This function test the function sum in the object triple_t.
/// @return The basic test value (should be true).
bool utest_11()
{
    udt::triple_t<int> tt = {22, 45, 23};
    return lite::test::basic<int>(tt.sum(), 90);
}
/// @brief This function test the function product in the object triple_t.
/// @return The basic test value (should be true).
bool utest_12()
{
    udt::triple_t<short> tt = {4, 3, 12};
    return lite::test::basic<short>(tt.product(), 144);
}
/// @brief This function test the operator == triple_t in the object triple_t.
/// @return The basic test value (should be true).
bool utest_13()
{
    udt::triple_t<short> tt1 = {4, 3, 9};
    udt::triple_t<short> tt2 = {2, 8, 3};
    return lite::test::basic<bool>(tt1 == tt2, false);
}
/// @brief This function test the operator != triple_t in the object triple_t.
/// @return The basic test value (should be true).
bool utest_14()
{
    udt::triple_t<short> tt1 = {4, 3, 9};
    udt::triple_t<short> tt2 = {2, 8, 3};
    return lite::test::basic<bool>(tt1 != tt2, true);
}
/// @brief This function test the operator == triple_t in the object triple_t.
/// @return The basic test value (should be true).
bool utest_15()
{
    udt::triple_t<short> tt1 = {2, 8, 3};
    udt::triple_t<short> tt2 = {2, 8, 3};
    return lite::test::basic<bool>(tt1 == tt2, true);
}
/// @brief This function test the operator != triple_t in the object triple_t.
/// @return The basic test value (should be true).
bool utest_16()
{
    udt::triple_t<short> tt1 = {2, 8, 3};
    udt::triple_t<short> tt2 = {2, 8, 3};
    return lite::test::basic<bool>(tt1 != tt2, false);
}
/// @brief This function test the operator += int in the object triple_t.
/// @return The basic test value (should be true).
bool utest_17()
{
    udt::triple_t<char> tt = {'o', '8', '#'};
    tt += 15; // {'~', 'G', '2'}
    return lite::test::basic<char>(tt.get_second(), 'G');
}
/// @brief This function test the operator -= int in the object triple_t.
/// @return The basic test value (should be true).
bool utest_18()
{
    udt::triple_t<int> tt = {138, 983, 938};
    tt -= 111;
    return lite::test::basic<int>(tt[3], 827);
}
/// @brief This function test the operator *= double in the object triple_t.
/// @return The basic test value (should be true).
bool utest_19()
{
    udt::triple_t<double> tt = {13.8, 9.83, 3.3};
    tt *= 2;
    return lite::test::basic<double>(tt[1], 27.6);
}
/// @brief This function test the operator /= int in the object triple_t.
/// @return The basic test value (should be true).
bool utest_20()
{
    udt::triple_t<double> tt = {1.8, 2.5, 8.8};
    tt /= 2;
    return lite::test::basic<double>(tt[3], 4.4);
}
/// @brief This function test the operator ++ in the object triple_t.
/// @return The basic test value (should be true).
bool utest_21()
{
    udt::triple_t<short> tt = {12, 23, 19};
    ++tt;
    return lite::test::basic<short>(tt[2], 24);
}
/// @brief This function test the operator -- in the object triple_t.
/// @return The basic test value (should be true).
bool utest_22()
{
    udt::triple_t<short> tt = {12, 23, 19};
    --tt;
    return lite::test::basic<short>(tt[1], 11);
}
/// @brief This function test the operator += triple_t in the object triple_t.
/// @return The basic test value (should be true).
bool utest_23()
{
    udt::triple_t<int> tt1 = {1, 9, 3};
    udt::triple_t<int> tt2 = {9, 2, 9};
    tt1 += tt2;
    return lite::test::basic<int>(tt1[3], 12);
}
/// @brief This function test the operator -= triple_t in the object triple_t.
/// @return The basic test value (should be true).
bool utest_24()
{
    udt::triple_t<double> tt1 = {19.8, 38.7, 29.3};
    udt::triple_t<double> tt2 = {22.8, 19.3, 29.3};
    tt1 -= tt2;
    return lite::test::basic<int>(tt1[1], -3);
}
/// @brief This function test the operator *= triple_t in the object triple_t.
/// @return The basic test value (should be true).
bool utest_25()
{
    udt::triple_t<float> tt1 = {11.2f, 2.3f, 39.4f};
    udt::triple_t<float> tt2 = {22.3f, 29.3f, 11.2f};
    tt1 *= tt2;
    return lite::test::basic<float>(tt1[2], 67.39f);
}
/// @brief This function test the operator /= triple_t in the object triple_t.
/// @return The basic test value (should be true).
bool utest_26()
{
    udt::triple_t<int> tt1 = {12, 100, 99};
    udt::triple_t<int> tt2 = {3, 10, 9};
    tt1 /= tt2;
    return lite::test::basic<int>(tt1[3], 11);
}
/// @brief This function test the function element_search in the object triple_t.
/// @return The basic test value (should be true).
bool utest_27()
{
    udt::triple_t<char> tt = {'x', '=', '8'};
    return lite::test::basic<bool>(tt.element_search('8'), true);
}
/// @brief This function test the operator [] and the function change_element by index in the object triple_t.
/// @return The basic test value (should be true).
bool utest_28()
{
    udt::triple_t<char> tt = {'p', '2', '.'};
    tt.change_element<true>('\0', '/', 2);
    return lite::test::basic<char>(tt[2], '/');
}
/// @brief This function test the operator [] and the function change_element by element_search in the object triple_t.
/// @return The basic test value (should be true).
bool utest_29()
{
    udt::triple_t<int> tt = {10, 28, 39};
    tt.change_element(10, 88);
    return lite::test::basic<int>(tt[1], 88);
}
/// @brief This function test the operator [] and the function change_element by element_search in the object triple_t.
/// @return The basic test value (should be true).
bool utest_30()
{
    udt::triple_t<char> tt = {'u', '9', 'c'};
    tt.change_element('c', '8');
    return lite::test::basic<char>(tt[3], '8');
}
void size_triple_t()
{
    udt::triple_t<bool> ttb;
    lite::io::print("The size of the triple_t<bool> data type in bytes: ");
    lite::io::println(lite::benchmark::mata_data(ttb));
    udt::triple_t<char> ttc;
    lite::io::print("The size of the triple_t<char> data type in bytes: ");
    lite::io::println(lite::benchmark::mata_data(ttc));
    udt::triple_t<short> tts;
    lite::io::print("The size of the triple_t<short> data type in bytes: ");
    lite::io::println(lite::benchmark::mata_data(tts));
    udt::triple_t<int> tti;
    lite::io::print("The size of the triple_t<int> data type in bytes: ");
    lite::io::println(lite::benchmark::mata_data(tti));
    udt::triple_t<long> ttl;
    lite::io::print("The size of the triple_t<long> data type in bytes: ");
    lite::io::println(lite::benchmark::mata_data(ttl));
    udt::triple_t<float> ttf;
    lite::io::print("The size of the triple_t<float> data type in bytes: ");
    lite::io::println(lite::benchmark::mata_data(ttf));
    udt::triple_t<long long> ttll;
    lite::io::print("The size of the triple_t<long long> data type in bytes: ");
    lite::io::println(lite::benchmark::mata_data(ttll));
    udt::triple_t<double> ttd;
    lite::io::print("The size of the triple_t<double> data type in bytes: ");
    lite::io::println(lite::benchmark::mata_data(ttd));
}
int main()
{
    lite::io::NewLines(5);
    bool result = true;
    lite::function::test_stream UTS;
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
    UTS << utest_26;
    UTS << utest_27;
    UTS << utest_28;
    UTS << utest_29;
    UTS << utest_30;
    UTS >> result;
    lite::io::print<std::string>("All test result: ");
    lite::io::println(lite::test::test_message(result));
    size_triple_t();
    float fresult;
    lite::function::benchmark_stream<false> UTB = 6;
    // UTB: unit test benchmark
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
    UTB << utest_26;
    UTB << utest_27;
    UTB << utest_28;
    UTB << utest_29;
    UTB << utest_30;
    UTB >> fresult;
    lite::io::print<std::string>(
        "The average time for all unit test: " +
        std::to_string(fresult) + " us");
    return 0;
}