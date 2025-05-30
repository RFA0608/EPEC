#ifndef CALC_H
#define CALC_H

#include <gmpxx.h>
#include "struct.h"

class calc
{
    public:
        static matrix_zt* multiple(matrix_zt* obj1, matrix_zt* obj2); 
        static polynomial_zt* multiple(polynomial_zt* obj1, polynomial_zt* obj2);
        static matrix_zt* multiple_mt(matrix_zt* obj1, matrix_zt* obj2); 
        static polynomial_zt* multiple_mt(polynomial_zt* obj1, polynomial_zt* obj2);

        static polynomial_zt* convolution(polynomial_zt* obj1, polynomial_zt* obj2);
        static polynomial_zt* convolution_mt(polynomial_zt* obj1, polynomial_zt* obj2);

        static matrix_zt* add(matrix_zt* obj1, matrix_zt* obj2);
        static polynomial_zt* add(polynomial_zt* obj1, polynomial_zt* obj2);
        static matrix_zt* add_mt(matrix_zt* obj1, matrix_zt* obj2);
        static polynomial_zt* add_mt(polynomial_zt* obj1, polynomial_zt* obj2);

        static matrix_zt* mult_constant(matrix_zt* obj, mpz_t c);
        static polynomial_zt* mult_constant(polynomial_zt* obj, mpz_t c);

        static matrix_zt* identity(matrix_zt* obj);
        static polynomial_zt* identity(polynomial_zt* obj);

        static matrix_zt* transpose(matrix_zt* obj);
        static matrix_zt* transpose_mt(matrix_zt* obj);

        static polynomial_zt* flip(polynomial_zt* obj);

        static matrix_zt* modulo(matrix_zt* obj, mpz_t q);

        static polynomial_zt* coeficient_modulo(polynomial_zt* obj, mpz_t q);
        
        static polynomial_zt* ring_modulo(polynomial_zt* obj, mpz_t N);
};

#endif