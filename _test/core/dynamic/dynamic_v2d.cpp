#include "metaCore/lite/stream.hpp"
#include "core/dynamic/dynamic_v2d.hpp"

bool utest_1()
{
    udt::dynamic_v2d d(5);
    return meta::lite::test::basic<size_t>(d.size(), 5);
}
bool utest_2()
{
    udt::dynamic_v2d d(3, 4);
    return meta::lite::test::basic<size_t>(d.size(), 3);
}
bool utest_3()
{
    std::vector<std::vector<udt::dynamic_f>> vvd = {
        {88, 93.8, 'c'},
        {true, false, 9},
        {'o', false, 88}};
    udt::dynamic_v2d d = vvd;
    return meta::lite::test::basic<bool>(d == vvd, true);
}
bool utest_4()
{
    udt::dynamic_v2d vvd1 = {
        {true, 'i', 99},
        {'o', 99.4f, false}};
    udt::dynamic_v2d vvd2 = vvd1;
    return meta::lite::test::basic<bool>(vvd1 == vvd2, true);
}
// bool utest_5() {}
int main()
{
    meta::lite::io::NewLines();

    return 0;
}