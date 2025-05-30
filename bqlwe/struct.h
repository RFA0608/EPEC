#ifndef STRUCT_H
#define STRUCT_H

#include <iostream>
#include <gmpxx.h>

// zt : mpz, ft : mpf, 64ft : double, 64it : int64_t

class scalar_zt
{
    private:
        mpz_t* scalar;
        uint64_t* size;
        char type;
    public:
        scalar_zt();
        ~scalar_zt();
        mpz_t* return_scalar();
        uint64_t* return_size();
        char return_type();
};

class scalar_ft
{
    private:
        mpf_t* scalar;
        uint64_t* size;
        char type;
    public:
        scalar_ft();
        ~scalar_ft();
        mpf_t* return_scalar();
        uint64_t* return_size();
        char return_type();
};

class scalar_64it
{
    private:
        int64_t* scalar;
        uint64_t* size;
        char type;
    public:
        scalar_64it();
        ~scalar_64it();
        int64_t* return_scalar();
        uint64_t* return_size();
        char return_type();
};

class scalar_64ft
{
    private:
        double* scalar;
        uint64_t* size;
        char type;
    public:
        scalar_64ft();
        ~scalar_64ft();
        double* return_scalar();
        uint64_t* return_size();
        char return_type();
};

// =================================================================================== //

class matrix_zt
{
    private:
        mpz_t* matrix;
        uint64_t* size;
        char type;
    public:
        matrix_zt(uint64_t row, uint64_t col);
        ~matrix_zt();
        mpz_t* return_matrix();
        uint64_t* return_size();
        char return_type();
};

class matrix_ft
{
    private:
        mpf_t* matrix;
        uint64_t* size;
        char type;
    public:
        matrix_ft(uint64_t row, uint64_t col);
        ~matrix_ft();
        mpf_t* return_matrix();
        uint64_t* return_size();
        char return_type();
};

class matrix_64it
{
    private:
        int64_t* matrix;
        uint64_t* size;
        char type;
    public:
        matrix_64it(uint64_t row, uint64_t col);
        ~matrix_64it();
        int64_t* return_matrix();
        uint64_t* return_size();
        char return_type();
};

class matrix_64ft
{
    private:
        double* matrix;
        uint64_t* size;
        char type;
    public:
        matrix_64ft(uint64_t row, uint64_t col);
        ~matrix_64ft();
        double* return_matrix();
        uint64_t* return_size();
        char return_type();
};

// =================================================================================== //

class polynomial_zt
{
    private:
        mpz_t* polynomial;
        uint64_t* size;
        char type;
    public:
        polynomial_zt(uint64_t order);
        ~polynomial_zt();
        mpz_t* return_polynomial();
        uint64_t* return_size();
        char return_type();
};

class polynomial_ft
{
    private:
        mpf_t* polynomial;
        uint64_t* size;
        char type;
    public:
        polynomial_ft(uint64_t order);
        ~polynomial_ft();
        mpf_t* return_polynomial();
        uint64_t* return_size();
        char return_type();
};

class polynomial_64it
{
    private:
        int64_t* polynomial;
        uint64_t* size;
        char type;
    public:
        polynomial_64it(uint64_t order);
        ~polynomial_64it();
        int64_t* return_polynomial();
        uint64_t* return_size();
        char return_type();
};

class polynomial_64ft
{
    private:
        double* polynomial;
        uint64_t* size;
        char type;
    public:
        polynomial_64ft(uint64_t order);
        ~polynomial_64ft();
        double* return_polynomial();
        uint64_t* return_size();
        char return_type();
};
#endif