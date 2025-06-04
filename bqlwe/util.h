#ifndef UTIL_H
#define UTIL_H

#include <format>
#include <string>
#include <iostream>
#include <iomanip>
#include <type_traits>
#include <charconv>
#include <ctime>
#include <pthread.h>
#include <thread>
#include <random>
#include <cstdlib>
#include <cmath>
#include <gmpxx.h>
#include "struct.h"

class util
{
    public:
        template <typename T>
        static void print_struct(T* obj);

        //-----------------------------------------//

        template <typename T>
        static void print_struct_meta(T* obj);

        //-----------------------------------------//

        template <typename T>
        static T* copy(T* obj);

        //-----------------------------------------//

        template <typename T>
        static void clear(T** obj);

        // =================================================================================== //

        void set_entry(scalar_zt* obj, char* value);
        void set_entry(matrix_zt* obj, char* value, uint64_t pos_row, uint64_t pos_col);
        void set_entry(matrix_zt* obj, scalar_zt* value, uint64_t pos_row, uint64_t pos_col);
        void set_entry(polynomial_zt* obj, char* value, uint64_t pos);
        void set_entry(polynomial_zt* obj, scalar_zt* value, uint64_t pos);

        // 아래는 통짜 배열을 넣는 데 이용하는 함수(미구현)
        void fetch_entry(scalar_zt* obj);
        void fetch_entry(matrix_zt* obj);
        void fetch_entry(polynomial_zt* obj);

        // =================================================================================== //

        static void set_random_seed(unsigned long T);
        static void clear_random_seed();

        //-----------------------------------------//

        // if up > 0 : low <= entry < up, else up < 0 : low < entry <= up
        // can using multi threading(in this function doesn't exist improve)
        template <typename T>
        static void uniform_random(T* obj, char* low, char* up);

        template <typename T>
        static void uniform_random_mt(T* obj, char* low, char* up);

        //-----------------------------------------//

        template <typename T>
        static void gaussian_random(T* obj, char* mean, char* std);

        template <typename T>
        static void gaussian_random_mt(T* obj, char* mean, char* std);

        // =================================================================================== //

        matrix_zt* stack_vertical(matrix_zt* obj1, matrix_zt* obj2);

        matrix_zt* stack_horizon(matrix_zt* obj1, matrix_zt* obj2);
        polynomial_zt* stack_horizon(polynomial_zt* obj1, polynomial_zt* obj2);

        // =================================================================================== //

        polynomial_zt* NTT_pack(matrix_zt* matrix);

        matrix_zt* NTT_unpack(polynomial_zt* polynomial);

        // =================================================================================== //

        polynomial_zt* COE_pack(matrix_zt* matrix);

        matrix_zt* COE_unpack(polynomial_zt* polynomial);
};

#include "util.tpp"

#endif