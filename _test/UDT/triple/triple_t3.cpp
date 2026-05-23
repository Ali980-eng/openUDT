#include "lite.hpp"
#include "UDT/triple.hpp"
/// @brief This function test the empty constructor and the function get_third in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_1()
{
    udt::triple_t3<int, char, bool> tt;
    return lite::test::basic<bool>(tt.get_third(), bool());
}
/// @brief This function test the constructor {T, T, T} and the function get_first in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_2()
{
    udt::triple_t3<short, double, char> tt = {188, 2.38, 'c'};
    return lite::test::basic<char>(tt.get_first(), 188);
}
/// @brief This function test the operator = triple_t3 and the function get_second in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_3()
{
    udt::triple_t3<short, double, char> tt1 = {188, 2.38, 'c'};
    udt::triple_t3<short, double, char> tt2 = tt1;
    return lite::test::basic<double>(tt2.get_second(), 2.38);
}
/// @brief This function test the functions set_first and set_second and set_third in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_4()
{
    udt::triple_t3<int, char, bool> tt;
    tt.set_first(10);
    tt.set_second('|');
    tt.set_third(true);
    return lite::test::basic<bool>(tt.get_second(), '|');
}
/// @brief This function test the function set in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_5()
{
    udt::triple_t3<int, char, bool> tt;
    tt.set(77, '<', false);
    return lite::test::basic<char>(tt.get_second(), '<');
}
/// @brief This function test the operator == in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_6()
{
    udt::triple_t3<short, int, char> tt1 = {12000, 1933330, 'i'};
    udt::triple_t3<short, int, char> tt2 = {12000, 1933330, 'i'};
    return lite::test::basic<bool>(tt1 == tt2, true);
}
/// @brief This function test the operator == in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_7()
{
    udt::triple_t3<short, int, char> tt1 = {12000, 1933330, 'i'};
    udt::triple_t3<short, int, char> tt2 = {2897, 5266330, 'c'};
    return lite::test::basic<bool>(tt1 == tt2, false);
}
/// @brief This function test the operator != in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_8()
{
    udt::triple_t3<short, int, char> tt1 = {12000, 1933330, 'i'};
    udt::triple_t3<short, int, char> tt2 = {12000, 1933330, 'i'};
    return lite::test::basic<bool>(tt1 != tt2, false);
}
/// @brief This function test the operator != in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_9()
{
    udt::triple_t3<short, int, char> tt1 = {12000, 1933330, 'i'};
    udt::triple_t3<short, int, char> tt2 = {2897, 5266330, 'c'};
    return lite::test::basic<bool>(tt1 != tt2, true);
}
/// @brief This function test the function swap in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_10()
{

    udt::triple_t3<short, int, char> tt1 = {12000, 1933330, 'i'};
    udt::triple_t3<short, int, char> tt2 = {2897, 5266330, 'c'};
    tt1.swap(tt2);
    return lite::test::basic<short>(tt2.get_first(), 12000);
}
/// @brief This function test the function sarch in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_11()
{
    udt::triple_t3<int, char, bool> tt = {188, 'o', false};
    return lite::test::basic<bool>(tt.sarch('o'), true);
}
/// @brief This function test the operator += int in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_12()
{
    udt::triple_t3<int, float, double> tt = {100, 2.3f, 8.8};
    tt += 30;
    return lite::test::basic<int>(tt.get_first(), 130);
}
/// @brief This function test the operator += float in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_13()
{
    udt::triple_t3<int, float, double> tt = {77, 2.77f, 837.1};
    tt += 66.6f;
    return lite::test::basic<int>(tt.get_second(), 69);
}
/// @brief This function test the operator += double in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_14()
{
    udt::triple_t3<int, float, double> tt = {10, 3.3f, 8.3};
    tt += 1.7;
    return lite::test::basic<double>(tt.get_third(), 10.0);
}
/// @brief This function test the operator += triple_t3 in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_15()
{
    udt::triple_t3<int, float, double> tt1 = {100, 2.3f, 8.8};
    udt::triple_t3<int, float, double> tt2 = {10, 3.3f, 8.3};
    udt::triple_t3<int, float, double> tt3 = {110, 5.6f, 17.1};
    tt1 += tt2;
    return lite::test::basic<int>(tt1 == tt3, true);
}
/// @brief This function test the operator ++ in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_16()
{
    udt::triple_t3<int, char, float> tt = {9, 'a', 1.8f};
    udt::triple_t3<int, char, float> t = {10, 'b', 2.8f};
    ++tt;
    return lite::test::basic<bool>(tt == t, true);
}
/// @brief This function test the operator -= int in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_17()
{
    udt::triple_t3<int, short, char> tt = {11, 38, 'z'};
    udt::triple_t3<int, short, char> t = {-7, 38, 'z'};
    tt -= 18;
    return lite::test::basic<bool>(tt == t, true);
}
/// @brief This function test the operator -= char in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_18()
{
    udt::triple_t3<float, int, char> tt = {77.92f, 22, 'o'};
    udt::triple_t3<float, int, char> t = {77.92f, 22, 'O'};
    tt -= ' ';
    return lite::test::basic<bool>(tt == t, true);
}
/// @brief This function test the operator -= int in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_19()
{
    udt::triple_t3<float, int, char> tt = {77.92f, 22, 'o'};
    udt::triple_t3<float, int, char> t = {77.92f, 0, 'o'};
    tt -= 22;
    return lite::test::basic<bool>(tt == t, true);
}
/// @brief This function test the operator -= triple_t3 in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_20()
{
    udt::triple_t3<int, float, double> tt1 = {100, 2.3f, 8.8};
    udt::triple_t3<int, float, double> tt2 = {10, 3.3f, 8.3};
    udt::triple_t3<int, float, double> tt3 = {90, -1.0f, 0.5};
    tt1 -= tt2;
    return lite::test::basic<bool>(tt1 == tt3, true);
}
/// @brief This function test the operator -- in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_21()
{
    udt::triple_t3<int, float, double> tt1 = {62, 2.3f, 4.3};
    udt::triple_t3<int, float, double> tt2 = {61, 1.3f, 3.3};
    --tt1;
    return lite::test::basic<bool>(tt1 == tt2, true);
}
/// @brief This function test the operator *= int in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_22()
{
    udt::triple_t3<int, float, double> tt1 = {62, 2.3f, 4.3};
    udt::triple_t3<int, float, double> tt2 = {124, 2.3f, 4.3};
    tt1 *= 2;
    return lite::test::basic<bool>(tt1 == tt2, true);
}
/// @brief This function test the operator *= float in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_23()
{
    udt::triple_t3<int, float, double> tt1 = {62, 2.3f, 4.3};
    udt::triple_t3<int, float, double> tt2 = {62, 5.29f, 4.3};
    tt1 *= 2.3f;
    return lite::test::basic<bool>(tt1 == tt2, true);
}
/// @brief This function test the operator *= double in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_24()
{
    udt::triple_t3<int, float, double> tt1 = {62, 2.3f, 4.3};
    udt::triple_t3<int, float, double> tt2 = {62, 2.3f, 23.65};
    tt1 *= 5.5;
    return lite::test::basic<bool>(tt1 == tt2, true);
}
/// @brief This function test the operator *= triple_t3 in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_25()
{
    udt::triple_t3<int, float, double> tt1 = {100, 2.3f, 8.8};
    udt::triple_t3<int, float, double> tt2 = {10, 3.3f, 8.3};
    udt::triple_t3<int, float, double> tt3 = {1000, 7.59f, 73.04};
    tt1 *= tt2;
    return lite::test::basic<int>(tt1.get_first(), tt3.get_first()) &&
           lite::test::basic<int>(tt1.get_second(), tt3.get_second()) &&
           lite::test::basic<int>(tt1.get_third(), tt3.get_third());
}
/// @brief This function test the operator /= int in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_26()
{
    udt::triple_t3<int, float, double> tt1 = {62, 2.3f, 4.3};
    udt::triple_t3<int, float, double> tt2 = {31, 2.3f, 4.3};
    tt1 /= 2;
    return lite::test::basic<bool>(tt1 == tt2, true);
}
/// @brief This function test the operator /= float in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_27()
{
    udt::triple_t3<int, float, double> tt1 = {62, 2.3f, 4.3};
    udt::triple_t3<int, float, double> tt2 = {62, 1.0f, 4.3};
    tt1 /= 2.3f;
    return lite::test::basic<bool>(tt1 == tt2, true);
}
/// @brief This function test the operator /= double in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_28()
{
    udt::triple_t3<int, float, double> tt1 = {62, 2.3f, 4.2};
    udt::triple_t3<int, float, double> tt2 = {62, 2.3f, 2.1};
    tt1 /= 2.0;
    return lite::test::basic<bool>(tt1 == tt2, true);
}
// @brief This function test the operator ^= int in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_29()
{
    udt::triple_t3<int, float, double> tt1 = {62, 2.3f, 4.3};
    udt::triple_t3<int, float, double> tt2 = {3844, 2.3f, 4.3};
    tt1 ^= 2;
    return lite::test::basic<bool>(tt1 == tt2, true);
}
// @brief This function test the operator ^= float in the object triple_t3.
/// @return The basic test value (should be true).
bool utest_30()
{
    udt::triple_t3<int, float, double> tt1 = {62, 2.3f, 4.3};
    udt::triple_t3<int, float, double> tt2 = {62, 5.29f, 4.3};
    tt1 ^= 2.0f;
    return lite::test::basic<bool>(tt1 == tt2, true);
}
int main()
{
    lite::io::NewLines();
    float fresult;
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
    udt::triple_t3<long, double, char> d;
    lite::io::print("The size of the dynamic data type in bytes: ");
    lite::io::println(lite::benchmark::mata_data(d));
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