#include <gmpxx.h>
#include "struct.h"

scalar_t::scalar_t()
{
    this->scalar = new mpz_t[1];
    this->size = new uint64_t[2];
    *(this->size) = 1;
    *(this->size + 1) = 1;
    this->type = 's';

    mpz_init_set_str(*(this->scalar), "0", 10);
}

scalar_t::~scalar_t()
{
    mpz_t* scalar = this->scalar;
    uint64_t row = *(this->size);
    uint64_t col = *(this->size + 1);
    for(uint64_t i = 0; i < row; i++)
    {
        for(uint64_t j = 0; j < col; j++)
        {
            mpz_clear(*(scalar + col * i + j));
        }
    }
    delete[] this->scalar;
    delete[] this->size;
}

mpz_t* scalar_t::return_scalar()
{
    return this->scalar;
}

uint64_t* scalar_t::return_size()
{
    return this->size;
}

char scalar_t:: return_type()
{
    return this->type;
}

matrix_t::matrix_t(uint64_t row, uint64_t col)
{
    this->matrix = new mpz_t[row * col];
    this->size = new uint64_t[2];
    *(this->size) = row;
    *(this->size + 1) = col;
    this->type = 'm';

    for(uint64_t i = 0; i < row; i++)
    {
        for(uint64_t j = 0; j < col; j++)
        {
            mpz_init_set_str(*(this->matrix + col * i + j), "0", 10);
        }
    }
}

matrix_t::~matrix_t()
{
    mpz_t* matrix = this->matrix;
    uint64_t row = *(this->size);
    uint64_t col = *(this->size + 1);
    for(uint64_t i = 0; i < row; i++)
    {
        for(uint64_t j = 0; j < col; j++)
        {
            mpz_clear(*(matrix + col * i + j));
        }
    }
    delete[] this->matrix;
    delete[] this->size;
}

mpz_t* matrix_t::return_matrix()
{
    return this->matrix;
}

uint64_t* matrix_t::return_size()
{
    return this->size;
}

char matrix_t:: return_type()
{
    return this->type;
}

polynomial_t::polynomial_t(uint64_t order)
{
    this->polynomial = new mpz_t[order];
    this->size = new uint64_t[2];
    *(this->size) = 1;
    *(this->size + 1) = order;
    this->type = 'p';

    for(uint64_t i = 0; i < order; i++)
    {
        mpz_init_set_str(*(this->polynomial + i), "0", 10);
    }
}

polynomial_t::~polynomial_t()
{
    mpz_t* polynomial = this->polynomial;
    uint64_t row = *(this->size);
    uint64_t col = *(this->size + 1);
    for(uint64_t i = 0; i < row; i++)
    {
        for(uint64_t j = 0; j < col; j++)
        {
            mpz_clear(*(polynomial + col * i + j));
        }
    }
    delete[] this->polynomial;
    delete[] this->size;
}

mpz_t* polynomial_t::return_polynomial()
{
    return this->polynomial;
}

uint64_t* polynomial_t::return_size()
{
    return this->size;
}

char polynomial_t::return_type()
{
    return this->type;
}