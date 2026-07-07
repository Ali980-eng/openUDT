#include "meta/lite/stream.hpp"
#include "udt/core/dynamic/dynamic_t.hpp"

/// @brief This function test the empty constructor and get_float function in the object dynamic_t.
/// @return The basic test value (should be true).
bool utest_1()
{
    udt::dynamic_t d;
    return meta::lite::test::basic<bool>(d.get_float(), 0.0f);
}

bool utest_2()
{
    udt::dynamic_t d(true);
    return meta::lite::test::basic<bool>(d.get_bool(), true);
}

bool utest_3()
{
    udt::dynamic_t d('o');
    return meta::lite::test::basic<char>(d.get_char(), 'o');
}

bool utest_4()
{
    udt::dynamic_t d(18);
    return meta::lite::test::basic<int>(d.get_int(), 18);
}

bool utest_5()
{
    udt::dynamic_t d(1.3f);
    return meta::lite::test::basic<float>(d.get_float(), 1.3f);
}

bool utest_6()
{
    udt::dynamic_t d(1.8);
    return meta::lite::test::basic<double>(d.get_double(), 1.8);
}

bool utest_7()
{
    udt::dynamic_t d = {true, 'I', 883, 22.5f, 33.9};
    return meta::lite::test::basic<bool>(
        d.get_bool() == true &&
            d.get_char() == 'I' &&
            d.get_int() == 883 &&
            d.get_float() == 22.5f &&
            d.get_double() == 33.9,
        true);
}

bool utest_8()
{
    udt::dynamic_t d1 = 9992;
    udt::dynamic_t d2(d1);
    return meta::lite::test::basic<int>(d2.get_int(), 9992);
}

bool utest_9()
{
    udt::dynamic_t d;
    d.set(true);
    return meta::lite::test::basic<bool>(d.get_bool(), true);
}

bool utest_10()
{
    udt::dynamic_t d;
    d.set('U');
    return meta::lite::test::basic<char>(d.get_char(), 'U');
}

bool utest_11()
{
    udt::dynamic_t d;
    d.set(8892);
    return meta::lite::test::basic<int>(d.get_int(), 8892);
}

bool utest_12()
{
    udt::dynamic_t d;
    d.set(22.3f);
    return meta::lite::test::basic<float>(d.get_float(), 22.3f);
}

bool utest_13()
{
    udt::dynamic_t d;
    d.set(93.8);
    return meta::lite::test::basic<double>(d.get_double(), 93.8);
}

bool utest_14()
{
    udt::dynamic_t d;
    d.set(true, 'O', 8831, 2.3f, 99.3);
    return meta::lite::test::basic<bool>(
        d.get_bool() == true &&
            d.get_char() == 'O' &&
            d.get_int() == 8831 &&
            d.get_float() == 2.3f &&
            d.get_double() == 99.3,
        true);
}

bool utest_15()
{
    udt::dynamic_t d1;
    udt::dynamic_t d2 = {false, 'z', 9283, 22.9f, 11.2};
    d2.clear();
    return meta::lite::test::basic<bool>(d1 == d2, true);
}

bool utest_16()
{
    udt::dynamic_t d = true;
    return meta::lite::test::basic<bool>(d && false, false);
}

bool utest_17()
{
    udt::dynamic_t d = false;
    return meta::lite::test::basic<bool>(d && false, false);
}

bool utest_18()
{
    udt::dynamic_t d = true;
    return meta::lite::test::basic<bool>(d && true, true);
}

bool utest_19()
{
    udt::dynamic_t d = false;
    return meta::lite::test::basic<bool>(d && true, false);
}

bool utest_20()
{
    udt::dynamic_t d = true;
    return meta::lite::test::basic<bool>(d || false, true);
}

bool utest_21()
{
    udt::dynamic_t d = false;
    return meta::lite::test::basic<bool>(d || false, false);
}

bool utest_22()
{
    udt::dynamic_t d = true;
    return meta::lite::test::basic<bool>(d || true, true);
}

bool utest_23()
{
    udt::dynamic_t d = false;
    return meta::lite::test::basic<bool>(d || true, true);
}

bool utest_24()
{
    udt::dynamic_t d = true;
    return meta::lite::test::basic<bool>(d ^ false, true);
}

bool utest_25()
{
    udt::dynamic_t d = false;
    return meta::lite::test::basic<bool>(d ^ false, false);
}

bool utest_26()
{
    udt::dynamic_t d = true;
    return meta::lite::test::basic<bool>(d ^ true, false);
}

bool utest_27()
{
    udt::dynamic_t d = false;
    return meta::lite::test::basic<bool>(d ^ true, true);
}

bool utest_28()
{
    udt::dynamic_t d;
    return meta::lite::test::basic<bool>(!d, true);
}

bool utest_29()
{
    udt::dynamic_t d = true;
    return meta::lite::test::basic<bool>(!d, false);
}

bool utest_30()
{
    udt::dynamic_t d;
    d &= true;
    return meta::lite::test::basic<bool>(d.get_bool(), false);
}

