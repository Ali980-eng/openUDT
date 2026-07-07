#include "meta/lite/stream.hpp"
#include "udt/core/dynamic/dynamic_r.hpp"

/// @brief This function test the empty constructor and empty function in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_1()
{
    udt::dynamic_r d;
    return meta::lite::test::basic<bool>(d.empty(), true);
}

/// @brief This function test the int constructor and type function in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_2()
{
    udt::dynamic_r d(8);
    return meta::lite::test::basic<std::string>(d.type(), "int");
}

/// @brief This function test the double constructor and type function in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_3()
{
    udt::dynamic_r d(8.8);
    return meta::lite::test::basic<std::string>(d.type(), "double");
}

/// @brief This function test the char constructor and type function in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_4()
{
    udt::dynamic_r d('c');
    return meta::lite::test::basic<std::string>(d.type(), "char");
}

/// @brief This function test the float constructor and type function in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_5()
{
    udt::dynamic_r d(float(9.88));
    return meta::lite::test::basic<std::string>(d.type(), "float");
}

/// @brief This function test the operator = `int` and type function in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_6()
{
    udt::dynamic_r d = 8;
    return meta::lite::test::basic<std::string>(d.type(), "int");
}

/// @brief This function test the operator = `double` and type function in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_7()
{
    udt::dynamic_r d = 8.8;
    return meta::lite::test::basic<std::string>(d.type(), "double");
}

/// @brief This function test the operator = `char` and type function in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_8()
{
    udt::dynamic_r d = 'c';
    return meta::lite::test::basic<std::string>(d.type(), "char");
}

/// @brief This function test the operator = `float` and type function in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_9()
{
    udt::dynamic_r d = float(7.99);
    return meta::lite::test::basic<std::string>(d.type(), "float");
}

/// @brief This function test the set_int function and get_int function in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_10()
{
    udt::dynamic_r d;
    d.set_int(99);
    return meta::lite::test::basic<int>(d.get_int(), 99);
}

/// @brief This function test the set_char function and get_char function in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_11()
{
    udt::dynamic_r d;
    d.set_char('U');
    return meta::lite::test::basic<char>(d.get_char(), 'U');
}

/// @brief This function test the set_double function and get_double function in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_12()
{
    udt::dynamic_r d;
    d.set_double(9.22);
    return meta::lite::test::basic<double>(d.get_double(), 9.22);
}

/// @brief This function test the set_float function and get_float function in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_13()
{
    udt::dynamic_r d;
    d.set_float(7.77f);
    return meta::lite::test::basic<float>(d.get_float(), 7.77f);
}

/// @brief This function test the set_value function and type function in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_14()
{
    udt::dynamic_r d;
    d.set_value(10);
    return meta::lite::test::basic<std::string>(d.type(), "int");
}

/// @brief This function test the set_value function and type function in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_15()
{
    udt::dynamic_r d;
    d.set_value(9.88);
    return meta::lite::test::basic<std::string>(d.type(), "double");
}

/// @brief This function test the set_value function and type function in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_16()
{
    udt::dynamic_r d;
    d.set_value(float(8.15));
    return meta::lite::test::basic<std::string>(d.type(), "float");
}

/// @brief This function test the set_value function and type function in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_17()
{
    udt::dynamic_r d;
    d.set_value('i');
    return meta::lite::test::basic<std::string>(d.type(), "char");
}

/// @brief This function test the function is_complex in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_18()
{
    udt::dynamic_r d;
    return meta::lite::test::basic<bool>(d.is_complex(), false);
}

/// @brief This function test the function is_complex in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_19()
{
    udt::dynamic_r d;
    d.complex();
    return meta::lite::test::basic<bool>(d.is_complex(), true);
}

