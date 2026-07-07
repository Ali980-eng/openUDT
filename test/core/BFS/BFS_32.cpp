#include "meta/lite.hpp"
#include "udt/core/bfs/bfs_32.hpp"

bool utest_1()
{
    udt::bfs_16 value1, value2;
    udt::bfs_32 value3;
    return meta::lite::test::basic<bool>(value1 == value3.get_upper() && value2 == value3.get_lower(), true);
}

bool utest2() { return false; }

int main()
{
    return 0;
}