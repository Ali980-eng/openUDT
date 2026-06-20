#include "metaCore/lite/stream.hpp"
#include "basic/string.hpp"

bool utest_1()
{
    udt::string es = "YouTube";
    std::string ss = "YouTube";
    return meta::lite::test::basic(es.gss(), ss);
}
bool utest_2()
{
    udt::string s(4);
    s = "abcd";
    return meta::lite::test::basic<size_t>(s.length(), 4);
}
bool utest_3()
{
    udt::string s1 = "hello all";
    udt::string s2 = s1;
    return meta::lite::test::basic(s2.gss(), s1.gss());
}
int main()
{
    meta::lite::io::NewLines(5);
    bool value = true;
    meta::lite::test_stream UTS;
    UTS << utest_1;
    UTS << utest_2;
    UTS << utest_3;
    UTS >> value;
    meta::lite::io::print<std::string>("All test result: ");
    meta::lite::io::println(meta::lite::test::test_message(value));
    return 0;
}