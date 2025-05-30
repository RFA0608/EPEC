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
    matrix_zt* T1 = new matrix_zt(30000, 100);
    matrix_zt* T2 = new matrix_zt(100, 3000);
    matrix_zt* To1, *To2, *Tt1, *Tt2, *Tstv, *Tsth;
    util::set_random_seed((unsigned long)time(NULL));

    debug::print_runtime((char*)"util", (char*)"uniform_random", false);
    util::uniform_random(T1, (char*)"0", (char*)"100000000");
    debug::print_runtime((char*)"util", (char*)"uniform_random", true);

    debug::print_runtime((char*)"util", (char*)"uniform_random_mt", false);
    util::uniform_random_mt(T1, (char*)"0", (char*)"100000000");
    debug::print_runtime((char*)"util", (char*)"uniform_random_mt", true);

    debug::print_runtime((char*)"util", (char*)"uniform_random", false);
    util::uniform_random(T2, (char*)"0", (char*)"100000000");
    debug::print_runtime((char*)"util", (char*)"uniform_random", true);

    debug::print_runtime((char*)"util", (char*)"uniform_random_mt ", false);
    util::uniform_random_mt(T2, (char*)"0", (char*)"100000000");
    debug::print_runtime((char*)"util", (char*)"uniform_random_mt", true);

    debug::print_runtime((char*)"calc", (char*)"multiple", false);
    To1 = calc::multiple(T1, T2);
    debug::print_runtime((char*)"calc", (char*)"multiple", true);

    debug::print_runtime((char*)"calc", (char*)"multiple_mt", false);
    To2 = calc::multiple_mt(T1, T2);
    debug::print_runtime((char*)"calc", (char*)"multiple_mt", true);

    debug::print_runtime((char*)"calc", (char*)"transpose", false);
    Tt1 = calc::transpose(To1);
    debug::print_runtime((char*)"calc", (char*)"transpose", true);
    
    debug::print_runtime((char*)"calc", (char*)"transpose_mt", false);
    Tt2 = calc::transpose_mt(To1);
    debug::print_runtime((char*)"calc", (char*)"transpose_mt", true);

    debug::print_runtime((char*)"util", (char*)"stack_vertical", false);
    Tstv = util::stack_vertical(Tt1, Tt2);
    debug::print_runtime((char*)"util", (char*)"stack_vertical", true);

    debug::print_runtime((char*)"util", (char*)"stack_horizon", false);
    Tsth = util::stack_horizon(Tt1, Tt2);
    debug::print_runtime((char*)"util", (char*)"stack_horizon", true);

    util::print_struct_meta(T1);
    util::print_struct_meta(T2);
    util::print_struct_meta(To1);
    util::print_struct_meta(To2);
    util::print_struct_meta(Tt1);
    util::print_struct_meta(Tt2);
    util::print_struct_meta(Tstv);
    util::print_struct_meta(Tsth);
    
    debug::print_runtime((char*)"util", (char*)"clear", false);
    util::clear_random_seed();
    util::clear(&T1);
    util::clear(&T2);
    util::clear(&To1);
    util::clear(&To2);
    util::clear(&Tt1);
    util::clear(&Tt2);
    util::clear(&Tstv);
    util::clear(&Tsth);
    debug::print_runtime((char*)"util", (char*)"clear", true);

    util::print_struct(To1);
    return 0;
}