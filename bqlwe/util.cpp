#include <iostream>
#include <ctime>
#include <pthread.h>
#include <thread>
#include "util.h"
using namespace std;

const uint64_t thread_num = std::thread::hardware_concurrency() > 1 ? std::thread::hardware_concurrency() : 1;
const uint64_t thread_block = 20;

gmp_randstate_t state;

void util::print_struct(scalar_t* obj)
{
    if(obj == nullptr)
    {
        cout << "[class : util, func : print_struct, error : reference nullptr]" << endl;
        cout << "specific : function attribution is nullptr" << endl;
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

void util::print_struct(matrix_t* obj)
{
    if(obj == nullptr)
    {
        cout << "[class : util, func : print_struct, error : reference nullptr]" << endl;
        cout << "specific : function attribution is nullptr" << endl;
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

void util::print_struct(polynomial_t* obj)
{
    if(obj == nullptr)
    {
        cout << "[class : util, func : print_struct, error : reference nullptr]" << endl;
        cout << "specific : function attribution is nullptr" << endl;
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

scalar_t* util::copy(scalar_t* obj)
{
    if(obj == nullptr)
    {
        cout << "[class : util, func : copy, error : reference nullptr]" << endl;
        cout << "specific : function attribution is nullptr" << endl;
        exit(-1);
    }
    else
    {
        mpz_t* scalar = obj->return_scalar();

        scalar_t* new_scalar_struct = new scalar_t();
        mpz_t* new_scalar = new_scalar_struct->return_scalar();
        
        mpz_set(*(new_scalar), *(scalar));

        return new_scalar_struct;
    }
}

matrix_t* util::copy(matrix_t* obj)
{
    if(obj == nullptr)
    {
        cout << "[class : util, func : copy, error : reference nullptr]" << endl;
        cout << "specific : function attribution is nullptr" << endl;
        exit(-1);
    }
    else
    {
        mpz_t* matrix = obj->return_matrix();
        uint64_t row = *(obj->return_size());
        uint64_t col = *(obj->return_size() + 1);

        matrix_t* new_matrix_struct = new matrix_t(row, col);
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

polynomial_t* util::copy(polynomial_t* obj)
{
    if(obj == nullptr)
    {
        cout << "[class : util, func : copy, error : reference nullptr]" << endl;
        cout << "specific : function attribution is nullptr" << endl;
        exit(-1);
    }
    else
    {
        mpz_t* matrix = obj->return_polynomial();
        uint64_t row = *(obj->return_size());
        uint64_t col = *(obj->return_size() + 1);

        polynomial_t* new_polynomial_struct = new polynomial_t(row * col);
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

void util::clear(scalar_t** obj)
{
    (*obj)->~scalar_t();
    *obj = nullptr;
}

void util::clear(matrix_t** obj)
{
    (*obj)->~matrix_t();
    *obj = nullptr;
}

void util::clear(polynomial_t** obj)
{
    (*obj)->~polynomial_t();
    *obj = nullptr;
}

// =================================================================================== //

void util::set_entry(scalar_t* obj, char* value)
{
    if(obj == nullptr)
    {
        cout << "[class : util, func : set_entry, error : reference nullptr]" << endl;
        cout << "specific : function attribution is nullptr" << endl;
        exit(-1);
    }
    else
    {
        mpz_t* scalar = obj->return_scalar();

        mpz_set_str(*(scalar), value, 10);
    }
}

// void util::set_entry(matrix_t* obj, mpz_t value, uint64_t pos_row, uint64_t pos_col)
// {
//     if(obj == nullptr)
//     {
//         cout << "[class : util, func : set_entry, error : reference nullptr]" << endl;
//         cout << "specific : function attribution is nullptr" << endl;
//         exit(-1);
//     }
//     else
//     {
//         mpz_t* matrix = obj->return_matrix();
//         uint64_t row = *(obj->return_size());
//         uint64_t col = *(obj->return_size() + 1);
        
//         if(pos_row < row && pos_col < col)
//         {
//             mpz_set(*(matrix + col * (pos_row - 1) + (pos_col - 1)), value);
//         }
//         else
//         {
//             cout << "[class : util, func : set_entry, error : pos_row or pos_col overflow]" << endl;
//             cout << "specific : pos_row or pos_col are overflowing obj matrix's size" << endl;
//             exit(-1);
//         }
//     }
// }

// void util::set_entry(matrix_t* obj, int64_t value, uint64_t pos_row, uint64_t pos_col)
// {
//     if(obj == nullptr)
//     {
//         cout << "[class : util, func : set_entry, error : reference nullptr]" << endl;
//         cout << "specific : function attribution is nullptr" << endl;
//         exit(-1);
//     }
//     else
//     {
//         mpz_t* matrix = obj->return_matrix();
//         uint64_t row = *(obj->return_size());
//         uint64_t col = *(obj->return_size() + 1);
        
//         if(pos_row < row && pos_col < col)
//         {
//             mpz_set_si(*(matrix + col * (pos_row - 1) + (pos_col - 1)), value);
//         }
//         else
//         {
//             cout << "[class : util, func : set_entry, error : pos_row or pos_col overflow]" << endl;
//             cout << "specific : pos_row or pos_col are overflowing obj matrix's size" << endl;
//             exit(-1);
//         }
//     }
// }

void util::set_entry(matrix_t* obj, char* value, uint64_t pos_row, uint64_t pos_col)
{
    if(obj == nullptr)
    {
        cout << "[class : util, func : set_entry, error : reference nullptr]" << endl;
        cout << "specific : function attribution is nullptr" << endl;
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
            cout << "[class : util, func : set_entry, error : pos_row or pos_col overflow]" << endl;
            cout << "specific : pos_row or pos_col are overflowing obj matrix's size" << endl;
            exit(-1);
        }
    }
}

void util::set_entry(matrix_t* obj, scalar_t* value, uint64_t pos_row, uint64_t pos_col)
{
    if(obj == nullptr || value == nullptr)
    {
        cout << "[class : util, func : set_entry, error : reference nullptr]" << endl;
        cout << "specific : function attribution is nullptr" << endl;
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
            cout << "[class : util, func : set_entry, error : pos_row or pos_col overflow]" << endl;
            cout << "specific : pos_row or pos_col are overflowing obj matrix's size" << endl;
            exit(-1);
        }
    }
}

// void util::set_entry(polynomial_t* obj, mpz_t value, uint64_t pos)
// {
//     if(obj == nullptr)
//     {
//         cout << "[class : util, func : set_entry, error : reference nullptr]" << endl;
//         cout << "specific : function attribution is nullptr" << endl;
//         exit(-1);
//     }
//     else
//     {
//         mpz_t* polynomial = obj->return_polynomial();
//         // uint64_t row = *(obj->return_size());
//         uint64_t col = *(obj->return_size() + 1);
        
//         if(pos < col)
//         {
//             mpz_set(*(polynomial + pos), value);
//         }
//         else
//         {
//             cout << "[class : util, func : set_entry, error : pos overflow]" << endl;
//             cout << "specific : pos is overflowing obj polynomial's order" << endl;
//             exit(-1);
//         }
//     }
// }

// void util::set_entry(polynomial_t* obj, int64_t value, uint64_t pos)
// {
//     if(obj == nullptr)
//     {
//         cout << "[class : util, func : set_entry, error : reference nullptr]" << endl;
//         cout << "specific : function attribution is nullptr" << endl;
//         exit(-1);
//     }
//     else
//     {
//         mpz_t* polynomial = obj->return_polynomial();
//         // uint64_t row = *(obj->return_size());
//         uint64_t col = *(obj->return_size() + 1);
        
//         if(pos < col)
//         {
//             mpz_set_si(*(polynomial + pos), value);
//         }
//         else
//         {
//             cout << "[class : util, func : set_entry, error : pos overflow]" << endl;
//             cout << "specific : pos is overflowing obj polynomial's order" << endl;
//             exit(-1);
//         }
//     }
// }

void util::set_entry(polynomial_t* obj, char* value, uint64_t pos)
{
    if(obj == nullptr)
    {
        cout << "[class : util, func : set_entry, error : reference nullptr]" << endl;
        cout << "specific : function attribution is nullptr" << endl;
        exit(-1);
    }
    else
    {
        mpz_t* polynomial = obj->return_polynomial();
        // uint64_t row = *(obj->return_size());
        uint64_t col = *(obj->return_size() + 1);
        
        if(pos < col)
        {
            mpz_set_str(*(polynomial + pos), value, 10);
        }
        else
        {
            cout << "[class : util, func : set_entry, error : pos overflow]" << endl;
            cout << "specific : pos is overflowing obj polynomial's order" << endl;
            exit(-1);
        }
    }
}

void util::set_entry(polynomial_t* obj, scalar_t* value, uint64_t pos_row, uint64_t pos_col)
{
    if(obj == nullptr || value == nullptr)
    {
        cout << "[class : util, func : set_entry, error : reference nullptr]" << endl;
        cout << "specific : function attribution is nullptr" << endl;
        exit(-1);
    }
    else
    {
        mpz_t* polynomial = obj->return_polynomial();
        mpz_t* scalar = value->return_scalar();
        uint64_t row = *(obj->return_size());
        uint64_t col = *(obj->return_size() + 1);
        
        if(pos_row < row && pos_col < col)
        {
            mpz_set(*(polynomial + col * (pos_row - 1) + (pos_col - 1)), *scalar);
        }
        else
        {
            cout << "[class : util, func : set_entry, error : pos_row or pos_col overflow]" << endl;
            cout << "specific : pos_row or pos_col are overflowing obj matrix's size" << endl;
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

void util::uniform_random(scalar_t* obj, char* low, char* up)
{
    if(obj == nullptr)
    {
        cout << "[class : util, func : uniform_random, error : reference nullptr]" << endl;
        cout << "specific : function attribution is nullptr" << endl;
        exit(-1);
    }
    else
    {
        mpz_t low_bound, up_bound, sum_bound;
        mpz_init_set_str(low_bound, low, 10);
        mpz_init_set_str(up_bound, up, 10);
        mpz_init_set_str(sum_bound, "0", 10);

        if(mpz_cmp(low_bound, up_bound) > 0 || mpz_cmp(low_bound, sum_bound) > 0 || mpz_cmp(up_bound, sum_bound) > 0)
        {
            mpz_neg(low_bound, low_bound);
            mpz_add(sum_bound, low_bound, up_bound);
            mpz_neg(low_bound, low_bound);

            mpz_t* scalar = obj->return_scalar();
            
            mpz_urandomm(*scalar, state, sum_bound);
            
            
            mpz_add(*scalar, *scalar, low_bound);
            
            mpz_clear(low_bound);
            mpz_clear(up_bound);
            mpz_clear(sum_bound);
        }
        else
        {
            cout << "[class : util, func : uniform_random, error : attr not satisfying condition]" << endl;
            cout << "specific : function attribution does not satisfying condition of 0 < low < up" << endl;
            exit(-1);
        }
    }
}

// void* ptr = [matrix_t* obj, mpz_t sum_bound, mpz_t low_bound, uint64_t start_point, uint64_t end_point, bool neg]
void* uniform_random_threading_matrix(void* ptr)
{
    void** arg_arr = (void**)ptr;
    matrix_t* obj = (matrix_t*)arg_arr[0];
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

    return NULL;
}

void util::uniform_random(matrix_t* obj, char* low, char* up)
{
    if(obj == nullptr)
    {
        cout << "[class : util, func : uniform_random, error : reference nullptr]" << endl;
        cout << "specific : function attribution is nullptr" << endl;
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

                cout << "[class : util, func : uniform_random, text : using thread num : " << thread_using << "]" << endl;

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
                        cout << "[class : util, func : uniform_random, error : threading]" << endl;
                        cout << "specific : can not create thread" << endl;
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

                cout << "[class : util, func : uniform_random, text : using thread num : " << thread_using << "]" << endl;

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
                        cout << "[class : util, func : uniform_random, error : threading]" << endl;
                        cout << "specific : can not create thread" << endl;
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
            cout << "[class : util, func : uniform_random, error : attr not satisfying condition]" << endl;
            cout << "specific : function attribution does not satisfying condition of low < up" << endl;
            exit(-1);
        }

        mpz_clear(low_bound);
        mpz_clear(up_bound);
        mpz_clear(sum_bound);
    }
}

// void* ptr = [polynomial_t* obj, mpz_t sum_bound, mpz_t low_bound, uint64_t start_point, uint64_t end_point]
void* uniform_random_threading_polynomial(void* ptr)
{
    void** arg_arr = (void**)ptr;
    polynomial_t* obj = (polynomial_t*)arg_arr[0];
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

    return NULL;
}

void util::uniform_random(polynomial_t* obj, char* low, char* up)
{
    if(obj == nullptr)
    {
        cout << "[class : util, func : uniform_random, error : reference nullptr]" << endl;
        cout << "specific : function attribution is nullptr" << endl;
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

                cout << "[class : util, func : uniform_random, text : using thread num : " << thread_using << "]" << endl;

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
                        cout << "[class : util, func : uniform_random, error : threading]" << endl;
                        cout << "specific : can not create thread" << endl;
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

                cout << "[class : util, func : uniform_random, text : using thread num : " << thread_using << "]" << endl;

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
                        cout << "[class : util, func : uniform_random, error : threading]" << endl;
                        cout << "specific : can not create thread" << endl;
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
            cout << "[class : util, func : uniform_random, error : attr not satisfying condition]" << endl;
            cout << "specific : function attribution does not satisfying condition of low < up" << endl;
            exit(-1);
        }

        mpz_clear(low_bound);
        mpz_clear(up_bound);
        mpz_clear(sum_bound);
    }
}
