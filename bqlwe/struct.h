#ifndef STRUCT_H
#define STRUCT_H

#include <gmpxx.h>

class scalar_t
{
    private:
        mpz_t* scalar;
        uint64_t* size;
        char type;
    public:
        scalar_t();
        ~scalar_t();
        mpz_t* return_scalar();
        uint64_t* return_size();
        char return_type();
};

class matrix_t
{
    private:
        mpz_t* matrix;
        uint64_t* size;
        char type;
    public:
        matrix_t(uint64_t row, uint64_t col);
        ~matrix_t();
        mpz_t* return_matrix();
        uint64_t* return_size();
        char return_type();
};

class polynomial_t
{
    private:
        mpz_t* polynomial;
        uint64_t* size;
        char type;
    public:
        polynomial_t(uint64_t order);
        ~polynomial_t();
        mpz_t* return_polynomial();
        uint64_t* return_size();
        char return_type();
};

#endif