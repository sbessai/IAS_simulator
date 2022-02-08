/**
 * @file uc.h
 * @author sofiane bessaï
 * @brief This file contain UC function and some accessors to the registers in UC sector.
 */

#ifndef UC_H
#define UC_H

#include "../include/iastype.h"

/**
 * @brief Put PC value to 0
 */
void PC_reset();

/**
 * @brief increment PC value by 1.
 */
void PC_increment();

/**
 * @brief Put MAR value to 0
 */
void MAR_reset();

/**
 * @brief Put IR value to 0
 */
void IR_reset();

/**
 * @brief Put IBR value to 0
 */
void IBR_reset();

/**
 * @brief return the value of PC on 12 bits
 * 
 * @return __uint12_t value of PC
 */
__uint12_t PC_read();

/**
 * @brief Modify the value of the PC register
 * 
 * @param address new address for PC
 */
void PC_write(__uint12_t address);

/**
 * @brief return the value of MAR on 12 bits
 * 
 * @return __uint12_t value of MAR
 */
__uint12_t MAR_read();

/**
 * @brief Modify the value of the MAR register
 * 
 * @param address new address for MAR
 */
void MAR_write(__uint12_t address);

/**
 * @brief return the value of IR on 8 bits
 * 
 * @return __uint8_t value of IR
 */
__uint8_t IR_read();

/**
 * @brief Modify the value of the IR register
 * 
 * @param opcode opcode of current instruction
 */
void IR_write(__uint8_t opcode);

/**
 * @brief return the opcode value on IBR on 8 bits
 * 
 * @return __uint8_t opcode in IBR
 */
__uint8_t IBR_read_opcode();

/**
 * @brief return the address value on IBR on 12 bits
 * 
 * @return __uint12_t address in IBR
 */
__uint12_t IBR_read_address();

/**
 * @brief return the value of IBR on 20 bits
 * 
 * @return __uint20_t value of IBR
 */
__uint20_t IBR_read();

/**
 * @brief Modify the value of the IBR register
 * 
 * @param instruction instruction to store
 */
void IBR_write(__uint20_t instruction);

/**
 * @brief Main function of this module.
 *        Do jump, modify data in main memory.
 *        And if opcode is an arithmetic instruction call UAL with opcode
 * 
 * @param opcode opcode of the current instruction
 */
void control_unit(__uint8_t opcode);

#endif