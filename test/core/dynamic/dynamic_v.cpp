#include "meta/lite/stream.hpp"
#include "udt/core/dynamic/dynamic_v.hpp"

bool utest_1()
{
    udt::dynamic_v d;
    return meta::lite::test::basic<bool>(d.empty(), true);
}

bool utest_2()
{
    udt::dynamic_v d = {true, 'c', 199, 1.2, 2.4f};
    return meta::lite::test::basic<bool>(d.at(1) == 'c', true);
}

bool utest_3()
{
    udt::dynamic_v d = {10, 88.9, 'l', false};
    return meta::lite::test::basic<bool>(d[2] == 'l', true);
}

bool utest_4()
{
    udt::dynamic_v d = {88, true, 'i', 10, false};
    return meta::lite::test::basic<size_t>(d.size(), 5);
}

bool utest_5()
{
    udt::dynamic_v d(4);
    d = {88, 22.8, 'c', true};
    return meta::lite::test::basic<bool>(d.is_fixed(), true);
}

bool utest_6()
{
    std::vector<udt::dynamic_f> vd = {true, false, 'p', 39};
    udt::dynamic_v d = vd;
    return meta::lite::test::basic<bool>(d[2] == vd[2], true);
}

bool utest_7()
{
    udt::dynamic_v d1 = {188, 3.9, 'U', false, true};
    udt::dynamic_v d2 = d1;
    return meta::lite::test::basic<bool>(d1 == d2, true);
}

bool utest_8()
{
    std::vector<udt::dynamic_f> vd = {103, '=', 7.8f, false};
    udt::dynamic_v d;
    d.set(vd);
    vd = {103, '=', 7.8f, false};
    return meta::lite::test::basic<bool>(d == vd, true);
}

bool utest_9()
{
    bool result = true;
    udt::dynamic_v d = {5, {28, 39.9, true, 88.4f, '.'}};
    result &= meta::lite::test::basic<size_t>(d.size(), 5);
    result &= meta::lite::test::basic<bool>(d[d.last_index()] == '.', true);
    return result;
}

bool utest_10()
{
    udt::dynamic_v d = {99, 576.8, false, true, 'c'};
    d.push_back('u');
    return meta::lite::test::basic<bool>(d[5] == 'u', true);
}

bool utest_11()
{
    udt::dynamic_v d = {9.9, 3.9f, 'u', true, false};
    d.push_front(88);
    return meta::lite::test::basic<bool>(d[0] == 88, true);
}

bool utest_12()
{
    udt::dynamic_v d = {99, 'i', true, 9.3, 33.1f};
    d.pop_back();
    return meta::lite::test::basic<bool>(d[3] == 9.3, true);
}

bool utest_13()
{
    udt::dynamic_v d = {99, 'i', true, 9.3, 33.1f};
    d.pop_front();
    return meta::lite::test::basic<bool>(d[0] == 'i', true);
}

bool utest_14()
{
    bool result = true;
    udt::dynamic_v d;
    d.set_size(8);
    result &= meta::lite::test::basic<bool>(d.is_fixed(), true);
    result &= meta::lite::test::basic<size_t>(d.size(), 8);
    return result;
}

bool utest_15()
{
    udt::dynamic_v d = {99, 'i', true, 9.8, 998.3f};
    std::vector<std::string> vs = {"int", "char", "bool", "double", "float"};
    return meta::lite::test::vector<std::string>(d.type_vector(), vs);
}

bool utest_16()
{
    udt::dynamic_v d = {0, true, 33.8, 'p'};
    d.insert(2, 'i');
    return meta::lite::test::basic<bool>(d[2] == 'i', true);
}

bool utest_17()
{
    udt::dynamic_v d = {'i', true, false, 88, 8.83};
    d.insert_after(1, 'o');
    return meta::lite::test::basic<bool>(d[2] == 'o', true);
}

bool utest_18()
{
    udt::dynamic_v d = {999, true, '.', false};
    d.insert_before(2, 898);
    return meta::lite::test::basic<bool>(d[2] == 898, true);
}

bool fun_1(const udt::dynamic_f &u) noexcept { return u == 'i'; }

bool utest_19()
{
    udt::dynamic_v d = {99, 38.8, 'i', true, false};
    d.insert_after(fun_1, 'o');
    return meta::lite::test::basic<bool>(d[3] == 'o', true);
}

bool fun_2(const udt::dynamic_f &u) noexcept { return u == 'o'; }

bool utest_20()
{
    udt::dynamic_v d = {99, 38, 'o', 'p', true};
    d.insert_before(fun_2, '.');
    return meta::lite::test::basic<bool>(d[2] == '.', true);
}

bool utest_21()
{
    udt::dynamic_v d = {99, 39, 'o', true, false};
    d.clear();
    return meta::lite::test::basic<bool>(d.empty(), true);
}

bool utest_22()
{
    udt::dynamic_v d = {98, 28, 'o', true, 88.89};
    d.erase(3);
    return meta::lite::test::basic<bool>(d[3] == 88.89, true);
}

bool fun_3(const udt::dynamic_f &du) noexcept { return du > 100; }

bool utest_23()
{
    udt::dynamic_v d = {192, 88, 'c', true, 283, 33.2f};
    d.erase(fun_3);
    return meta::lite::test::basic<bool>(d[0] == 88 && d[1] == 'c', true);
}

