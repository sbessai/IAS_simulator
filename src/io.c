/**
 * @file io.c
 * @author sofiane bessaï
 * @brief source of io module.
 */

#include "../include/io.h"

#include "../include/translator.h"
#include "../include/memory.h"
#include "../include/ual.h"
#include "../include/uc.h"
#include "../include/macro.h"

void print_translated_program(struct __program *program) {
	printf("\nTRANSLATED PROGRAM OUTPUT\n\n");
    printf("Number of word in program : %d\n\n", program->nb_data);

	printf("--------------------------------------------------------\n"
		   "| MM_address | lopcode | laddress | ropcode | raddress |\n"
		   "--------------------------------------------------------\n");
	for(int i=0 ; i<program->nb_data ; i++)
	if(program->data[i]->id == 1)
		printf("| %10d | %7d | %8d | %7d | %8d |\n",program->data[i]->main_memory_address.value,
								                    program->data[i]->word.left_opcode,
								                    program->data[i]->word.left_address,
								                    program->data[i]->word.right_opcode,
								                    program->data[i]->word.right_address
								                    );

	printf("--------------------------------------------------------\n");

	printf("\n");

	printf("--------------------------------------------------------\n"
		   "| MM_address |                    data                 |\n"
		   "--------------------------------------------------------\n");
	for(int i=0 ; i<program->nb_data ; i++)
	if(program->data[i]->id == 0)
		printf("| %10d | %39d |\n", program->data[i]->main_memory_address.value,
								    program->data[i]->word.number
								    );
	
	printf("--------------------------------------------------------\n\n");
}

void print_main_memory() {
	__uint12_t address;
	__int40_t data;
	union word_u separator;

	printf("+------------+---------------------------------------------+\n"
		   "| MM_address |                     data                    |\n"
		   "+------------+---------------------------------------------+\n");

	for(int i=0 ; i<MAIN_MEMORY_SIZE ; i++) {
		address.value = i;
		data = main_memory_read(address);
		if(data.value) {
			separator.number = data.value;

			printf("| %10d | ", address.value);
			print_int8_t(separator.left_opcode);
			putchar(' ');
			print_int12_t(separator.left_address);
			putchar(' ');
			print_int8_t(separator.right_opcode);
			putchar(' ');
			print_int12_t(separator.right_address);
			printf(" | ");
			printf("(%ld)\n", data.value);
		}
	}

	printf("+------------+---------------------------------------------+\n\n");
}

static void print_AC() {
	printf("AC = ");
	print_int40_t(AC_read().value);
	printf(" (%d)", AC_read().value);
	putchar('\n');
}

static void print_MQ() {
	printf("MQ = ");
	print_int40_t(MQ_read().value);
	printf(" (%d)", MQ_read().value);
	putchar('\n');
}

static void print_MBR() {
	printf("MBR = ");
	print_int8_t(MBR_read_opcode(0));
	putchar(' ');
	print_int12_t(MBR_read_address(0).value);
	putchar(' ');
	print_int8_t(MBR_read_opcode(1));
	putchar(' ');
	print_int12_t(MBR_read_address(1).value);
	printf(" (%d)", MBR_read().value);
	putchar('\n');
}

static void print_PC() {
	printf("PC = ");
	print_int12_t(PC_read().value);
	printf(" (%d)", PC_read().value);
	putchar('\n');
}

static void print_MAR() {
	printf("MAR = ");
	print_int12_t(MAR_read().value);
	printf(" (%d)", MAR_read().value);
	putchar('\n');
}

static void print_IR() {
	printf("IR = ");
	print_int8_t(IR_read());
	printf(" (%d)", IR_read());
	putchar('\n');
}

static void print_IBR() {
	printf("IBR = ");
	print_int20_t(IBR_read().value);
	printf(" (%d)", IBR_read().value);
	putchar('\n');
}

void print_all_register() {
	//printf("\n");
	print_AC();
	print_MQ();
	print_MBR();
	print_PC();
	print_MAR();
	print_IR();
	print_IBR();
	printf("\n");
}