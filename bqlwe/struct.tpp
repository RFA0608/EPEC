#include "struct.h"
#include "debug.h"
#define mpf_prec 512

scalar_zt::scalar_zt()
{
    this->scalar = new mpz_t[1];
    this->size = new uint64_t[2];
    *(this->size) = 1;
    *(this->size + 1) = 1;
    this->type = 's';
    this->space = 'z';

    mpz_init_set_str(*(this->scalar), "0", 10);
}

scalar_zt::~scalar_zt()
{
    mpz_t* scalar = this->scalar;

    mpz_clear(*(scalar));

    delete[] this->scalar;
    delete[] this->size;
}

mpz_t* scalar_zt::return_content()
{
    return this->scalar;
}

uint64_t* scalar_zt::return_size()
{
    return this->size;
}

char scalar_zt:: return_type()
{
    return this->type;
}

scalar_ft::scalar_ft()
{
    this->scalar = new mpf_t[1];
    this->size = new uint64_t[2];
    *(this->size) = 1;
    *(this->size + 1) = 1;
    this->type = 's';
    this->space = 'f';

    mpf_init2(*(this->scalar), mpf_prec);
    mpf_set_str(*(this->scalar), "0.0", 10);
}

scalar_ft::~scalar_ft()
{
    mpf_t* scalar = this->scalar;

    mpf_clear(*(scalar));

    delete[] this->scalar;
    delete[] this->size;
}

mpf_t* scalar_ft::return_content()
{
    return this->scalar;
}

uint64_t* scalar_ft::return_size()
{
    return this->size;
}

char scalar_ft:: return_type()
{
    return this->type;
}

scalar_64it::scalar_64it()
{
    this->scalar = new int64_t[1];
    this->size = new uint64_t[2];
    *(this->size) = 1;
    *(this->size + 1) = 1;
    this->type = 's';
    this->space = 'i';

    *(this->scalar) = 0.0;
}

scalar_64it::~scalar_64it()
{
    delete[] this->scalar;
    delete[] this->size;
}

int64_t* scalar_64it::return_content()
{
    return this->scalar;
}

uint64_t* scalar_64it::return_size()
{
    return this->size;
}

char scalar_64it:: return_type()
{
    return this->type;
}

scalar_64ft::scalar_64ft()
{
    this->scalar = new double[1];
    this->size = new uint64_t[2];
    *(this->size) = 1;
    *(this->size + 1) = 1;
    this->type = 's';
    this->space = 'd';

    *(this->scalar) = 0.0;
}

scalar_64ft::~scalar_64ft()
{
    delete[] this->scalar;
    delete[] this->size;
}

double* scalar_64ft::return_content()
{
    return this->scalar;
}

uint64_t* scalar_64ft::return_size()
{
    return this->size;
}

char scalar_64ft:: return_type()
{
    return this->type;
}

// =================================================================================== //

matrix_zt::matrix_zt(uint64_t row, uint64_t col)
{
    this->matrix = new mpz_t[row * col];
    this->size = new uint64_t[2];
    *(this->size) = row;
    *(this->size + 1) = col;
    this->type = 'm';
    this->space = 'z';

    for(uint64_t i = 0; i < row; i++)
    {
        for(uint64_t j = 0; j < col; j++)
        {
            mpz_init_set_str(*(this->matrix + col * i + j), "0", 10);
        }
    }
}

matrix_zt::~matrix_zt()
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

mpz_t* matrix_zt::return_content()
{
    return this->matrix;
}

uint64_t* matrix_zt::return_size()
{
    return this->size;
}

char matrix_zt:: return_type()
{
    return this->type;
}

matrix_ft::matrix_ft(uint64_t row, uint64_t col)
{
    this->matrix = new mpf_t[row * col];
    this->size = new uint64_t[2];
    *(this->size) = row;
    *(this->size + 1) = col;
    this->type = 'm';
    this->space = 'f';

    for(uint64_t i = 0; i < row; i++)
    {
        for(uint64_t j = 0; j < col; j++)
        {
            mpf_init2(*(this->matrix + col * i + j), mpf_prec);
            mpf_set_str(*(this->matrix + col * i + j), "0.0", 10);
        }
    }
}

matrix_ft::~matrix_ft()
{
    mpf_t* matrix = this->matrix;
    uint64_t row = *(this->size);
    uint64_t col = *(this->size + 1);
    for(uint64_t i = 0; i < row; i++)
    {
        for(uint64_t j = 0; j < col; j++)
        {
            mpf_clear(*(matrix + col * i + j));
        }
    }
    delete[] this->matrix;
    delete[] this->size;
}

mpf_t* matrix_ft::return_content()
{
    return this->matrix;
}

uint64_t* matrix_ft::return_size()
{
    return this->size;
}

char matrix_ft:: return_type()
{
    return this->type;
}

