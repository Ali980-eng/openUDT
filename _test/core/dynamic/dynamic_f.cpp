#include "metaCore/lite/stream.hpp"
#include "core/dynamic/dynamic_f.hpp"

bool utest_1()
{
    udt::dynamic_f d;
    return meta::lite::test::basic<bool>(d.empty(), true);
}

bool utest_2()
{
    udt::dynamic_f d(true);
    return meta::lite::test::basic<bool>(d.is_bool(), true);
}

bool utest_3()
{
    udt::dynamic_f d('A');
    return meta::lite::test::basic<bool>(d.is_char(), true);
}

bool utest_4()
{
    udt::dynamic_f d(short(123));
    return meta::lite::test::basic<bool>(d.is_short(), true);
}

bool utest_5()
{
    udt::dynamic_f d(12345);
    return meta::lite::test::basic<bool>(d.is_int(), true);
}

bool utest_6()
{
    udt::dynamic_f d(1234567890L);
    return meta::lite::test::basic<bool>(d.is_long(), true);
}

bool utest_7()
{
    udt::dynamic_f d(3.14f);
    return meta::lite::test::basic<bool>(d.is_float(), true);
}

bool utest_8()
{
    udt::dynamic_f d(3.14159265358979323846);
    return meta::lite::test::basic<bool>(d.is_double(), true);
}

bool utest_9()
{
    udt::dynamic_f d1 = 1000;
    udt::dynamic_f d2(d1);
    return meta::lite::test::basic<bool>(d2.is_int(), true);
}

bool utest_10()
{
    udt::dynamic_f d;
    d.set(true);
    return meta::lite::test::basic<bool>(d.type(), "bool");
}

bool utest_11()
{
    udt::dynamic_f d;
    d.set('Z');
    return meta::lite::test::basic<bool>(d.type(), "char");
}

bool utest_12()
{
    udt::dynamic_f d;
    d.set(short(456));
    return meta::lite::test::basic<bool>(d.type(), "short");
}

bool utest_13()
{
    udt::dynamic_f d;
    d.set(7890);
    return meta::lite::test::basic<bool>(d.type(), "int");
}

bool utest_14()
{
    udt::dynamic_f d;
    d.set(1234567890L);
    return meta::lite::test::basic<bool>(d.type(), "long");
}

bool utest_15()
{
    udt::dynamic_f d;
    d.set(2.71f);
    return meta::lite::test::basic<bool>(d.type(), "float");
}

bool utest_16()
{
    udt::dynamic_f d;
    d.set(1.6180339887);
    return meta::lite::test::basic<bool>(d.type(), "double");
}

bool utest_17()
{
    udt::dynamic_f d(true);
    return meta::lite::test::basic<bool>(d.get_bool(), true);
}

bool utest_18()
{
    udt::dynamic_f d('B');
    return meta::lite::test::basic<bool>(d.get_char(), 'B');
}

bool utest_19()
{
    udt::dynamic_f d(short(321));
    return meta::lite::test::basic<bool>(d.get_short(), short(321));
}

bool utest_20()
{
    udt::dynamic_f d(54321);
    return meta::lite::test::basic<bool>(d.get_int(), 54321);
}

bool utest_21()
{
    udt::dynamic_f d(9876543210L);
    return meta::lite::test::basic<bool>(d.get_long(), 9876543210L);
}

bool utest_22()
{
    udt::dynamic_f d(6.28f);
    return meta::lite::test::basic<bool>(d.get_float(), 6.28f);
}

bool utest_23()
{
    udt::dynamic_f d(3.1415926535);
    return meta::lite::test::basic<bool>(d.get_double(), 3.1415926535);
}

bool utest_24()
{
    udt::dynamic_f d = true;
    return meta::lite::test::basic<bool>(d == true, true);
}

bool utest_25()
{
    udt::dynamic_f d = true;
    return meta::lite::test::basic<bool>(d == false, false);
}

