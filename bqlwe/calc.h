#ifndef CALC_H
#define CALC_H

#include <gmpxx.h>
#include "struct.h"

class calc
{
    public:
        static matrix_t* multiple(matrix_t* obj1, matrix_t* obj2); 
        static polynomial_t* multiple(polynomial_t* obj1, polynomial_t* obj2);
        static polynomial_t* convolution(polynomial_t* obj1, polynomial_t* obj2);

        static matrix_t* add(matrix_t* obj1, matrix_t* obj2);
        static polynomial_t* add(polynomial_t* obj1, polynomial_t* obj2);

        static matrix_t* mult_constant(matrix_t* obj, mpz_t c);
        static polynomial_t* mult_constant(polynomial_t* obj, mpz_t c);

        static matrix_t* identity(matrix_t* obj);
        static polynomial_t* identity(polynomial_t* obj);

        static matrix_t* transpose(matrix_t* obj);

        static polynomial_t* flip(polynomial_t* obj);

        static matrix_t* modulo(matrix_t* obj, mpz_t q);

        static polynomial_t* coeficient_modulo(polynomial_t* obj, mpz_t q);
        
        static polynomial_t* ring_modulo(polynomial_t* obj, mpz_t N);
};

#endif