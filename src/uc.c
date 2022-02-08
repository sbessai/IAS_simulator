/**
 * @file io.c
 * @author sofiane bessaï
 * @brief source of control unit module.
 */

#include "../include/uc.h"

#include "../include/iastype.h"
#include "../include/ual.h"
#include "../include/io.h"
#include "../include/memory.h"

#include <stdio.h>
#include <stdlib.h>

static __uint12_t PC;
static __uint12_t MAR;
static __uint8_t IR;
static __uint20_t IBR;

void PC_reset() {
    PC.value = 0;
}

void PC_increment() {
    PC.value++;
}

void MAR_reset() {
    MAR.value = 0;
}

void IR_reset() {
    IR = 0;
}

void IBR_reset() {
    IBR.value = 0;
}

__uint12_t PC_read() {
    return PC;
}

void PC_write(__uint12_t data) {
    PC.value = data.value;
}

__uint12_t MAR_read() {
    return MAR;
}

void MAR_write(__uint12_t data) {
    MAR.value = data.value;
}

__uint8_t IR_read() {
    return IR;
}

void IR_write(__uint8_t data) {
    IR = data;
}

__uint8_t IBR_read_opcode() {
    union word_u separator;

    separator.right_instruction = IBR.value;

    return separator.right_opcode;
}

__uint12_t IBR_read_address() { 
    union word_u separator;
    __uint12_t tmp_address;

    separator.right_instruction = IBR.value;

    tmp_address.value = separator.right_address;

    return tmp_address;
}

__uint20_t IBR_read() {
    return IBR;
}

void IBR_write(__uint20_t data) {
    IBR.value = data.value;
}

static void load_data() {
    MBR_write(main_memory_read(MAR_read()));
}

static void save_data(__int40_t data) {
    union word_u tmp_data;

    tmp_data.number = data.value;

    main_memory_write(MAR_read(), tmp_data);
}

static void jump(int side) {

    PC_write(MAR_read());

    //left jump
    if(!side) {
        IBR_reset();
    }
    //right jump
    else {
        load_data();
        IR_write(MBR_read_opcode(1));
		MAR_write(MBR_read_address(1));
    }
}

static void address_modify(int side) {
    union word_u separator;
    __int40_t data;

    load_data();

    separator.number = MBR_read().value;

    if(!side) {
        separator.left_address = AC_read_address(side).value;
    }
    else {
        separator.right_address = AC_read_address(side).value;
    }

    data.value = separator.number;

    save_data(data);
}

void control_unit(__uint8_t opcode) {

    switch (opcode) {

        case 33:    /* STOR M(X) */
            save_data(AC_read());
            break;

        case 13:    /* JUMP M(X,0:19) */
            jump(0);
            break;

        case 14:    /* JUMP M(X,20:39) */
            jump(1);
            break;

        case 15:    /* JUMP+ M(X,0:19) */
            if(AC_read().value >= 0)
                jump(0);
            break;

        case 16:    /* JUMP+ M(X,20:39) */
            if(AC_read().value >= 0)
                jump(1);
            break;
    
        case 9:     /* LOAD MQ,M(X) */
        case 1:     /* LOAD M(X) */
        case 2:     /* LOAD –M(X) */
        case 3:     /* LOAD |M(X)| */
        case 4:     /* LOAD –|M(X)| */

        case 5:     /* ADD M(X) */
        case 7:     /* ADD |M(X)| */
        case 6:     /* SUB M(X) */
        case 8:     /* SUB |M(X)| */
        case 11:    /* MUL M(X) */
        case 12:	/* DIV M(X) */
            load_data();
            arithmetic_and_logic_unit(opcode);
            break;
        
        case 10:    /* LOAD MQ */
		case 20:	/* LSH */
        case 21:	/* RSH */
            arithmetic_and_logic_unit(opcode);
            break;

        case 22:    /* STOR M(X,8:19) */
            address_modify(0);
            break;

        case 23:    /* STOR M(X,28:39) */
            address_modify(1);
            break;

        case 0:     /* NOOP */
            break;

        case 42:    /* EXIT */
            printf("Programme terminated\n\n");
            print_main_memory();
            exit(EXIT_SUCCESS);
            break;
        
        default:
            fprintf(stderr, "\033[31m" "error : " "\033[0m" "unrecognized opcode %d\n", opcode);
            exit(EXIT_FAILURE);
            break;
    }
}