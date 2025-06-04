#include "util.h"
#include "debug.h"
#define mpf_prec 512
#define float_digit 5
using namespace std;

const uint64_t thread_num = std::thread::hardware_concurrency() > 1 ? std::thread::hardware_concurrency() : 1;
const uint64_t thread_block = 1; 

gmp_randstate_t state;

template <typename T>
void util::print_struct(T* obj)
{
    if(obj == nullptr)
    {
        debug::print_error((char*)"util", (char*)"print_struct", 0, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        if constexpr (is_same_v<T, scalar_zt> || is_same_v<T, matrix_zt> || is_same_v<T, polynomial_zt>)
        {
            mpz_t* content = obj->return_content();
            uint64_t row = *(obj->return_size());
            uint64_t col = *(obj->return_size() + 1);

            cout << "This struct type : " << obj->return_type() << " | row : " << row << " | col : " << col << endl;

            for(uint64_t i = 0; i < row; i++)
            {
                for(uint64_t j = 0; j < col; j++)
                {
                    mpz_out_str(stdout, 10, *(content + col * i + j));
                    if(j != col - 1)
                    {
                        cout << ", ";
                    }
                }
                cout << endl;
            }
        }
        else if constexpr (is_same_v<T, scalar_ft> || is_same_v<T, matrix_ft> || is_same_v<T, polynomial_ft>)
        {
            mpf_t* content = obj->return_content();
            uint64_t row = *(obj->return_size());
            uint64_t col = *(obj->return_size() + 1);

            cout << "This struct type : " << obj->return_type() << " | row : " << row << " | col : " << col << endl;

            for(uint64_t i = 0; i < row; i++)
            {
                for(uint64_t j = 0; j < col; j++)
                {
                    mpf_out_str(stdout, 10, float_digit, *(content + col * i + j));
                    if(j != col - 1)
                    {
                        cout << ", ";
                    }
                }
                cout << endl;
            }
        }
        else if constexpr (is_same_v<T, scalar_64it> || is_same_v<T, matrix_64it> || is_same_v<T, polynomial_64it>)
        {
            int64_t* content = obj->return_content();
            uint64_t row = *(obj->return_size());
            uint64_t col = *(obj->return_size() + 1);

            cout << "This struct type : " << obj->return_type() << " | row : " << row << " | col : " << col << endl;

            for(uint64_t i = 0; i < row; i++)
            {
                for(uint64_t j = 0; j < col; j++)
                {
                    cout << *(content + col * i + j);
                    if(j != col - 1)
                    {
                        cout << ", ";
                    }
                }
                cout << endl;
            }
        }
        else if constexpr (is_same_v<T, scalar_64ft> || is_same_v<T, matrix_64ft> || is_same_v<T, polynomial_64ft>)
        {
            double* content = obj->return_content();
            uint64_t row = *(obj->return_size());
            uint64_t col = *(obj->return_size() + 1);

            cout << "This struct type : " << obj->return_type() << " | row : " << row << " | col : " << col << endl;

            for(uint64_t i = 0; i < row; i++)
            {
                for(uint64_t j = 0; j < col; j++)
                {
                    cout << fixed << setprecision(float_digit) << *(content + col * i + j);
                    if(j != col - 1)
                    {
                        cout << ", ";
                    }
                }
                cout << endl;
            }
        }
        else
        {
            debug::print_error((char*)"util", (char*)"print_struct", 0, (char*)"non exist struct");
            debug::print_error_specific((char*)"given struct is not defined");
            exit(-1);
        }
    }
}

//-----------------------------------------//

template <typename T>
void util::print_struct_meta(T* obj)
{
    if(obj == nullptr)
    {
        debug::print_error((char*)"util", (char*)"print_struct_meta", 0, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        if constexpr (is_same_v<T, scalar_zt> || is_same_v<T, matrix_zt> || is_same_v<T, polynomial_zt>)
        {
            uint64_t row = *(obj->return_size());
            uint64_t col = *(obj->return_size() + 1);

            cout << "This struct type : " << obj->return_type() << " | row : " << row << " | col : " << col << endl;
        }
        else if constexpr (is_same_v<T, scalar_ft> || is_same_v<T, matrix_ft> || is_same_v<T, polynomial_ft>)
        {
            uint64_t row = *(obj->return_size());
            uint64_t col = *(obj->return_size() + 1);

            cout << "This struct type : " << obj->return_type() << " | row : " << row << " | col : " << col << endl;
        }
        else if constexpr (is_same_v<T, scalar_64it> || is_same_v<T, matrix_64it> || is_same_v<T, polynomial_64it>)
        {
            uint64_t row = *(obj->return_size());
            uint64_t col = *(obj->return_size() + 1);

            cout << "This struct type : " << obj->return_type() << " | row : " << row << " | col : " << col << endl;
        }
        else if constexpr (is_same_v<T, scalar_64ft> || is_same_v<T, matrix_64ft> || is_same_v<T, polynomial_64ft>)
        {
            uint64_t row = *(obj->return_size());
            uint64_t col = *(obj->return_size() + 1);

            cout << "This struct type : " << obj->return_type() << " | row : " << row << " | col : " << col << endl;
        }
        else
        {
            debug::print_error((char*)"util", (char*)"print_struct_meta", 0, (char*)"non exist struct");
            debug::print_error_specific((char*)"given struct is not defined");
            exit(-1);
        }
    }
}

//-----------------------------------------//

template <typename T>
T* util::copy(T* obj)
{
    if(obj == nullptr)
    {
        debug::print_error((char*)"util", (char*)"copy", 0, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        if constexpr (is_same_v<T, scalar_zt> || is_same_v<T, matrix_zt> || is_same_v<T, polynomial_zt>)
        {
            mpz_t* content = obj->return_content();
            uint64_t row = *(obj->return_size());
            uint64_t col = *(obj->return_size() + 1);

            if constexpr (is_same_v<T, scalar_zt>)
            {
                T* new_content_struct = new T();
                mpz_t* new_content = new_content_struct->return_content();

                mpz_set(*(new_content), *(content));

                return new_content_struct;
            }
            else if constexpr (is_same_v<T, matrix_zt>)
            {
                T* new_content_struct = new T(row, col);
                mpz_t* new_content = new_content_struct->return_content();

                for(uint64_t i = 0; i < row; i++)
                {
                    for(uint64_t j = 0; j < col; j++)
                    {
                        mpz_set(*(new_content + col * i + j), *(content + col * i + j));
                    }
                }

                return new_content_struct;
            }
            else
            {
                T* new_content_struct = new T(row * col);
                mpz_t* new_content = new_content_struct->return_content();

                for(uint64_t i = 0; i < row; i++)
                {

                    mpz_set(*(new_content + i), *(content + i));
                }

                return new_content_struct;
            }
        }
        else if constexpr (is_same_v<T, scalar_ft> || is_same_v<T, matrix_ft> || is_same_v<T, polynomial_ft>)
        {
            mpf_t* content = obj->return_content();
            uint64_t row = *(obj->return_size());
            uint64_t col = *(obj->return_size() + 1);

            if constexpr (is_same_v<T, scalar_zt>)
            {
                T* new_content_struct = new T();
                mpf_t* new_content = new_content_struct->return_content();

                mpf_set(*(new_content), *(content));

                return new_content_struct;
            }
            else if constexpr (is_same_v<T, matrix_zt>)
            {
                T* new_content_struct = new T(row, col);
                mpf_t* new_content = new_content_struct->return_content();

                for(uint64_t i = 0; i < row; i++)
                {
                    for(uint64_t j = 0; j < col; j++)
                    {
                        mpf_set(*(new_content + col * i + j), *(content + col * i + j));
                    }
                }

                return new_content_struct;
            }
            else
            {
                T* new_content_struct = new T(row * col);
                mpf_t* new_content = new_content_struct->return_content();

                for(uint64_t i = 0; i < row; i++)
                {

                    mpf_set(*(new_content + i), *(content + i));
                }

                return new_content_struct;
            }

        }
        else if constexpr (is_same_v<T, scalar_64it> || is_same_v<T, matrix_64it> || is_same_v<T, polynomial_64it>)
        {
            int64_t* content = obj->return_content();
            uint64_t row = *(obj->return_size());
            uint64_t col = *(obj->return_size() + 1);

            if constexpr (is_same_v<T, scalar_zt>)
            {
                T* new_content_struct = new T();
                int64_t* new_content = new_content_struct->return_content();

                *(new_content) = *(content);

                return new_content_struct;
            }
            else if constexpr (is_same_v<T, matrix_zt>)
            {
                T* new_content_struct = new T(row, col);
                int64_t* new_content = new_content_struct->return_content();

                for(uint64_t i = 0; i < row; i++)
                {
                    for(uint64_t j = 0; j < col; j++)
                    {
                        *(new_content + col * i + j) = *(content + col * i + j);
                    }
                }

                return new_content_struct;
            }
            else
            {
                T* new_content_struct = new T(row * col);
                int64_t* new_content = new_content_struct->return_content();

                for(uint64_t i = 0; i < row; i++)
                {

                    *(new_content + i) = *(content + i);
                }

                return new_content_struct;
            }
        }
        else if constexpr (is_same_v<T, scalar_64ft> || is_same_v<T, matrix_64ft> || is_same_v<T, polynomial_64ft>)
        {
            double* content = obj->return_content();
            uint64_t row = *(obj->return_size());
            uint64_t col = *(obj->return_size() + 1);

            if constexpr (is_same_v<T, scalar_zt>)
            {
                T* new_content_struct = new T();
                double* new_content = new_content_struct->return_content();

                *(new_content) = *(content);

                return new_content_struct;
            }
            else if constexpr (is_same_v<T, matrix_zt>)
            {
                T* new_content_struct = new T(row, col);
                double* new_content = new_content_struct->return_content();

                for(uint64_t i = 0; i < row; i++)
                {
                    for(uint64_t j = 0; j < col; j++)
                    {
                        *(new_content + col * i + j) = *(content + col * i + j);
                    }
                }

                return new_content_struct;
            }
            else
            {
                T* new_content_struct = new T(row * col);
                double* new_content = new_content_struct->return_content();

                for(uint64_t i = 0; i < row; i++)
                {

                    *(new_content + i) = *(content + i);
                }

                return new_content_struct;
            }
        }
        else
        {
            debug::print_error((char*)"util", (char*)"copy", 0, (char*)"non exist struct");
            debug::print_error_specific((char*)"given struct is not defined");
            exit(-1);
        }
    }
}

//-----------------------------------------//

template <typename T>
void util::clear(T** obj)
{
    if(*obj == nullptr)
    {
        debug::print_error((char*)"util", (char*)"clear", 0, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        if constexpr (is_same_v<T, scalar_zt> || is_same_v<T, matrix_zt> || is_same_v<T, polynomial_zt>
                    || is_same_v<T, scalar_ft> || is_same_v<T, matrix_ft> || is_same_v<T, polynomial_ft>
                    || is_same_v<T, scalar_64it> || is_same_v<T, matrix_64it> || is_same_v<T, polynomial_64it>
                    || is_same_v<T, scalar_64ft> || is_same_v<T, matrix_64ft> || is_same_v<T, polynomial_64ft>)
        {
            (*obj)->~T();
            *obj = nullptr;
        }
        else
        {
            debug::print_error((char*)"util", (char*)"copy", 0, (char*)"non exist struct");
            debug::print_error_specific((char*)"given struct is not defined");
            exit(-1);
        }
    }
}

// =================================================================================== //

// void util::set_entry(scalar_zt* obj, char* value)
// {
//     if(obj == nullptr)
//     {
//         debug::print_error((char*)"util", (char*)"set_entry", 0, (char*)"reference nullptr");
//         debug::print_error_specific((char*)"function attribution is nullptr");
//         exit(-1);
//     }
//     else
//     {
//         mpz_t* scalar = obj->return_scalar();

//         mpz_set_str(*(scalar), value, 10);
//     }
// }

// void util::set_entry(matrix_zt* obj, char* value, uint64_t pos_row, uint64_t pos_col)
// {
//     if(obj == nullptr)
//     {
//         debug::print_error((char*)"util", (char*)"set_entry", 1, (char*)"reference nullptr");
//         debug::print_error_specific((char*)"function attribution is nullptr");
//         exit(-1);
//     }
//     else
//     {
//         mpz_t* matrix = obj->return_matrix();
//         uint64_t row = *(obj->return_size());
//         uint64_t col = *(obj->return_size() + 1);
        
//         if(pos_row < row && pos_col < col)
//         {
//             mpz_set_str(*(matrix + col * (pos_row - 1) + (pos_col - 1)), value, 10);
//         }
//         else
//         {
//             debug::print_error((char*)"util", (char*)"set_entry", 1, (char*)"attribution overflow");
//             debug::print_error_specific((char*)"pos_row or pos_col are overflowing obj matrix's size");
//             exit(-1);
//         }
//     }
// }

// void util::set_entry(matrix_zt* obj, scalar_zt* value, uint64_t pos_row, uint64_t pos_col)
// {
//     if(obj == nullptr || value == nullptr)
//     {
//         debug::print_error((char*)"util", (char*)"set_entry", 2, (char*)"reference nullptr");
//         debug::print_error_specific((char*)"function attribution is nullptr");
//         exit(-1);
//     }
//     else
//     {
//         mpz_t* matrix = obj->return_matrix();
//         mpz_t* scalar = value->return_scalar();
//         uint64_t row = *(obj->return_size());
//         uint64_t col = *(obj->return_size() + 1);
        
//         if(pos_row < row && pos_col < col)
//         {
//             mpz_set(*(matrix + col * (pos_row - 1) + (pos_col - 1)), *scalar);
//         }
//         else
//         {
//             debug::print_error((char*)"util", (char*)"set_entry", 2, (char*)"attribution overflow");
//             debug::print_error_specific((char*)"pos_row or pos_col are overflowing obj matrix's size");
//             exit(-1);
//         }
//     }
// }

// void util::set_entry(polynomial_zt* obj, char* value, uint64_t pos)
// {
//     if(obj == nullptr)
//     {
//         debug::print_error((char*)"util", (char*)"set_entry", 3, (char*)"reference nullptr");
//         debug::print_error_specific((char*)"function attribution is nullptr");
//         exit(-1);
//     }
//     else
//     {
//         mpz_t* polynomial = obj->return_polynomial();
//         uint64_t col = *(obj->return_size() + 1);
        
//         if(pos < col)
//         {
//             mpz_set_str(*(polynomial + pos), value, 10);
//         }
//         else
//         {
//             debug::print_error((char*)"util", (char*)"set_entry", 3, (char*)"attribution overflow");
//             debug::print_error_specific((char*)"pos is overflowing obj polynomial's order");
//             exit(-1);
//         }
//     }
// }

// void util::set_entry(polynomial_zt* obj, scalar_zt* value, uint64_t pos)
// {
//     if(obj == nullptr || value == nullptr)
//     {
//         debug::print_error((char*)"util", (char*)"set_entry", 4, (char*)"reference nullptr");
//         debug::print_error_specific((char*)"function attribution is nullptr");
//         exit(-1);
//     }
//     else
//     {
//         mpz_t* polynomial = obj->return_polynomial();
//         mpz_t* scalar = value->return_scalar();
//         uint64_t col = *(obj->return_size() + 1);
        
//         if(pos < col)
//         {
//             mpz_set(*(polynomial + pos), *scalar);
//         }
//         else
//         {
//             debug::print_error((char*)"util", (char*)"set_entry", 4, (char*)"attribution overflow");
//             debug::print_error_specific((char*)"pos is overflowing obj polynomial's order");
//             exit(-1);
//         }
//     }
// }

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

//-----------------------------------------//

template <typename T>
void util::uniform_random(T* obj, char* low, char* up)
{
    if(obj == nullptr)
    {
        debug::print_error((char*)"util", (char*)"uniform_random", 0, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        if constexpr (is_same_v<T, scalar_zt> || is_same_v<T, matrix_zt> || is_same_v<T, polynomial_zt>)
        {
            mpz_t low_bound, up_bound, sum_bound, zero;
            mpz_init_set_str(low_bound, low, 10);
            mpz_init_set_str(up_bound, up, 10);
            mpz_init_set_str(sum_bound, "0", 10);
            mpz_init_set_str(zero, "0", 10);

            if(mpz_cmp(low_bound, up_bound) < 0 && (mpz_cmp(low_bound, zero) != 0 || mpz_cmp(up_bound, zero) != 0))
            {
                if(mpz_cmp(zero, up_bound) < 0)
                {
                    mpz_neg(low_bound, low_bound);
                    mpz_add(sum_bound, low_bound, up_bound);
                    mpz_neg(low_bound, low_bound);

                    mpz_t* content = obj->return_content();
                    uint64_t row = *(obj->return_size());
                    uint64_t col = *(obj->return_size() + 1);
                    
                    for(uint64_t i = 0; i < row; i++)
                    {
                        for(uint64_t j = 0; j < col; j++)
                        {
                            mpz_urandomm(*(content + col * i + j), state, sum_bound);
                            mpz_add(*(content + col * i + j), *(content + col * i + j), low_bound);
                        }
                    }
                }
                else
                {
                    mpz_neg(low_bound, low_bound);
                    mpz_add(sum_bound, low_bound, up_bound);
                    mpz_neg(up_bound, up_bound);

                    mpz_t* content = obj->return_content();
                    uint64_t row = *(obj->return_size());
                    uint64_t col = *(obj->return_size() + 1);

                    for(uint64_t i = 0; i < row; i++)
                    {
                        for(uint64_t j = 0; j < col; j++)
                        {
                            mpz_urandomm(*(content + col * i + j), state, sum_bound);
                            mpz_add(*(content + col * i + j), *(content + col * i + j), up_bound);
                            mpz_neg(*(content + col * i + j), *(content + col * i + j));
                        }
                    }
                }
            }
            else
            {
                debug::print_error((char*)"util", (char*)"uniform_random", 0, (char*)"attribution bed condition");
                debug::print_error_specific((char*)"function attribution does not satisfying condition of low < up");
                exit(-1);
            }

            mpz_clear(low_bound);
            mpz_clear(up_bound);
            mpz_clear(sum_bound);
            mpz_clear(zero);
        }
        else if constexpr (is_same_v<T, scalar_ft> || is_same_v<T, matrix_ft> || is_same_v<T, polynomial_ft>)
        {
            mpf_t low_bound, up_bound, sum_bound, zero;
            mpf_init2(low_bound, mpf_prec);
            mpf_set_str(low_bound, low, 10);
            mpf_init2(up_bound, mpf_prec);
            mpf_set_str(up_bound, up, 10);
            mpf_init2(sum_bound, mpf_prec);
            mpf_set_str(sum_bound, "0", 10);
            mpf_init2(zero, mpf_prec);
            mpf_set_str(zero, "0", 10);

            if(mpf_cmp(low_bound, up_bound) < 0 && (mpf_cmp(low_bound, zero) != 0 || mpf_cmp(up_bound, zero) != 0))
            {
                if(mpf_cmp(zero, up_bound) < 0)
                {
                    mpf_neg(low_bound, low_bound);
                    mpf_add(sum_bound, low_bound, up_bound);
                    mpf_neg(low_bound, low_bound);

                    mpf_t* content = obj->return_content();
                    uint64_t row = *(obj->return_size());
                    uint64_t col = *(obj->return_size() + 1);

                    mpf_t temp;
                    mpf_init2(temp, mpf_prec);
                    
                    for(uint64_t i = 0; i < row; i++)
                    {
                        for(uint64_t j = 0; j < col; j++)
                        {
                            mpf_urandomb(temp, state, mpf_prec);
                            mpf_mul(temp, temp, sum_bound);
                            mpf_add(temp, temp, low_bound);
                            mpf_set(*(content + col * i + j), temp);
                        }
                    }

                    mpf_clear(temp);
                }
                else
                {
                    mpf_neg(low_bound, low_bound);
                    mpf_add(sum_bound, low_bound, up_bound);
                    mpf_neg(up_bound, up_bound);

                    mpf_t* content = obj->return_content();
                    uint64_t row = *(obj->return_size());
                    uint64_t col = *(obj->return_size() + 1);

                    mpf_t temp;
                    mpf_init2(temp, mpf_prec);

                    for(uint64_t i = 0; i < row; i++)
                    {
                        for(uint64_t j = 0; j < col; j++)
                        {
                            mpf_urandomb(temp, state, mpf_prec);
                            mpf_mul(temp, temp, sum_bound);
                            mpf_add(temp, temp, up_bound);
                            mpf_neg(temp, temp);
                            mpf_set(*(content + col * i + j), temp);
                        }
                    }

                    mpf_clear(temp);
                }
            }
            else
            {
                debug::print_error((char*)"util", (char*)"uniform_random", 0, (char*)"attribution bed condition");
                debug::print_error_specific((char*)"function attribution does not satisfying condition of low < up");
                exit(-1);
            }

            mpf_clear(low_bound);
            mpf_clear(up_bound);
            mpf_clear(sum_bound);
            mpf_clear(zero);
        }
        else if constexpr (is_same_v<T, scalar_64it> || is_same_v<T, matrix_64it> || is_same_v<T, polynomial_64it>)
        {
            random_device rd;
            mt19937_64 gen(rd());

            int64_t low_bound, up_bound; 
            string_view svl(low);
            from_chars(svl.data(), svl.data() + svl.size(), low_bound);
            string_view svu(up);
            from_chars(svu.data(), svu.data() + svu.size(), up_bound);
            up_bound -= 1;
            
            uniform_int_distribution<int64_t> dist(low_bound, up_bound);
            
            if((low_bound < up_bound) && ((low_bound != 0) || (up_bound != 0)))
            {
                int64_t* content = obj->return_content();
                uint64_t row = *(obj->return_size());
                uint64_t col = *(obj->return_size() + 1);
                    
                for(uint64_t i = 0; i < row; i++)
                {
                    for(uint64_t j = 0; j < col; j++)
                    {
                        *(content + col * i + j) = dist(gen);
                    }
                }
            }
            else
            {
                debug::print_error((char*)"util", (char*)"uniform_random", 0, (char*)"attribution bed condition");
                debug::print_error_specific((char*)"function attribution does not satisfying condition of low < up");
                exit(-1);
            }
        }
        else if constexpr (is_same_v<T, scalar_64ft> || is_same_v<T, matrix_64ft> || is_same_v<T, polynomial_64ft>)
        {
            random_device rd;
            mt19937_64 gen(rd());

            double low_bound, up_bound;
            string_view svl(low);
            from_chars(svl.data(), svl.data() + svl.size(), low_bound);
            string_view svu(up);
            from_chars(svu.data(), svu.data() + svu.size(), up_bound);

            uniform_real_distribution<double> dist(low_bound, up_bound);
            
            if((low_bound < up_bound) && ((low_bound != 0) || (up_bound != 0)))
            {
                double* content = obj->return_content();
                uint64_t row = *(obj->return_size());
                uint64_t col = *(obj->return_size() + 1);
                    
                for(uint64_t i = 0; i < row; i++)
                {
                    for(uint64_t j = 0; j < col; j++)
                    {
                        *(content + col * i + j) = dist(gen);
                    }
                }
            }
            else
            {
                debug::print_error((char*)"util", (char*)"uniform_random", 0, (char*)"attribution bed condition");
                debug::print_error_specific((char*)"function attribution does not satisfying condition of low < up");
                exit(-1);
            }
        }
        else
        {
            debug::print_error((char*)"util", (char*)"uniform_random", 0, (char*)"non exist struct");
            debug::print_error_specific((char*)"given struct is not defined");
            exit(-1);
        }
    }
}

// void* ptr = [T* obj, char* sum_bound, char* low_bound, uint64_t start_point, uint64_t end_point, bool neg]
template <typename T>
void* uniform_random_threading(void* ptr)
{
    void** arg_arr = (void**)ptr;

    if constexpr (is_same_v<T, scalar_zt> || is_same_v<T, matrix_zt> || is_same_v<T, polynomial_zt>)
    {
        T* obj = (T*)arg_arr[0];
        mpz_t sum_bound;
        mpz_init_set_str(sum_bound, (char*)arg_arr[1], 10);
        mpz_t low_bound;
        mpz_init_set_str(low_bound, (char*)arg_arr[2], 10);
        uint64_t start_point = *(uint64_t*)arg_arr[3];
        uint64_t end_point = *(uint64_t*)arg_arr[4];
        bool neg = *(bool*)arg_arr[5];

        mpz_t* content = obj->return_content();

        for(uint64_t i = start_point; i < end_point; i++)
        {
            mpz_urandomm(*(content + i), state, sum_bound);
            mpz_add(*(content + i), *(content + i), low_bound);
            if(neg)
            {
                mpz_neg(*(content + i), *(content + i));
            }
        }

        mpz_clear(sum_bound);
        mpz_clear(low_bound);
    }
    else if constexpr (is_same_v<T, scalar_ft> || is_same_v<T, matrix_ft> || is_same_v<T, polynomial_ft>)
    {
        T* obj = (T*)arg_arr[0];
        mpf_t sum_bound;
        mpf_init2(sum_bound, mpf_prec);
        mpf_set_str(sum_bound, (char*)arg_arr[1], 10);
        mpf_t low_bound;
        mpf_init2(low_bound, mpf_prec);
        mpf_set_str(low_bound, (char*)arg_arr[2], 10);
        uint64_t start_point = *(uint64_t*)arg_arr[3];
        uint64_t end_point = *(uint64_t*)arg_arr[4];
        bool neg = *(bool*)arg_arr[5];

        mpf_t* content = obj->return_content();

        for(uint64_t i = start_point; i < end_point; i++)
        {
            mpf_urandomb(*(content + i), state, mpf_prec);
            mpf_mul(*(content + i), *(content + i), sum_bound);
            mpf_add(*(content + i), *(content + i), low_bound);
            if(neg)
            {
                mpf_neg(*(content + i), *(content + i));
            }
        }

        mpf_clear(sum_bound);
        mpf_clear(low_bound);
    }
    else if constexpr (is_same_v<T, scalar_64it> || is_same_v<T, matrix_64it> || is_same_v<T, polynomial_64it>)
    {
        T* obj = (T*)arg_arr[0];
        int64_t low_bound, sum_bound;
        string_view svs(((char*)arg_arr[1]));
        from_chars(svs.data(), svs.data() + svs.size(), sum_bound);
        string_view svl(((char*)arg_arr[2]));
        from_chars(svl.data(), svl.data() + svl.size(), low_bound);

        uint64_t start_point = *(uint64_t*)arg_arr[3];
        uint64_t end_point = *(uint64_t*)arg_arr[4];
        bool neg = *(bool*)arg_arr[5];

        int64_t* content = obj->return_content();

        random_device rd;
        mt19937_64 gen(rd());
        uniform_int_distribution<int64_t> dist(0, sum_bound);

        for(uint64_t i = start_point; i < end_point; i++)
        {
            *(content + i) = dist(gen);
            *(content + i) += low_bound;
            if(neg)
            {
                *(content + i) = - *(content + i);
            }
        }
    }
    else if constexpr (is_same_v<T, scalar_64ft> || is_same_v<T, matrix_64ft> || is_same_v<T, polynomial_64ft>)
    {
        T* obj = (T*)arg_arr[0];
        double sum_bound, low_bound;
        string_view svs(((char*)arg_arr[1]));
        from_chars(svs.data(), svs.data() + svs.size(), sum_bound);
        string_view svl(((char*)arg_arr[2]));
        from_chars(svl.data(), svl.data() + svl.size(), low_bound);

        uint64_t start_point = *(uint64_t*)arg_arr[3];
        uint64_t end_point = *(uint64_t*)arg_arr[4];
        bool neg = *(bool*)arg_arr[5];

        double* content = obj->return_content();

        random_device rd;
        mt19937_64 gen(rd());
        uniform_real_distribution<double> dist(0, sum_bound);

        for(uint64_t i = start_point; i < end_point; i++)
        {
            *(content + i) = dist(gen);
            *(content + i) += low_bound;
            if(neg)
            {
                *(content + i) = - *(content + i);
            }
        }
    }
    else
    {
        debug::print_error((char*)"util", (char*)"uniform_random_threading", 0, (char*)"non exist struct");
        debug::print_error_specific((char*)"given struct is not defined");
        exit(-1);
    }

    return NULL;
}

template <typename T>
void util::uniform_random_mt(T* obj, char* low, char* up)
{
    if(obj == nullptr)
    {
        debug::print_error((char*)"util", (char*)"uniform_random", 0, (char*)"reference nullptr");
        debug::print_error_specific((char*)"function attribution is nullptr");
        exit(-1);
    }
    else
    {
        if constexpr (is_same_v<T, scalar_zt> || is_same_v<T, matrix_zt> || is_same_v<T, polynomial_zt>)
        {
            char* low_bound_c,* sum_bound_c;
            mpz_t low_bound, up_bound, sum_bound, zero;
            mpz_init_set_str(low_bound, low, 10);
            mpz_init_set_str(up_bound, up, 10);
            mpz_init_set_str(sum_bound, "0", 10);
            mpz_init_set_str(zero, "0", 10);
            bool neg = false;

            if(mpz_cmp(low_bound, up_bound) < 0 && (mpz_cmp(low_bound, zero) != 0 || mpz_cmp(up_bound, zero) != 0))
            {
                if(mpz_cmp(zero, up_bound) < 0)
                {
                    mpz_neg(low_bound, low_bound);
                    mpz_add(sum_bound, low_bound, up_bound);
                    mpz_neg(low_bound, low_bound);

                    low_bound_c = mpz_get_str(NULL, 10, low_bound);
                    sum_bound_c = mpz_get_str(NULL, 10, sum_bound);

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
                        arg_arr[i][1] = (void*)sum_bound_c;
                        arg_arr[i][2] = (void*)low_bound_c;
                        arg_arr[i][3] = (void*)(start_point + i);
                        arg_arr[i][4] = (void*)(end_point + i);
                        arg_arr[i][5] = (void*)&neg;

                        int error = pthread_create(&*(thread_id + i), NULL, uniform_random_threading<T>, (void*) arg_arr[i]);
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

                    low_bound_c = mpz_get_str(NULL, 10, up_bound);
                    sum_bound_c = mpz_get_str(NULL, 10, sum_bound);

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
                        arg_arr[i][1] = (void*)sum_bound_c;
                        arg_arr[i][2] = (void*)low_bound_c;
                        arg_arr[i][3] = (void*)(start_point + i);
                        arg_arr[i][4] = (void*)(end_point + i);
                        arg_arr[i][5] = (void*)&neg;

                        int error = pthread_create(&*(thread_id + i), NULL, uniform_random_threading<T>, (void*) arg_arr[i]);
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

            free(low_bound_c);
            free(sum_bound_c);
            mpz_clear(low_bound);
            mpz_clear(up_bound);
            mpz_clear(sum_bound);
            mpz_clear(zero);
        }
        else if constexpr (is_same_v<T, scalar_ft> || is_same_v<T, matrix_ft> || is_same_v<T, polynomial_ft>)
        {
            string low_bound_s, sum_bound_s;
            const char* low_bound_c,* sum_bound_c;
            mpf_t low_bound, up_bound, sum_bound, zero;
            mpf_init2(low_bound, mpf_prec);
            mpf_set_str(low_bound, low, 10);
            mpf_init2(up_bound, mpf_prec);
            mpf_set_str(up_bound, up, 10);
            mpf_init2(sum_bound, mpf_prec);
            mpf_set_str(sum_bound, "0", 10);
            mpf_init2(zero, mpf_prec);
            mpf_set_str(zero, "0", 10);
            bool neg = false;

            if(mpf_cmp(low_bound, up_bound) < 0 && (mpf_cmp(low_bound, zero) != 0 || mpf_cmp(up_bound, zero) != 0))
            {
                if(mpf_cmp(zero, up_bound) < 0)
                {
                    mpf_neg(low_bound, low_bound);
                    mpf_add(sum_bound, low_bound, up_bound);
                    mpf_neg(low_bound, low_bound);

                    mp_exp_t exponent = 0;
                    char* temp = nullptr;

                    temp = mpf_get_str(NULL, &exponent, 10, 0, low_bound);
                    if(mpf_cmp(low_bound, zero) < 0)
                    {
                        exponent -= strlen(temp) - 1;
                    }
                    else
                    {
                        exponent -= strlen(temp);
                    }
                    
                    low_bound_s = format("{}e{}", temp, exponent);
                    low_bound_c = low_bound_s.c_str();

                    free(temp);

                    temp = mpf_get_str(NULL, &exponent, 10, 0, sum_bound);
                    exponent -= strlen(temp);
                    sum_bound_s = format("{}e{}", temp, exponent);
                    sum_bound_c = sum_bound_s.c_str();

                    free(temp);

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
                        arg_arr[i][1] = (void*)sum_bound_c;
                        arg_arr[i][2] = (void*)low_bound_c;
                        arg_arr[i][3] = (void*)(start_point + i);
                        arg_arr[i][4] = (void*)(end_point + i);
                        arg_arr[i][5] = (void*)&neg;

                        int error = pthread_create(&*(thread_id + i), NULL, uniform_random_threading<T>, (void*) arg_arr[i]);
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
                    mpf_neg(low_bound, low_bound);
                    mpf_add(sum_bound, low_bound, up_bound);
                    mpf_neg(up_bound, up_bound);

                    mp_exp_t exponent = 0;
                    char* temp = nullptr;

                    temp = mpf_get_str(NULL, &exponent, 10, 0, up_bound);
                    exponent -= strlen(temp);
                    low_bound_s = format("{}e{}", temp, exponent);
                    low_bound_c = low_bound_s.c_str();

                    free(temp);

                    temp = mpf_get_str(NULL, &exponent, 10, 0, sum_bound);
                    exponent -= strlen(temp);
                    sum_bound_s = format("{}e{}", temp, exponent);
                    sum_bound_c = sum_bound_s.c_str();

                    free(temp);

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
                        arg_arr[i][1] = (void*)sum_bound_c;
                        arg_arr[i][2] = (void*)low_bound_c;
                        arg_arr[i][3] = (void*)(start_point + i);
                        arg_arr[i][4] = (void*)(end_point + i);
                        arg_arr[i][5] = (void*)&neg;

                        int error = pthread_create(&*(thread_id + i), NULL, uniform_random_threading<T>, (void*) arg_arr[i]);
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

            mpf_clear(low_bound);
            mpf_clear(up_bound);
            mpf_clear(sum_bound);
            mpf_clear(zero);
        }
        else if constexpr (is_same_v<T, scalar_64it> || is_same_v<T, matrix_64it> || is_same_v<T, polynomial_64it>)
        {
            string low_bound_s, sum_bound_s;
            const char* low_bound_c,* sum_bound_c;
            int64_t low_bound, up_bound, sum_bound = 0;
            string_view svl(low);
            from_chars(svl.data(), svl.data() + svl.size(), low_bound);
            string_view svu(up);
            from_chars(svu.data(), svu.data() + svu.size(), up_bound);
            up_bound -= 1;

            bool neg = false;

            if((low_bound < up_bound) && ((low_bound != sum_bound) || (up_bound != sum_bound)))
            {
                if(sum_bound < up_bound)
                {
                    sum_bound = up_bound - low_bound;
                   
                    low_bound_s = format("{}", low_bound);
                    low_bound_c = low_bound_s.c_str();

                    sum_bound_s = format("{}", sum_bound);
                    sum_bound_c = sum_bound_s.c_str();

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
                        arg_arr[i][1] = (void*)sum_bound_c;
                        arg_arr[i][2] = (void*)low_bound_c;
                        arg_arr[i][3] = (void*)(start_point + i);
                        arg_arr[i][4] = (void*)(end_point + i);
                        arg_arr[i][5] = (void*)&neg;

                        int error = pthread_create(&*(thread_id + i), NULL, uniform_random_threading<T>, (void*) arg_arr[i]);
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
                    sum_bound = up_bound - low_bound;
                    up_bound = - up_bound;
                
                    low_bound_s = format("{}", up_bound);
                    low_bound_c = low_bound_s.c_str();

                    sum_bound_s = format("{}", sum_bound);
                    sum_bound_c = sum_bound_s.c_str();

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
                        arg_arr[i][1] = (void*)sum_bound_c;
                        arg_arr[i][2] = (void*)low_bound_c;
                        arg_arr[i][3] = (void*)(start_point + i);
                        arg_arr[i][4] = (void*)(end_point + i);
                        arg_arr[i][5] = (void*)&neg;

                        int error = pthread_create(&*(thread_id + i), NULL, uniform_random_threading<T>, (void*) arg_arr[i]);
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
        }
        else if constexpr (is_same_v<T, scalar_64ft> || is_same_v<T, matrix_64ft> || is_same_v<T, polynomial_64ft>)
        {
            string low_bound_s, sum_bound_s;
            const char* low_bound_c,* sum_bound_c;
            double low_bound, up_bound, sum_bound = 0.0;
            string_view svl(low);
            from_chars(svl.data(), svl.data() + svl.size(), low_bound);
            string_view svu(up);
            from_chars(svu.data(), svu.data() + svu.size(), up_bound);
            
            bool neg = false;

            if((low_bound < up_bound) && ((low_bound != sum_bound) || (up_bound != sum_bound)))
            {
                if(sum_bound < up_bound)
                {
                    sum_bound = up_bound - low_bound;
                   
                    low_bound_s = format("{}", low_bound);
                    low_bound_c = low_bound_s.c_str();

                    sum_bound_s = format("{}", sum_bound);
                    sum_bound_c = sum_bound_s.c_str();

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
                        arg_arr[i][1] = (void*)sum_bound_c;
                        arg_arr[i][2] = (void*)low_bound_c;
                        arg_arr[i][3] = (void*)(start_point + i);
                        arg_arr[i][4] = (void*)(end_point + i);
                        arg_arr[i][5] = (void*)&neg;

                        int error = pthread_create(&*(thread_id + i), NULL, uniform_random_threading<T>, (void*) arg_arr[i]);
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
                    sum_bound = up_bound - low_bound;
                    up_bound = - up_bound;
                
                    low_bound_s = format("{}", up_bound);
                    low_bound_c = low_bound_s.c_str();

                    sum_bound_s = format("{}", sum_bound);
                    sum_bound_c = sum_bound_s.c_str();

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
                        arg_arr[i][1] = (void*)sum_bound_c;
                        arg_arr[i][2] = (void*)low_bound_c;
                        arg_arr[i][3] = (void*)(start_point + i);
                        arg_arr[i][4] = (void*)(end_point + i);
                        arg_arr[i][5] = (void*)&neg;

                        int error = pthread_create(&*(thread_id + i), NULL, uniform_random_threading<T>, (void*) arg_arr[i]);
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
        }
        else
        {
            debug::print_error((char*)"util", (char*)"uniform_random_mt", 0, (char*)"non exist struct");
            debug::print_error_specific((char*)"given struct is not defined");
            exit(-1);
        }
    }
}

// matrix_zt* util::stack_vertical(matrix_zt* obj1, matrix_zt* obj2)
// {
//     if(obj1 == nullptr || obj2 == nullptr)
//     {
//         debug::print_error((char*)"util", (char*)"stack_vertical", 0, (char*)"reference nullptr");
//         debug::print_error_specific((char*)"function attribution is nullptr");
//         exit(-1);
//     }
//     else
//     {
//         mpz_t* matrix_1= obj1->return_matrix();
//         uint64_t row_1 = *(obj1->return_size());
//         uint64_t col_1 = *(obj1->return_size() + 1);

//         mpz_t* matrix_2 = obj2->return_matrix();
//         uint64_t row_2 = *(obj2->return_size());
//         uint64_t col_2 = *(obj2->return_size() + 1);
    
//         if(col_1 != col_2)
//         {
//             debug::print_error((char*)"util", (char*)"stack_vertical", 0, (char*)"size unmatched");
//             debug::print_error_specific((char*)"obj1 matrix and obj2 matrix column size unmatched");
//             exit(-1);
//         }
//         else
//         {
//             matrix_zt* new_matrix_struct = new matrix_zt((row_1 + row_2), col_1);
//             mpz_t* new_matrix = new_matrix_struct->return_matrix();
//             uint64_t col = *(new_matrix_struct->return_size() + 1);

//             for(uint64_t i = 0; i < row_1; i++)
//             {
//                 for(uint64_t j = 0; j < col; j++)
//                 {
//                     mpz_set(*(new_matrix + col * i + j), *(matrix_1 + col_1 * i + j));
//                 }
//             }
//             for(uint64_t i = 0; i < row_2; i++)
//             {
//                 for(uint64_t j = 0; j < col; j++)
//                 {
//                     mpz_set(*(new_matrix + col * i + j), *(matrix_2 + col_2 * i + j));
//                 }
//             }
            
//             return new_matrix_struct;
//         }
//     }
// }

// matrix_zt* util::stack_horizon(matrix_zt* obj1, matrix_zt* obj2)
// {
//     if(obj1 == nullptr || obj2 == nullptr)
//     {
//         debug::print_error((char*)"util", (char*)"stack_horizon", 0, (char*)"reference nullptr");
//         debug::print_error_specific((char*)"function attribution is nullptr");
//         exit(-1);
//     }
//     else
//     {
//         mpz_t* matrix_1= obj1->return_matrix();
//         uint64_t row_1 = *(obj1->return_size());
//         uint64_t col_1 = *(obj1->return_size() + 1);

//         mpz_t* matrix_2 = obj2->return_matrix();
//         uint64_t row_2 = *(obj2->return_size());
//         uint64_t col_2 = *(obj2->return_size() + 1);
    
//         if(row_1 != row_2)
//         {
//             debug::print_error((char*)"util", (char*)"stack_horizon", 0, (char*)"size unmatched");
//             debug::print_error_specific((char*)"obj1 matrix and obj2 matrix row size unmatched");
//             exit(-1);
//         }
//         else
//         {
//             matrix_zt* new_matrix_struct = new matrix_zt(row_1, (col_1 + col_2));
//             mpz_t* new_matrix = new_matrix_struct->return_matrix();
//             uint64_t col = *(new_matrix_struct->return_size() + 1);

//             for(uint64_t i = 0; i < row_1; i++)
//             {
//                 for(uint64_t j = 0; j < col_1; j++)
//                 {
//                     mpz_set(*(new_matrix + col * i + j), *(matrix_1 + col_1 * i + j));
//                 }
//                 for(uint64_t j = col_1; j < col_2; j++)
//                 {
//                     mpz_set(*(new_matrix + col * i + j), *(matrix_2 + col_2 * i + j));
//                 }
//             }
            
//             return new_matrix_struct;
//         }
//     }
// }

// polynomial_zt* util::stack_horizon(polynomial_zt* obj1, polynomial_zt* obj2)
// {
//     if(obj1 == nullptr || obj2 == nullptr)
//     {
//         debug::print_error((char*)"util", (char*)"stack_horizon", 1, (char*)"reference nullptr");
//         debug::print_error_specific((char*)"function attribution is nullptr");
//         exit(-1);
//     }
//     else
//     {
//         mpz_t* polynomial_1= obj1->return_polynomial();
//         uint64_t order_1 = *(obj1->return_size() + 1);

//         mpz_t* polynomial_2 = obj2->return_polynomial();
//         uint64_t order_2 = *(obj2->return_size() + 1);
    
//         polynomial_zt* new_polynomial_struct = new polynomial_zt((order_1 + order_2));
//         mpz_t* new_polynomial = new_polynomial_struct->return_polynomial();

//         for(uint64_t i = 0; i < order_1; i++)
//         {
//             mpz_set(*(new_polynomial + i), *(polynomial_1 + i));
//         }
//         for(uint64_t i = order_1; i < order_2; i++)
//         {
//             mpz_set(*(new_polynomial + i), *(polynomial_2 + i));
//         }
            
//         return new_polynomial_struct;
//     }
// }