matrix_64it::matrix_64it(uint64_t row, uint64_t col)
{
    this->matrix = new int64_t[row * col];
    this->size = new uint64_t[2];
    *(this->size) = row;
    *(this->size + 1) = col;
    this->type = 'm';
    this->space = 'i';

    for(uint64_t i = 0; i < row; i++)
    {
        for(uint64_t j = 0; j < col; j++)
        {
            *(this->matrix + col * i + j) = 0;
        }
    }
}

matrix_64it::~matrix_64it()
{
    delete[] this->matrix;
    delete[] this->size;
}

int64_t* matrix_64it::return_content()
{
    return this->matrix;
}

uint64_t* matrix_64it::return_size()
{
    return this->size;
}

char matrix_64it:: return_type()
{
    return this->type;
}

matrix_64ft::matrix_64ft(uint64_t row, uint64_t col)
{
    this->matrix = new double[row * col];
    this->size = new uint64_t[2];
    *(this->size) = row;
    *(this->size + 1) = col;
    this->type = 'm';
    this->space = 'd';

    for(uint64_t i = 0; i < row; i++)
    {
        for(uint64_t j = 0; j < col; j++)
        {
            *(this->matrix + col * i + j) = 0.0;
        }
    }
}

matrix_64ft::~matrix_64ft()
{
    delete[] this->matrix;
    delete[] this->size;
}

double* matrix_64ft::return_content()
{
    return this->matrix;
}

uint64_t* matrix_64ft::return_size()
{
    return this->size;
}

char matrix_64ft:: return_type()
{
    return this->type;
}

// =================================================================================== //

polynomial_zt::polynomial_zt(uint64_t order)
{
    this->polynomial = new mpz_t[order];
    this->size = new uint64_t[2];
    *(this->size) = 1;
    *(this->size + 1) = order;
    this->type = 'p';
    this->space = 'z';

    for(uint64_t i = 0; i < order; i++)
    {
        mpz_init_set_str(*(this->polynomial + i), "0", 10);
    }
}

polynomial_zt::~polynomial_zt()
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

mpz_t* polynomial_zt::return_content()
{
    return this->polynomial;
}

uint64_t* polynomial_zt::return_size()
{
    return this->size;
}

char polynomial_zt::return_type()
{
    return this->type;
}

polynomial_ft::polynomial_ft(uint64_t order)
{
    this->polynomial = new mpf_t[order];
    this->size = new uint64_t[2];
    *(this->size) = 1;
    *(this->size + 1) = order;
    this->type = 'p';
    this->space = 'f';

    for(uint64_t i = 0; i < order; i++)
    {
        mpf_init2(*(this->polynomial + i), mpf_prec);
        mpf_init_set_str(*(this->polynomial + i), "0.0", 10);
    }
}

polynomial_ft::~polynomial_ft()
{
    mpf_t* polynomial = this->polynomial;
    uint64_t row = *(this->size);
    uint64_t col = *(this->size + 1);
    for(uint64_t i = 0; i < row; i++)
    {
        for(uint64_t j = 0; j < col; j++)
        {
            mpf_clear(*(polynomial + col * i + j));
        }
    }
    delete[] this->polynomial;
    delete[] this->size;
}

mpf_t* polynomial_ft::return_content()
{
    return this->polynomial;
}

uint64_t* polynomial_ft::return_size()
{
    return this->size;
}

char polynomial_ft::return_type()
{
    return this->type;
}

polynomial_64it::polynomial_64it(uint64_t order)
{
    this->polynomial = new int64_t[order];
    this->size = new uint64_t[2];
    *(this->size) = 1;
    *(this->size + 1) = order;
    this->type = 'p';
    this->space = 'i';

    for(uint64_t i = 0; i < order; i++)
    {
        *(this->polynomial + i) = 0;
    }
}

polynomial_64it::~polynomial_64it()
{
    delete[] this->polynomial;
    delete[] this->size;
}

int64_t* polynomial_64it::return_content()
{
    return this->polynomial;
}

uint64_t* polynomial_64it::return_size()
{
    return this->size;
}

char polynomial_64it::return_type()
{
    return this->type;
}

polynomial_64ft::polynomial_64ft(uint64_t order)
{
    this->polynomial = new double[order];
    this->size = new uint64_t[2];
    *(this->size) = 1;
    *(this->size + 1) = order;
    this->type = 'p';
    this->space = 'd';

    for(uint64_t i = 0; i < order; i++)
    {
        *(this->polynomial + i) = 0.0;
    }
}

polynomial_64ft::~polynomial_64ft()
{
    delete[] this->polynomial;
    delete[] this->size;
}

double* polynomial_64ft::return_content()
{
    return this->polynomial;
}

uint64_t* polynomial_64ft::return_size()
{
    return this->size;
}

char polynomial_64ft::return_type()
{
    return this->type;
}