#ifndef UTIL_H
#define UTIL_H

#include <gmpxx.h>
#include "struct.h"

class util
{
    public:
        static void print_struct(scalar_zt* obj);
        static void print_struct(matrix_zt* obj);
        static void print_struct(polynomial_zt* obj);

        static void print_struct_meta(scalar_zt* obj);
        static void print_struct_meta(matrix_zt* obj);
        static void print_struct_meta(polynomial_zt* obj);

        static scalar_zt* copy(scalar_zt* obj);
        static matrix_zt* copy(matrix_zt* obj);
        static polynomial_zt* copy(polynomial_zt* obj);

        static void clear(scalar_zt** obj);
        static void clear(matrix_zt** obj);
        static void clear(polynomial_zt** obj);

        // =================================================================================== //

        static void set_entry(scalar_zt* obj, char* value);
        static void set_entry(matrix_zt* obj, char* value, uint64_t pos_row, uint64_t pos_col);
        static void set_entry(matrix_zt* obj, scalar_zt* value, uint64_t pos_row, uint64_t pos_col);
        static void set_entry(polynomial_zt* obj, char* value, uint64_t pos);
        static void set_entry(polynomial_zt* obj, scalar_zt* value, uint64_t pos);

        // 아래는 통짜 배열을 넣는 데 이용하는 함수(미구현)
        static void fetch_entry(scalar_zt* obj);
        static void fetch_entry(matrix_zt* obj);
        static void fetch_entry(polynomial_zt* obj);

        // =================================================================================== //

        static void set_random_seed(unsigned long T);
        static void clear_random_seed();

        // if up > 0 : low <= entry < up, else up < 0 : low < entry <= up
        // can using multi threading(in this function doesn't exist improve)
        static void uniform_random(scalar_zt* obj, char* low, char* up);
        static void uniform_random(matrix_zt* obj, char* low, char* up);
        static void uniform_random(polynomial_zt* obj, char* low, char* up);
        static void uniform_random_mt(matrix_zt* obj, char* low, char* up);
        static void uniform_random_mt(polynomial_zt* obj, char* low, char* up);

        static void gaussian_random(scalar_zt* obj, char* mean, char* std);
        static void gaussian_random(matrix_zt* obj, char* mean, char* std);
        static void gaussian_random(polynomial_zt* obj, char* mean, char* std);
        static void gaussian_random_mt(matrix_zt* obj, char* mean, char* std);
        static void gaussian_random_mt(polynomial_zt* obj, char* mean, char* std);

        // =================================================================================== //

        static matrix_zt* stack_vertical(matrix_zt* obj1, matrix_zt* obj2);

        static matrix_zt* stack_horizon(matrix_zt* obj1, matrix_zt* obj2);
        static polynomial_zt* stack_horizon(polynomial_zt* obj1, polynomial_zt* obj2);

        // =================================================================================== //

        static polynomial_zt* NTT_pack(matrix_zt* matrix);

        static matrix_zt* NTT_unpack(polynomial_zt* polynomial);

        // =================================================================================== //

        static polynomial_zt* COE_pack(matrix_zt* matrix);

        static matrix_zt* COE_unpack(polynomial_zt* polynomial);
};

#endif