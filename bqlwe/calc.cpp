#include <iostream>
#include <pthread.h>
#include <thread>
#include "util.h"
#include "calc.h"
using namespace std;

const uint64_t thread_num = std::thread::hardware_concurrency() > 1 ? std::thread::hardware_concurrency() : 1;
const uint64_t thread_block = 2;

// void* ptr = [matrix_t* objo, matrix_t* obj1, matrix_t* obj2, uint64_t start_obj1_row_point, uint64_t end_obj1_row_point]
void* mutiple_row_threading_matrix(void* ptr)
{
    void** arg_arr = (void**)ptr;
    matrix_t* objo = (matrix_t*)arg_arr[0];
    matrix_t* obj1 = (matrix_t*)arg_arr[1];
    matrix_t* obj2 = (matrix_t*)arg_arr[2];
    uint64_t start_point = *(uint64_t*)arg_arr[3];
    uint64_t end_point = *(uint64_t*)arg_arr[4];

    mpz_t* matrix_o = objo->return_matrix();
    uint64_t col_o = *(objo->return_size() + 1);

    mpz_t* matrix_1 = obj1->return_matrix();
    uint64_t col_1 = *(obj1->return_size() + 1);

    mpz_t* matrix_2 = obj2->return_matrix();
    uint64_t col_2 = *(obj2->return_size() + 1);

    mpz_t temp;
    mpz_init_set_str(temp, "0", 10);

    for(uint64_t i = start_point; i < end_point; i++)
    {
        for(uint64_t j = 0; j < col_2; j++)
        {
            for(uint64_t k = 0; k < col_1; k++)
            {
                mpz_mul(temp, *(matrix_1 + col_1 * i + k), *(matrix_2 + col_2 * k + j));
                mpz_add(*(matrix_o + col_o * i + j), *(matrix_o + col_o * i + j), temp);
            }
        }
    }

    mpz_clear(temp);

    return NULL;
}

// void* ptr = [matrix_t* objo, matrix_t* obj1, matrix_t* obj2, uint64_t start_obj1_col_point, uint64_t end_obj1_col_point]
void* mutiple_col_threading_matrix(void* ptr)
{
    void** arg_arr = (void**)ptr;
    matrix_t* objo = (matrix_t*)arg_arr[0];
    matrix_t* obj1 = (matrix_t*)arg_arr[1];
    matrix_t* obj2 = (matrix_t*)arg_arr[2];
    uint64_t start_point = *(uint64_t*)arg_arr[3];
    uint64_t end_point = *(uint64_t*)arg_arr[4];

    mpz_t* matrix_o = objo->return_matrix();
    uint64_t col_o = *(objo->return_size() + 1);

    mpz_t* matrix_1 = obj1->return_matrix();
    uint64_t row_1 = *(obj1->return_size());
    uint64_t col_1 = *(obj1->return_size() + 1);

    mpz_t* matrix_2 = obj2->return_matrix();
    uint64_t col_2 = *(obj2->return_size() + 1);

    mpz_t temp;
    mpz_init_set_str(temp, "0", 10);

    for(uint64_t i = start_point; i < end_point; i++)
    {
        for(uint64_t j = 0; j < row_1; j++)
        {
            for(uint64_t k = 0; k < col_2; k++)
            {
                mpz_mul(temp, *(matrix_1 + col_1 * j + i), *(matrix_2 + col_2 * i + k));
                mpz_add(*(matrix_o + col_o * j + k), *(matrix_o + col_o * j + k), temp);
            }
        }
    }

    mpz_clear(temp);

    return NULL;
}