bool utest_31()
{
    udt::dynamic_t d;
    d |= true;
    return meta::lite::test::basic<bool>(d.get_bool(), true);
}

bool utest_32()
{
    udt::dynamic_t d;
    d ^= true;
    return meta::lite::test::basic<bool>(d.get_bool(), true);
}

bool utest_33()
{
    udt::dynamic_t d;
    return meta::lite::test::basic<bool>(d == false, true);
}

bool utest_34()
{
    udt::dynamic_t d;
    return meta::lite::test::basic<bool>(d == true, false);
}

bool utest_35()
{
    udt::dynamic_t d;
    return meta::lite::test::basic<bool>(d != false, false);
}

bool utest_36()
{
    udt::dynamic_t d;
    return meta::lite::test::basic<bool>(d != true, true);
}

bool utest_37()
{
    udt::dynamic_t d = 'i';
    return meta::lite::test::basic<bool>(d == 'i', true);
}

bool utest_38()
{
    udt::dynamic_t d = ';';
    return meta::lite::test::basic<bool>(d == 'i', false);
}

bool utest_39()
{
    udt::dynamic_t d = 'o';
    return meta::lite::test::basic<bool>(d != 'o', false);
}

bool utest_40()
{
    udt::dynamic_t d = 'y';
    return meta::lite::test::basic<bool>(d != 'o', true);
}

bool utest_41()
{
    udt::dynamic_t d1 = {false, 'p', 9983, 9.4f, 3.8};
    udt::dynamic_t d2 = {false, 'p', 9983, 9.4f, 3.8};
    return meta::lite::test::basic<bool>(d1 == d2, true);
}

bool utest_42()
{
    udt::dynamic_t d1 = {false, 'p', 9983, 9.4f, 3.8};
    udt::dynamic_t d2 = {false, 'p', 9983, 9.4f, 3.8};
    return meta::lite::test::basic<bool>(d1 != d2, false);
}

bool utest_43()
{
    udt::dynamic_t d1 = {false, 'p', 9983, 9.4f, 3.8};
    udt::dynamic_t d2 = {true, '6', 662, 5.4f, 9.8};
    return meta::lite::test::basic<bool>(d1 == d2, false);
}

bool utest_44()
{
    udt::dynamic_t d1 = {false, 'p', 9983, 9.4f, 3.8};
    udt::dynamic_t d2 = {true, '6', 662, 5.4f, 9.8};
    return meta::lite::test::basic<bool>(d1 != d2, true);
}

bool utest_45()
{
    udt::dynamic_t d = 'O';
    d += ' ';
    return meta::lite::test::basic<char>(d.get_char(), 'o');
}

bool utest_46()
{
    udt::dynamic_t d = 10;
    d += 88;
    return meta::lite::test::basic<int>(d.get_int(), 98);
}

bool utest_47()
{
    udt::dynamic_t d = 9.3f;
    d += 3.2f;
    return meta::lite::test::basic<float>(d.get_float(), 12.5f);
}

bool utest_48()
{
    udt::dynamic_t d = 99.3;
    d += 26.25;
    return meta::lite::test::basic<double>(d.get_double(), 125.55);
}

bool utest_49()
{
    udt::dynamic_t d1 = {false, 'D', 102, 99.3f, 8.3};
    udt::dynamic_t d2 = {false, ' ', 48, 26.5f, 1.2};
    udt::dynamic_t d3 = {false, 'd', 150, 125.8f, 9.5};
    d1 += d2;
    return meta::lite::test::basic<bool>(d1 == d3, true);
}

bool utest_50()
{
    udt::dynamic_t d = '@';
    d -= ' ';
    return meta::lite::test::basic<char>(d.get_char(), ' ');
}

bool utest_51()
{
    udt::dynamic_t d = 99;
    d -= 44;
    return meta::lite::test::basic<int>(d.get_int(), 55);
}

bool utest_52()
{
    udt::dynamic_t d = 9.8f;
    d -= 1.3f;
    return meta::lite::test::basic<float>(d.get_float(), 8.5f);
}

bool utest_53()
{
    udt::dynamic_t d = 5.5;
    d -= 1.5;
    return meta::lite::test::basic<double>(d.get_double(), 4.0);
}

bool utest_54()
{
    udt::dynamic_t d1 = {true, '~', 9983, 982.3f, 9385.4};
    udt::dynamic_t d2 = {true, ' ', 983, 282.3f, 9000.4};
    udt::dynamic_t d3 = {true, '^', 9000, 700.0f, 385.0};
    d1 -= d2;
    return meta::lite::test::basic<bool>(d1 == d3, true);
}

bool utest_55()
{
    udt::dynamic_t d = 880;
    d *= 1238;
    return meta::lite::test::basic<int>(d.get_int(), 1089440);
}

bool utest_56()
{
    udt::dynamic_t d = 1.2f;
    d *= 5.0f;
    return meta::lite::test::basic<float>(d.get_float(), 6.0f);
}

bool utest_57()
{
    udt::dynamic_t d = 2.25;
    d *= 2.0;
    return meta::lite::test::basic<double>(d.get_double(), 4.5);
}

