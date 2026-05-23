#include "lite.hpp"
#include "UDT/BFS/BFS_32.hpp"

bool utest_1()
{
    udt::BFS_16 value1, value2;
    udt::BFS_32 value3;
    return lite::test::basic<bool>(value1 == value3.get_upper() && value2 == value3.get_lower(), true);
}
bool utest2() { return false; }
int main()
{
    lite::io::NewLines();
    bool bresult;
    float fresult;
    lite::function::test_stream UTS;
    lite::io::print<std::string>("All test result: ");
    lite::io::println(lite::test::test_message(bresult));
    udt::BFS_32 value;
    lite::io::print("The size of the type BFS_16: ", lite::benchmark::mata_data(value), " Byte\n");
    return 0;
}