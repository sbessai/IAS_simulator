/**
 * @file translator.h
 * @author sofiane bessaï
 * @brief This file contain translate function and translated program structure.
 */

#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "../include/iastype.h"

#include <stdio.h>

/**
 * @brief Represent a data in translated program.
 * 
 * - id : 0 it's data, 1 it's instructions.
 * 
 * - main_memory_address : The targeted address.
 * 
 * - word : The data to put in main memory.
 * 
 */
struct __data{
    int id;
    __uint12_t main_memory_address;
    union word_u word;
};

/**
 * @brief Represent a translated program.
 * 
 * - nb_data : Number of data in program.
 * 
 * - data : Array of data in the program.
 * 
 */
struct __program{
    int nb_data;
    struct __data **data;
};

/**
 * @brief 
 * 
 * @return struct __program* 
 */
struct __program *translate_program(FILE *);

#endif