bool utest_58()
{
    udt::dynamic_t d = 10;
    d /= 5;
    return meta::lite::test::basic<int>(d.get_int(), 2);
}

bool utest_59()
{
    udt::dynamic_t d = 8.0f;
    d /= 10.0f;
    return meta::lite::test::basic<float>(d.get_float(), 0.8f);
}

bool utest_60()
{
    udt::dynamic_t d = 15.0;
    d /= 10.0;
    return meta::lite::test::basic<double>(d.get_double(), 1.5);
}

bool utest_61()
{
    udt::dynamic_t d = 2;
    d ^= 10;
    return meta::lite::test::basic<int>(d.get_int(), 1024);
}

bool utest_62()
{
    udt::dynamic_t d = 3.0f;
    d ^= 5.0f;
    return meta::lite::test::basic<float>(d.get_float(), 243.0f);
}

bool utest_63()
{
    udt::dynamic_t d = 3.0;
    d ^= 5.0;
    return meta::lite::test::basic<double>(d.get_double(), 243.0);
}

bool utest_64()
{
    udt::dynamic_t d = ':';
    return meta::lite::test::basic<char>(d + '\n', 'D');
}

bool utest_65()
{
    udt::dynamic_t d = 77;
    return meta::lite::test::basic<int>(d + 77, 154);
}

bool utest_66()
{
    udt::dynamic_t d = 7.9f;
    return meta::lite::test::basic<float>(d + 2.1f, 10.0f);
}

bool utest_67()
{
    udt::dynamic_t d = 88.3;
    return meta::lite::test::basic<double>(d + 21.7, 110.0);
}

bool utest_68()
{
    udt::dynamic_t d = ':';
    return meta::lite::test::basic<char>(d - '\n', '0');
}

bool utest_69()
{
    udt::dynamic_t d = 77;
    return meta::lite::test::basic<int>(d - 77, 0);
}

bool utest_70()
{
    udt::dynamic_t d = 7.9f;
    return meta::lite::test::basic<float>(d - 2.1f, 5.8f);
}

bool utest_71()
{
    udt::dynamic_t d = 88.3;
    return meta::lite::test::basic<double>(d - 21.7, 66.6);
}

bool utest_72()
{
    udt::dynamic_t d = 77;
    return meta::lite::test::basic<int>(d * 77, 5929);
}

bool utest_73()
{
    udt::dynamic_t d = 7.9f;
    return meta::lite::test::basic<float>(d * 2.1f, 16.59f);
}

bool utest_74()
{
    udt::dynamic_t d = 88.3;
    return meta::lite::test::basic<double>(d * 21.7, 1916.11);
}

bool utest_75()
{
    udt::dynamic_t d = 77;
    return meta::lite::test::basic<int>(d / 77, 1);
}

bool utest_76()
{
    udt::dynamic_t d = 7.9f;
    return meta::lite::test::basic<int>(std::pow(10, 4) * (d / 2.1f), 37619);
}

bool utest_77()
{
    udt::dynamic_t d = 88.3;
    return meta::lite::test::basic<int>(std::pow(10, 4) * (d / 21.7), 40691);
}

bool utest_78()
{
    udt::dynamic_t d = 12;
    return meta::lite::test::basic<int>(d ^ 5, 248832);
}

bool utest_79()
{
    udt::dynamic_t d = 12.0f;
    return meta::lite::test::basic<int>(std::pow(10, 2) * (d ^ 2.5f), 49883);
}

bool utest_80()
{
    udt::dynamic_t d = 12.0;
    return meta::lite::test::basic<int>(std::pow(10, 2) * (d ^ 2.5), 49883);
}

bool utest_81()
{
    udt::dynamic_t d = 12;
    return meta::lite::test::basic<int>(d % 2, 0);
}

bool utest_82()
{
    udt::dynamic_t d = 7;
    return meta::lite::test::basic<int>(d % 2, 1);
}

bool utest_83()
{
    udt::dynamic_t d = 12;
    return meta::lite::test::basic<int>(d % 10, 2);
}

bool utest_84()
{
    udt::dynamic_t d = 112;
    d %= 100;
    return meta::lite::test::basic<int>(d.get_int(), 12);
}

bool utest_85()
{
    udt::dynamic_t d = 12;
    d %= 3;
    return meta::lite::test::basic<int>(d.get_int(), 0);
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
    UTS << utest_77;
    UTS << utest_78;
    UTS << utest_79;
    UTS << utest_80;
    UTS << utest_81;
    UTS << utest_82;
    UTS << utest_83;
    UTS << utest_84;
    UTS << utest_85;
    UTS.print_summary();
    udt::dynamic_t d;
    meta::lite::io::println(
        "The size of the dynamic_t data type in bytes: ",
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
    UTB << utest_77;
    UTB << utest_78;
    UTB << utest_79;
    UTB << utest_80;
    UTB << utest_81;
    UTB << utest_82;
    UTB << utest_83;
    UTB << utest_84;
    UTB << utest_85;
    UTB.print_summary();
    return 0;
}