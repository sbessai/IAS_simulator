/**
 * @file io.c
 * @author sofiane bessaï
 * @brief source of main memory module.
 */

#include "../include/memory.h"
#include "../include/iastype.h"
#include "../include/macro.h"

#include <stdlib.h>

static __int40_t main_memory[MAIN_MEMORY_SIZE]; /* The main memory */

void main_memory_reset() {
    for (unsigned int i = 0 ; i < MAIN_MEMORY_SIZE; i++) {
        main_memory[i].value = 0;
    }
}

__int40_t main_memory_read(__uint12_t address) {
    address_interval_ctl(address);  //USELESS ERR_CTL
    return main_memory[address.value];
}

void main_memory_write(__uint12_t address, union word_u data) {
    address_interval_ctl(address);  //USELESS ERR_CTL
    main_memory[address.value].value = data.number;
}