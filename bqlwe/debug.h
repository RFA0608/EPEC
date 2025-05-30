#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <chrono>

class debug
{
    public:
        static void print_error(char* class_name, char* func_name, uint64_t over_ride, char* summary);
        static void print_error_specific(char* text);
        static void print_runtime(char* class_name, char* func_name, bool stack);
        static void print_thread_info(char* class_name, char* func_name, uint64_t over_ride, uint64_t thread_number);
};

#endif