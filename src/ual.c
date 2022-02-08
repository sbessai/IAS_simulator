/**
 * @file io.c
 * @author sofiane bessaï
 * @brief source of arithmetic and logic unit module.
 */

#include "../include/ual.h"

#include "../include/iastype.h"
#include "../include/macro.h"

#include <stdio.h>
#include <stdlib.h>

static __int40_t AC;
static __int40_t MQ;
static union word_u MBR;

void AC_reset() {
    AC.value = 0;
}

void MQ_reset() {
    MQ.value = 0;
}

void MBR_reset() {
    MBR.number = 0;
}

void MBR_left_instruction_reset() {
    MBR.left_instruction = 0;
}

__int40_t AC_read() {
    return AC;
}

__uint12_t AC_read_address(int side) {
    union word_u separator;
    __uint12_t tmp_data;

    separator.number = AC_read().value;

    if(!side)
        tmp_data.value =  separator.left_address;
    else
        tmp_data.value =  separator.right_address;

    return tmp_data;
}

void AC_write(__int40_t data) {
    AC.value = data.value;
}

__int40_t MQ_read() {
    return MQ;
}

void MQ_write(__int40_t data) {
    MQ.value = data.value;
}

__uint8_t MBR_read_opcode(int side) {
    if(!side)
        return MBR.left_opcode;
    else
        return MBR.right_opcode;
}

__uint12_t MBR_read_address(int side) {
    __uint12_t tmp_data;

    if(!side) {
        tmp_data.value = MBR.left_address;
        return tmp_data;
    }
    else {
        tmp_data.value = MBR.right_address;
        return tmp_data;
    }
}

__uint20_t MBR_read_instruction(int side) {
    __uint20_t tmp_data;

    if(!side) {
        tmp_data.value = MBR.left_instruction;
        return tmp_data;
    }
    else {
        tmp_data.value = MBR.right_instruction;
        return tmp_data;
    }
}

__int40_t MBR_read() {
    __int40_t tmp_data;

    tmp_data.value = MBR.number;
    return tmp_data;
}

void MBR_write(__int40_t data) {
    MBR.number = data.value;
}

static void load_mq() {
    AC_write(MQ_read());
}

static void load_mq_mx() {
    MQ_write(MBR_read());
}

static void load_mx() {
    AC_write(MBR_read());
}

static void load_sub_mx() {
    __int40_t data = MBR_read();

    data.value = -data.value;

    AC_write(data);
}

static void load_abs_mx() {
    __int40_t data = MBR_read();

    data.value = abs(data.value);

    AC_write(data);
}

static void load_sub_abs_mx() {
    __int40_t data = MBR_read();

    data.value = -abs(data.value);

    AC_write(data);
}

static void add() {
    __int40_t data = MBR_read();
    __int40_t ac_value = AC_read();

    ac_value.value += data.value;

    AC_write(ac_value);
}

static void add_abs() {
    __int40_t data = MBR_read();
    __int40_t ac_value = AC_read();

    ac_value.value += abs(data.value);

    AC_write(ac_value);
}

static void sub() {
    __int40_t data = MBR_read();
    __int40_t ac_value = AC_read();

    ac_value.value -= data.value;

    AC_write(ac_value);
}

static void sub_abs() {
    __int40_t data = MBR_read();
    __int40_t ac_value = AC_read();

    ac_value.value -= abs(data.value);

    AC_write(ac_value);
}

/**
 * @brief Need to be modified
 */
static void mul() {
    __int40_t mbr_value = MBR_read();
    __int40_t mq_value = MQ_read();
    __int40_t ac_value;
    union double_word_u dword;
    
    dword.number = 0;

    dword.number = (__int128_t) mbr_value.value * (__int128_t) mq_value.value;

    /*
    printf("dword.number = %lld\n", dword.number);
    printf("dword.msb = %d\n", dword.msb);
    printf("dword.lsb = %d\n", dword.lsb);
    */

    ac_value.value = dword.msb;
    mq_value.value = dword.lsb;

    AC_write(ac_value);
    MQ_write(mq_value);
}

/**
 * @brief Useless prototype of new mul function
 */
static void mul2() {
    __int40_t mbr_value = MBR_read();
    __int40_t mq_value = MQ_read();
    __int40_t ac_value;
    int a_sign;
    int b_sign;

    // Sign calculus
    a_sign = mq_value.value >> 39;
    b_sign = mbr_value.value >> 39;

    // Multiplication    

    AC_write(ac_value);
    MQ_write(mq_value);
}

/**
 * @brief Need to be modified
 */
void divide() {
    __int40_t ac_value = AC_read();
    __int40_t mbr_value = MBR_read();
    
    __int40_t quotient;
    __int40_t rest;

    if(mbr_value.value == 0) {
        fprintf(stderr, "\033[31m" "error : " "\033[0m" "divide by zero\n");
        exit(EXIT_FAILURE);
    }

    quotient.value = ac_value.value / mbr_value.value;
    rest.value = ac_value.value % mbr_value.value;

    AC_write(rest);
    MQ_write(quotient);
}

void shift_left() {
    __int40_t ac_value = AC_read();

    ac_value.value *= 2;

    AC_write(ac_value);
}

void shift_right() {
    __int40_t ac_value = AC_read();

    ac_value.value /= 2;

    AC_write(ac_value);
}

void arithmetic_and_logic_unit(__uint8_t opcode) {
    switch (opcode) {

        case 10:    /* LOAD MQ */
            load_mq();
            break;

        case 9:     /* LOAD MQ,M(X) */
            load_mq_mx();
            break;

        case 1:     /* LOAD M(X) */
            load_mx();
            break;

        case 2:     /* LOAD –M(X) */
            load_sub_mx();
            break;

        case 3:     /* LOAD |M(X)| */
            load_abs_mx();
            break;

        case 4:     /* LOAD –|M(X)| */
            load_sub_abs_mx();
            break;

        case 5:     /* ADD M(X) */
            add();
            break;

        case 7:     /* ADD |M(X)| */
            add_abs();
            break;

        case 6:     /* SUB M(X) */
            sub();
            break;

        case 8:     /* SUB |M(X)| */
            sub_abs();
            break;

        case 11:    /* MUL M(X) */
            mul();
            break;

        case 12:	/* DIV M(X) */
            divide();
            break;

		case 20:	/* LSH */
            shift_left();
            break;

        case 21:	/* RSH */
            shift_right();
            break;
        
        default:
            fprintf(stderr, "\033[31m" "error : " "\033[0m" "unrecognized opcode %d\n", opcode);
            exit(EXIT_FAILURE);
            break;
    }
}