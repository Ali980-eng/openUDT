#include "meta/lite/stream.hpp"
#include "udt/core/string.hpp"

bool utest_1()
{
    udt::str es = "YouTube";
    std::string ss = "YouTube";
    return meta::lite::test::basic(es.gss(), ss);
}

bool utest_2()
{
    udt::str s(4);
    s = "abcd";
    return meta::lite::test::basic<size_t>(s.length(), 4);
}

bool utest_3()
{
    udt::str s1 = "hello all";
    udt::str s2 = s1;
    return meta::lite::test::basic(s2.gss(), s1.gss());
}

int main()
{
    meta::lite::test_stream UTS;
    UTS << utest_1;
    UTS << utest_2;
    UTS << utest_3;
    UTS.print_summary();
    return 0;
}