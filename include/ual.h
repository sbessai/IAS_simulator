/**
 * @file ual.h
 * @author sofiane bessaï
 * @brief This file contain UAL function and some accessors to the registers in UAL sector.
 */

#ifndef UAL_H
#define UAL_H

#include "../include/iastype.h"

/**
 * @brief Put AC value to 0
 */
void AC_reset();

/**
 * @brief  Put AC value to 0
 */
void MQ_reset();

/**
 * @brief Put MBR value to 0
 */
void MBR_reset();

/**
 * @brief return the value of AC on 40 bits
 * 
 * @return __int40_t value of AC
 */
__int40_t AC_read();

/**
 * @brief return address in AC on 12 bits it depends on the value of side (STOR instruction)
 * 
 * @param side 0 left, 1 right
 * @return __uint12_t address
 */
__uint12_t AC_read_address(int side);

/**
 * @brief Modify the value of the AC register
 * 
 * @param data data to write
 */
void AC_write(__int40_t data);

/**
 * @brief return the value of MQ on 40 bits
 * 
 * @return __int40_t value of MQ
 */
__int40_t MQ_read();

/**
 * @brief Modify the value of the MQ register.
 * 
 * @param data data to write.
 */
void MQ_write(__int40_t data);

/**
 * @brief return opcode in MBR on 8 bits, it depends on the value of side.
 * 
 * @param side 0 left, 1 right
 * @return __uint8_t opcode readed.
 */
__uint8_t MBR_read_opcode(int side);

/**
 * @brief return address in MBR on 12 bits, it depends on the value of side.
 * 
 * @param side 0 left, 1 right.
 * @return __uint12_t address readed.
 */
__uint12_t MBR_read_address(int side);

/**
 * @brief return instruction in MBR on 20 bits it depends on the value of side
 * 
 * @param side 0 left, 1 right
 * @return __uint20_t instruction readed.
 */
__uint20_t MBR_read_instruction(int side);

/**
 * @brief return the value of MQ on 40 bits
 * 
 * @return __int40_t value of MBR.
 */
__int40_t MBR_read();

/**
 * @brief Modify the value of the MBR register.
 * 
 * @param data data to write
 */
void MBR_write(__int40_t data);

/**
 * @brief Main function of this module execute the defined instruction.
 * 
 * @param opcode opcode of the current instruction
 */
void arithmetic_and_logic_unit(__uint8_t opcode);

#endif