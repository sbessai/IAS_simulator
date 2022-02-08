/**
 * @file iastype.h
 * @author sofiane bessaï
 * @brief This file contains new types of data for the simulator
 */

#ifndef IASTYPE_H
#define IASTYPE_H

#include <stdio.h> // __uint128_t __uint64_t __uint32_t __uint16_t

/**
 * @brief A structure to represente a word in my architecture.
 *        64 bits declared but 40 bits used (using bits field).
 */
typedef struct{
	__int64_t value : 40;
}__int40_t;

/**
 * @brief A structure to represente an instruction in my architecture.
 *        32 bits declared but 20 bits used (using bits field).
 */
typedef struct {
	__uint32_t value : 20;
}__uint20_t;

/**
 * @brief A structure to represente an address in my architecture.
 *        16 bits declared but 12 bits used (using bits field).
 */
typedef struct{
	__uint16_t value : 12;
}__uint12_t;

/**
 * @brief An union to translate a word to all types of data in my simulator.
 *        A word can be read as :
 * 
 *        - a number
 *        +-+---------------------------------------+
 *        |s|xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx|
 *        +-+---------------------------------------+
 * 
 *        - left_instruction and right_instruction
 *        +--------------------+--------------------+
 *        |xxxxxxxxxxxxxxxxxxxx|xxxxxxxxxxxxxxxxxxxx|
 *        +--------------------+--------------------+
 * 
 *        - left_opcode, left_address and right_opcode, right_address
 *        +--------+------------+---------+-----------+
 *        |xxxxxxxx|xxxxxxxxxxxx|xxxxxxxxx|xxxxxxxxxxx|
 *        +--------+------------+---------+-----------+
 */
union word_u {
    struct{
        __uint64_t right_instruction : 20;
        __uint64_t left_instruction : 20;
    };
    struct{
        __uint64_t right_address : 12;
        __uint64_t right_opcode : 8;
        __uint64_t left_address : 12;
        __uint64_t left_opcode : 8;
    };
    __int64_t number : 40;
};

/**
 * @brief Temporary union to help pseudo-multiplication implemented
 */
union double_word_u {
    struct {
        __uint128_t lsb : 40;
        __uint128_t msb : 40;
    };
    __uint128_t number : 80;
};

#endif