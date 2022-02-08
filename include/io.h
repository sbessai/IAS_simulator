/**
 * @file io.h
 * @author sofiane bessaï
 * @brief This file some print functions.
 */

#ifndef IO_H
#define IO_H

#include "../include/translator.h"

/**
 * @brief Print translated program this is a Control function.
 * 
 * @param program The program translated.
 */
void print_translated_program(struct __program *program);

/**
 * @brief Print element of main memory =/= 0.
 *        (used at the end of the program).
 */
void print_main_memory();

/**
 * @brief Print all register value at t instant.
 */
void print_all_register();

#endif