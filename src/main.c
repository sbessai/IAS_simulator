/**
 * @file main.c
 * @author sofiane bessaï
 * @brief 
 */

#include "../include/iastype.h"

#include "../include/memory.h"
#include "../include/ual.h"
#include "../include/uc.h"
#include "../include/io.h"

#include "../include/translator.h"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h> // Parsing command-line argument(s)

static void print_help();
static void interrupt();

int main(int argc, char *argv[]) {

	// ** Declaration **
	FILE *input_stream = NULL;
    char *input_file_path = NULL;

	struct __program *program;

	const char *short_options = "hnom:";
	
	static const struct option long_options[] = {
		{"help", no_argument, NULL, 'h'},
		{"no-debug", no_argument, NULL, 'n'},
		{"output-to-file", no_argument, NULL, 'o'},
		{"max-cycle", required_argument, NULL, 'm'},
		{NULL, 0, NULL, 0}
	};

    int current_option;

	int debug = 1;
	int output_to_file = 0;
	int max_cycle = 1000;
	int cycle = 0;

	int exit_instruction = 0;

	// **

    // Arguments parsing
    while( (current_option = getopt_long(argc, argv, short_options, long_options, NULL )) != -1) {
 
		switch(current_option)
		{	
            case 'h':
                print_help();
                exit(EXIT_SUCCESS);
			break;

			case 'n':
                debug = 0;
			break;

			case 'o':
                output_to_file = 1;
			break;

			case 'm':
                max_cycle = atoi(optarg);
			break;

			case '?':	// Unrecognized option
                print_help();
                exit(EXIT_FAILURE);
			break;
		}
	}

	// Init

	// PC = 0
	PC_reset();
	// MAR = 0
	MAR_reset();
	// MBR = 0
	MBR_reset();
	// IR = 0
	IR_reset();
	// IBR = 0
	IBR_reset();
	// AC = 0
	AC_reset();
	// MQ = 0
	MQ_reset();
	// Main Memory = {0}
	main_memory_reset();

    // Load program
	if(optind >= argc) {
        fprintf(stderr, "\033[31m" "fatal error : " "\033[0m" "no input file\n");
        exit(EXIT_FAILURE);
    }
    else {
        input_file_path = argv[optind];
    }

	printf("Open file : %s\n", input_file_path);

	// Open input file
	input_stream = fopen(input_file_path, "r");
	if(input_stream == NULL) { //ERR_CTL
        perror("\033[31m" "error : " "\033[0m");
        exit(EXIT_FAILURE);
    }

	// Translate program
	program = translate_program(input_stream);

	// Free pointer to input file
	fclose(input_stream);

	// Print translated program (output control)
	print_translated_program(program);

	// Verify exit instruction is in program
	for(int i=0 ; i<program->nb_data ; i++) {
		if(program->data[i]->id == 1) {
			if(program->data[i]->word.left_opcode == 42 || program->data[i]->word.right_opcode == 42)
				exit_instruction = 1;
		}
	}

	// If no exit instruction 
	if(!exit_instruction) {
		printf("\033[35m" "warning :" "\033[0m" " no exit instruction in program\n");
	}

	// Load program translated in Main Memory
	for(int i=0 ; i<program->nb_data ; i++) {
		main_memory_write(program->data[i]->main_memory_address, program->data[i]->word);
	}

	// Free struct __program->__data[i]
	for(int i=0 ; i<program->nb_data ; i++) {
		if(program->data[i] != NULL)
			free(program->data[i]);
	}

	// Free struct __program->__data
	free(program->data);
	
	// Free program
	free(program);

	// ** Main code **

	while ( cycle < max_cycle ) {

		if( IBR_read().value == 0 ) {

			// Send PC value to MAR
			MAR_write(PC_read());

			// Use address in MAR to load next instruction in Main Memory
			// Send word from Maim Memory to MBR
			MBR_write(main_memory_read(MAR_read()));

			// left instruction
			if(MBR_read_instruction(0).value != 0) {

				// Put right instruction into IBR
				IBR_write(MBR_read_instruction(1));

				// Put left opcode into IR
				IR_write(MBR_read_opcode(0));

				// Put left address into MAR
				MAR_write(MBR_read_address(0));

				// Increment PC if right instruction is NOOP
				if(IBR_read().value == 0) {
					// increment PC by 1
					PC_increment();
				}
			}
			// right instruction
			else {

				// Put left opcode from MBR into IR
				IR_write(MBR_read_opcode(1));

				// Put left address from MBR into MAR
				MAR_write(MBR_read_address(1));

				// IBR reset
				IBR_reset();
			
				// increment PC by 1
				PC_increment();
			}
		
		}
		else {

			// Put left opcode from IBR into IR
			IR_write(IBR_read_opcode());

			// Put left address from IBR into MAR
			MAR_write(IBR_read_address());

			// IBR reset
			IBR_reset();
			
			// increment PC by 1
			PC_increment();
		}

		if(debug) {
			printf("Instruction loaded\n");
			print_all_register();
			print_main_memory();
		}

		if(!output_to_file)
			interrupt();

		// Execute instruction in IR
		control_unit(IR_read());

		if(debug) {
			printf("Instruction executed\n");
			print_all_register();
			print_main_memory();
		}

		if(!output_to_file)
			interrupt();

		cycle++;
	}

	// **

    printf("\033[35m" "warning :" "\033[0m" " max number of cycle reached (%d)\n", max_cycle);

	return 0;
}
 
void print_help() {
    printf("##################### HELP #####################\n"
           "-h, --help : to have information on all the options available.\n"
		   "-n, --no-debug : to not show the register at each step of execution.\n"
		   "-o, --output-to-file : to block the interrupt func.\n"
		   "-m, --max-cycle : with a number in arg to specify how many cycles is the limit before the simulation stop (by default 1000).\n"
           "################################################\n");
}

static void interrupt() {
	printf("Press ENTER key to Continue\n");  
	getchar();
}