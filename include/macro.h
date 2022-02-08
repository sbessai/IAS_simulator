/**
 * @file macro.h
 * @author sofiane bessaï
 * @brief This file contain some defined macros.
 */

#ifndef MACRO_H
#define MACRO_H

/**
 * @brief Verify the id variable is not NULL
 *        else print error message and quit the program.
 * 
 * @param id the variable to test.
 */
#define alloc_ctrl(id)                            \
    if( (id) == NULL ) {                          \
        perror("\033[31m" "error : " "\033[0m");  \
        exit(EXIT_FAILURE);                       \
    }

/**
 * @brief Verify the id variable is not NULL
 *        else print error message.
 * 
 * @param id the variable to test.
 * @param func_name the function concerned.
 */
#define check_ptr(id, func_name)                                                                \
    if( (id) == NULL ) {                                                                        \
        fprintf(stderr, "\033[31m" "error : " "\033[0m" "NULL ptr in %s\n", (func_name));       \
    }

/**
 * @brief Test if an address is between 0 and 4095 (main memory address set).
 * 
 * @param a address tested.
 */
#define address_interval_ctl(a)                                                     \
    if( (a).value < 0 || (a).value > MAIN_MEMORY_SIZE ) {                           \
        fprintf(stderr, "\033[31m" "error : " "\033[0m" "address out of bound\n");  \
        exit(EXIT_FAILURE);                                                         \
    }

/**
 * @brief print 40 bits of the variables.
 * 
 * @param x the variable to print.
 */
#define print_int40_t(x)                                                \
    do {                                                                \
        unsigned long long tmp_x = (x);                                 \
        int bits_c = 40;                                                \
        while (bits_c--) putchar(tmp_x &(1ULL << bits_c) ? '1' : '0');  \
    }                                                                   \
    while(0);

/**
 * @brief print 20 bits of the variables.
 * 
 * @param x the variable to print.
 */
#define print_int20_t(x)                                                \
    do {                                                                \
        unsigned long tmp_x = (x);                                      \
        int bits_c = 20;                                                \
        while (bits_c--) putchar(tmp_x &(1ULL << bits_c) ? '1' : '0');  \
    }                                                                   \
    while(0);

/**
 * @brief print 12 bits of the variables.
 * 
 * @param x the variable to print.
 */
#define print_int12_t(x)                                                \
    do {                                                                \
        unsigned int tmp_x = (x);                                       \
        int bits_c = 12;                                                \
        while (bits_c--) putchar(tmp_x &(1ULL << bits_c) ? '1' : '0');  \
    }                                                                   \
    while(0);

/**
 * @brief print 8 bits of the variables.
 * 
 * @param x the variable to print.
 */
#define print_int8_t(x)                                                 \
    do {                                                                \
        unsigned int tmp_x = (x);                                       \
        int bits_c = 8;                                                 \
        while (bits_c--) putchar(tmp_x &(1ULL << bits_c) ? '1' : '0');  \
    }                                                                   \
    while(0);

#endif