/// @brief This function test the Behavior of the object dynamic_r in complex style.
/// @return The basic test value (should be true).
bool utest_20()
{
    udt::dynamic_r d;
    d.complex();
    d = 10;
    d = 9.8;
    d = float(11.2);
    d = 'o';
    return meta::lite::test::basic<float>(d.get_float(), 11.2) &&
           meta::lite::test::basic<double>(d.get_double(), 9.8) &&
           meta::lite::test::basic<int>(d.get_int(), 10) &&
           meta::lite::test::basic<char>(d.get_char(), 'o');
}

/// @brief This function test the function is_pure_numeric in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_21()
{
    udt::dynamic_r d;
    d.complex();
    return meta::lite::test::basic<std::string>(d.type(), "complex") &&
           meta::lite::test::basic<bool>(d.is_pure_numeric(), false);
}

/// @brief This function test the function is_pure_numeric in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_22()
{
    udt::dynamic_r d;
    d.complex();
    d = 10;
    d = 9.8;
    d = float(11.2);
    return meta::lite::test::basic<bool>(d.is_pure_numeric(), true);
}

/// @brief This function test the functions has_int and has_float and has_double and has_char in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_23()
{
    udt::dynamic_r d;
    d.complex();
    d = 19;
    d = 'p';
    return meta::lite::test::basic<bool>(d.has_int(), true) &&
           meta::lite::test::basic<bool>(d.has_float(), false) &&
           meta::lite::test::basic<bool>(d.has_double(), false) &&
           meta::lite::test::basic<bool>(d.has_char(), true);
}

/// @brief This function test the has function in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_24()
{
    udt::dynamic_r d;
    d.complex();
    d = 19;
    d = 9.02;
    return meta::lite::test::basic<bool>(d.has("int"), true) &&
           meta::lite::test::basic<bool>(d.has("float"), false) &&
           meta::lite::test::basic<bool>(d.has("double"), true) &&
           meta::lite::test::basic<bool>(d.has("char"), false);
}

/// @brief This function test the functions is_complex and get_int in the object dynamic_r.
/// @return The result of the all basic tests.
bool utest_25()
{
    udt::dynamic_r d;
    bool result = true;
    d.complex();
    d = 10;
    d = 9.8;
    d = float(11.2);
    d = 'o';
    result &= meta::lite::test::basic<bool>(d.is_complex(), true);
    d.uncomplex(false);
    result &= meta::lite::test::basic<int>(d.get_int(), 10);
    result &= meta::lite::test::basic<bool>(d.is_complex(), false);
    return result;
}

/// @brief This function test the has function in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_26()
{
    udt::dynamic_r d = {10, 9.9f, 6.33, 'z'};
    return meta::lite::test::basic<bool>(d.has("int"), true) &&
           meta::lite::test::basic<bool>(d.has("float"), true) &&
           meta::lite::test::basic<bool>(d.has("double"), true) &&
           meta::lite::test::basic<bool>(d.has("char"), true) &&
           meta::lite::test::basic<bool>(d.is_complex(), true);
}

/// @brief This function test the operator == and != int in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_27()
{
    udt::dynamic_r d = 99;
    return meta::lite::test::basic<bool>(d == 99, true) &&
           meta::lite::test::basic<bool>(d != 38, true);
}

/// @brief This function test the operator == and != int in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_28()
{
    udt::dynamic_r d = 82;
    return meta::lite::test::basic<bool>(d == 23, false) &&
           meta::lite::test::basic<bool>(d != 82, false);
}

/// @brief This function test the operator == and != float in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_29()
{
    udt::dynamic_r d = 2.2f;
    return meta::lite::test::basic<bool>(d == 2.2f, true) &&
           meta::lite::test::basic<bool>(d != 1.7f, true);
}

/// @brief This function test the operator == and != float in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_30()
{
    udt::dynamic_r d = 8.23f;
    return meta::lite::test::basic<bool>(d == 2.2f, false) &&
           meta::lite::test::basic<bool>(d != 8.23f, false);
}

/// @brief This function test the operator == and != char in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_31()
{
    udt::dynamic_r d = 'C';
    return meta::lite::test::basic<bool>(d == 'C', true) &&
           meta::lite::test::basic<bool>(d != '[', true);
}

