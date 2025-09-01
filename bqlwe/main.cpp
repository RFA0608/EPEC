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
    matrix_ft* T1 = new matrix_ft(3, 3);
    matrix_ft* T2 = new matrix_ft(3, 3);

    polynomial_64ft* P1 = new polynomial_64ft(3);
    polynomial_64ft* P2 = new polynomial_64ft(5);

    util::set_random_seed((unsigned long)time(NULL));

    // debug::print_runtime((char*)"util", (char*)"uniform_random", false);
    util::uniform_random<matrix_ft>(T1, (char*)"0", (char*)"10");
    util::uniform_random<matrix_ft>(T2, (char*)"0", (char*)"10");

    // util::uniform_random<polynomial_zt>(P1, (char*)"0", (char*)"10");
    // util::uniform_random<polynomial_zt>(P2, (char*)"0", (char*)"10");
    util::set_entry<polynomial_64ft>(P1, (char*)"1", 1 , 1);
    util::set_entry<polynomial_64ft>(P1, (char*)"2", 1 , 2);
    util::set_entry<polynomial_64ft>(P1, (char*)"3", 1 , 3);
    // util::set_entry<polynomial_zt>(P1, (char*)"3", 1 , 4);
    // util::set_entry<polynomial_zt>(P1, (char*)"3", 1 , 5);

    util::set_entry<polynomial_64ft>(P2, (char*)"4", 1 , 1);
    util::set_entry<polynomial_64ft>(P2, (char*)"5", 1 , 2);
    util::set_entry<polynomial_64ft>(P2, (char*)"6", 1 , 3);
    util::set_entry<polynomial_64ft>(P2, (char*)"3", 1 , 4);
    util::set_entry<polynomial_64ft>(P2, (char*)"3", 1 , 5);


    matrix_ft* T3 = calc::add<matrix_ft>(T1, T2);
    polynomial_64ft* P3 = calc::conv<polynomial_64ft>(P1, P2);
    // matrix_zt* T3 = util::stack_vertical<matrix_zt>(T1, T2);
    // matrix_zt* T4 = util::stack_horizon<matrix_zt>(T1, T2);
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

    // util::print_struct<matrix_ft>(T1);
    // util::print_struct<matrix_ft>(T2);
    // util::print_struct<matrix_ft>(T3);

    util::print_struct<polynomial_64ft>(P1);
    util::print_struct<polynomial_64ft>(P2);
    util::print_struct<polynomial_64ft>(P3);
    // util::print_struct<matrix_zt>(T3);
    // util::print_struct<matrix_zt>(T4);
    // u::print_struct_meta(T2);
    // u::print_struct_meta(To1);
    // u::print_struct_meta(To2);
    // u::print_struct_meta(Tt1);
    // u::print_struct_meta(Tt2);
    // u::print_struct_meta(Tstv);
    // u::print_struct_meta(Tsth);
    
    // debug::print_runtime((char*)"util", (char*)"clear", false);
    util::clear_random_seed();
    util::clear<matrix_ft>(&T1);
    util::clear<matrix_ft>(&T2);
    util::clear<matrix_ft>(&T3);

    util::clear<polynomial_64ft>(&P1);
    util::clear<polynomial_64ft>(&P2);
    util::clear<polynomial_64ft>(&P3);
    // util::clear<matrix_zt>(&T4);
    // u::clear(&T2);
    // u::clear(&To1);
    // u::clear(&To2);
    // u::clear(&Tt1);
    // u::clear(&Tt2);
    // u::clear(&Tstv);
    // u::clear(&Tsth);
    // debug::print_runtime((char*)"util", (char*)"clear", true);

    util::print_struct_meta<matrix_ft>(T1);
    // delete u;
    return 0;
}