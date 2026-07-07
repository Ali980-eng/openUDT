#include "meta/lite/stream.hpp"
#include "udt/core/dynamic.hpp"

bool utest_1()
{
    udt::dynamic d;
    return meta::lite::test::basic<bool>(
        d.get_double() == 0.0 &&
            d.type() == "double",
        true);
}

bool utest_2()
{
    udt::dynamic d(true);
    return meta::lite::test::basic<bool>(
        d.get_bool() == true &&
            d.type() == "bool",
        true);
}

bool utest_3()
{
    udt::dynamic d('/');
    return meta::lite::test::basic<bool>(
        d.get_char() == '/' &&
            d.type() == "char",
        true);
}

bool utest_4()
{
    udt::dynamic d(2.3f);
    return meta::lite::test::basic<bool>(
        d.get_float() &&
            d.type() == "float",
        true);
}

bool utest_5()
{
    udt::dynamic d(9.3);
    return meta::lite::test::basic<bool>(
        d.get_double() == 9.3 &&
            d.type() == "double",
        true);
}

bool utest_6()
{
    udt::dynamic d1 = 77;
    udt::dynamic d2 = d1;
    return meta::lite::test::basic<bool>(
        d1.get_int() == d2.get_int() &&
            d1.type() == d2.type(),
        true);
}

bool utest_7()
{
    udt::dynamic d;
    d.set(true);
    return meta::lite::test::basic<bool>(d.get_bool(), true);
}

bool utest_8()
{
    udt::dynamic d;
    d.set('O');
    return meta::lite::test::basic<char>(d.get_char(), 'O');
}

bool utest_9()
{
    udt::dynamic d;
    d.set(88);
    return meta::lite::test::basic<int>(d.get_int(), 88);
}

bool utest_10()
{
    udt::dynamic d;
    d.set(88.7f);
    return meta::lite::test::basic<float>(d.get_float(), 88.7f);
}

bool utest_11()
{
    udt::dynamic d;
    d.set(8.3);
    return meta::lite::test::basic<double>(d.get_double(), 8.3);
}

bool utest_12()
{
    udt::dynamic d = 99;
    d.reset();
    return meta::lite::test::basic<double>(d.get_double(), 0.0);
}

bool utest_13()
{
    udt::dynamic d = true;
    return meta::lite::test::basic<bool>(d == true, true);
}

bool utest_14()
{
    udt::dynamic d = true;
    return meta::lite::test::basic<bool>(d != true, false);
}

bool utest_15()
{
    udt::dynamic d = true;
    return meta::lite::test::basic<bool>(d == false, false);
}

bool utest_16()
{
    udt::dynamic d = true;
    return meta::lite::test::basic<bool>(d != false, true);
}

bool utest_17()
{
    udt::dynamic d = 'P';
    return meta::lite::test::basic<bool>(d == 'P', true);
}

bool utest_18()
{
    udt::dynamic d = 'P';
    return meta::lite::test::basic<bool>(d == 'O', false);
}

bool utest_19()
{
    udt::dynamic d = 'P';
    return meta::lite::test::basic<bool>(d != 'O', true);
}

bool utest_20()
{
    udt::dynamic d = 'P';
    return meta::lite::test::basic<bool>(d != 'P', false);
}

bool utest_21()
{
    udt::dynamic d = 9938;
    return meta::lite::test::basic<bool>(d == 9938, true);
}

bool utest_22()
{
    udt::dynamic d = 9938;
    return meta::lite::test::basic<bool>(d == 9838, false);
}

bool utest_23()
{
    udt::dynamic d = 9938;
    return meta::lite::test::basic<bool>(d != 9938, false);
}

bool utest_24()
{
    udt::dynamic d = 9938;
    return meta::lite::test::basic<bool>(d != 9838, true);
}

bool utest_25()
{
    udt::dynamic d = 9.4f;
    return meta::lite::test::basic<bool>(d == 9.4f, true);
}

bool utest_26()
{
    udt::dynamic d = 9.4f;
    return meta::lite::test::basic<bool>(d == 8.7f, false);
}

bool utest_27()
{
    udt::dynamic d = 9.4f;
    return meta::lite::test::basic<bool>(d != 9.4f, false);
}