/// @brief This function test the operator == and != char in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_32()
{
    udt::dynamic_r d = 'a';
    return meta::lite::test::basic<bool>(d == 'c', false) &&
           meta::lite::test::basic<bool>(d != 'a', false);
}

/// @brief This function test the operator += and + int in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_33()
{
    udt::dynamic_r d = 9;
    d += 10;
    int result = d + 11;
    return meta::lite::test::basic<int>(result, 30);
}

/// @brief This function test the operator -= and - int in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_34()
{
    udt::dynamic_r d = 19;
    d -= 10;
    int result = d - 4;
    return meta::lite::test::basic<int>(result, 5);
}

/// @brief This function test the operator *= and * int in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_35()
{
    udt::dynamic_r d = 5;
    d *= 10;
    int result = d * 6;
    return meta::lite::test::basic<int>(result, 300);
}

/// @brief This function test the operator /= and / int in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_36()
{
    udt::dynamic_r d = 900;
    d /= 10;
    int result = d / 3;
    return meta::lite::test::basic<int>(result, 30);
}

/// @brief This function test the function has_bool in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_37()
{
    udt::dynamic_r d = true;
    return meta::lite::test::basic<bool>(d.has_bool(), true);
}

/// @brief This function test the function get_bool in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_38()
{
    udt::dynamic_r d = false;
    return meta::lite::test::basic<bool>(d.get_bool(), false);
}

/// @brief This function test the operator += and + double in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_39()
{
    udt::dynamic_r d = 9.9;
    d += 1.1;
    double result = d + 4.3;
    return meta::lite::test::basic<double>(result, 15.3);
}

/// @brief This function test the operator -= and - double in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_40()
{
    udt::dynamic_r d = 8.3;
    d -= 1.3;
    double result = d - 1.5;
    return meta::lite::test::basic<int>(10 * result, 55);
}

/// @brief This function test the operator *= and * double in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_41()
{
    udt::dynamic_r d = 1.5;
    d *= 4;
    double result = d * 1.5;
    return meta::lite::test::basic<double>(result, 9);
}

/// @brief This function test the operator /= and / double in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_42()
{
    udt::dynamic_r d = 6.4;
    d /= 2;                // 3.2
    double result = d / 2; // 1.6
    return meta::lite::test::basic<double>(result, 1.6);
}

/// @brief This function test the operator += and + float in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_43()
{
    udt::dynamic_r d = 6.66f;
    d += 7.44f; // 14.0f
    float result = d + 1.5f;
    return meta::lite::test::basic<float>(result, 15.6);
}

/// @brief This function test the operator -= and - float in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_44()
{
    udt::dynamic_r d = 2.24f;
    d -= 0.24f;
    float result = d - 0.5;
    return meta::lite::test::basic<float>(result, 1.5);
}

/// @brief This function test the operator *= and * float in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_45()
{
    udt::dynamic_r d = 0.01f;
    d *= 1000;
    float result = d * 0.15;
    return meta::lite::test::basic<float>(result, 1.5);
}

/// @brief This function test the operator /= and / float in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_46()
{
    udt::dynamic_r d = 112.4f;
    d /= 4;                 // 28.1
    float result = d / 0.5; //
    return meta::lite::test::basic<float>(result, 56.2);
}

/// @brief This function test the operator += and + char in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_47()
{
    udt::dynamic_r d = 'c';
    d += 2;
    char result = d + 10;
    return meta::lite::test::basic<char>(result, 'o');
}

/// @brief This function test the operator -= and - char in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_48()
{
    udt::dynamic_r d = 'k';
    d -= 4;
    char result = d - 3;
    return meta::lite::test::basic<char>(result, 'd');
}

/// @brief This function test the operator ^= and ^ int in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_49()
{
    udt::dynamic_r d = 10;
    d ^= 2;
    int result = d ^ 3;
    return meta::lite::test::basic<int>(result, std::pow(10, 6));
}

/// @brief This function test the operator % int in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_50()
{
    udt::dynamic_r d = 10;
    return meta::lite::test::basic<int>(d % 2, 0);
}

