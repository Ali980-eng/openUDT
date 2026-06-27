#include "metaCore/lite/stream.hpp"
#include "core/pair/pair_t.hpp"

bool utest_1()
{
    udt::pair_t<int> value;
    return meta::lite::test::basic<int>(value.get(true), 0);
}

bool utest_2()
{
    udt::pair_t<int> value = {189983, 3388};
    return meta::lite::test::basic<int>(value.get(true), 189983);
}

bool utest_3()
{
    udt::pair_t<int> value = {188, 9983};
    return meta::lite::test::basic<int>(value.get(false), 188);
}

bool utest_4()
{
    udt::pair_t<char> value = {'c', 't'};
    return meta::lite::test::basic<char>(value.get(true), 'c');
}

bool utest_5()
{
    udt::pair_t<char> value = {'c', 't'};
    return meta::lite::test::basic<char>(value.get(false), 't');
}

bool utest_6()
{
    udt::pair_t<short> value1 = {120, 99};
    udt::pair_t<short> value2 = value1;
    return meta::lite::test::basic<bool>(value1 == value2, true);
}

bool utest_7()
{
    udt::pair_t<int> value = {100, 388};
    value.set();
    return meta::lite::test::basic<int>(value.get(false), 388);
}

bool utest_8()
{
    udt::pair_t<char> value;
    value.set('7', false);
    return meta::lite::test::basic<char>(value.get(false), '7');
}

int main()
{
    meta::lite::test_stream UTS;
    UTS << utest_1;
    UTS << utest_2;
    UTS << utest_3;
    UTS << utest_4;
    UTS << utest_5;
    UTS.print_summary();
    return 0;
}