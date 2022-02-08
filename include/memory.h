/**
 * @file memory.h
 * @author sofiane bessaï
 * @brief This file contain accessors for main memory.
 */

#ifndef MEMORY_H
#define MEMORY_H

#include "../include/iastype.h"

#define MAIN_MEMORY_SIZE 4096   /* Size of main memory DO NOT MODIFY THE VALUE */

/**
 * @brief Set all cells of main memory to 0
 */
void main_memory_reset();

/**
 * @brief Return word at address specified in parametre.
 *        Address must be in 0 to 4095.
 * 
 * @param address main memory address
 * @return __int40_t the word at this address
 */
__int40_t main_memory_read(__uint12_t address);

/**
 * @brief Write data at address specified in parametre.
 *        Address must be in 0 to 4095.
 *        Data need to be on 40 bits.
 * 
 * @param address main memory address
 * @param data The word to write.
 */
void main_memory_write(__uint12_t address, union word_u data);

#endif