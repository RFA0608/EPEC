#include <memory>
#include <iostream>
#include <ctime>
#include "struct.h"
#include "util.h"
#include "calc.h"
using namespace std;

int main()
{
    // == test calc == //
    matrix_t* T1 = new matrix_t(10, 40000);
    matrix_t* T2 = new matrix_t(40000, 400);
    matrix_t* To;
    util::set_random_seed((unsigned long)time(NULL));
    util::uniform_random(T1, (char*)"0", (char*)"100000000000000000000000000000000000");
    util::uniform_random(T2, (char*)"0", (char*)"100000000000000000000000000000000000");

    To = calc::multiple(T1, T2);

    // util::print_struct(T1);
    // util::print_struct(T2);
    // util::print_struct(To);
    
    util::clear_random_seed();
    util::clear(&T1);
    util::clear(&T2);
    util::clear(&To);
    // util::print_struct(To);

    // == test util == //
    // util::print_struct(T);
    // matrix_t* T = new matrix_t(20, 20);
    // // util::set_entry(T, (char*)"-23132023819",1, 1);
    // util::set_random_seed((unsigned long)time(NULL));
    // util::uniform_random(T, (char*)"-3221430", (char*)"-30");

    // util::print_struct(T);
    // T->~matrix_t();
    // util::clear_random_seed();
    // T = nullptr;
    // util::print_struct(T);


    // polynomial_t* T1 = new polynomial_t(40);
    // // util::set_entry(T, (char*)"-23132023819",1, 1);
    // util::set_random_seed((unsigned long)time(NULL));
    // util::uniform_random(T1, (char*)"-1", (char*)"3");

    // util::print_struct(T1);
    // T1->~polynomial_t();
    // util::clear_random_seed();
    // T1 = nullptr;
    // util::print_struct(T1);

    // polynomial_t* T1 = new polynomial_t(9);
    // util::print_struct(T1);
    return 0;
}