/// @brief This function test the operator %= int in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_51()
{
    udt::dynamic_r d = 12;
    d %= 2;
    return meta::lite::test::basic<int>(d.get_int(), 0);
}

/// @brief This function test the operator ^= double in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_52()
{
    udt::dynamic_r d = 2.5;
    d ^= 5;
    return meta::lite::test::basic<double>(d.get_double(), 97.65625);
}

/// @brief This function test the operator && bool in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_53()
{
    udt::dynamic_r d = true;
    return meta::lite::test::basic<bool>(d && false, false);
}

/// @brief This function test the operator && bool in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_54()
{
    udt::dynamic_r d = true;
    return meta::lite::test::basic<bool>(d && true, true);
}

/// @brief This function test the operator && bool in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_55()
{
    udt::dynamic_r d = false;
    return meta::lite::test::basic<bool>(d && true, false);
}

/// @brief This function test the operator && bool in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_56()
{
    udt::dynamic_r d = false;
    return meta::lite::test::basic<bool>(d && false, false);
}

/// @brief This function test the operator || bool in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_57()
{
    udt::dynamic_r d = true;
    return meta::lite::test::basic<bool>(d || false, true);
}

/// @brief This function test the operator || bool in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_58()
{
    udt::dynamic_r d = true;
    return meta::lite::test::basic<bool>(d || true, true);
}

/// @brief This function test the operator || bool in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_59()
{
    udt::dynamic_r d = false;
    return meta::lite::test::basic<bool>(d || true, true);
}

/// @brief This function test the operator || bool in the object dynamic_r.
/// @return The basic test value (should be true).
bool utest_60()
{
    udt::dynamic_r d = false;
    return meta::lite::test::basic<bool>(d || false, false);
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
    UTS << utest_26;
    UTS << utest_27;
    UTS << utest_28;
    UTS << utest_29;
    UTS << utest_30;
    UTS << utest_31;
    UTS << utest_32;
    UTS << utest_33;
    UTS << utest_34;
    UTS << utest_35;
    UTS << utest_36;
    UTS << utest_37;
    UTS << utest_38;
    UTS << utest_39;
    UTS << utest_40;
    UTS << utest_41;
    UTS << utest_42;
    UTS << utest_43;
    UTS << utest_44;
    UTS << utest_45;
    UTS << utest_46;
    UTS << utest_47;
    UTS << utest_48;
    UTS << utest_49;
    UTS << utest_50;
    UTS << utest_51;
    UTS << utest_52;
    UTS << utest_53;
    UTS << utest_54;
    UTS << utest_55;
    UTS << utest_56;
    UTS << utest_57;
    UTS << utest_58;
    UTS << utest_59;
    UTS << utest_60;
    UTS.print_summary();
    udt::dynamic_r d;
    meta::lite::io::println(
        "The size of the dynamic_r data type in bytes: ",
        meta::lite::benchmark::mata_data(d));
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
    UTB << utest_26;
    UTB << utest_27;
    UTB << utest_28;
    UTB << utest_29;
    UTB << utest_30;
    UTB << utest_31;
    UTB << utest_32;
    UTB << utest_33;
    UTB << utest_34;
    UTB << utest_35;
    UTB << utest_36;
    UTB << utest_37;
    UTB << utest_38;
    UTB << utest_39;
    UTB << utest_40;
    UTB << utest_41;
    UTB << utest_42;
    UTB << utest_43;
    UTB << utest_44;
    UTB << utest_45;
    UTB << utest_46;
    UTB << utest_47;
    UTB << utest_48;
    UTB << utest_49;
    UTB << utest_50;
    UTB << utest_51;
    UTB << utest_52;
    UTB << utest_53;
    UTB << utest_54;
    UTB << utest_55;
    UTB << utest_56;
    UTB << utest_57;
    UTB << utest_58;
    UTB << utest_59;
    UTB << utest_60;
    UTB.print_summary();
    return 0;
}