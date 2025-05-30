#include <iostream>
#include <ctime>
#include <pthread.h>
#include <thread>
#include <random>
#include <cstdlib>
#include <cmath>
#include "util.h"
#include "debug.h"
using namespace std;

const uint64_t thread_num = std::thread::hardware_concurrency() > 1 ? std::thread::hardware_concurrency() : 1;
const uint64_t thread_block = 100000; 

gmp_randstate_t state;

void util::print_struct(scalar_zt* obj)
{
    if(obj == nullptr)
    {
        debug::print_error((char*)"util", (char*)"print_struct", 0, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        mpz_t* scalar = obj->return_scalar();
        uint64_t row = *(obj->return_size());
        uint64_t col = *(obj->return_size() + 1);

        cout << "This struct type : " << obj->return_type() << " | row : " << row << " | col : " << col << endl;

        mpz_out_str(stdout, 10, *(scalar));
        cout << endl;
    }
}

void util::print_struct(matrix_zt* obj)
{
    if(obj == nullptr)
    {
        debug::print_error((char*)"util", (char*)"print_struct", 1, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        mpz_t* matrix = obj->return_matrix();
        uint64_t row = *(obj->return_size());
        uint64_t col = *(obj->return_size() + 1);

        cout << "This struct type : " << obj->return_type() << " | row : " << row << " | col : " << col << endl;

        for(uint64_t i = 0; i < row; i++)
        {
            for(uint64_t j = 0; j < col; j++)
            {
                mpz_out_str(stdout, 10, *(matrix + col * i + j));
                if(j != col - 1)
                {
                    cout << ", ";
                }
            }
            cout << endl;
        }
    }
}

void util::print_struct(polynomial_zt* obj)
{
    if(obj == nullptr)
    {
        debug::print_error((char*)"util", (char*)"print_struct", 2, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        mpz_t* polynomial = obj->return_polynomial();
        uint64_t row = *(obj->return_size());
        uint64_t col = *(obj->return_size() + 1);

        cout << "This struct type : " << obj->return_type() << " | row : " << row << " | col : " << col << endl;

        for(uint64_t i = 0; i < row; i++)
        {
            for(uint64_t j = 0; j < col; j++)
            {
                mpz_out_str(stdout, 10, *(polynomial + col * i + j));
                if(j != col - 1)
                {
                    cout << ", ";
                }
            }
            cout << endl;
        }
    }
}

void util::print_struct_meta(scalar_zt* obj)
{
    if(obj == nullptr)
    {
        debug::print_error((char*)"util", (char*)"print_struct_meta", 0, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        uint64_t row = *(obj->return_size());
        uint64_t col = *(obj->return_size() + 1);

        cout << "This struct type : " << obj->return_type() << " | row : " << row << " | col : " << col << endl;
    }
}

void util::print_struct_meta(matrix_zt* obj)
{
    if(obj == nullptr)
    {
        debug::print_error((char*)"util", (char*)"print_struct_meta", 1, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        uint64_t row = *(obj->return_size());
        uint64_t col = *(obj->return_size() + 1);

        cout << "This struct type : " << obj->return_type() << " | row : " << row << " | col : " << col << endl;
    }
}

void util::print_struct_meta(polynomial_zt* obj)
{
    if(obj == nullptr)
    {
        debug::print_error((char*)"util", (char*)"print_struct_meta", 2, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        uint64_t row = *(obj->return_size());
        uint64_t col = *(obj->return_size() + 1);

        cout << "This struct type : " << obj->return_type() << " | row : " << row << " | col : " << col << endl;
    }
}

scalar_zt* util::copy(scalar_zt* obj)
{
    if(obj == nullptr)
    {
        debug::print_error((char*)"util", (char*)"copy", 0, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        mpz_t* scalar = obj->return_scalar();

        scalar_zt* new_scalar_struct = new scalar_zt();
        mpz_t* new_scalar = new_scalar_struct->return_scalar();
        
        mpz_set(*(new_scalar), *(scalar));

        return new_scalar_struct;
    }
}

matrix_zt* util::copy(matrix_zt* obj)
{
    if(obj == nullptr)
    {
        debug::print_error((char*)"util", (char*)"copy", 1, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        mpz_t* matrix = obj->return_matrix();
        uint64_t row = *(obj->return_size());
        uint64_t col = *(obj->return_size() + 1);

        matrix_zt* new_matrix_struct = new matrix_zt(row, col);
        mpz_t* new_matrix = new_matrix_struct->return_matrix();

        for(uint64_t i = 0; i < row; i++)
        {
            for(uint64_t j = 0; j < col; j++)
            {
                mpz_set(*(new_matrix + col * i + j), *(matrix + col * i + j));
            }
        }

        return new_matrix_struct;
    }
}

polynomial_zt* util::copy(polynomial_zt* obj)
{
    if(obj == nullptr)
    {
        debug::print_error((char*)"util", (char*)"copy", 2, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        mpz_t* matrix = obj->return_polynomial();
        uint64_t row = *(obj->return_size());
        uint64_t col = *(obj->return_size() + 1);

        polynomial_zt* new_polynomial_struct = new polynomial_zt(row * col);
        mpz_t* new_polynomial = new_polynomial_struct->return_polynomial();

        for(uint64_t i = 0; i < row; i++)
        {
            for(uint64_t j = 0; j < col; j++)
            {
                mpz_set(*(new_polynomial + col * i + j), *(matrix + col * i + j));
            }
        }

        return new_polynomial_struct;
    }
}

void util::clear(scalar_zt** obj)
{
    (*obj)->~scalar_zt();
    *obj = nullptr;
}

void util::clear(matrix_zt** obj)
{
    (*obj)->~matrix_zt();
    *obj = nullptr;
}

void util::clear(polynomial_zt** obj)
{
    (*obj)->~polynomial_zt();
    *obj = nullptr;
}

// =================================================================================== //

void util::set_entry(scalar_zt* obj, char* value)
{
    if(obj == nullptr)
    {
        debug::print_error((char*)"util", (char*)"set_entry", 0, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        mpz_t* scalar = obj->return_scalar();

        mpz_set_str(*(scalar), value, 10);
    }
}

void util::set_entry(matrix_zt* obj, char* value, uint64_t pos_row, uint64_t pos_col)
{
    if(obj == nullptr)
    {
        debug::print_error((char*)"util", (char*)"set_entry", 1, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        mpz_t* matrix = obj->return_matrix();
        uint64_t row = *(obj->return_size());
        uint64_t col = *(obj->return_size() + 1);
        
        if(pos_row < row && pos_col < col)
        {
            mpz_set_str(*(matrix + col * (pos_row - 1) + (pos_col - 1)), value, 10);
        }
        else
        {
            debug::print_error((char*)"util", (char*)"set_entry", 1, (char*)"attribution overflow");
            debug::print_error_specific((char*)"pos_row or pos_col are overflowing obj matrix's size");
            exit(-1);
        }
    }
}

void util::set_entry(matrix_zt* obj, scalar_zt* value, uint64_t pos_row, uint64_t pos_col)
{
    if(obj == nullptr || value == nullptr)
    {
        debug::print_error((char*)"util", (char*)"set_entry", 2, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        mpz_t* matrix = obj->return_matrix();
        mpz_t* scalar = value->return_scalar();
        uint64_t row = *(obj->return_size());
        uint64_t col = *(obj->return_size() + 1);
        
        if(pos_row < row && pos_col < col)
        {
            mpz_set(*(matrix + col * (pos_row - 1) + (pos_col - 1)), *scalar);
        }
        else
        {
            debug::print_error((char*)"util", (char*)"set_entry", 2, (char*)"attribution overflow");
            debug::print_error_specific((char*)"pos_row or pos_col are overflowing obj matrix's size");
            exit(-1);
        }
    }
}

void util::set_entry(polynomial_zt* obj, char* value, uint64_t pos)
{
    if(obj == nullptr)
    {
        debug::print_error((char*)"util", (char*)"set_entry", 3, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        mpz_t* polynomial = obj->return_polynomial();
        uint64_t col = *(obj->return_size() + 1);
        
        if(pos < col)
        {
            mpz_set_str(*(polynomial + pos), value, 10);
        }
        else
        {
            debug::print_error((char*)"util", (char*)"set_entry", 3, (char*)"attribution overflow");
            debug::print_error_specific((char*)"pos is overflowing obj polynomial's order");
            exit(-1);
        }
    }
}

void util::set_entry(polynomial_zt* obj, scalar_zt* value, uint64_t pos)
{
    if(obj == nullptr || value == nullptr)
    {
        debug::print_error((char*)"util", (char*)"set_entry", 4, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        mpz_t* polynomial = obj->return_polynomial();
        mpz_t* scalar = value->return_scalar();
        uint64_t col = *(obj->return_size() + 1);
        
        if(pos < col)
        {
            mpz_set(*(polynomial + pos), *scalar);
        }
        else
        {
            debug::print_error((char*)"util", (char*)"set_entry", 4, (char*)"attribution overflow");
            debug::print_error_specific((char*)"pos is overflowing obj polynomial's order");
            exit(-1);
        }
    }
}

// =================================================================================== //

void util::set_random_seed(unsigned long T)
{
    gmp_randinit_default(state);
    gmp_randseed_ui(state, T);
}

void util::clear_random_seed()
{
    gmp_randclear(state);
}

void util::uniform_random(scalar_zt* obj, char* low, char* up)
{
    if(obj == nullptr)
    {
        debug::print_error((char*)"util", (char*)"uniform_random", 0, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        mpz_t low_bound, up_bound, sum_bound;
        mpz_init_set_str(low_bound, low, 10);
        mpz_init_set_str(up_bound, up, 10);
        mpz_init_set_str(sum_bound, "0", 10);

        if(mpz_cmp(low_bound, up_bound) < 0 && (mpz_cmp(low_bound, sum_bound) != 0 || mpz_cmp(up_bound, sum_bound) != 0))
        {
            if(mpz_cmp(sum_bound, up_bound) < 0)
            {
                mpz_neg(low_bound, low_bound);
                mpz_add(sum_bound, low_bound, up_bound);
                mpz_neg(low_bound, low_bound);

                mpz_t* scalar = obj->return_scalar();
            
                mpz_urandomm(*scalar, state, sum_bound);
                mpz_add(*scalar, *scalar, low_bound);
            }
            else
            {
                mpz_neg(low_bound, low_bound);
                mpz_add(sum_bound, low_bound, up_bound);
                mpz_neg(up_bound, up_bound);

                mpz_t* scalar = obj->return_scalar();
            
                mpz_urandomm(*scalar, state, sum_bound);
                mpz_add(*scalar, *scalar, up_bound);
                mpz_neg(*scalar, *scalar);
            }
            
            mpz_clear(low_bound);
            mpz_clear(up_bound);
            mpz_clear(sum_bound);
        }
        else
        {
            debug::print_error((char*)"util", (char*)"uniform_random", 0, (char*)"attribution bed condition");
            debug::print_error_specific((char*)"function attribution does not satisfying condition of low < up");
            exit(-1);
        }
    }
}

void util::uniform_random(matrix_zt* obj, char* low, char* up)
{
    if(obj == nullptr)
    {
        debug::print_error((char*)"util", (char*)"uniform_random", 1, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        mpz_t low_bound, up_bound, sum_bound;
        mpz_init_set_str(low_bound, low, 10);
        mpz_init_set_str(up_bound, up, 10);
        mpz_init_set_str(sum_bound, "0", 10);

        if(mpz_cmp(low_bound, up_bound) < 0 && (mpz_cmp(low_bound, sum_bound) != 0 || mpz_cmp(up_bound, sum_bound) != 0))
        {
            if(mpz_cmp(sum_bound, up_bound) < 0)
            {
                mpz_neg(low_bound, low_bound);
                mpz_add(sum_bound, low_bound, up_bound);
                mpz_neg(low_bound, low_bound);

                mpz_t* matrix = obj->return_matrix();
                uint64_t row = *(obj->return_size());
                uint64_t col = *(obj->return_size() + 1);
            
                for(uint64_t i = 0; i < row; i++)
                {
                    for(uint64_t j = 0; j < col; j++)
                    {
                        mpz_urandomm(*(matrix + col * i + j), state, sum_bound);
                        mpz_add(*(matrix + col * i + j), *(matrix + col * i + j), low_bound);
                    }
                }
            }
            else
            {
                mpz_neg(low_bound, low_bound);
                mpz_add(sum_bound, low_bound, up_bound);
                mpz_neg(up_bound, up_bound);

                mpz_t* matrix = obj->return_matrix();
                uint64_t row = *(obj->return_size());
                uint64_t col = *(obj->return_size() + 1);

                for(uint64_t i = 0; i < row; i++)
                {
                    for(uint64_t j = 0; j < col; j++)
                    {
                        mpz_urandomm(*(matrix + col * i + j), state, sum_bound);
                        mpz_add(*(matrix + col * i + j), *(matrix + col * i + j), up_bound);
                        mpz_neg(*(matrix + col * i + j), *(matrix + col * i + j));
                    }
                }
            }
            
            mpz_clear(low_bound);
            mpz_clear(up_bound);
            mpz_clear(sum_bound);
        }
        else
        {
            debug::print_error((char*)"util", (char*)"uniform_random", 1, (char*)"attribution bed condition");
            debug::print_error_specific((char*)"function attribution does not satisfying condition of low < up");
            exit(-1);
        }
    }
}

void util::uniform_random(polynomial_zt* obj, char* low, char* up)
{
    if(obj == nullptr)
    {
        debug::print_error((char*)"util", (char*)"uniform_random", 2, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        mpz_t low_bound, up_bound, sum_bound;
        mpz_init_set_str(low_bound, low, 10);
        mpz_init_set_str(up_bound, up, 10);
        mpz_init_set_str(sum_bound, "0", 10);

        if(mpz_cmp(low_bound, up_bound) < 0 && (mpz_cmp(low_bound, sum_bound) != 0 || mpz_cmp(up_bound, sum_bound) != 0))
        {
            if(mpz_cmp(sum_bound, up_bound) < 0)
            {
                mpz_neg(low_bound, low_bound);
                mpz_add(sum_bound, low_bound, up_bound);
                mpz_neg(low_bound, low_bound);

                mpz_t* polynomial = obj->return_polynomial();
                uint64_t col = *(obj->return_size() + 1);
            
                for(uint64_t i = 0; i < col; i++)
                {
                    mpz_urandomm(*(polynomial + i), state, sum_bound);
                    mpz_add(*(polynomial + i), *(polynomial + i), low_bound);
                }
            }
            else
            {
                mpz_neg(low_bound, low_bound);
                mpz_add(sum_bound, low_bound, up_bound);
                mpz_neg(up_bound, up_bound);

                mpz_t* polynomial = obj->return_polynomial();
                uint64_t col = *(obj->return_size() + 1);

                for(uint64_t i = 0; i < col; i++)
                {
                    mpz_urandomm(*(polynomial + i), state, sum_bound);
                    mpz_add(*(polynomial + i), *(polynomial + i), up_bound);
                    mpz_neg(*(polynomial + i), *(polynomial + i));
                }
            }
            
            mpz_clear(low_bound);
            mpz_clear(up_bound);
            mpz_clear(sum_bound);
        }
        else
        {
            debug::print_error((char*)"util", (char*)"uniform_random", 2, (char*)"attribution bed condition");
            debug::print_error_specific((char*)"function attribution does not satisfying condition of low < up");
            exit(-1);
        }
    }
}

// void* ptr = [matrix_zt* obj, mpz_t sum_bound, mpz_t low_bound, uint64_t start_point, uint64_t end_point, bool neg]
void* uniform_random_threading_matrix(void* ptr)
{
    void** arg_arr = (void**)ptr;
    matrix_zt* obj = (matrix_zt*)arg_arr[0];
    mpz_t sum_bound;
    mpz_init_set(sum_bound, *(mpz_t*)arg_arr[1]);
    mpz_t low_bound;
    mpz_init_set(low_bound, *(mpz_t*)arg_arr[2]);
    uint64_t start_point = *(uint64_t*)arg_arr[3];
    uint64_t end_point = *(uint64_t*)arg_arr[4];
    bool neg = *(bool*)arg_arr[5];

    mpz_t* matrix = obj->return_matrix();

    for(uint64_t i = start_point; i < end_point; i++)
    {
        mpz_urandomm(*(matrix + i), state, sum_bound);
        mpz_add(*(matrix + i), *(matrix + i), low_bound);
        if(neg)
        {
            mpz_neg(*(matrix + i), *(matrix + i));
        }
    }

    mpz_clear(sum_bound);
    mpz_clear(low_bound);

    return NULL;
}

void util::uniform_random_mt(matrix_zt* obj, char* low, char* up)
{
    if(obj == nullptr)
    {
        debug::print_error((char*)"util", (char*)"uniform_random_mt", 0, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        mpz_t low_bound, up_bound, sum_bound;
        mpz_init_set_str(low_bound, low, 10);
        mpz_init_set_str(up_bound, up, 10);
        mpz_init_set_str(sum_bound, "0", 10);
        bool neg = false;

        if(mpz_cmp(low_bound, up_bound) < 0 && (mpz_cmp(low_bound, sum_bound) != 0 || mpz_cmp(up_bound, sum_bound) != 0))
        {
            if(mpz_cmp(sum_bound, up_bound) < 0)
            {
                mpz_neg(low_bound, low_bound);
                mpz_add(sum_bound, low_bound, up_bound);
                mpz_neg(low_bound, low_bound);

                uint64_t row = *(obj->return_size());
                uint64_t col = *(obj->return_size() + 1);
                    
                uint64_t block_length = 0;
                uint64_t block_residue = 0;
                uint64_t thread_using = 0;

                for(uint64_t i = thread_num; i > 0; i--)
                {
                    block_length = (uint64_t) (row * col / i);
                    block_residue = (row * col % i);
                    thread_using = i;

                    if(block_length > thread_block)
                    {
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }

                debug::print_thread_info((char*)"util", (char*)"uniform_random_mt", 0, thread_using);

                pthread_t* thread_id = new pthread_t[thread_using];
                void*** arg_arr = new void**[thread_using];
                for(uint64_t i = 0; i < thread_using; i++)
                {
                    arg_arr[i] = new void*[6];
                }

                neg = false;

                uint64_t* start_point = new uint64_t[thread_using]{0};
                uint64_t* end_point = new uint64_t[thread_using]{0};

                for(uint64_t i = 0; i < thread_using; i++)
                {
                    if(i != (thread_using - 1))
                    {
                        *(start_point + i) = block_length * i;
                        *(end_point + i) = block_length * (i + 1);
                    }
                    else if(i > 0)
                    {
                        *(start_point + i) = *(end_point + i - 1);
                        *(end_point + i) = block_length * (i + 1) + block_residue;
                    }
                    else
                    {
                        *(start_point + i) = 0;
                        *(end_point + i) = block_length * (i + 1) + block_residue;
                    }
                                            
                    arg_arr[i][0] = (void*)obj;
                    arg_arr[i][1] = (void*)&sum_bound;
                    arg_arr[i][2] = (void*)&low_bound;
                    arg_arr[i][3] = (void*)(start_point + i);
                    arg_arr[i][4] = (void*)(end_point + i);
                    arg_arr[i][5] = (void*)&neg;

                    int error = pthread_create(&*(thread_id + i), NULL, uniform_random_threading_matrix, (void*) arg_arr[i]);
                    if(error)
                    {
                        debug::print_error((char*)"util", (char*)"uniform_random_mt", 0, (char*)"threading");
                        debug::print_error_specific((char*)"can not create thread");
                        exit(-1);
                    }
                }

                for(uint64_t i = 0; i < thread_using; i++)
                {
                    pthread_join(*(thread_id + i), NULL);
                }

                delete[] start_point;
                delete[] end_point;
                delete[] thread_id;
                for(uint64_t i = 0; i < thread_using; i++)
                {
                    delete[] arg_arr[i];
                }
                delete[] arg_arr;
            }
            else
            {
                mpz_neg(low_bound, low_bound);
                mpz_add(sum_bound, low_bound, up_bound);
                mpz_neg(up_bound, up_bound);

                uint64_t row = *(obj->return_size());
                uint64_t col = *(obj->return_size() + 1);
                    
                uint64_t block_length = 0;
                uint64_t block_residue = 0;
                uint64_t thread_using = 0;

                for(uint64_t i = thread_num; i > 0; i--)
                {
                    block_length = (uint64_t) (row * col / i);
                    block_residue = (row * col % i);
                    thread_using = i;

                    if(block_length > thread_block)
                    {
                        break;
                    }
                    
                    {
                        continue;
                    }
                }

                debug::print_thread_info((char*)"util", (char*)"uniform_random_mt", 0, thread_using);

                pthread_t* thread_id = new pthread_t[thread_using];
                void*** arg_arr = new void**[thread_using];
                for(uint64_t i = 0; i < thread_using; i++)
                {
                    arg_arr[i] = new void*[6];
                }

                neg = true;

                uint64_t* start_point = new uint64_t[thread_using]{0};
                uint64_t* end_point = new uint64_t[thread_using]{0};

                for(uint64_t i = 0; i < thread_using; i++)
                {
                    if(i != (thread_using - 1))
                    {
                        *(start_point + i) = block_length * i;
                        *(end_point + i) = block_length * (i + 1);
                    }
                    else if(i > 0)
                    {
                        *(start_point + i) = *(end_point + i - 1);
                        *(end_point + i) = block_length * (i + 1) + block_residue;
                    }
                    else
                    {
                        *(start_point + i) = 0;
                        *(end_point + i) = block_length * (i + 1) + block_residue;
                    }
                                            
                    arg_arr[i][0] = (void*)obj;
                    arg_arr[i][1] = (void*)&sum_bound;
                    arg_arr[i][2] = (void*)&up_bound;
                    arg_arr[i][3] = (void*)(start_point + i);
                    arg_arr[i][4] = (void*)(end_point + i);
                    arg_arr[i][5] = (void*)&neg;

                    int error = pthread_create(&*(thread_id + i), NULL, uniform_random_threading_matrix, (void*) arg_arr[i]);
                    if(error)
                    {
                        debug::print_error((char*)"util", (char*)"uniform_random_mt", 0, (char*)"threading");
                        debug::print_error_specific((char*)"can not create thread");
                        exit(-1);
                    }
                }

                for(uint64_t i = 0; i < thread_using; i++)
                {
                    pthread_join(*(thread_id + i), NULL);
                }

                delete[] start_point;
                delete[] end_point;
                delete[] thread_id;
                for(uint64_t i = 0; i < thread_using; i++)
                {
                    delete[] arg_arr[i];
                }
                delete[] arg_arr;
            }
        }
        else
        {
            debug::print_error((char*)"util", (char*)"uniform_random_mt", 0, (char*)"attribution bed condition");
            debug::print_error_specific((char*)"function attribution does not satisfying condition of low < up");
            exit(-1);
        }

        mpz_clear(low_bound);
        mpz_clear(up_bound);
        mpz_clear(sum_bound);
    }
}

// void* ptr = [polynomial_zt* obj, mpz_t sum_bound, mpz_t low_bound, uint64_t start_point, uint64_t end_point]
void* uniform_random_threading_polynomial(void* ptr)
{
    void** arg_arr = (void**)ptr;
    polynomial_zt* obj = (polynomial_zt*)arg_arr[0];
    mpz_t sum_bound;
    mpz_init_set(sum_bound, *(mpz_t*)arg_arr[1]);
    mpz_t low_bound;
    mpz_init_set(low_bound, *(mpz_t*)arg_arr[2]);
    uint64_t start_point = *(uint64_t*)arg_arr[3];
    uint64_t end_point = *(uint64_t*)arg_arr[4];
    bool neg = *(bool*)arg_arr[5];

    mpz_t* polynomial = obj->return_polynomial();

    for(uint64_t i = start_point; i < end_point; i++)
    {
        mpz_urandomm(*(polynomial + i), state, sum_bound);
        mpz_add(*(polynomial + i), *(polynomial + i), low_bound);
        if(neg)
        {
            mpz_neg(*(polynomial + i), *(polynomial + i));
        }
    }

    mpz_clear(sum_bound);
    mpz_clear(low_bound);

    return NULL;
}

void util::uniform_random_mt(polynomial_zt* obj, char* low, char* up)
{
    if(obj == nullptr)
    {
        debug::print_error((char*)"util", (char*)"uniform_random_mt", 1, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        mpz_t low_bound, up_bound, sum_bound;
        mpz_init_set_str(low_bound, low, 10);
        mpz_init_set_str(up_bound, up, 10);
        mpz_init_set_str(sum_bound, "0", 10);
        bool neg = false;

        if(mpz_cmp(low_bound, up_bound) < 0 && (mpz_cmp(low_bound, sum_bound) != 0 || mpz_cmp(up_bound, sum_bound) != 0))
        {
            if(mpz_cmp(sum_bound, up_bound) < 0)
            {
                mpz_neg(low_bound, low_bound);
                mpz_add(sum_bound, low_bound, up_bound);
                mpz_neg(low_bound, low_bound);

                uint64_t row = *(obj->return_size());
                uint64_t col = *(obj->return_size() + 1);
                    
                uint64_t block_length = 0;
                uint64_t block_residue = 0;
                uint64_t thread_using = 0;

                for(uint64_t i = thread_num; i > 0; i--)
                {
                    block_length = (uint64_t) (row * col / i);
                    block_residue = (row * col % i);
                    thread_using = i;

                    if(block_length > thread_block)
                    {
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }

                debug::print_thread_info((char*)"util", (char*)"uniform_random_mt", 1, thread_using);

                pthread_t* thread_id = new pthread_t[thread_using];
                void*** arg_arr = new void**[thread_using];
                for(uint64_t i = 0; i < thread_using; i++)
                {
                    arg_arr[i] = new void*[6];
                }

                neg = false;

                uint64_t* start_point = new uint64_t[thread_using];
                uint64_t* end_point = new uint64_t[thread_using];

                for(uint64_t i = 0; i < thread_using; i++)
                {
                    if(i != (thread_using - 1))
                    {
                        *(start_point + i) = block_length * i;
                        *(end_point + i) = block_length * (i + 1);
                    }
                    else if(i > 0)
                    {
                        *(start_point + i) = *(end_point + i - 1);
                        *(end_point + i) = block_length * (i + 1) + block_residue;
                    }
                    else
                    {
                        *(start_point + i) = 0;
                        *(end_point + i) = block_length * (i + 1) + block_residue;
                    }
                                            
                    arg_arr[i][0] = (void*)obj;
                    arg_arr[i][1] = (void*)&sum_bound;
                    arg_arr[i][2] = (void*)&low_bound;
                    arg_arr[i][3] = (void*)(start_point + i);
                    arg_arr[i][4] = (void*)(end_point + i);
                    arg_arr[i][5] = (void*)&neg;

                    int error = pthread_create(&*(thread_id + i), NULL, uniform_random_threading_matrix, (void*) arg_arr[i]);
                    if(error)
                    {
                        debug::print_error((char*)"util", (char*)"uniform_random_mt", 1, (char*)"threading");
                        debug::print_error_specific((char*)"can not create thread");
                        exit(-1);
                    }
                }

                for(uint64_t i = 0; i < thread_using; i++)
                {
                    pthread_join(*(thread_id + i), NULL);
                }

                delete[] start_point;
                delete[] end_point;
                delete[] thread_id;
                for(uint64_t i = 0; i < thread_using; i++)
                {
                    delete[] arg_arr[i];
                }
                delete[] arg_arr;
            }
            else
            {
                mpz_neg(low_bound, low_bound);
                mpz_add(sum_bound, low_bound, up_bound);
                mpz_neg(up_bound, up_bound);

                uint64_t row = *(obj->return_size());
                uint64_t col = *(obj->return_size() + 1);
                    
                uint64_t block_length = 0;
                uint64_t block_residue = 0;
                uint64_t thread_using = 0;

                for(uint64_t i = thread_num; i > 0; i--)
                {
                    block_length = (uint64_t) (row * col / i);
                    block_residue = (row * col % i);
                    thread_using = i;

                    if(block_length > thread_block)
                    {
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }

                debug::print_thread_info((char*)"util", (char*)"uniform_random_mt", 1, thread_using);

                pthread_t* thread_id = new pthread_t[thread_using];
                void*** arg_arr = new void**[thread_using];
                for(uint64_t i = 0; i < thread_using; i++)
                {
                    arg_arr[i] = new void*[6];
                }

                neg = true;

                uint64_t* start_point = new uint64_t[thread_using];
                uint64_t* end_point = new uint64_t[thread_using];

                for(uint64_t i = 0; i < thread_using; i++)
                {
                    if(i != (thread_using - 1))
                    {
                        *(start_point + i) = block_length * i;
                        *(end_point + i) = block_length * (i + 1);
                    }
                    else if(i > 0)
                    {
                        *(start_point + i) = *(end_point + i - 1);
                        *(end_point + i) = block_length * (i + 1) + block_residue;
                    }
                    else
                    {
                        *(start_point + i) = 0;
                        *(end_point + i) = block_length * (i + 1) + block_residue;
                    }
                                            
                    arg_arr[i][0] = (void*)obj;
                    arg_arr[i][1] = (void*)&sum_bound;
                    arg_arr[i][2] = (void*)&low_bound;
                    arg_arr[i][3] = (void*)(start_point + i);
                    arg_arr[i][4] = (void*)(end_point + i);
                    arg_arr[i][5] = (void*)&neg;

                    int error = pthread_create(&*(thread_id + i), NULL, uniform_random_threading_matrix, (void*) arg_arr[i]);
                    if(error)
                    {
                        debug::print_error((char*)"util", (char*)"uniform_random_mt", 1, (char*)"threading");
                        debug::print_error_specific((char*)"can not create thread");
                        exit(-1);
                    }
                }

                for(uint64_t i = 0; i < thread_using; i++)
                {
                    pthread_join(*(thread_id + i), NULL);
                }

                delete[] start_point;
                delete[] end_point;
                delete[] thread_id;
                for(uint64_t i = 0; i < thread_using; i++)
                {
                    delete[] arg_arr[i];
                }
                delete[] arg_arr;
            }
        }
        else
        {
            debug::print_error((char*)"util", (char*)"uniform_random_mt", 1, (char*)"attribution bed condition");
            debug::print_error_specific((char*)"function attribution does not satisfying condition of low < up");
            exit(-1);
        }

        mpz_clear(low_bound);
        mpz_clear(up_bound);
        mpz_clear(sum_bound);
    }
}

void util::gaussian_random(scalar_zt* obj, char* mean, char* std)
{
    // discrete gaussian sampler required
}

void util::gaussian_random(matrix_zt* obj, char* mean, char* std)
{
    // discrete gaussian sampler required
}

void util::gaussian_random(polynomial_zt* obj, char* mean, char* std)
{
    // discrete gaussian sampler required
}

void util::gaussian_random_mt(matrix_zt* obj, char* mean, char* std)
{
    // discrete gaussian sampler required
}

void util::gaussian_random_mt(polynomial_zt* obj, char* mean, char* std)
{
    // discrete gaussian sampler required
}

matrix_zt* util::stack_vertical(matrix_zt* obj1, matrix_zt* obj2)
{
    if(obj1 == nullptr || obj2 == nullptr)
    {
        debug::print_error((char*)"util", (char*)"stack_vertical", 0, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        mpz_t* matrix_1= obj1->return_matrix();
        uint64_t row_1 = *(obj1->return_size());
        uint64_t col_1 = *(obj1->return_size() + 1);

        mpz_t* matrix_2 = obj2->return_matrix();
        uint64_t row_2 = *(obj2->return_size());
        uint64_t col_2 = *(obj2->return_size() + 1);
    
        if(col_1 != col_2)
        {
            debug::print_error((char*)"util", (char*)"stack_vertical", 0, (char*)"size unmatched");
            debug::print_error_specific((char*)"obj1 matrix and obj2 matrix column size unmatched");
            exit(-1);
        }
        else
        {
            matrix_zt* new_matrix_struct = new matrix_zt((row_1 + row_2), col_1);
            mpz_t* new_matrix = new_matrix_struct->return_matrix();
            uint64_t col = *(new_matrix_struct->return_size() + 1);

            for(uint64_t i = 0; i < row_1; i++)
            {
                for(uint64_t j = 0; j < col; j++)
                {
                    mpz_set(*(new_matrix + col * i + j), *(matrix_1 + col_1 * i + j));
                }
            }
            for(uint64_t i = 0; i < row_2; i++)
            {
                for(uint64_t j = 0; j < col; j++)
                {
                    mpz_set(*(new_matrix + col * i + j), *(matrix_2 + col_2 * i + j));
                }
            }
            
            return new_matrix_struct;
        }
    }
}

matrix_zt* util::stack_horizon(matrix_zt* obj1, matrix_zt* obj2)
{
    if(obj1 == nullptr || obj2 == nullptr)
    {
        debug::print_error((char*)"util", (char*)"stack_horizon", 0, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        mpz_t* matrix_1= obj1->return_matrix();
        uint64_t row_1 = *(obj1->return_size());
        uint64_t col_1 = *(obj1->return_size() + 1);

        mpz_t* matrix_2 = obj2->return_matrix();
        uint64_t row_2 = *(obj2->return_size());
        uint64_t col_2 = *(obj2->return_size() + 1);
    
        if(row_1 != row_2)
        {
            debug::print_error((char*)"util", (char*)"stack_horizon", 0, (char*)"size unmatched");
            debug::print_error_specific((char*)"obj1 matrix and obj2 matrix row size unmatched");
            exit(-1);
        }
        else
        {
            matrix_zt* new_matrix_struct = new matrix_zt(row_1, (col_1 + col_2));
            mpz_t* new_matrix = new_matrix_struct->return_matrix();
            uint64_t col = *(new_matrix_struct->return_size() + 1);

            for(uint64_t i = 0; i < row_1; i++)
            {
                for(uint64_t j = 0; j < col_1; j++)
                {
                    mpz_set(*(new_matrix + col * i + j), *(matrix_1 + col_1 * i + j));
                }
                for(uint64_t j = col_1; j < col_2; j++)
                {
                    mpz_set(*(new_matrix + col * i + j), *(matrix_2 + col_2 * i + j));
                }
            }
            
            return new_matrix_struct;
        }
    }
}

polynomial_zt* util::stack_horizon(polynomial_zt* obj1, polynomial_zt* obj2)
{
    if(obj1 == nullptr || obj2 == nullptr)
    {
        debug::print_error((char*)"util", (char*)"stack_horizon", 1, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        mpz_t* polynomial_1= obj1->return_polynomial();
        uint64_t order_1 = *(obj1->return_size() + 1);

        mpz_t* polynomial_2 = obj2->return_polynomial();
        uint64_t order_2 = *(obj2->return_size() + 1);
    
        polynomial_zt* new_polynomial_struct = new polynomial_zt((order_1 + order_2));
        mpz_t* new_polynomial = new_polynomial_struct->return_polynomial();

        for(uint64_t i = 0; i < order_1; i++)
        {
            mpz_set(*(new_polynomial + i), *(polynomial_1 + i));
        }
        for(uint64_t i = order_1; i < order_2; i++)
        {
            mpz_set(*(new_polynomial + i), *(polynomial_2 + i));
        }
            
        return new_polynomial_struct;
    }
}