matrix_t* calc::multiple(matrix_t* obj1, matrix_t* obj2)
{
    if(obj1 == nullptr || obj2 == nullptr)
    {
        cout << "[class : calc, func : multiple, error : reference nullptr]" << endl;
        cout << "specific : function attribution is nullptr" << endl;
        exit(-1);
    }
    else
    {
        uint64_t row_1 = *(obj1->return_size());
        uint64_t col_1 = *(obj1->return_size() + 1);

        uint64_t row_2 = *(obj2->return_size());
        uint64_t col_2 = *(obj2->return_size() + 1);

        if(col_1 != row_2)
        {
            cout << "[class : calc, func : multiple, error : matrix define]" << endl;
            cout << "specific : obj1 matrix and obj2 matrix size unmatched over matrix multiple" << endl;
            exit(-1);
        }
        else
        {
            if(row_1 >= col_1)
            {
                uint64_t block_length = 0;
                uint64_t block_residue = 0;
                uint64_t thread_using = 0;

                for(uint64_t i = thread_num; i > 0; i--)
                {
                    block_length = (uint64_t) (row_1 / i);
                    block_residue = (row_1 % i);
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

                cout << "[class : calc, func : multiple, text : using thread num : " << thread_using << "]" << endl;

                matrix_t* new_matrix_struct = new matrix_t(row_1, col_2);

                pthread_t* thread_id = new pthread_t[thread_using];
                void*** arg_arr = new void**[thread_using];
                for(uint64_t i = 0; i < thread_using; i++)
                {
                    arg_arr[i] = new void*[5];
                }

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
                                                
                    arg_arr[i][0] = (void*)new_matrix_struct;
                    arg_arr[i][1] = (void*)obj1;
                    arg_arr[i][2] = (void*)obj2;
                    arg_arr[i][3] = (void*)(start_point + i);
                    arg_arr[i][4] = (void*)(end_point + i);

                    int error = pthread_create(&*(thread_id + i), NULL, mutiple_row_threading_matrix, (void*) arg_arr[i]);
                    if(error)
                    {
                        cout << "[class : calc, func : multiple, error : threading]" << endl;
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

                return new_matrix_struct;
            }
            else
            {
                uint64_t block_length = 0;
                uint64_t block_residue = 0;
                uint64_t thread_using = 0;

                for(uint64_t i = thread_num; i > 0; i--)
                {
                    block_length = (uint64_t) (col_1 / i);
                    block_residue = (col_1 % i);
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

                cout << "[class : calc, func : multiple, text : using thread num : " << thread_using << "]" << endl;

                matrix_t** new_matrix_struct_list = new matrix_t*[thread_using];
                for(uint64_t i = 0; i < thread_using; i++)
                {
                    *(new_matrix_struct_list + i) = new matrix_t(row_1, col_2);
                }

                pthread_t* thread_id = new pthread_t[thread_using];
                void*** arg_arr = new void**[thread_using];
                for(uint64_t i = 0; i < thread_using; i++)
                {
                    arg_arr[i] = new void*[5];
                }

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
                                                
                    arg_arr[i][0] = (void*)new_matrix_struct_list[i];
                    arg_arr[i][1] = (void*)obj1;
                    arg_arr[i][2] = (void*)obj2;
                    arg_arr[i][3] = (void*)(start_point + i);
                    arg_arr[i][4] = (void*)(end_point + i);

                    int error = pthread_create(&*(thread_id + i), NULL, mutiple_col_threading_matrix, (void*) arg_arr[i]);
                    if(error)
                    {
                        cout << "[class : calc, func : multiple, error : threading]" << endl;
                        cout << "specific : can not create thread" << endl;
                        exit(-1);
                    }
                }

                for(uint64_t i = 0; i < thread_using; i++)
                {
                    pthread_join(*(thread_id + i), NULL);
                }

                matrix_t* new_matrix_struct = new matrix_t(row_1, col_2);
                matrix_t* temp;
                for(uint64_t i = 0; i < thread_using; i++)
                {
                    temp = calc::add(new_matrix_struct, *(new_matrix_struct_list + i));
                    util::clear(&new_matrix_struct);
                    new_matrix_struct = temp;
                }

                for(uint64_t i = 0; i < thread_using; i++)
                {
                    util::clear(&(*(new_matrix_struct_list + i)));
                }
                delete[] new_matrix_struct_list;
                delete[] start_point;
                delete[] end_point;
                delete[] thread_id;
                for(uint64_t i = 0; i < thread_using; i++)
                {
                    delete[] arg_arr[i];
                }
                delete[] arg_arr;

                return new_matrix_struct;
            }   
        }
    }
}

matrix_t* calc::add(matrix_t* obj1, matrix_t* obj2)
{
    if(obj1 == nullptr || obj2 == nullptr)
    {
        cout << "[class : calc, func : add, error : reference nullptr]" << endl;
        cout << "specific : function attribution is nullptr" << endl;
        exit(-1);
    }
    else
    {
        mpz_t* matrix_1 = obj1->return_matrix();
        uint64_t row_1 = *(obj1->return_size());
        uint64_t col_1 = *(obj1->return_size() + 1);

        mpz_t* matrix_2 = obj2->return_matrix();
        uint64_t row_2 = *(obj2->return_size());
        uint64_t col_2 = *(obj2->return_size() + 1);
        
        if(row_1 != row_2 || col_1 != col_2)
        {
            cout << "[class : calc, func : add, error : matrix define]" << endl;
            cout << "specific : obj1 matrix and obj2 matrix size unmatched over matrix add" << endl;
            exit(-1);
        }
        else
        {
            matrix_t* new_matrix_struct = new matrix_t(row_1, col_1);
            mpz_t* new_matrix = new_matrix_struct->return_matrix();
            uint64_t row = *(new_matrix_struct->return_size());
            uint64_t col = *(new_matrix_struct->return_size() + 1);

            for(uint64_t i = 0; i < row; i++)
            {
                for(uint64_t j = 0; j < col; j++)
                {
                    mpz_add(*(new_matrix + col * i + j), *(matrix_1 + col_1 * i + j), *(matrix_2 + col_2 * i + j));
                }
            }

            return new_matrix_struct;
        }
    }
}

matrix_t* calc::transpose(matrix_t* obj)
{
    if(obj == nullptr)
    {
        cout << "[class : calc, func : transpose, error : reference nullptr]" << endl;
        cout << "specific : function attribution is nullptr" << endl;
        exit(-1);
    }
    else
    {
        mpz_t* matrix = obj->return_matrix();
        uint64_t row = *(obj->return_size());
        uint64_t col = *(obj->return_size() + 1);

        matrix_t* new_matrix_struct = new matrix_t(col, row);
        mpz_t* new_matrix = new_matrix_struct->return_matrix();

        for(uint64_t i = 0; i < row; i++)
        {
            for(uint64_t j = 0; j < col; j++)
            {
                mpz_set(*(new_matrix + row * j + i), *(matrix + col * i + j));
            }
        }

        return new_matrix_struct;
    }
}