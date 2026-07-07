#include "meta/lite.hpp"
#include "udt/core/bfs/bfs_8.hpp"

bool utest_1()
{
    udt::bfs_8 value;
    value.set_flag1();
    return meta::lite::test::basic<bool>(value[1], true);
}

bool utest_2()
{
    udt::bfs_8 value;
    value.set_flag2();
    return meta::lite::test::basic<bool>(value[2], true);
}

bool utest_3()
{
    udt::bfs_8 value;
    value.set_flag3();
    return meta::lite::test::basic<bool>(value[3], true);
}

bool utest_4()
{
    udt::bfs_8 value;
    value.set_flag4();
    return meta::lite::test::basic<bool>(value[4], true);
}

bool utest_5()
{
    udt::bfs_8 value;
    value.set_flag5();
    return meta::lite::test::basic<bool>(value[5], true);
}

bool utest_6()
{
    udt::bfs_8 value;
    value.set_flag6();
    return meta::lite::test::basic<bool>(value[6], true);
}

bool utest_7()
{
    udt::bfs_8 value;
    value.set_flag7();
    return meta::lite::test::basic<bool>(value[7], true);
}

bool utest_8()
{
    udt::bfs_8 value;
    value.set_flag8();
    return meta::lite::test::basic<bool>(value[8], true);
}

bool utest_9()
{
    udt::bfs_8 value = 255;
    value.reset_all();
    return meta::lite::test::basic<uint8_t>(value.get(), 0);
}

bool utest_10()
{
    udt::bfs_8 value = 255;
    value.reset_flag1();
    return meta::lite::test::basic<bool>(value[1], false);
}

bool utest_11()
{
    udt::bfs_8 value = 255;
    value.reset_flag2();
    return meta::lite::test::basic<bool>(value[2], false);
}

bool utest_12()
{
    udt::bfs_8 value = 255;
    value.reset_flag3();
    return meta::lite::test::basic<bool>(value[3], false);
}

bool utest_13()
{
    udt::bfs_8 value = 255;
    value.reset_flag4();
    return meta::lite::test::basic<bool>(value[4], false);
}

bool utest_14()
{
    udt::bfs_8 value = 255;
    value.reset_flag5();
    return meta::lite::test::basic<bool>(value[5], false);
}

bool utest_15()
{
    udt::bfs_8 value = 255;
    value.reset_flag6();
    return meta::lite::test::basic<bool>(value[6], false);
}

bool utest_16()
{
    udt::bfs_8 value = 255;
    value.reset_flag7();
    return meta::lite::test::basic<bool>(value[7], false);
}

bool utest_17()
{
    udt::bfs_8 value = 255;
    value.reset_flag8();
    return meta::lite::test::basic<bool>(value[8], false);
}

bool utest_18()
{
    udt::bfs_8 value;
    value.set_all();
    return meta::lite::test::basic<uint8_t>(value.get(), 255);
}

bool utest_19()
{
    udt::bfs_8 value;
    value.set(5);
    return meta::lite::test::basic<bool>(value.get(5), true);
}

bool utest_20()
{
    udt::bfs_8 value;
    value.set_all();
    value.reset(3);
    return meta::lite::test::basic<bool>(value.get(3), false);
}

bool utest_21()
{
    udt::bfs_8 value1 = 200;
    uint8_t value2 = 200;
    return meta::lite::test::basic<bool>(value1 == value2, true);
}

bool utest_22()
{
    udt::bfs_8 value1 = 200;
    uint8_t value2 = 120;
    return meta::lite::test::basic<bool>(value1 == value2, false);
}

bool utest_23()
{
    udt::bfs_8 value1 = 200;
    uint8_t value2 = 200;
    return meta::lite::test::basic<bool>(value1 != value2, false);
}

bool utest_24()
{
    udt::bfs_8 value1 = 200;
    uint8_t value2 = 100;
    return meta::lite::test::basic<bool>(value1 != value2, true);
}

bool utest_25()
{
    udt::bfs_8 value1 = 200;
    udt::bfs_8 value2 = 200;
    return meta::lite::test::basic<bool>(value1 == value2, true);
}

bool utest_26()
{
    udt::bfs_8 value1 = 200;
    udt::bfs_8 value2 = 120;
    return meta::lite::test::basic<bool>(value1 == value2, false);
}

bool utest_27()
{
    udt::bfs_8 value1 = 200;
    udt::bfs_8 value2 = 200;
    return meta::lite::test::basic<bool>(value1 != value2, false);
}

bool utest_28()
{
    udt::bfs_8 value1 = 200;
    udt::bfs_8 value2 = 100;
    return meta::lite::test::basic<bool>(value1 != value2, true);
}

bool utest_29()
{
    udt::bfs_8 value1 = 222;
    udt::bfs_8 value2 = value1;
    return meta::lite::test::basic<bool>(value1 == value2, true);
}

bool utest_30()
{
    udt::bfs_8 value1 = 223;
    udt::bfs_8 value2;
    value2 = value1;
    return meta::lite::test::basic<bool>(value1 == value2, true);
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
    UTS.print_summary();
    udt::bfs_8 value;
    meta::lite::io::print("The size of the type BFS_8: ", meta::lite::benchmark::mata_data(value), " Byte\n");
    meta::lite::benchmark_stream<false> UTB = 9;
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
    UTB.print_summary();
    return 0;
}