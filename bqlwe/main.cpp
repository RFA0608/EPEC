#include <memory>
#include <iostream>
#include <chrono>
#include <ctime>
#include "struct.h"
#include "util.h"
#include "calc.h"
#include "debug.h"
using namespace std;

int main()
{
    // == test calc == //
    matrix_zt* T1 = new matrix_zt(30, 10);
    matrix_zt* T2 = new matrix_zt(30, 10);

    util::set_random_seed((unsigned long)time(NULL));

    // debug::print_runtime((char*)"util", (char*)"uniform_random", false);
    util::uniform_random_mt<matrix_zt>(T1, (char*)"-10", (char*)"-1");
    util::uniform_random_mt<matrix_zt>(T2, (char*)"1", (char*)"10");
    matrix_zt* T3 = util::stack_vertical<matrix_zt>(T1, T2);
    matrix_zt* T4 = util::stack_horizon<matrix_zt>(T1, T2);
    // debug::print_runtime((char*)"util", (char*)"uniform_random", true);

    // debug::print_runtime((char*)"util", (char*)"uniform_random_mt", false);
    // u::uniform_random_mt(T1, (char*)"0", (char*)"100000000");
    // debug::print_runtime((char*)"util", (char*)"uniform_random_mt", true);

    // debug::print_runtime((char*)"util", (char*)"uniform_random", false);
    // u::uniform_random(T2, (char*)"0", (char*)"100000000");
    // debug::print_runtime((char*)"util", (char*)"uniform_random", true);

    // debug::print_runtime((char*)"util", (char*)"uniform_random_mt ", false);
    // u::uniform_random_mt(T2, (char*)"0", (char*)"100000000");
    // debug::print_runtime((char*)"util", (char*)"uniform_random_mt", true);

    // debug::print_runtime((char*)"calc", (char*)"multiple", false);
    // To1 = calc::multiple(T1, T2);
    // debug::print_runtime((char*)"calc", (char*)"multiple", true);

    // debug::print_runtime((char*)"calc", (char*)"multiple_mt", false);
    // To2 = calc::multiple_mt(T1, T2);
    // debug::print_runtime((char*)"calc", (char*)"multiple_mt", true);

    // debug::print_runtime((char*)"calc", (char*)"transpose", false);
    // Tt1 = calc::transpose(To1);
    // debug::print_runtime((char*)"calc", (char*)"transpose", true);
    
    // debug::print_runtime((char*)"calc", (char*)"transpose_mt", false);
    // Tt2 = calc::transpose_mt(To1);
    // debug::print_runtime((char*)"calc", (char*)"transpose_mt", true);

    // debug::print_runtime((char*)"util", (char*)"stack_vertical", false);
    // Tstv = u::stack_vertical(Tt1, Tt2);
    // debug::print_runtime((char*)"util", (char*)"stack_vertical", true);

    // debug::print_runtime((char*)"util", (char*)"stack_horizon", false);
    // Tsth = u::stack_horizon(Tt1, Tt2);
    // debug::print_runtime((char*)"util", (char*)"stack_horizon", true);

    util::print_struct<matrix_zt>(T1);
    util::print_struct<matrix_zt>(T2);
    util::print_struct<matrix_zt>(T3);
    util::print_struct<matrix_zt>(T4);
    // u::print_struct_meta(T2);
    // u::print_struct_meta(To1);
    // u::print_struct_meta(To2);
    // u::print_struct_meta(Tt1);
    // u::print_struct_meta(Tt2);
    // u::print_struct_meta(Tstv);
    // u::print_struct_meta(Tsth);
    
    // debug::print_runtime((char*)"util", (char*)"clear", false);
    util::clear_random_seed();
    util::clear<matrix_zt>(&T1);
    util::clear<matrix_zt>(&T2);
    util::clear<matrix_zt>(&T3);
    util::clear<matrix_zt>(&T4);
    // u::clear(&T2);
    // u::clear(&To1);
    // u::clear(&To2);
    // u::clear(&Tt1);
    // u::clear(&Tt2);
    // u::clear(&Tstv);
    // u::clear(&Tsth);
    // debug::print_runtime((char*)"util", (char*)"clear", true);

    util::print_struct_meta<matrix_zt>(T1);
    // delete u;
    return 0;
}