bool utest_26()
{
    udt::dynamic_f d = false;
    return meta::lite::test::basic<bool>(d == false, true);
}

bool utest_27()
{
    udt::dynamic_f d = false;
    return meta::lite::test::basic<bool>(d == true, false);
}

bool utest_28()
{
    udt::dynamic_f d = 'a';
    return meta::lite::test::basic<bool>(d == 'a', true);
}

bool utest_29()
{
    udt::dynamic_f d = 'a';
    return meta::lite::test::basic<bool>(d == 'b', false);
}

bool utest_30()
{
    udt::dynamic_f d = 100;
    return meta::lite::test::basic<bool>(d == 100, true);
}

bool utest_31()
{
    udt::dynamic_f d = 100;
    return meta::lite::test::basic<bool>(d == 200, false);
}

bool utest_32()
{
    udt::dynamic_f d = 1000L;
    return meta::lite::test::basic<bool>(d == 1000L, true);
}

bool utest_33()
{
    udt::dynamic_f d = 1000L;
    return meta::lite::test::basic<bool>(d == 2000L, false);
}

bool utest_34()
{
    udt::dynamic_f d = 3.14f;
    return meta::lite::test::basic<bool>(d == 3.14f, true);
}

bool utest_35()
{
    udt::dynamic_f d = 3.14f;
    return meta::lite::test::basic<bool>(d == 2.71f, false);
}

bool utest_36()
{
    udt::dynamic_f d = 2.7182818284;
    return meta::lite::test::basic<bool>(d == 2.7182818284, true);
}

bool utest_37()
{
    udt::dynamic_f d = 2.7182818284;
    return meta::lite::test::basic<bool>(d == 3.1415926535, false);
}

bool utest_38()
{
    udt::dynamic_f d1 = 12345;
    udt::dynamic_f d2 = 12345;
    return meta::lite::test::basic<bool>(d1 == d2, true);
}

bool utest_39()
{
    udt::dynamic_f d = true;
    return meta::lite::test::basic<bool>(d != false, true);
}

bool utest_40()
{
    udt::dynamic_f d = true;
    return meta::lite::test::basic<bool>(d != true, false);
}

bool utest_41()
{
    udt::dynamic_f d = 'X';
    return meta::lite::test::basic<bool>(d != 'Y', true);
}

bool utest_42()
{
    udt::dynamic_f d = 'X';
    return meta::lite::test::basic<bool>(d != 'X', false);
}

bool utest_43()
{
    udt::dynamic_f d = 500;
    return meta::lite::test::basic<bool>(d != 600, true);
}

bool utest_44()
{
    udt::dynamic_f d = 500;
    return meta::lite::test::basic<bool>(d != 500, false);
}

bool utest_45()
{
    udt::dynamic_f d = 5000L;
    return meta::lite::test::basic<bool>(d != 6000L, true);
}

bool utest_46()
{
    udt::dynamic_f d = 5000L;
    return meta::lite::test::basic<bool>(d != 5000L, false);
}

bool utest_47()
{
    udt::dynamic_f d = 1.23f;
    return meta::lite::test::basic<bool>(d != 4.56f, true);
}

bool utest_48()
{
    udt::dynamic_f d = 1.23f;
    return meta::lite::test::basic<bool>(d != 1.23f, false);
}

bool utest_49()
{
    udt::dynamic_f d = 9.87;
    return meta::lite::test::basic<bool>(d != 6.54, true);
}

bool utest_50()
{
    udt::dynamic_f d = 9.87;
    return meta::lite::test::basic<bool>(d != 9.87, false);
}

bool utest_51()
{
    udt::dynamic_f d1 = 12345;
    udt::dynamic_f d2 = 54321;
    return meta::lite::test::basic<bool>(d1 != d2, true);
}

bool utest_52()
{
    udt::dynamic_f d1 = 12345;
    udt::dynamic_f d2 = 12345;
    return meta::lite::test::basic<bool>(d1 != d2, false);
}

int main()
{
    meta::lite::io::NewLines();
    return 0;
}