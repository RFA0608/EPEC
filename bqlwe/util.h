#ifndef UTIL_H
#define UTIL_H

#include <gmpxx.h>
#include "struct.h"

class util
{
    public:
        static void print_struct(scalar_t* obj);
        static void print_struct(matrix_t* obj);
        static void print_struct(polynomial_t* obj);

        static scalar_t* copy(scalar_t* obj);
        static matrix_t* copy(matrix_t* obj);
        static polynomial_t* copy(polynomial_t* obj);

        static void clear(scalar_t** obj);
        static void clear(matrix_t** obj);
        static void clear(polynomial_t** obj);

        // =================================================================================== //

        static void set_entry(scalar_t* obj, char* value);
        // static void set_entry(matrix_t* obj, mpz_t value, uint64_t pos_row, uint64_t pos_col);
        // static void set_entry(matrix_t* obj, int64_t value, uint64_t pos_row, uint64_t pos_col);
        static void set_entry(matrix_t* obj, char* value, uint64_t pos_row, uint64_t pos_col);
        static void set_entry(matrix_t* obj, scalar_t* value, uint64_t pos_row, uint64_t pos_col);
        // static void set_entry(polynomial_t* obj, mpz_t value, uint64_t pos);
        // static void set_entry(polynomial_t* obj, int64_t value, uint64_t pos);
        static void set_entry(polynomial_t* obj, char* value, uint64_t pos);
        static void set_entry(polynomial_t* obj, scalar_t* value, uint64_t pos_row, uint64_t pos_col);

        static void fetch_scalar();
        static void fetch_matrix();
        static void fetch_polynomial();

        // =================================================================================== //

        static void set_random_seed(unsigned long T);
        static void clear_random_seed();

        // if up > 0 : low <= entry < up, else up < 0 : low < entry <= up
        static void uniform_random(scalar_t* obj, char* low, char* up);
        // static void uniform_random(matrix_t* obj, mpz_t low, mpz_t up);
        // static void uniform_random(matrix_t* obj, int64_t low, int64_t up);
        static void uniform_random(matrix_t* obj, char* low, char* up);
        // static void uniform_random(polynomial_t* obj, mpz_t low, mpz_t up);
        // static void uniform_random(polynomial_t* obj, int64_t low, int64_t up);
        static void uniform_random(polynomial_t* obj, char* low, char* up);


        static matrix_t* gaussian_random(matrix_t* obj, mpz_t mean, mpz_t std);
        static polynomial_t* gaussian_random(polynomial_t* obj, mpz_t mean, mpz_t std);

        // =================================================================================== //

        static matrix_t* stack_vertical(matrix_t* obj1, matrix_t* obj2);

        static matrix_t* stack_horizon(matrix_t* obj1, matrix_t* obj2);
        static polynomial_t* stack_horizon(polynomial_t* obj1, polynomial_t* obj2);

        // =================================================================================== //

        static polynomial_t* NTT_pack(matrix_t* matrix);

        static matrix_t* NTT_unpack(polynomial_t* polynomial);

        // =================================================================================== //

        static polynomial_t* COE_pack(matrix_t* matrix);

        static matrix_t* COE_unpack(polynomial_t* polynomial);
};

#endif