bool utest_28()
{
    udt::dynamic d = 9.4f;
    return meta::lite::test::basic<bool>(d != 8.7f, true);
}

bool utest_29()
{
    udt::dynamic d = 2.2;
    return meta::lite::test::basic<bool>(d == 2.2, true);
}

bool utest_30()
{
    udt::dynamic d = 2.2;
    return meta::lite::test::basic<bool>(d == 3.5, false);
}

bool utest_31()
{
    udt::dynamic d = 2.2;
    return meta::lite::test::basic<bool>(d != 2.2, false);
}

bool utest_32()
{
    udt::dynamic d = 2.2;
    return meta::lite::test::basic<bool>(d != 3.3, true);
}

bool utest_33()
{
    udt::dynamic d = 99;
    ++d;
    return meta::lite::test::basic<int>(d.get_int(), 100);
}

bool utest_34()
{
    udt::dynamic d = 38;
    --d;
    return meta::lite::test::basic<int>(d.get_int(), 37);
}

bool utest_35()
{
    udt::dynamic d = true;
    return meta::lite::test::basic<bool>(d && true, true);
}

bool utest_36()
{
    udt::dynamic d = true;
    return meta::lite::test::basic<bool>(d && false, false);
}

bool utest_37()
{
    udt::dynamic d = false;
    return meta::lite::test::basic<bool>(d && true, false);
}

bool utest_38()
{
    udt::dynamic d = false;
    return meta::lite::test::basic<bool>(d && false, false);
}

bool utest_39()
{
    udt::dynamic d = true;
    return meta::lite::test::basic<bool>(d || true, true);
}

bool utest_40()
{
    udt::dynamic d = true;
    return meta::lite::test::basic<bool>(d || false, true);
}

bool utest_41()
{
    udt::dynamic d = false;
    return meta::lite::test::basic<bool>(d || true, true);
}

bool utest_42()
{
    udt::dynamic d = false;
    return meta::lite::test::basic<bool>(d || false, false);
}

bool utest_43()
{
    udt::dynamic d = true;
    return meta::lite::test::basic<bool>(d ^ true, false);
}

bool utest_44()
{
    udt::dynamic d = true;
    return meta::lite::test::basic<bool>(d ^ false, true);
}

bool utest_45()
{
    udt::dynamic d = false;
    return meta::lite::test::basic<bool>(d ^ true, true);
}

bool utest_46()
{
    udt::dynamic d = false;
    return meta::lite::test::basic<bool>(d ^ false, false);
}

bool utest_47()
{
    udt::dynamic d = true;
    return meta::lite::test::basic<bool>(!d, false);
}

bool utest_48()
{
    udt::dynamic d = false;
    return meta::lite::test::basic<bool>(!d, true);
}

bool utest_49()
{
    udt::dynamic d = true;
    d &= true;
    return meta::lite::test::basic<bool>(d.get_bool(), true);
}

bool utest_50()
{
    udt::dynamic d = true;
    d &= false;
    return meta::lite::test::basic<bool>(d.get_bool(), false);
}

bool utest_51()
{
    udt::dynamic d = false;
    d &= true;
    return meta::lite::test::basic<bool>(d.get_bool(), false);
}

bool utest_52()
{
    udt::dynamic d = false;
    d &= false;
    return meta::lite::test::basic<bool>(d.get_bool(), false);
}

bool utest_53()
{
    udt::dynamic d = true;
    d |= true;
    return meta::lite::test::basic<bool>(d.get_bool(), true);
}

bool utest_54()
{
    udt::dynamic d = true;
    d |= false;
    return meta::lite::test::basic<bool>(d.get_bool(), true);
}

bool utest_55()
{
    udt::dynamic d = false;
    d |= true;
    return meta::lite::test::basic<bool>(d.get_bool(), true);
}

bool utest_56()
{
    udt::dynamic d = false;
    d |= false;
    return meta::lite::test::basic<bool>(d.get_bool(), false);
}

bool utest_57()
{
    udt::dynamic d = 77;
    d += ' ';
    return meta::lite::test::basic<int>(d.get_int(), 109);
}

