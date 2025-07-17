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

        template <typename T>
        static void print_struct_meta(T* obj);

        template <typename T>
        static T* copy(T* obj);

        template <typename T>
        static void clear(T** obj);

        // =================================================================================== //

        template <typename T>
        static void set_entry(T* obj, char* value, uint64_t pos_row = 1, uint64_t pos_col = 1);

        template <typename T, typename K>
        static T* fetch(K* out_obj, uint64_t num_row = 1, uint64_t num_col = 1);

        template <typename T>
        static void generate_file_struct(char* file_name);

        template <typename T>
        static T* fetch_from_file(char* file_name);

        // =================================================================================== //

        static void set_random_seed(unsigned long T);
        static void clear_random_seed();

        // if up > 0 : low <= entry < up, else up < 0 : low < entry <= up
        // can using multi threading(in this function doesn't exist improve)
        template <typename T>
        static void uniform_random(T* obj, char* low, char* up);

        template <typename T>
        static void uniform_random_mt(T* obj, char* low, char* up);

        template <typename T>
        static void gaussian_random(T* obj, char* mean, char* std);

        template <typename T>
        static void gaussian_random_mt(T* obj, char* mean, char* std);

        // =================================================================================== //
        
        // only for matrix type
        template <typename T>
        static T* stack_vertical(T* obj1, T* obj2);

        template <typename T>
        static T* stack_horizon(T* obj1, T* obj2);

        // =================================================================================== //

        polynomial_zt* NTT_pack(matrix_zt* matrix);

        matrix_zt* NTT_unpack(polynomial_zt* polynomial);

        // =================================================================================== //

        polynomial_zt* COE_pack(matrix_zt* matrix);

        matrix_zt* COE_unpack(polynomial_zt* polynomial);
};

#include "util.tpp"

#endif