bool utest_24()
{
    udt::dynamic_v d(9);
    d.resize(7);
    return meta::lite::test::basic<size_t>(d.size(), 7);
}

bool utest_25()
{
    udt::dynamic_v d = {88, 39.8, 'c', false};
    return meta::lite::test::basic<std::string>(d.type(2), "char");
}

bool utest_26()
{
    udt::dynamic_v d1 = {'i', 88, 3.3f, 398.3, true};
    udt::dynamic_v d2 = {388, 'o', 8.8, 99.8, false};
    return meta::lite::test::basic<bool>(d1 == d2, false);
}

bool utest_27()
{
    udt::dynamic_v d1 = {'i', 88, 3.3f, 398.3, true};
    udt::dynamic_v d2 = d1;
    return meta::lite::test::basic<bool>(d1 == d2, true);
}

bool utest_28()
{
    udt::dynamic_v d1 = {'i', 88, 3.3f, 398.3, true};
    udt::dynamic_v d2 = {388, 'o', 8.8, 99.8, false};
    return meta::lite::test::basic<bool>(d1 != d2, true);
}

bool utest_29()
{
    udt::dynamic_v d1 = {'i', 88, 3.3f, 398.3, true};
    udt::dynamic_v d2 = d1;
    return meta::lite::test::basic<bool>(d1 != d2, false);
}

bool utest_30()
{
    std::vector<udt::dynamic_f> vd = {'i', 88, false};
    udt::dynamic_v d = vd;
    return meta::lite::test::basic<bool>(d == vd, true);
}

bool utest_31()
{
    std::vector<udt::dynamic_f> vd = {'i', 88, false};
    udt::dynamic_v d = {19, true, '8'};
    return meta::lite::test::basic<bool>(d == vd, false);
}

bool utest_32()
{
    std::vector<udt::dynamic_f> vd = {'i', 88, false};
    udt::dynamic_v d = vd;
    return meta::lite::test::basic<bool>(d != vd, false);
}

bool utest_33()
{
    std::vector<udt::dynamic_f> vd = {'i', 88, false};
    udt::dynamic_v d = {19, true, '8'};
    return meta::lite::test::basic<bool>(d != vd, true);
}

bool utest_34()
{
    udt::dynamic_v d = {0, 2.3, 'o'};
    return meta::lite::test::basic<bool>(
        d == std::initializer_list<udt::dynamic_f>{0, 2.3, 'o'},
        true);
}

bool utest_35()
{
    udt::dynamic_v d = {0, 2.3, 'o'};
    return meta::lite::test::basic<bool>(
        d == std::initializer_list<udt::dynamic_f>{'9', 9.8, false},
        false);
}

bool utest_36()
{
    udt::dynamic_v d = {0, 2.3, 'o'};
    return meta::lite::test::basic<bool>(
        d != std::initializer_list<udt::dynamic_f>{0, 2.3, 'o'},
        false);
}

bool utest_37()
{
    udt::dynamic_v d = {0, 2.3, 'o'};
    return meta::lite::test::basic<bool>(
        d != std::initializer_list<udt::dynamic_f>{'9', 9.8, false},
        true);
}

bool utest_38()
{
    udt::dynamic_v d1 = {'p', 9};
    udt::dynamic_v d2 = {'w', 16};
    d1 += 7;
    return meta::lite::test::basic<bool>(d1 == d2, true);
}

bool utest_39()
{
    udt::dynamic_v d1 = {'p', 9};
    udt::dynamic_v d2 = {'i', 2};
    d1 -= 7;
    return meta::lite::test::basic<bool>(d1 == d2, true);
}

bool utest_40()
{
    udt::dynamic_v d1 = {9, '!'};
    udt::dynamic_v d2 = {27, 'c'};
    d1 *= 3;
    return meta::lite::test::basic<bool>(d1 == d2, true);
}

int main()
{
    meta::lite::test_stream UTS;
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
    UTS << utest_26;
    UTS << utest_27;
    UTS << utest_28;
    UTS << utest_29;
    UTS << utest_30;
    UTS << utest_31;
    UTS << utest_32;
    UTS << utest_33;
    UTS << utest_34;
    UTS << utest_35;
    UTS << utest_36;
    UTS << utest_37;
    UTS << utest_38;
    UTS << utest_39;
    UTS << utest_40;
    UTS.print_summary();
    udt::dynamic_v d = {983, 33.8, 98.4f, 'a', false};
    meta::lite::io::println(
        "The size of the dynamic_v mata data type in bytes: ",
        meta::lite::benchmark::mata_data(d));
    meta::lite::io::println(
        "The size of the dynamic_v heap data type in bytes: ",
        meta::lite::benchmark::heap_data(d.get()));
    meta::lite::benchmark_stream<false> UTB = 6;
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
    UTB << utest_26;
    UTB << utest_27;
    UTB << utest_28;
    UTB << utest_29;
    UTB << utest_30;
    UTB << utest_31;
    UTB << utest_32;
    UTB << utest_33;
    UTB << utest_34;
    UTB << utest_35;
    UTB << utest_36;
    UTB << utest_37;
    UTB << utest_38;
    UTB << utest_39;
    UTB << utest_40;
    UTB.print_summary();
    return 0;
}