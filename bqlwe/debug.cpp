#include "debug.h"
using namespace std;

const bool error_switch = true;
const bool runtime_switch = true;
const bool thread_switch = true;

void debug::print_error(char* class_name, char* func_name, uint64_t over_ride, char* summary)
{
    if(error_switch)
    {
        cout << "[class : " << class_name << ", func : "<< func_name << "(override : " << over_ride <<"), error : "<< summary << "]" << endl;
    }
}

void debug::print_error_specific(char* text)
{
    if(error_switch)
    {
        cout << "[specific : "<< text << "]" << endl;
    }
}

void debug::print_runtime(char* class_name, char* func_name, bool stack)
{
    static auto start = chrono::steady_clock::now();
    static auto end = chrono::steady_clock::now();
    static auto duration_ns = chrono::duration_cast<chrono::nanoseconds>(end - start);
    static auto duration_us = chrono::duration_cast<chrono::microseconds>(end - start);
    static auto duration_ms = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    switch(stack)
    {
        case false:
        {
            start = chrono::steady_clock::now();
            break;
        }
        default:
        {
            end = chrono::steady_clock::now();
            duration_ns = chrono::duration_cast<chrono::nanoseconds>(end - start);
            duration_us = chrono::duration_cast<chrono::microseconds>(end - start);
            duration_ms = chrono::duration_cast<chrono::milliseconds>(end - start);
            if(runtime_switch)
            {
                cout << "[class : " << class_name << ", func : "<< func_name <<", running time : ";
                cout << duration_ns.count() << "ns" << " | ";
                cout << duration_us.count() << "us" << " | ";
                cout << duration_ms.count() << "ms" << "]" << endl;
            }
            break;
        }
    }
}

void debug::print_thread_info(char* class_name, char* func_name, uint64_t over_ride, uint64_t thread_number)
{
    if(thread_switch)
    {
        cout << "[class : " << class_name << ", func : "<< func_name << "(override : " << over_ride <<"), using thread number : "<< thread_number << "]" << endl;
    }
}