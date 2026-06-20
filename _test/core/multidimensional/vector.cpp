#include <CXXETL\CXXVector\CXXMultidimensionalVector.hpp>
#include <CXXETL\CXXLite.hpp>

bool utest_1()
{
    etl::vector<int> v1;
    return etl::test::basic<bool>(true, v1.empty());
}
bool utest_2()
{
    etl::vector<int> v2 = {10, 19, 18};
    return etl::test::basic<bool>(false, v2.is_fixed_size());
}
bool utest_3()
{
    etl::vector<int> v3 = {3, {10, 88, 99}};
    return etl::test::basic<size_t>(3, v3.size());
}
bool utest_4()
{
    std::vector<char> stdv4 = {'c', 'l', 'i', 'e'};
    etl::vector<char> v4(stdv4);
    return etl::test::vector<char>(stdv4, v4.get());
}
bool utest_5()
{
    etl::vector<char> v5(3);
    bool result = true;
    result &= etl::test::basic<bool>(true, v5.is_fixed_size());
    result &= etl::test::basic<size_t>(3, v5.size());
    v5.resize(5);
    result &= etl::test::basic<size_t>(5, v5.size());
    return result;
}
bool utest_6()
{
    etl::vector<float> v6 = {0, 10, 39, 88};
    std::vector<float> stdv6 = {0, 10, 39, 88};
    return etl::test::basic<bool>(true, v6 == stdv6);
}
bool utest_7()
{
    bool result = true;
    etl::vector<double> v7 = {1.2, 2.8, 1.5, 2.5};
    result &= etl::test::basic<double>(9.5, v7.sum(1.5));
    result &= etl::test::basic<double>(1.5, v7.at(2));
    return result;
}
bool utest_8()
{
    etl::vector<char> v8 = {'u', 't', 'e', 's', 't'};
    v8.clear();
    return etl::test::basic<bool>(true, v8.empty());
}
bool utest_9()
{
    std::vector<int> stdv9 = {19, 88, 34};
    etl::vector<int> v9 = {34, 88, 19};
    return etl::test::vector<int>(stdv9, v9.reverse());
}
bool utest_10()
{
    etl::vector<int> v10 = {10, 11, 5};
    return etl::test::basic<int>(550, v10.multiply());
}
bool utest_11()
{
    etl::vector<double> v11 = {1, 3, 5, 1};
    return etl::test::basic<double>(0.1, v11.divide());
}
bool utest_12()
{
    bool result = true;
    etl::vector<char> v12 = {'a', 's', 'i', 'l'};
    v12.push_front('o');
    result &= etl::test::basic<char>('o', v12[0]);
    v12.pop_back();
    result &= etl::test::basic<char>('i', v12.top_back());
    return result;
}
bool fun1(int number)
{
    if (number > 10)
        return true;
    return false;
}
bool utest_13()
{
    bool result = true;
    etl::vector<int> v13 = {1, 8, 19, 3, 2};
    v13.push_front(fun1, 10);
    result &= etl::test::basic(10, v13[2]);
    result &= etl::test::basic(1, v13.top_front());
    result &= etl::test::basic(2, v13.top_back());
    v13.pop_front();
    result &= etl::test::basic(8, v13.top_front());
    return result;
}
bool utest_14()
{
    bool result = true;
    etl::vector<char> v14 = {'u', 'i', 'e', 'o'};
    result &= etl::test::basic<bool>(false, v14.find('z'));
    result &= etl::test::basic<bool>(true, v14.find('i'));
    return result;
}
bool even_num(int num)
{
    if (num % 2 == 0)
        return true;
    return false;
}
bool fun2(int num)
{
    if (num > 20)
        return true;
    return false;
}
bool utest_15()
{
    bool result = true;
    etl::vector<int> v15 = {15, 9, 7, 10, 11, 13};
    result &= etl::test::basic<bool>(true, v15.find(even_num));
    result &= etl::test::basic<bool>(false, v15.find(fun2));
    return result;
}
bool fun3(char ch)
{
    if (ch == 'l')
        return true;
    return false;
}
bool utest_16()
{
    bool result = true;
    etl::vector<char> v16 = {'y', 'o', 'u', 'm', 'y', 'l', 'o', 'v', 'e'};
    result &= etl::test::basic<int>(5, v16.find_index('l'));
    result &= etl::test::basic<int>(5, v16.find_index(fun3));
    return result;
}
bool fun4(char ch)
{
    if (ch == 'e')
        return true;
    return false;
}
bool utest_17()
{
    bool result = true;
    etl::vector<char> v17 = {'y', 'o', 'm', 'l', 'o', 'e'};
    v17.erase('m');
    result &= etl::test::basic<bool>(false, v17.find('m'));
    v17.erase_index(2);
    result &= etl::test::basic<bool>(false, v17.find('l'));
    v17.erase(fun4);
    result &= etl::test::basic<bool>(false, v17.find('e'));
    return result;
}
bool utest_18()
{
    etl::vector<float> v18 = {0, 10, 39, 88};
    std::vector<float> stdv18 = {6, 16, 45, 94};
    v18 + 6;
    return etl::test::vector<float>(stdv18, v18.get());
}
bool utest_19()
{
    etl::vector<float> v19 = {0, 10, 39, 88};
    std::vector<float> stdv19 = {0, 1, 3.9, 8.8};
    v19 / 10;
    return etl::test::vector<float>(stdv19, v19.get());
}
bool utest_20()
{
    etl::vector<float> v20 = {0, 10, 39, 88};
    std::vector<float> stdv20 = {0, 100, 390, 880};
    v20 * 10;
    return etl::test::vector<float>(stdv20, v20.get());
}
bool utest_21()
{
    etl::vector<int> v21 = {10, 98, 38, 29};
    std::vector<int> stdv21 = {-10, 78, 18, 9};
    v21 - 20;
    return etl::test::vector<int>(stdv21, v21.get());
}
bool utest_22()
{
    etl::vector<int> v22 = {10, 98, 38, 29};
    const std::vector<int> stdv22 = {-10, 52, 21, 11};
    std::vector<int> real_value = {20, 46, 17, 18};
    v22 - stdv22;
    return etl::test::vector<int>(real_value, v22.get());
}
bool utest_23()
{
    bool result = true;
    etl::vector<int> v23 = {10, 98, 38, 29};
    v23.add_after(38, 99);
    result &= etl::test::basic<int>(99, v23[3]);
    result &= etl::test::basic<bool>(true, v23.find(99));
    return result;
}
bool utest_24()
{
    bool result = true;
    etl::vector<std::string> v24 = {"ean", "eon", "enwm"};
    v24.add_before("eon", "iiii");
    result &= etl::test::basic("iiii", v24[1]);
    result &= etl::test::basic<bool>(true, v24.find("iiii"));
    return result;
}
bool utest_25()
{
    bool result = true;
    etl::vector<int> v25 = {25, 28, 18, 29, 29, 8, 4, 3, 2, 5, 15, 16, 18, 19, 11};
    std::vector<int> stdv25 = {5, 2, 3, 4, 8};
    result &= etl::test::basic<int>(15, int(v25.average()));
    v25.pop_front();
    result &= etl::test::basic<bool>(false, v25.find(25));
    result &= etl::test::vector<int>(stdv25, v25.reverse(5, 9));
    return result;
}
int main()
{
    etl::io::NewLines(5);
    bool bresult;
    float fresult;
    etl::function::test_stream UTS;
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
    UTS << utest_11;
    UTS << utest_12;
    UTS << utest_13;
    UTS << utest_14;
    UTS << utest_15;
    UTS << utest_16;
    UTS << utest_17;
    UTS << utest_18;
    UTS << utest_19;
    UTS << utest_20;
    UTS << utest_21;
    UTS << utest_22;
    UTS << utest_23;
    UTS << utest_24;
    UTS << utest_25;
    UTS >> bresult;
    etl::io::print<std::string>("All test result: ");
    etl::io::println(etl::test::test_message(bresult));
    etl::vector<int> v = {77, 49, 388, 392, 389, 209};
    etl::io::print("The size of the etl::vector data type in bytes using mata data: ");
    etl::io::println(etl::benchmark::mata_data(v));
    etl::io::print("The size of the etl::vector data type in bytes using heap data: ");
    etl::io::println(etl::benchmark::heap_data(v.get()));
    etl::function::benchmark_stream<false> UTB = 6;
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
    UTB << utest_11;
    UTB << utest_12;
    UTB << utest_13;
    UTB << utest_14;
    UTB << utest_15;
    UTB << utest_16;
    UTB << utest_17;
    UTB << utest_18;
    UTB << utest_19;
    UTB << utest_20;
    UTB << utest_21;
    UTB << utest_22;
    UTB << utest_23;
    UTB << utest_24;
    UTB << utest_25;
    UTB >> fresult;
    etl::io::print<std::string>(
        "The average time for all unit test: " +
        std::to_string(fresult) + " us");
    return 0;
}