bool utest_58()
{
    udt::dynamic d = 88;
    d += 12;
    return meta::lite::test::basic<int>(d.get_int(), 100);
}

bool utest_59()
{
    udt::dynamic d = 9983;
    d += 16.9f;
    return meta::lite::test::basic<int>(d.get_int(), 9999);
}

bool utest_60()
{
    udt::dynamic d = 88.9;
    d += 1.1;
    return meta::lite::test::basic<double>(d.get_double(), 90.0);
}

bool utest_61()
{
    udt::dynamic d = 250;
    d -= '|';
    return meta::lite::test::basic<int>(d.get_int(), 126);
}

bool utest_62()
{
    udt::dynamic d = 200;
    d -= 100;
    return meta::lite::test::basic<int>(d.get_int(), 100);
}

bool utest_63()
{
    udt::dynamic d = 9.5f;
    d -= 1.3f;
    return meta::lite::test::basic<float>(d.get_float(), 8.2f);
}

bool utest_64()
{
    udt::dynamic d = 8.8;
    d -= 4.4;
    return meta::lite::test::basic<double>(d.get_double(), 4.4);
}

bool utest_65()
{
    udt::dynamic d = 18;
    d *= '~';
    return meta::lite::test::basic<int>(d.get_int(), 2268);
}

bool utest_66()
{
    udt::dynamic d = 24;
    d *= 22;
    return meta::lite::test::basic<int>(d.get_int(), 528);
}

bool utest_67()
{
    udt::dynamic d = 100;
    d *= 2.8f;
    return meta::lite::test::basic<int>(d.get_int(), 279);
}

bool utest_68()
{
    udt::dynamic d = 1000;
    d *= 0.525;
    return meta::lite::test::basic<int>(d.get_int(), 525);
}

bool utest_69()
{
    udt::dynamic d = 80;
    d /= '\n';
    return meta::lite::test::basic<int>(d.get_int(), 8);
}

bool utest_70()
{
    udt::dynamic d = 160;
    d /= 8;
    return meta::lite::test::basic<int>(d.get_int(), 20);
}

bool utest_71()
{
    udt::dynamic d = 7;
    d /= 1.2f;
    return meta::lite::test::basic<int>(d.get_int(), 5);
}

bool utest_72()
{
    udt::dynamic d = 22.8;
    d /= 2.0;
    return meta::lite::test::basic<double>(d.get_double(), 11.4);
}

bool utest_73()
{
    udt::dynamic d = 2;
    d ^= '\n';
    return meta::lite::test::basic<int>(d.get_int(), 1024);
}

bool utest_74()
{
    udt::dynamic d = 1.01f;
    d ^= 365;
    return meta::lite::test::basic<int>(100 * d.get_float(), 3778);
}

bool utest_75()
{
    udt::dynamic d = 77;
    d ^= 1.5f;
    return meta::lite::test::basic<int>(d.get_int(), 675);
}

bool utest_76()
{
    udt::dynamic d = 65;
    d ^= 1.1;
    return meta::lite::test::basic<int>(d.get_int(), 98);
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
    UTS << utest_61;
    UTS << utest_62;
    UTS << utest_63;
    UTS << utest_64;
    UTS << utest_65;
    UTS << utest_66;
    UTS << utest_67;
    UTS << utest_68;
    UTS << utest_69;
    UTS << utest_70;
    UTS << utest_71;
    UTS << utest_72;
    UTS << utest_73;
    UTS << utest_74;
    UTS << utest_75;
    UTS << utest_76;
    UTS.print_summary();
    udt::dynamic d;
    meta::lite::io::println(
        "The size of the dynamic data type in bytes: ",
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
    UTB << utest_61;
    UTB << utest_62;
    UTB << utest_63;
    UTB << utest_64;
    UTB << utest_65;
    UTB << utest_66;
    UTB << utest_67;
    UTB << utest_68;
    UTB << utest_69;
    UTB << utest_70;
    UTB << utest_71;
    UTB << utest_72;
    UTB << utest_73;
    UTB << utest_74;
    UTB << utest_75;
    UTB << utest_76;
    UTB.print_summary();
    return 0;
}