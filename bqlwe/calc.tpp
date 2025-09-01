#include <iostream>
#include <pthread.h>
#include <thread>
#include "util.h"
#include "calc.h"
#include "debug.h"
#include "parameters.h"
using namespace std;

template <typename T>
T* calc::mult(T* obj1, T* obj2)
{
    if(obj1 == nullptr || obj2 == nullptr)
    {
        debug::print_error((char*)"calc", (char*)"mult", 0, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        if constexpr (is_same_v<T, scalar_zt> || is_same_v<T, matrix_zt> || is_same_v<T, polynomial_zt>)
        {
            mpz_t* content1 = obj1->return_content();
            uint64_t row1 = *(obj1->return_size());
            uint64_t col1 = *(obj1->return_size() + 1);

            mpz_t* content2 = obj2->return_content();
            uint64_t row2 = *(obj2->return_size());
            uint64_t col2 = *(obj2->return_size() + 1);

            if constexpr (is_same_v<T, scalar_zt>)
            {
                T* new_struct = new T();
                mpz_t* structure = new_struct->return_content();
                uint64_t row = *(new_struct->return_size());
                uint64_t col = *(new_struct->return_size() + 1);

                mpz_t temp;
                mpz_init_set_str(temp, "0", 10);

                for(uint64_t i = 0; i < row; i++)
                {
                    for(uint64_t j = 0; j < col; j++)
                    {
                        for(uint64_t k = 0; k < col1; k++)
                        {
                            mpz_mul(temp, *(content1 + col1 * i + k), *(content2 + col2 * k + j));
                            mpz_add(*(structure + col * i + j), *(structure + col * i + j), temp);
                        }
                    }
                }

                mpz_clear(temp);

                return new_struct;
            }
            else if constexpr (is_same_v<T, matrix_zt>)
            {
                if(col1 != row2)
                {
                    debug::print_error((char*)"calc", (char*)"mult", 0, (char*)"size error");
                    debug::print_error_specific((char*)"obj1 and obj2 not suitable mult(under matrix)");
                    exit(-1);
                }
                else
                {
                    T* new_struct = new T(row1, col2);
                    mpz_t* structure = new_struct->return_content();
                    uint64_t row = *(new_struct->return_size());
                    uint64_t col = *(new_struct->return_size() + 1);

                    mpz_t temp;
                    mpz_init_set_str(temp, "0", 10);

                    for(uint64_t i = 0; i < row; i++)
                    {
                        for(uint64_t j = 0; j < col; j++)
                        {
                            for(uint64_t k = 0; k < col1; k++)
                            {
                                mpz_mul(temp, *(content1 + col1 * i + k), *(content2 + col2 * k + j));
                                mpz_add(*(structure + col * i + j), *(structure + col * i + j), temp);
                            }
                        }
                    }

                    mpz_clear(temp);

                    return new_struct;
                }
            }
            else
            {
                if(col1 != col2)
                {
                    debug::print_error((char*)"calc", (char*)"mult", 0, (char*)"size error");
                    debug::print_error_specific((char*)"obj1 and obj2 not suitable mult(under polynomial)");
                    exit(-1);
                }
                else
                {
                    T* new_struct = new T(col1);
                    mpz_t* structure = new_struct->return_content();
                    uint64_t row = *(new_struct->return_size());
                    uint64_t col = *(new_struct->return_size() + 1);

                    mpz_t temp;
                    mpz_init_set_str(temp, "0", 10);

                    for(uint64_t i = 0; i < row; i++)
                    {
                        for(uint64_t j = 0; j < col; j++)
                        {
                            for(uint64_t k = 0; k < col1; k++)
                            {
                                mpz_mul(temp, *(content1 + col1 * i + k), *(content2 + col2 * k + j));
                                mpz_add(*(structure + col * i + j), *(structure + col * i + j), temp);
                            }
                        }
                    }

                    mpz_clear(temp);

                    return new_struct;
                }
            }
        }
        else if constexpr (is_same_v<T, scalar_ft> || is_same_v<T, matrix_ft> || is_same_v<T, polynomial_ft>)
        {
            mpf_t* content1 = obj1->return_content();
            uint64_t row1 = *(obj1->return_size());
            uint64_t col1 = *(obj1->return_size() + 1);

            mpf_t* content2 = obj2->return_content();
            uint64_t row2 = *(obj2->return_size());
            uint64_t col2 = *(obj2->return_size() + 1);

            if constexpr (is_same_v<T, scalar_ft>)
            {
                T* new_struct = new T();
                mpf_t* structure = new_struct->return_content();
                uint64_t row = *(new_struct->return_size());
                uint64_t col = *(new_struct->return_size() + 1);

                mpf_t temp;
                mpf_init2(temp, mpf_prec);
                mpf_set_str(temp, "0.0", 10);

                for(uint64_t i = 0; i < row; i++)
                {
                    for(uint64_t j = 0; j < col; j++)
                    {
                        for(uint64_t k = 0; k < col1; k++)
                        {
                            mpf_mul(temp, *(content1 + col1 * i + k), *(content2 + col2 * k + j));
                            mpf_add(*(structure + col * i + j), *(structure + col * i + j), temp);
                        }
                    }
                }

                mpf_clear(temp);

                return new_struct;
            }
            else if constexpr (is_same_v<T, matrix_ft>)
            {
                if(col1 != row2)
                {
                    debug::print_error((char*)"calc", (char*)"mult", 0, (char*)"size error");
                    debug::print_error_specific((char*)"obj1 and obj2 not suitable mult(under matrix)");
                    exit(-1);
                }
                else
                {
                    T* new_struct = new T(row1, col2);
                    mpf_t* structure = new_struct->return_content();
                    uint64_t row = *(new_struct->return_size());
                    uint64_t col = *(new_struct->return_size() + 1);

                    mpf_t temp;
                    mpf_init2(temp, mpf_prec);
                    mpf_set_str(temp, "0.0", 10);

                    for(uint64_t i = 0; i < row; i++)
                    {
                        for(uint64_t j = 0; j < col; j++)
                        {
                            for(uint64_t k = 0; k < col1; k++)
                            {
                                mpf_mul(temp, *(content1 + col1 * i + k), *(content2 + col2 * k + j));
                                mpf_add(*(structure + col * i + j), *(structure + col * i + j), temp);
                            }
                        }
                    }

                    mpf_clear(temp);

                    return new_struct;
                }
            }
            else
            {
                if(col1 != col2)
                {
                    debug::print_error((char*)"calc", (char*)"mult", 0, (char*)"size error");
                    debug::print_error_specific((char*)"obj1 and obj2 not suitable mult(under polynomial)");
                    exit(-1);
                }
                else
                {
                    T* new_struct = new T(row1, col2);
                    mpf_t* structure = new_struct->return_content();
                    uint64_t row = *(new_struct->return_size());
                    uint64_t col = *(new_struct->return_size() + 1);

                    mpf_t temp;
                    mpf_init2(temp, mpf_prec);
                    mpf_set_str(temp, "0.0", 10);

                    for(uint64_t i = 0; i < row; i++)
                    {
                        for(uint64_t j = 0; j < col; j++)
                        {
                            for(uint64_t k = 0; k < col1; k++)
                            {
                                mpf_mul(temp, *(content1 + col1 * i + k), *(content2 + col2 * k + j));
                                mpf_add(*(structure + col * i + j), *(structure + col * i + j), temp);
                            }
                        }
                    }

                    mpf_clear(temp);

                    return new_struct;
                }
            }
        }
        else if constexpr (is_same_v<T, scalar_64it> || is_same_v<T, matrix_64it> || is_same_v<T, polynomial_64it>)
        {
            int64_t* content1 = obj1->return_content();
            uint64_t row1 = *(obj1->return_size());
            uint64_t col1 = *(obj1->return_size() + 1);

            int64_t* content2 = obj2->return_content();
            uint64_t row2 = *(obj2->return_size());
            uint64_t col2 = *(obj2->return_size() + 1);

            if constexpr (is_same_v<T, scalar_64it>)
            {
                T* new_struct = new T();
                int64_t* structure = new_struct->return_content();
                uint64_t row = *(new_struct->return_size());
                uint64_t col = *(new_struct->return_size() + 1);

                int64_t temp = 0;

                for(uint64_t i = 0; i < row; i++)
                {
                    for(uint64_t j = 0; j < col; j++)
                    {
                        for(uint64_t k = 0; k < col1; k++)
                        {
                            temp = *(content1 + col1 * i + k) * *(content2 + col2 * k + j);
                            *(structure + col * i + j) = *(structure + col * i + j) + temp;
                        }
                    }
                }

                return new_struct;
            }
            else if constexpr (is_same_v<T, matrix_64it>)
            {
                if(col1 != row2)
                {
                    debug::print_error((char*)"calc", (char*)"mult", 0, (char*)"size error");
                    debug::print_error_specific((char*)"obj1 and obj2 not suitable mult(under matrix)");
                    exit(-1);
                }
                else
                {
                    T* new_struct = new T(row1, col2);
                    int64_t* structure = new_struct->return_content();
                    uint64_t row = *(new_struct->return_size());
                    uint64_t col = *(new_struct->return_size() + 1);

                    int64_t temp = 0;

                    for(uint64_t i = 0; i < row; i++)
                    {
                        for(uint64_t j = 0; j < col; j++)
                        {
                            for(uint64_t k = 0; k < col1; k++)
                            {
                                temp = *(content1 + col1 * i + k) * *(content2 + col2 * k + j);
                                *(structure + col * i + j) = *(structure + col * i + j) + temp;
                            }
                        }
                    }

                    return new_struct;
                }
            }
            else
            {
                if(col1 != col2)
                {
                    debug::print_error((char*)"calc", (char*)"mult", 0, (char*)"size error");
                    debug::print_error_specific((char*)"obj1 and obj2 not suitable mult(under polynomial)");
                    exit(-1);
                }
                else
                {
                    T* new_struct = new T(row1, col2);
                    int64_t* structure = new_struct->return_content();
                    uint64_t row = *(new_struct->return_size());
                    uint64_t col = *(new_struct->return_size() + 1);

                    int64_t temp = 0;

                    for(uint64_t i = 0; i < row; i++)
                    {
                        for(uint64_t j = 0; j < col; j++)
                        {
                            for(uint64_t k = 0; k < col1; k++)
                            {
                                temp = *(content1 + col1 * i + k) * *(content2 + col2 * k + j);
                                *(structure + col * i + j) = *(structure + col * i + j) + temp;
                            }
                        }
                    }

                    return new_struct;
                }
            }
        }
        else if constexpr (is_same_v<T, scalar_64ft> || is_same_v<T, matrix_64ft> || is_same_v<T, polynomial_64ft>)
        {
            double* content1 = obj1->return_content();
            uint64_t row1 = *(obj1->return_size());
            uint64_t col1 = *(obj1->return_size() + 1);

            double* content2 = obj2->return_content();
            uint64_t row2 = *(obj2->return_size());
            uint64_t col2 = *(obj2->return_size() + 1);

            if constexpr (is_same_v<T, scalar_64ft>)
            {
                T* new_struct = new T();
                double* structure = new_struct->return_content();
                uint64_t row = *(new_struct->return_size());
                uint64_t col = *(new_struct->return_size() + 1);

                double temp = 0.0;

                for(uint64_t i = 0; i < row; i++)
                {
                    for(uint64_t j = 0; j < col; j++)
                    {
                        for(uint64_t k = 0; k < col1; k++)
                        {
                            temp = *(content1 + col1 * i + k) * *(content2 + col2 * k + j);
                            *(structure + col * i + j) = *(structure + col * i + j) + temp;
                        }
                    }
                }

                return new_struct;
            }
            else if constexpr (is_same_v<T, matrix_64ft>)
            {
                if(col1 != row2)
                {
                    debug::print_error((char*)"calc", (char*)"mult", 0, (char*)"size error");
                    debug::print_error_specific((char*)"obj1 and obj2 not suitable mult(under matrix)");
                    exit(-1);
                }
                else
                {
                    T* new_struct = new T(row1, col2);
                    double* structure = new_struct->return_content();
                    uint64_t row = *(new_struct->return_size());
                    uint64_t col = *(new_struct->return_size() + 1);

                    double temp = 0;

                    for(uint64_t i = 0; i < row; i++)
                    {
                        for(uint64_t j = 0; j < col; j++)
                        {
                            for(uint64_t k = 0; k < col1; k++)
                            {
                                temp = *(content1 + col1 * i + k) * *(content2 + col2 * k + j);
                                *(structure + col * i + j) = *(structure + col * i + j) + temp;
                            }
                        }
                    }

                    return new_struct;
                }
            }
            else
            {
                if(col1 != col2)
                {
                    debug::print_error((char*)"calc", (char*)"mult", 0, (char*)"size error");
                    debug::print_error_specific((char*)"obj1 and obj2 not suitable mult(under polynomial)");
                    exit(-1);
                }
                else
                {
                    T* new_struct = new T(row1, col2);
                    double* structure = new_struct->return_content();
                    uint64_t row = *(new_struct->return_size());
                    uint64_t col = *(new_struct->return_size() + 1);

                    double temp = 0;

                    for(uint64_t i = 0; i < row; i++)
                    {
                        for(uint64_t j = 0; j < col; j++)
                        {
                            for(uint64_t k = 0; k < col1; k++)
                            {
                                temp = *(content1 + col1 * i + k) * *(content2 + col2 * k + j);
                                *(structure + col * i + j) = *(structure + col * i + j) + temp;
                            }
                        }
                    }

                    return new_struct;
                }
            }
        }
        else
        {
            debug::print_error((char*)"calc", (char*)"mult", 0, (char*)"non exist struct");
            debug::print_error_specific((char*)"given struct is not defined");
            exit(-1);
        }
    }
}

template <typename T>
T* calc::conv(T* obj1, T* obj2)
{
    if(obj1 == nullptr || obj2 == nullptr)
    {
        debug::print_error((char*)"calc", (char*)"conv", 0, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        if constexpr (is_same_v<T, polynomial_zt> || is_same_v<T, polynomial_ft> || is_same_v<T, polynomial_64it> || is_same_v<T, polynomial_64ft>)
        {
            if constexpr (is_same_v<T, polynomial_zt>)
            {
                uint64_t col1 = *(obj1->return_size() + 1);

                mpz_t* content2 = obj2->return_content();
                uint64_t col2 = *(obj2->return_size() + 1);

                T* zero_struct = new T(col2 - 1);
                T* temp_struct = util::stack_horizon<T>(obj1, zero_struct);
                mpz_t* temp_structure = temp_struct->return_content();
                
                T* new_struct = new T(col1 + col2 - 1);
                mpz_t* structure = new_struct->return_content();
                uint64_t col = *(new_struct->return_size() + 1);

                mpz_t temp;
                mpz_init_set_str(temp, "0", 10);

                for(uint64_t i = 0; i < col; i++)
                {
                    mpz_set_str(temp, "0", 10);
                    if(i < col2)
                    {
                        for(uint64_t j = 0; j <= i; j++)
                        {
                            mpz_mul(temp, *(temp_structure + j), *(content2 + i - j));
                            mpz_add(*(structure + i), *(structure + i), temp);
                        }
                    }
                    else
                    {
                        for(uint64_t j = 0; j < col2; j++)
                        {
                            mpz_mul(temp, *(temp_structure + (i - col2 + 1) + j), *(content2 + (col2 - 1) - j));
                            mpz_add(*(structure + i), *(structure + i), temp);
                        }
                    }
                }

                util::clear<T>(&zero_struct);
                util::clear<T>(&temp_struct);
                mpz_clear(temp);

                return new_struct;
            }
            else if constexpr (is_same_v<T, polynomial_ft>)
            {
                uint64_t col1 = *(obj1->return_size() + 1);

                mpf_t* content2 = obj2->return_content();
                uint64_t col2 = *(obj2->return_size() + 1);

                T* zero_struct = new T(col2 - 1);
                T* temp_struct = util::stack_horizon<T>(obj1, zero_struct);
                mpf_t* temp_structure = temp_struct->return_content();
                
                T* new_struct = new T(col1 + col2 - 1);
                mpf_t* structure = new_struct->return_content();
                uint64_t col = *(new_struct->return_size() + 1);

                mpf_t temp;
                mpf_init2(temp, mpf_prec);
                mpf_set_str(temp, "0.0", 10);

                for(uint64_t i = 0; i < col; i++)
                {
                    mpf_set_str(temp, "0.0", 10);
                    if(i < col2)
                    {
                        for(uint64_t j = 0; j <= i; j++)
                        {
                            mpf_mul(temp, *(temp_structure + j), *(content2 + i - j));
                            mpf_add(*(structure + i), *(structure + i), temp);
                        }
                    }
                    else
                    {
                        for(uint64_t j = 0; j < col2; j++)
                        {
                            mpf_mul(temp, *(temp_structure + (i - col2 + 1) + j), *(content2 + (col2 - 1) - j));
                            mpf_add(*(structure + i), *(structure + i), temp);
                        }
                    }
                }

                util::clear<T>(&zero_struct);
                util::clear<T>(&temp_struct);
                mpf_clear(temp);

                return new_struct;
            }
            else if constexpr (is_same_v<T, polynomial_64it>)
            {
                uint64_t col1 = *(obj1->return_size() + 1);

                int64_t* content2 = obj2->return_content();
                uint64_t col2 = *(obj2->return_size() + 1);

                T* zero_struct = new T(col2 - 1);
                T* temp_struct = util::stack_horizon<T>(obj1, zero_struct);
                int64_t* temp_structure = temp_struct->return_content();
                
                T* new_struct = new T(col1 + col2 - 1);
                int64_t* structure = new_struct->return_content();
                uint64_t col = *(new_struct->return_size() + 1);

                int64_t temp = 0;

                for(uint64_t i = 0; i < col; i++)
                {
                    temp = 0;
                    if(i < col2)
                    {
                        for(uint64_t j = 0; j <= i; j++)
                        {
                            temp = *(temp_structure + j) * *(content2 + i - j);
                            *(structure + i) = *(structure + i) + temp;
                        }
                    }
                    else
                    {
                        for(uint64_t j = 0; j < col2; j++)
                        {
                            temp = *(temp_structure + (i - col2 + 1) + j) * *(content2 + (col2 - 1) - j);
                            *(structure + i) = *(structure + i) + temp;
                        }
                    }
                }

                util::clear<T>(&zero_struct);
                util::clear<T>(&temp_struct);

                return new_struct;
            }
            else
            {
                uint64_t col1 = *(obj1->return_size() + 1);

                double* content2 = obj2->return_content();
                uint64_t col2 = *(obj2->return_size() + 1);

                T* zero_struct = new T(col2 - 1);
                T* temp_struct = util::stack_horizon<T>(obj1, zero_struct);
                double* temp_structure = temp_struct->return_content();
                
                T* new_struct = new T(col1 + col2 - 1);
                double* structure = new_struct->return_content();
                uint64_t col = *(new_struct->return_size() + 1);

                double temp = 0;

                for(uint64_t i = 0; i < col; i++)
                {
                    temp = 0;
                    if(i < col2)
                    {
                        for(uint64_t j = 0; j <= i; j++)
                        {
                            temp = *(temp_structure + j) * *(content2 + i - j);
                            *(structure + i) = *(structure + i) + temp;
                        }
                    }
                    else
                    {
                        for(uint64_t j = 0; j < col2; j++)
                        {
                            temp = *(temp_structure + (i - col2 + 1) + j) * *(content2 + (col2 - 1) - j);
                            *(structure + i) = *(structure + i) + temp;
                        }
                    }
                }

                util::clear<T>(&zero_struct);
                util::clear<T>(&temp_struct);

                return new_struct;
            }
        }
        else
        {
            debug::print_error((char*)"calc", (char*)"conv", 0, (char*)"non supported struct");
            debug::print_error_specific((char*)"given struct is not supported");
            exit(-1);
        }
    }
}

template <typename T>
T* calc::add(T* obj1, T* obj2)
{
    if(obj1 == nullptr || obj2 == nullptr)
    {
        debug::print_error((char*)"calc", (char*)"add", 0, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        if constexpr (is_same_v<T, scalar_zt> || is_same_v<T, matrix_zt> || is_same_v<T, polynomial_zt>)
        {
            mpz_t* content1 = obj1->return_content();
            uint64_t row1 = *(obj1->return_size());
            uint64_t col1 = *(obj1->return_size() + 1);

            mpz_t* content2 = obj2->return_content();
            uint64_t row2 = *(obj2->return_size());
            uint64_t col2 = *(obj2->return_size() + 1);

            if(row1 != row2 || col1 != col2)
            {
                debug::print_error((char*)"calc", (char*)"add", 0, (char*)"size error");
                debug::print_error_specific((char*)"obj1 and obj2 not suitable add");
                exit(-1);
            }
            else
            {
                if constexpr (is_same_v<T, scalar_zt>)
                {
                    T* new_struct = new T();
                    mpz_t* structure = new_struct->return_content();
                    uint64_t row = *(new_struct->return_size());
                    uint64_t col = *(new_struct->return_size() + 1);

                    for(uint64_t i = 0; i < row; i++)
                    {
                        for(uint64_t j = 0; j < col; j++)
                        {
                            mpz_add(*(structure + col * i + j), *(content1 + col * i + j), *(content2 + col * i + j));
                        }
                    }

                    return new_struct;
                }
                else if constexpr (is_same_v<T, matrix_zt>)
                {
                    T* new_struct = new T(row1, col1);
                    mpz_t* structure = new_struct->return_content();
                    uint64_t row = *(new_struct->return_size());
                    uint64_t col = *(new_struct->return_size() + 1);

                    for(uint64_t i = 0; i < row; i++)
                    {
                        for(uint64_t j = 0; j < col; j++)
                        {
                            mpz_add(*(structure + col * i + j), *(content1 + col * i + j), *(content2 + col * i + j));
                        }
                    }

                    return new_struct;
                }
                else
                {
                    T* new_struct = new T(col1);
                    mpz_t* structure = new_struct->return_content();
                    uint64_t row = *(new_struct->return_size());
                    uint64_t col = *(new_struct->return_size() + 1);

                    for(uint64_t i = 0; i < row; i++)
                    {
                        for(uint64_t j = 0; j < col; j++)
                        {
                            mpz_add(*(structure + col * i + j), *(content1 + col * i + j), *(content2 + col * i + j));
                        }
                    }

                    return new_struct;
                }
            }
        }
        else if constexpr (is_same_v<T, scalar_ft> || is_same_v<T, matrix_ft> || is_same_v<T, polynomial_ft>)
        {
            mpf_t* content1 = obj1->return_content();
            uint64_t row1 = *(obj1->return_size());
            uint64_t col1 = *(obj1->return_size() + 1);

            mpf_t* content2 = obj2->return_content();
            uint64_t row2 = *(obj2->return_size());
            uint64_t col2 = *(obj2->return_size() + 1);

            if(row1 != row2 || col1 != col2)
            {
                debug::print_error((char*)"calc", (char*)"add", 0, (char*)"size error");
                debug::print_error_specific((char*)"obj1 and obj2 not suitable add");
                exit(-1);
            }
            else
            {
                if constexpr (is_same_v<T, scalar_ft>)
                {
                    T* new_struct = new T();
                    mpf_t* structure = new_struct->return_content();
                    uint64_t row = *(new_struct->return_size());
                    uint64_t col = *(new_struct->return_size() + 1);

                    for(uint64_t i = 0; i < row; i++)
                    {
                        for(uint64_t j = 0; j < col; j++)
                        {
                            mpf_add(*(structure + col * i + j), *(content1 + col * i + j), *(content2 + col * i + j));
                        }
                    }

                    return new_struct;
                }
                else if constexpr (is_same_v<T, matrix_ft>)
                {
                    T* new_struct = new T(row1, col1);
                    mpf_t* structure = new_struct->return_content();
                    uint64_t row = *(new_struct->return_size());
                    uint64_t col = *(new_struct->return_size() + 1);

                    for(uint64_t i = 0; i < row; i++)
                    {
                        for(uint64_t j = 0; j < col; j++)
                        {
                            mpf_add(*(structure + col * i + j), *(content1 + col * i + j), *(content2 + col * i + j));
                        }
                    }

                    return new_struct;
                }
                else
                {
                    T* new_struct = new T(col1);
                    mpf_t* structure = new_struct->return_content();
                    uint64_t row = *(new_struct->return_size());
                    uint64_t col = *(new_struct->return_size() + 1);

                    for(uint64_t i = 0; i < row; i++)
                    {
                        for(uint64_t j = 0; j < col; j++)
                        {
                            mpf_add(*(structure + col * i + j), *(content1 + col * i + j), *(content2 + col * i + j));
                        }
                    }

                    return new_struct;
                }
            }
        }
        else if constexpr (is_same_v<T, scalar_64it> || is_same_v<T, matrix_64it> || is_same_v<T, polynomial_64it>)
        {
            int64_t* content1 = obj1->return_content();
            uint64_t row1 = *(obj1->return_size());
            uint64_t col1 = *(obj1->return_size() + 1);

            int64_t* content2 = obj2->return_content();
            uint64_t row2 = *(obj2->return_size());
            uint64_t col2 = *(obj2->return_size() + 1);

            if(row1 != row2 || col1 != col2)
            {
                debug::print_error((char*)"calc", (char*)"add", 0, (char*)"size error");
                debug::print_error_specific((char*)"obj1 and obj2 not suitable add");
                exit(-1);
            }
            else
            {
                if constexpr (is_same_v<T, scalar_64it>)
                {
                    T* new_struct = new T();
                    int64_t* structure = new_struct->return_content();
                    uint64_t row = *(new_struct->return_size());
                    uint64_t col = *(new_struct->return_size() + 1);

                    for(uint64_t i = 0; i < row; i++)
                    {
                        for(uint64_t j = 0; j < col; j++)
                        {
                            *(structure + col * i + j) = *(content1 + col * i + j) + *(content2 + col * i + j);
                        }
                    }

                    return new_struct;
                }
                else if constexpr (is_same_v<T, matrix_64it>)
                {
                    T* new_struct = new T(row1, col1);
                    int64_t* structure = new_struct->return_content();
                    uint64_t row = *(new_struct->return_size());
                    uint64_t col = *(new_struct->return_size() + 1);

                    for(uint64_t i = 0; i < row; i++)
                    {
                        for(uint64_t j = 0; j < col; j++)
                        {
                            *(structure + col * i + j) = *(content1 + col * i + j) + *(content2 + col * i + j);
                        }
                    }

                    return new_struct;
                }
                else
                {
                    T* new_struct = new T(col1);
                    int64_t* structure = new_struct->return_content();
                    uint64_t row = *(new_struct->return_size());
                    uint64_t col = *(new_struct->return_size() + 1);

                    for(uint64_t i = 0; i < row; i++)
                    {
                        for(uint64_t j = 0; j < col; j++)
                        {
                            *(structure + col * i + j) = *(content1 + col * i + j) + *(content2 + col * i + j);
                        }
                    }

                    return new_struct;
                }
            }
        }
        else if constexpr (is_same_v<T, scalar_64ft> || is_same_v<T, matrix_64ft> || is_same_v<T, polynomial_64ft>)
        {
            double* content1 = obj1->return_content();
            uint64_t row1 = *(obj1->return_size());
            uint64_t col1 = *(obj1->return_size() + 1);

            double* content2 = obj2->return_content();
            uint64_t row2 = *(obj2->return_size());
            uint64_t col2 = *(obj2->return_size() + 1);

            if(row1 != row2 || col1 != col2)
            {
                debug::print_error((char*)"calc", (char*)"add", 0, (char*)"size error");
                debug::print_error_specific((char*)"obj1 and obj2 not suitable add");
                exit(-1);
            }
            else
            {
                if constexpr (is_same_v<T, scalar_64it>)
                {
                    T* new_struct = new T();
                    double* structure = new_struct->return_content();
                    uint64_t row = *(new_struct->return_size());
                    uint64_t col = *(new_struct->return_size() + 1);

                    for(uint64_t i = 0; i < row; i++)
                    {
                        for(uint64_t j = 0; j < col; j++)
                        {
                            *(structure + col * i + j) = *(content1 + col * i + j) + *(content2 + col * i + j);
                        }
                    }

                    return new_struct;
                }
                else if constexpr (is_same_v<T, matrix_64it>)
                {
                    T* new_struct = new T(row1, col1);
                    double* structure = new_struct->return_content();
                    uint64_t row = *(new_struct->return_size());
                    uint64_t col = *(new_struct->return_size() + 1);

                    for(uint64_t i = 0; i < row; i++)
                    {
                        for(uint64_t j = 0; j < col; j++)
                        {
                            *(structure + col * i + j) = *(content1 + col * i + j) + *(content2 + col * i + j);
                        }
                    }

                    return new_struct;
                }
                else
                {
                    T* new_struct = new T(col1);
                    double* structure = new_struct->return_content();
                    uint64_t row = *(new_struct->return_size());
                    uint64_t col = *(new_struct->return_size() + 1);

                    for(uint64_t i = 0; i < row; i++)
                    {
                        for(uint64_t j = 0; j < col; j++)
                        {
                            *(structure + col * i + j) = *(content1 + col * i + j) + *(content2 + col * i + j);
                        }
                    }

                    return new_struct;
                }
            }
        }
        else
        {
            debug::print_error((char*)"calc", (char*)"add", 0, (char*)"non exist struct");
            debug::print_error_specific((char*)"given struct is not defined");
            exit(-1);
        }
    }
}


/// previous code ///

// const uint64_t thread_num = std::thread::hardware_concurrency() > 1 ? std::thread::hardware_concurrency() : 1;
// const uint64_t thread_block = 2;
// const uint64_t multple_block_coefficient = 1;
// const uint64_t add_block_coefficient = 320;
// const uint64_t transpose_block_coefficient = 20;

// matrix_zt* calc::multiple(matrix_zt* obj1, matrix_zt* obj2)
// {
//     if(obj1 == nullptr || obj2 == nullptr)
//     {
//         debug::print_error((char*)"calc", (char*)"multiple", 0, (char*)"reference nullptr");
//         debug::print_error_specific((char*)"function attribution is nullptr");
//         exit(-1);
//     }
//     else
//     {
//         mpz_t* matrix_1 = obj1->return_matrix();
//         uint64_t row_1 = *(obj1->return_size());
//         uint64_t col1 = *(obj1->return_size() + 1);

//         mpz_t* matrix_2 = obj2->return_matrix();
//         uint64_t row_2 = *(obj2->return_size());
//         uint64_t col2 = *(obj2->return_size() + 1);

//         if(col1 != row_2)
//         {
//             debug::print_error((char*)"calc", (char*)"multiple", 0, (char*)"matrix define");
//             debug::print_error_specific((char*)"obj1 matrix and obj2 matrix size unmatched over matrix multiple");
//             exit(-1);
//         }
//         else
//         {
//             matrix_zt* new_matrix_struct = new matrix_zt(row_1, col2);
//             mpz_t* new_matrix = new_matrix_struct->return_matrix();
//             uint64_t col = *(new_matrix_struct->return_size() + 1);

//             mpz_t temp;
//             mpz_init_set_str(temp, "0", 10);

//             for(uint64_t i = 0; i < row_1; i++)
//             {
//                 for(uint64_t j = 0; j < col2; j++)
//                 {
//                     for(uint64_t k = 0; k < col1; k++)
//                     {
//                         mpz_mul(temp, *(matrix_1 + col1 * i + k), *(matrix_2 + col2 * k + j));
//                         mpz_add(*(new_matrix + col * i + j), *(new_matrix + col * i + j), temp);
//                     }
//                 }
//             }

//             mpz_clear(temp);

//             return new_matrix_struct;
//         }
//     }
// }

// polynomial_zt* calc::multiple(polynomial_zt* obj1, polynomial_zt* obj2)
// {
//     if(obj1 == nullptr || obj2 == nullptr)
//     {
//         debug::print_error((char*)"calc", (char*)"multiple", 1, (char*)"reference nullptr");
//         debug::print_error_specific((char*)"function attribution is nullptr");
//         exit(-1);
//     }
//     else
//     {
//         mpz_t* polynomial_1 = obj1->return_polynomial();
//         uint64_t order_1 = *(obj1->return_size() + 1);

//         mpz_t* polynomial_2 = obj2->return_polynomial();
//         uint64_t order_2 = *(obj2->return_size() + 1);

//         if(order_1 != order_2)
//         {
//             debug::print_error((char*)"calc", (char*)"multiple", 1, (char*)"polynomial length");
//             debug::print_error_specific((char*)"obj1 polynomial and obj2 polynomial order unmatched over component multiple on polynomial");
//             exit(-1);
//         }
//         else
//         {
//             polynomial_zt* new_polynomial_struct = new polynomial_zt(order_1);
//             mpz_t* new_polynomial = new_polynomial_struct->return_polynomial();
//             uint64_t order = *(new_polynomial_struct->return_size() + 1);

//             for(uint64_t i = 0; i < order; i++)
//             {
//                 mpz_mul(*(new_polynomial + i), *(polynomial_1 + i), *(polynomial_2 + i));
//             }

//             return new_polynomial_struct;
//         }
//     }
// }

// // void* ptr = [matrix_zt* objo, matrix_zt* obj1, matrix_zt* obj2, uint64_t start_obj1_row_point, uint64_t end_obj1_row_point]
// void* mutiple_row_threading_matrix(void* ptr)
// {
//     void** arg_arr = (void**)ptr;
//     matrix_zt* objo = (matrix_zt*)arg_arr[0];
//     matrix_zt* obj1 = (matrix_zt*)arg_arr[1];
//     matrix_zt* obj2 = (matrix_zt*)arg_arr[2];
//     uint64_t start_point = *(uint64_t*)arg_arr[3];
//     uint64_t end_point = *(uint64_t*)arg_arr[4];

//     mpz_t* matrix_o = objo->return_matrix();
//     uint64_t col_o = *(objo->return_size() + 1);

//     mpz_t* matrix_1 = obj1->return_matrix();
//     uint64_t col1 = *(obj1->return_size() + 1);

//     mpz_t* matrix_2 = obj2->return_matrix();
//     uint64_t col2 = *(obj2->return_size() + 1);

//     mpz_t temp;
//     mpz_init_set_str(temp, "0", 10);

//     for(uint64_t i = start_point; i < end_point; i++)
//     {
//         for(uint64_t j = 0; j < col2; j++)
//         {
//             for(uint64_t k = 0; k < col1; k++)
//             {
//                 mpz_mul(temp, *(matrix_1 + col1 * i + k), *(matrix_2 + col2 * k + j));
//                 mpz_add(*(matrix_o + col_o * i + j), *(matrix_o + col_o * i + j), temp);
//             }
//         }
//     }

//     mpz_clear(temp);

//     return NULL;
// }

// // void* ptr = [matrix_zt* objo, matrix_zt* obj1, matrix_zt* obj2, uint64_t start_obj1_col_point, uint64_t end_obj1_col_point]
// void* mutiple_col_threading_matrix(void* ptr)
// {
//     void** arg_arr = (void**)ptr;
//     matrix_zt* objo = (matrix_zt*)arg_arr[0];
//     matrix_zt* obj1 = (matrix_zt*)arg_arr[1];
//     matrix_zt* obj2 = (matrix_zt*)arg_arr[2];
//     uint64_t start_point = *(uint64_t*)arg_arr[3];
//     uint64_t end_point = *(uint64_t*)arg_arr[4];

//     mpz_t* matrix_o = objo->return_matrix();
//     uint64_t col_o = *(objo->return_size() + 1);

//     mpz_t* matrix_1 = obj1->return_matrix();
//     uint64_t row_1 = *(obj1->return_size());
//     uint64_t col1 = *(obj1->return_size() + 1);

//     mpz_t* matrix_2 = obj2->return_matrix();
//     uint64_t col2 = *(obj2->return_size() + 1);

//     mpz_t temp;
//     mpz_init_set_str(temp, "0", 10);

//     for(uint64_t i = start_point; i < end_point; i++)
//     {
//         for(uint64_t j = 0; j < row_1; j++)
//         {
//             for(uint64_t k = 0; k < col2; k++)
//             {
//                 mpz_mul(temp, *(matrix_1 + col1 * j + i), *(matrix_2 + col2 * i + k));
//                 mpz_add(*(matrix_o + col_o * j + k), *(matrix_o + col_o * j + k), temp);
//             }
//         }
//     }

//     mpz_clear(temp);

//     return NULL;
// }

// matrix_zt* calc::multiple_mt(matrix_zt* obj1, matrix_zt* obj2)
// {
//     if(obj1 == nullptr || obj2 == nullptr)
//     {
//         debug::print_error((char*)"calc", (char*)"multiple_mt", 0, (char*)"reference nullptr");
//         debug::print_error_specific((char*)"function attribution is nullptr");
//         exit(-1);
//     }
//     else
//     {
//         uint64_t row_1 = *(obj1->return_size());
//         uint64_t col1 = *(obj1->return_size() + 1);

//         uint64_t row_2 = *(obj2->return_size());
//         uint64_t col2 = *(obj2->return_size() + 1);

//         if(col1 != row_2)
//         {
//             debug::print_error((char*)"calc", (char*)"multiple_mt", 0, (char*)"matrix define");
//             debug::print_error_specific((char*)"obj1 matrix and obj2 matrix size unmatched over matrix multiple");
//             exit(-1);
//         }
//         else
//         {
//             if(row_1 >= col1)
//             {
//                 uint64_t block_length = 0;
//                 uint64_t block_residue = 0;
//                 uint64_t thread_using = 0;

//                 for(uint64_t i = thread_num; i > 0; i--)
//                 {
//                     block_length = (uint64_t) (row_1 / i);
//                     block_residue = (row_1 % i);
//                     thread_using = i;

//                     if(block_length > multple_block_coefficient * thread_block)
//                     {
//                         break;
//                     }
//                     else
//                     {
//                         continue;
//                     }
//                 }

//                 debug::print_thread_info((char*)"calc", (char*)"multiple_mt", 0, thread_using);

//                 matrix_zt* new_matrix_struct = new matrix_zt(row_1, col2);

//                 pthread_t* thread_id = new pthread_t[thread_using];
//                 void*** arg_arr = new void**[thread_using];
//                 for(uint64_t i = 0; i < thread_using; i++)
//                 {
//                     arg_arr[i] = new void*[5];
//                 }

//                 uint64_t* start_point = new uint64_t[thread_using]{0};
//                 uint64_t* end_point = new uint64_t[thread_using]{0};

//                 for(uint64_t i = 0; i < thread_using; i++)
//                 {
//                     if(i != (thread_using - 1))
//                     {
//                         *(start_point + i) = block_length * i;
//                         *(end_point + i) = block_length * (i + 1);
//                     }
//                     else if(i > 0)
//                     {
//                         *(start_point + i) = *(end_point + i - 1);
//                         *(end_point + i) = block_length * (i + 1) + block_residue;
//                     }
//                     else
//                     {
//                         *(start_point + i) = 0;
//                         *(end_point + i) = block_length * (i + 1) + block_residue;
//                     }
                                                
//                     arg_arr[i][0] = (void*)new_matrix_struct;
//                     arg_arr[i][1] = (void*)obj1;
//                     arg_arr[i][2] = (void*)obj2;
//                     arg_arr[i][3] = (void*)(start_point + i);
//                     arg_arr[i][4] = (void*)(end_point + i);

//                     int error = pthread_create(&*(thread_id + i), NULL, mutiple_row_threading_matrix, (void*) arg_arr[i]);
//                     if(error)
//                     {
//                         debug::print_error((char*)"calc", (char*)"multiple_mt", 0, (char*)"threading");
//                         debug::print_error_specific((char*)"can not create thread");
//                         exit(-1);
//                     }
//                 }

//                 for(uint64_t i = 0; i < thread_using; i++)
//                 {
//                     pthread_join(*(thread_id + i), NULL);
//                 }

//                 delete[] start_point;
//                 delete[] end_point;
//                 delete[] thread_id;
//                 for(uint64_t i = 0; i < thread_using; i++)
//                 {
//                     delete[] arg_arr[i];
//                 }
//                 delete[] arg_arr;

//                 return new_matrix_struct;
//             }
//             else
//             {
//                 uint64_t block_length = 0;
//                 uint64_t block_residue = 0;
//                 uint64_t thread_using = 0;

//                 for(uint64_t i = thread_num; i > 0; i--)
//                 {
//                     block_length = (uint64_t) (col1 / i);
//                     block_residue = (col1 % i);
//                     thread_using = i;

//                     if(block_length > multple_block_coefficient * thread_block)
//                     {
//                         break;
//                     }
//                     else
//                     {
//                         continue;
//                     }
//                 }

//                 debug::print_thread_info((char*)"calc", (char*)"multiple_mt", 0, thread_using);

//                 matrix_zt** new_matrix_struct_list = new matrix_zt*[thread_using];
//                 for(uint64_t i = 0; i < thread_using; i++)
//                 {
//                     *(new_matrix_struct_list + i) = new matrix_zt(row_1, col2);
//                 }

//                 pthread_t* thread_id = new pthread_t[thread_using];
//                 void*** arg_arr = new void**[thread_using];
//                 for(uint64_t i = 0; i < thread_using; i++)
//                 {
//                     arg_arr[i] = new void*[5];
//                 }

//                 uint64_t* start_point = new uint64_t[thread_using]{0};
//                 uint64_t* end_point = new uint64_t[thread_using]{0};

//                 for(uint64_t i = 0; i < thread_using; i++)
//                 {
//                     if(i != (thread_using - 1))
//                     {
//                         *(start_point + i) = block_length * i;
//                         *(end_point + i) = block_length * (i + 1);
//                     }
//                     else if(i > 0)
//                     {
//                         *(start_point + i) = *(end_point + i - 1);
//                         *(end_point + i) = block_length * (i + 1) + block_residue;
//                     }
//                     else
//                     {
//                         *(start_point + i) = 0;
//                         *(end_point + i) = block_length * (i + 1) + block_residue;
//                     }
                                                
//                     arg_arr[i][0] = (void*)new_matrix_struct_list[i];
//                     arg_arr[i][1] = (void*)obj1;
//                     arg_arr[i][2] = (void*)obj2;
//                     arg_arr[i][3] = (void*)(start_point + i);
//                     arg_arr[i][4] = (void*)(end_point + i);

//                     int error = pthread_create(&*(thread_id + i), NULL, mutiple_col_threading_matrix, (void*) arg_arr[i]);
//                     if(error)
//                     {
//                         debug::print_error((char*)"calc", (char*)"multiple_mt", 0, (char*)"threading");
//                         debug::print_error_specific((char*)"can not create thread");
//                         exit(-1);
//                     }
//                 }

//                 for(uint64_t i = 0; i < thread_using; i++)
//                 {
//                     pthread_join(*(thread_id + i), NULL);
//                 }

//                 matrix_zt* new_matrix_struct = new matrix_zt(row_1, col2);
//                 matrix_zt* temp;
//                 for(uint64_t i = 0; i < thread_using; i++)
//                 {
//                     temp = calc::add_mt(new_matrix_struct, *(new_matrix_struct_list + i));
//                     util::clear(&new_matrix_struct);
//                     new_matrix_struct = temp;
//                 }

//                 for(uint64_t i = 0; i < thread_using; i++)
//                 {
//                     util::clear(&(*(new_matrix_struct_list + i)));
//                 }
//                 delete[] new_matrix_struct_list;
//                 delete[] start_point;
//                 delete[] end_point;
//                 delete[] thread_id;
//                 for(uint64_t i = 0; i < thread_using; i++)
//                 {
//                     delete[] arg_arr[i];
//                 }
//                 delete[] arg_arr;

//                 return new_matrix_struct;
//             }   
//         }
//     }
// }

// matrix_zt* calc::add(matrix_zt* obj1, matrix_zt* obj2)
// {
//     if(obj1 == nullptr || obj2 == nullptr)
//     {
//         debug::print_error((char*)"calc", (char*)"add", 0, (char*)"reference nullptr");
//         debug::print_error_specific((char*)"function attribution is nullptr");
//         exit(-1);
//     }
//     else
//     {
//         mpz_t* matrix_1 = obj1->return_matrix();
//         uint64_t row_1 = *(obj1->return_size());
//         uint64_t col1 = *(obj1->return_size() + 1);

//         mpz_t* matrix_2 = obj2->return_matrix();
//         uint64_t row_2 = *(obj2->return_size());
//         uint64_t col2 = *(obj2->return_size() + 1);
        
//         if(row_1 != row_2 || col1 != col2)
//         {
//             debug::print_error((char*)"calc", (char*)"add", 0, (char*)"matrix define");
//             debug::print_error_specific((char*)"obj1 matrix and obj2 matrix size unmatched over matrix add");
//             exit(-1);
//         }
//         else
//         {
//             matrix_zt* new_matrix_struct = new matrix_zt(row_1, col1);
//             mpz_t* new_matrix = new_matrix_struct->return_matrix();
//             uint64_t row = *(new_matrix_struct->return_size());
//             uint64_t col = *(new_matrix_struct->return_size() + 1);

//             for(uint64_t i = 0; i < row; i++)
//             {
//                 for(uint64_t j = 0; j < col; j++)
//                 {
//                     mpz_add(*(new_matrix + col * i + j), *(matrix_1 + col1 * i + j), *(matrix_2 + col2 * i + j));
//                 }
//             }

//             return new_matrix_struct;
//         }
//     }
// }

// // void* ptr = [matrix_zt* objo, matrix_zt* obj1, matrix_zt* obj2, uint64_t start_point, uint64_t end_point]
// void* add_threading_matrix(void* ptr)
// {
//     void** arg_arr = (void**)ptr;
//     matrix_zt* objo = (matrix_zt*)arg_arr[0];
//     matrix_zt* obj1 = (matrix_zt*)arg_arr[1];
//     matrix_zt* obj2 = (matrix_zt*)arg_arr[2];
//     uint64_t start_point = *(uint64_t*)arg_arr[3];
//     uint64_t end_point = *(uint64_t*)arg_arr[4];

//     mpz_t* matrix_o = objo->return_matrix();

//     mpz_t* matrix_1 = obj1->return_matrix();

//     mpz_t* matrix_2 = obj2->return_matrix();

//     for(uint64_t i = start_point; i < end_point; i++)
//     {
//         mpz_add(*(matrix_o + i), *(matrix_1 + i), *(matrix_2 + i));
//     }

//     return NULL;
// }

// matrix_zt* calc::add_mt(matrix_zt* obj1, matrix_zt* obj2)
// {
//     if(obj1 == nullptr || obj2 == nullptr)
//     {
//         debug::print_error((char*)"calc", (char*)"add_mt", 0, (char*)"reference nullptr");
//         debug::print_error_specific((char*)"function attribution is nullptr");
//         exit(-1);
//     }
//     else
//     {
//         uint64_t row_1 = *(obj1->return_size());
//         uint64_t col1 = *(obj1->return_size() + 1);

//         uint64_t row_2 = *(obj2->return_size());
//         uint64_t col2 = *(obj2->return_size() + 1);
        
//         if(row_1 != row_2 || col1 != col2)
//         {
//             debug::print_error((char*)"calc", (char*)"add_mt", 0, (char*)"matrix define");
//             debug::print_error_specific((char*)"obj1 matrix and obj2 matrix size unmatched over matrix add");
//             exit(-1);
//         }
//         else
//         {
//             uint64_t block_length = 0;
//             uint64_t block_residue = 0;
//             uint64_t thread_using = 0;

//             for(uint64_t i = thread_num; i > 0; i--)
//             {
//                 block_length = (uint64_t) (row_1 * col1 / i);
//                 block_residue = (row_1 * col1 % i);
//                 thread_using = i;

//                 if(block_length > add_block_coefficient * thread_block)
//                 {
//                     break;
//                 }
//                 else
//                 {
//                     continue;
//                 }
//             }

//             debug::print_thread_info((char*)"calc", (char*)"add_mt", 0, thread_using);

//             matrix_zt* new_matrix_struct = new matrix_zt(row_1, col1);

//             pthread_t* thread_id = new pthread_t[thread_using];
//             void*** arg_arr = new void**[thread_using];
//             for(uint64_t i = 0; i < thread_using; i++)
//             {
//                 arg_arr[i] = new void*[5];
//             }

//             uint64_t* start_point = new uint64_t[thread_using]{0};
//             uint64_t* end_point = new uint64_t[thread_using]{0};

//             for(uint64_t i = 0; i < thread_using; i++)
//             {
//                 if(i != (thread_using - 1))
//                 {
//                     *(start_point + i) = block_length * i;
//                     *(end_point + i) = block_length * (i + 1);
//                 }
//                 else if(i > 0)
//                 {
//                     *(start_point + i) = *(end_point + i - 1);
//                     *(end_point + i) = block_length * (i + 1) + block_residue;
//                 }
//                 else
//                 {
//                     *(start_point + i) = 0;
//                     *(end_point + i) = block_length * (i + 1) + block_residue;
//                 }
                                                
//                 arg_arr[i][0] = (void*)new_matrix_struct;
//                 arg_arr[i][1] = (void*)obj1;
//                 arg_arr[i][2] = (void*)obj2;
//                 arg_arr[i][3] = (void*)(start_point + i);
//                 arg_arr[i][4] = (void*)(end_point + i);

//                 int error = pthread_create(&*(thread_id + i), NULL, add_threading_matrix, (void*) arg_arr[i]);
//                 if(error)
//                 {
//                     debug::print_error((char*)"calc", (char*)"add_mt", 0, (char*)"threading");
//                         debug::print_error_specific((char*)"can not create thread");
//                     exit(-1);
//                 }
//             }

//             for(uint64_t i = 0; i < thread_using; i++)
//             {
//                 pthread_join(*(thread_id + i), NULL);
//             }

//             delete[] start_point;
//             delete[] end_point;
//             delete[] thread_id;
//             for(uint64_t i = 0; i < thread_using; i++)
//             {
//                 delete[] arg_arr[i];
//             }
//             delete[] arg_arr;

//             return new_matrix_struct;
//         }
//     }
// }

// matrix_zt* calc::transpose(matrix_zt* obj)
// {
//     if(obj == nullptr)
//     {
//         debug::print_error((char*)"calc", (char*)"transpose", 0, (char*)"reference nullptr");
//         debug::print_error_specific((char*)"function attribution is nullptr");
//         exit(-1);
//     }
//     else
//     {
//         mpz_t* matrix = obj->return_matrix();
//         uint64_t row = *(obj->return_size());
//         uint64_t col = *(obj->return_size() + 1);

//         matrix_zt* new_matrix_struct = new matrix_zt(col, row);
//         mpz_t* new_matrix = new_matrix_struct->return_matrix();

//         for(uint64_t i = 0; i < row; i++)
//         {
//             for(uint64_t j = 0; j < col; j++)
//             {
//                 mpz_set(*(new_matrix + row * j + i), *(matrix + col * i + j));
//             }
//         }

//          return new_matrix_struct;
//     }
// }

// // void* ptr = [matrix_zt* objo, matrix_zt* obji, uint64_t start_row_point, uint64_t end_row_point]
// void* transpose_row_threading_matrix(void* ptr)
// {
//     void** arg_arr = (void**)ptr;
//     matrix_zt* objo = (matrix_zt*)arg_arr[0];
//     matrix_zt* obji = (matrix_zt*)arg_arr[1];
//     uint64_t start_point = *(uint64_t*)arg_arr[2];
//     uint64_t end_point = *(uint64_t*)arg_arr[3];

//     mpz_t* matrix_o = objo->return_matrix();
//     uint64_t col_o = *(objo->return_size() + 1);

//     mpz_t* matrix_i = obji->return_matrix();
//     uint64_t col_i = *(obji->return_size() + 1);

//     for(uint64_t i = start_point; i < end_point; i++)
//     {
//         for(uint64_t j = 0; j < col_i; j++)
//         {
//             mpz_set(*(matrix_o + col_o * j + i), *(matrix_i + col_i * i + j));
//         }
//     }

//     return NULL;
// }

// // void* ptr = [matrix_zt* objo, matrix_zt* obji, uint64_t start_col_point, uint64_t end_col_point]
// void* transpose_col_threading_matrix(void* ptr)
// {
//     void** arg_arr = (void**)ptr;
//     matrix_zt* objo = (matrix_zt*)arg_arr[0];
//     matrix_zt* obji = (matrix_zt*)arg_arr[1];
//     uint64_t start_point = *(uint64_t*)arg_arr[2];
//     uint64_t end_point = *(uint64_t*)arg_arr[3];

//     mpz_t* matrix_o = objo->return_matrix();
//     uint64_t col_o = *(objo->return_size() + 1);

//     mpz_t* matrix_i = obji->return_matrix();
//     uint64_t row_i = *(obji->return_size());
//     uint64_t col_i = *(obji->return_size() + 1);

//     for(uint64_t i = start_point; i < end_point; i++)
//     {
//         for(uint64_t j = 0; j < row_i; j++)
//         {
//             mpz_set(*(matrix_o + col_o * i + j), *(matrix_i + col_i * j + i));
//         }
//     }

//     return NULL;
// }

// matrix_zt* calc::transpose_mt(matrix_zt* obj)
// {
//     if(obj == nullptr)
//     {
//         debug::print_error((char*)"calc", (char*)"transpose_mt", 0, (char*)"reference nullptr");
//         debug::print_error_specific((char*)"function attribution is nullptr");
//         exit(-1);
//     }
//     else
//     {
//         uint64_t row = *(obj->return_size());
//         uint64_t col = *(obj->return_size() + 1);

//         if(row >= col)
//         {
//             uint64_t block_length = 0;
//             uint64_t block_residue = 0;
//             uint64_t thread_using = 0;

//             for(uint64_t i = thread_num; i > 0; i--)
//             {
//                 block_length = (uint64_t) (row / i);
//                 block_residue = (row % i);
//                 thread_using = i;

//                 if(block_length > transpose_block_coefficient * thread_block)
//                 {
//                     break;
//                 }
//                 else
//                 {
//                     continue;
//                 }
//             }

//             debug::print_thread_info((char*)"calc", (char*)"transpose_mt", 0, thread_using);

//             matrix_zt* new_matrix_struct = new matrix_zt(col, row);

//             pthread_t* thread_id = new pthread_t[thread_using];
//             void*** arg_arr = new void**[thread_using];
//             for(uint64_t i = 0; i < thread_using; i++)
//             {
//                 arg_arr[i] = new void*[4];
//             }

//             uint64_t* start_point = new uint64_t[thread_using]{0};
//             uint64_t* end_point = new uint64_t[thread_using]{0};

//             for(uint64_t i = 0; i < thread_using; i++)
//             {
//                 if(i != (thread_using - 1))
//                 {
//                     *(start_point + i) = block_length * i;
//                     *(end_point + i) = block_length * (i + 1);
//                 }
//                 else if(i > 0)
//                 {
//                     *(start_point + i) = *(end_point + i - 1);
//                     *(end_point + i) = block_length * (i + 1) + block_residue;
//                 }
//                 else
//                 {
//                     *(start_point + i) = 0;
//                     *(end_point + i) = block_length * (i + 1) + block_residue;
//                 }
                                                
//                 arg_arr[i][0] = (void*)new_matrix_struct;
//                 arg_arr[i][1] = (void*)obj;
//                 arg_arr[i][2] = (void*)(start_point + i);
//                 arg_arr[i][3] = (void*)(end_point + i);

//                 int error = pthread_create(&*(thread_id + i), NULL, transpose_row_threading_matrix, (void*) arg_arr[i]);
//                 if(error)
//                 {
//                     debug::print_error((char*)"calc", (char*)"transpose_mt", 0, (char*)"threading");
//                     debug::print_error_specific((char*)"can not create thread");
//                     exit(-1);
//                 }
//             }

//             for(uint64_t i = 0; i < thread_using; i++)
//             {
//                 pthread_join(*(thread_id + i), NULL);
//             }

//             delete[] start_point;
//             delete[] end_point;
//             delete[] thread_id;
//             for(uint64_t i = 0; i < thread_using; i++)
//             {
//                 delete[] arg_arr[i];
//             }
//             delete[] arg_arr;

//             return new_matrix_struct;
//         }
//         else
//         {
//             uint64_t block_length = 0;
//             uint64_t block_residue = 0;
//             uint64_t thread_using = 0;

//             for(uint64_t i = thread_num; i > 0; i--)
//             {
//                 block_length = (uint64_t) (col / i);
//                 block_residue = (col % i);
//                 thread_using = i;

//                 if(block_length > transpose_block_coefficient * thread_block)
//                 {
//                     break;
//                 }
//                 else
//                 {
//                     continue;
//                 }
//             }

//             debug::print_thread_info((char*)"calc", (char*)"transpose_mt", 0, thread_using);

//             matrix_zt* new_matrix_struct = new matrix_zt(col, row);

//             pthread_t* thread_id = new pthread_t[thread_using];
//             void*** arg_arr = new void**[thread_using];
//             for(uint64_t i = 0; i < thread_using; i++)
//             {
//                 arg_arr[i] = new void*[4];
//             }

//             uint64_t* start_point = new uint64_t[thread_using]{0};
//             uint64_t* end_point = new uint64_t[thread_using]{0};

//             for(uint64_t i = 0; i < thread_using; i++)
//             {
//                 if(i != (thread_using - 1))
//                 {
//                     *(start_point + i) = block_length * i;
//                     *(end_point + i) = block_length * (i + 1);
//                 }
//                 else if(i > 0)
//                 {
//                     *(start_point + i) = *(end_point + i - 1);
//                     *(end_point + i) = block_length * (i + 1) + block_residue;
//                 }
//                 else
//                 {
//                     *(start_point + i) = 0;
//                     *(end_point + i) = block_length * (i + 1) + block_residue;
//                 }
                                                
//                 arg_arr[i][0] = (void*)new_matrix_struct;
//                 arg_arr[i][1] = (void*)obj;
//                 arg_arr[i][2] = (void*)(start_point + i);
//                 arg_arr[i][3] = (void*)(end_point + i);

//                 int error = pthread_create(&*(thread_id + i), NULL, transpose_col_threading_matrix, (void*) arg_arr[i]);
//                 if(error)
//                 {
//                     debug::print_error((char*)"calc", (char*)"transpose_mt", 0, (char*)"threading");
//                     debug::print_error_specific((char*)"can not create thread");
//                     exit(-1);
//                 }
//             }

//             for(uint64_t i = 0; i < thread_using; i++)
//             {
//                 pthread_join(*(thread_id + i), NULL);
//             }

//             delete[] start_point;
//             delete[] end_point;
//             delete[] thread_id;
//             for(uint64_t i = 0; i < thread_using; i++)
//             {
//                 delete[] arg_arr[i];
//             }
//             delete[] arg_arr;

//             return new_matrix_struct;
//         }
//     }
// }