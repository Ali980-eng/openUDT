#include "lite.hpp"
#include "UDT/string/stringObject.hpp"

bool utest_1()
{
    udt::string es = "YouTube";
    std::string ss = "YouTube";
    return lite::test::basic(es.gss(), ss);
}
bool utest_2()
{
    udt::string s(4);
    s = "abcd";
    return lite::test::basic<size_t>(s.length(), 4);
}
bool utest_3()
{
    udt::string s1 = "hello all";
    udt::string s2 = s1;
    return lite::test::basic(s2.gss(), s1.gss());
}
int main()
{
    lite::io::NewLines(5);
    bool value = true;
    lite::function::test_stream UTS;
    UTS << utest_1;
    UTS << utest_2;
    UTS << utest_3;
    UTS >> value;
    lite::io::print<std::string>("All test result: ");
    lite::io::println(lite::test::test_message(value));
    return 0;
}