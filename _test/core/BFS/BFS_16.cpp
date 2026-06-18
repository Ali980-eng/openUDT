#include "lite.hpp"
#include "UDT/BFS/BFS_16.hpp"

bool utest_1()
{
    udt::BFS_16 value;
    return lite::test::basic<uint8_t>(value.get_lower(), 0) && lite::test::basic<size_t>(value.get_upper(), 0);
}
bool utest_2()
{
    udt::BFS_8 value1 = 80;
    udt::BFS_16 value2 = {value1, false};
    return lite::test::basic<uint8_t>(value1.get(), value2.get_lower());
}
bool utest_3()
{
    udt::BFS_16 value = 7;
    return lite::test::basic<bool>(value.get(7), true);
}
bool utest_4()
{
    udt::BFS_16 value1 = {20, 35};
    udt::BFS_16 value2 = value1;
    return lite::test::basic<bool>(value1 == value2, true);
}
bool utest_5()
{
    udt::BFS_8 value1 = 90, value2 = 8;
    udt::BFS_16 value3 = {value1, value2};
    return lite::test::basic<bool>(value1 == value3.get_upper(), 90) && lite::test::basic<bool>(value2 == value3.get_lower(), 8);
}
bool utest_6()
{
    udt::BFS_8 value1, value2;
    udt::BFS_16 value3;
    value1.set_all();
    value2.set_all();
    value3.set_all();
    return lite::test::basic<bool>(value1 == value3.get_lower() && value2 == value3.get_upper(), true);
}
bool utest_7()
{
    udt::BFS_16 value;
    value.set(7);
    value.set(13);
    return lite::test::basic<bool>(value[7] == true && value[13] == true, true);
}
bool utest_8()
{
    udt::BFS_16 value;
    value.set_all();
    value.reset(11);
    return lite::test::basic<bool>(value[11] == false && value[7] == true, true);
}
bool utest_9()
{
    udt::BFS_16 value1 = {0, 0}, value2;
    value2.set(10);
    value2.set(3);
    value2.reset_all();
    return lite::test::basic<bool>(value1 == value2, true);
}
bool utest_10()
{
    udt::BFS_8 value1 = 99, value2 = 110;
    udt::BFS_16 value3 = {13, 38}, value4 = {value1, value2};
    return lite::test::basic<bool>(
        value4 != value3 &&
            value3 != value2 &&
            value3 != value1 &&
            value4 == value2 &&
            value4 == value1 &&
            value1 != value2,
        true);
}
int main()
{
    lite::io::NewLines();
    bool bresult;
    float fresult;
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
    UTS >> bresult;
    lite::io::print<std::string>("All test result: ");
    lite::io::println(lite::test::test_message(bresult));
    udt::BFS_16 value;
    lite::io::print("The size of the type BFS_16: ", lite::benchmark::mata_data(value), " Byte\n");
    lite::function::benchmark_stream<false> UTB = 9;
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
    lite::io::print<std::string>(
        "The average time for all unit test: " +
        std::to_string(fresult) + " ns");
    return 0;
}