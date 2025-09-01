#ifndef STRUCT_H
#define STRUCT_H

#include <iostream>
#include <format>
#include <gmpxx.h>

// zt : mpz, ft : mpf, 64ft : double, 64it : int64_t
// polynomial order = index number (ex, constant value section is poly[0])

class scalar_zt
{
    private:
        mpz_t* scalar;
        uint64_t* size;
        char type;
        char space;
    public:
        scalar_zt();
        ~scalar_zt();
        mpz_t* return_content();
        uint64_t* return_size();
        char return_type();
        char return_space();
};

class scalar_ft
{
    private:
        mpf_t* scalar;
        uint64_t* size;
        char type;
        char space;
    public:
        scalar_ft();
        ~scalar_ft();
        mpf_t* return_content();
        uint64_t* return_size();
        char return_type();
        char return_space();
};

class scalar_64it
{
    private:
        int64_t* scalar;
        uint64_t* size;
        char type;
        char space;
    public:
        scalar_64it();
        ~scalar_64it();
        int64_t* return_content();
        uint64_t* return_size();
        char return_type();
        char return_space();
};

class scalar_64ft
{
    private:
        double* scalar;
        uint64_t* size;
        char type;
        char space;
    public:
        scalar_64ft();
        ~scalar_64ft();
        double* return_content();
        uint64_t* return_size();
        char return_type();
        char return_space();
};

// =================================================================================== //

class matrix_zt
{
    private:
        mpz_t* matrix;
        uint64_t* size;
        char type;
        char space;
    public:
        matrix_zt(uint64_t row, uint64_t col);
        ~matrix_zt();
        mpz_t* return_content();
        uint64_t* return_size();
        char return_type();
        char return_space();
};

class matrix_ft
{
    private:
        mpf_t* matrix;
        uint64_t* size;
        char type;
        char space;
    public:
        matrix_ft(uint64_t row, uint64_t col);
        ~matrix_ft();
        mpf_t* return_content();
        uint64_t* return_size();
        char return_type();
        char return_space();
};

class matrix_64it
{
    private:
        int64_t* matrix;
        uint64_t* size;
        char type;
        char space;
    public:
        matrix_64it(uint64_t row, uint64_t col);
        ~matrix_64it();
        int64_t* return_content();
        uint64_t* return_size();
        char return_type();
        char return_space();
};

class matrix_64ft
{
    private:
        double* matrix;
        uint64_t* size;
        char type;
        char space;
    public:
        matrix_64ft(uint64_t row, uint64_t col);
        ~matrix_64ft();
        double* return_content();
        uint64_t* return_size();
        char return_type();
        char return_space();
};

// =================================================================================== //

class polynomial_zt
{
    private:
        mpz_t* polynomial;
        uint64_t* size;
        char type;
        char space;
    public:
        polynomial_zt(uint64_t order);
        ~polynomial_zt();
        mpz_t* return_content();
        uint64_t* return_size();
        char return_type();
        char return_space();
};

class polynomial_ft
{
    private:
        mpf_t* polynomial;
        uint64_t* size;
        char type;
        char space;
    public:
        polynomial_ft(uint64_t order);
        ~polynomial_ft();
        mpf_t* return_content();
        uint64_t* return_size();
        char return_type();
        char return_space();
};

class polynomial_64it
{
    private:
        int64_t* polynomial;
        uint64_t* size;
        char type;
        char space;
    public:
        polynomial_64it(uint64_t order);
        ~polynomial_64it();
        int64_t* return_content();
        uint64_t* return_size();
        char return_type();
        char return_space();
};

class polynomial_64ft
{
    private:
        double* polynomial;
        uint64_t* size;
        char type;
        char space;
    public:
        polynomial_64ft(uint64_t order);
        ~polynomial_64ft();
        double* return_content();
        uint64_t* return_size();
        char return_type();
        char return_space();
};

#include "struct.tpp"

#endif