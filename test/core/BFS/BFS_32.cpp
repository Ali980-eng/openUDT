#include "metaCore/lite.hpp"
#include "core/bfs/bfs_32.hpp"

bool utest_1()
{
    udt::bfs_16 value1, value2;
    udt::bfs_32 value3;
    return meta::lite::test::basic<bool>(value1 == value3.get_upper() && value2 == value3.get_lower(), true);
}

bool utest2() { return false; }

int main()
{
    meta::lite::io::NewLines();
    bool bresult;
    float fresult;
    meta::lite::test_stream UTS;
    meta::lite::io::print<std::string>("All test result: ");
    meta::lite::io::println(meta::lite::test::test_message(bresult));
    udt::bfs_32 value;
    meta::lite::io::print("The size of the type BFS_16: ", meta::lite::benchmark::mata_data(value), " Byte\n");
    return 0;
}