#include "lite.hpp"
bool utest_1()
{
    bool result = true;
    lite::vstream<int> vs;
    result &= lite::test::basic<bool>(vs.empty(), true);
    vs << 24;
    vs << 99;
    result &= lite::test::basic<int>(vs[1], 99);
    result &= lite::test::basic<int>(vs[0], 24);
    result &= lite::test::basic<size_t>(vs.size(), 2);
    return result;
}
bool utest_2()
{
    bool result = true;
    lite::vstream<char> vs({'a', 'b', 'c'});
    result &= lite::test::basic<size_t>(vs.size(), 3);
    result &= lite::test::basic<char>(vs[0], 'a');
    result &= lite::test::basic<char>(vs[1], 'b');
    result &= lite::test::basic<char>(vs[2], 'c');
    char ch;
    vs >> ch;
    result &= lite::test::basic<char>(ch, 'c');
    result &= lite::test::basic<size_t>(vs.size(), 2);
    return result;
}
bool utest_3()
{
    bool result = true;
    lite::vstream<float> vs = {2.7, 3.14f, 1.414f};
    result &= lite::test::basic<size_t>(vs.size(), 3);
    result &= lite::test::basic<float>(vs[0], 2.7f);
    result &= lite::test::basic<float>(vs[1], 3.14f);
    result &= lite::test::basic<float>(vs[2], 1.414f);
    result &= lite::test::basic<bool>(vs.empty(), false);
    vs.clear();
    result &= lite::test::basic<bool>(vs.empty(), true);
    return result;
}
bool utest_4()
{
    bool result = true;
    lite::vstream<std::string> vs;
    result &= lite::test::basic<bool>(vs.empty(), true);
    vs << "hello";
    vs << "world";
    result &= lite::test::basic<std::string>(vs[0], "hello");
    result &= lite::test::basic<std::string>(vs[1], "world");
    result &= lite::test::basic<size_t>(vs.size(), 2);
    std::string str;
    vs >> str;
    result &= lite::test::basic<std::string>(str, "world");
    result &= lite::test::basic<size_t>(vs.size(), 1);
    return result;
}
bool utest_5()
{
    bool result = true;
    std::vector<int> vec = {1, 2, 3, 4, 5};
    lite::vstream<int> vs(vec);
    result &= lite::test::basic<size_t>(vs.size(), 5);
    result &= lite::test::basic<size_t>(vs.capacity(), vec.capacity());
    for (int i = 0; i < 5; i++)
        result &= lite::test::basic<int>(vs[i], i + 1);
    return result;
}
int main()
{
    lite::io::NewLines(5);
    bool bresult;
    float fresult;
    lite::function::test_stream UTS;
    UTS << utest_1;
    UTS << utest_2;
    UTS << utest_3;
    UTS << utest_4;
    UTS << utest_5;
    UTS >> bresult;
    lite::io::print<std::string>("All test result: ");
    lite::io::println(lite::test::test_message(bresult));
    lite::function::benchmark_stream<false> UTB = 6;
    UTB << utest_1;
    UTB << utest_2;
    UTB << utest_3;
    UTB << utest_4;
    UTB << utest_5;
    UTB >> fresult;
    lite::io::print<std::string>(
        "The average time for all unit test: " +
        std::to_string(fresult) + " us");
    return 0;
}