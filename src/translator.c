/**
 * @file io.c
 * @author sofiane bessaï
 * @brief source of assembly ias translator module.
 */

#include "../include/translator.h"

#include "../include/macro.h"
#include "../include/iastype.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * ###################
 * # INSTRUCTION SET #
 * ###################
 * 
 * symbolic representation      opcode      address
 * 
 * LOAD MQ                   	10              0    
 * LOAD MQ,M(X)					9				X
 * STOR M(X)					33				X
 * LOAD M(X)					1				X
 * LOAD -M(X)					2				X
 * LOAD |M(X)|					3				X
 * LOAD -|M(X)|					4				X
 * 
 * JUMP M(X,0:19)				13				X
 * JUMP M(X,20:39)				14				X
 * 
 * JUMP+ M(X,0:19)				15				X
 * JUMP+ M(X,20:39)				16				X
 * 
 * ADD M(X)						5				X
 * ADD |M(X)|					7				X
 * SUB M(X)						6				X
 * SUB |M(X)|					8				X
 * MUL M(X)						11				X
 * DIV M(X)						12				X
 * LSH							20				0
 * RSH							21				0
 * 
 * STOR M(X,8:19)				22				X
 * STOR M(X,28:39)				23				X
 * 
 * NOOP							0				0
 * 
 * EXIT							42				0
 * 
 */

#define NB_COMPOSED_INSTRUCTION 8	/* Number of composed instruction in instruction set */
#define MAX_TOKEN 6					/* Max number of member in an assembly ias program line */
#define ADDRESS_BUFFER_SIZE 5		/* Size of an address buffer */
#define NB_MAX_WORD 4096			/* Max number of words in an assembly ias program */

int line_no = 0; /* the line traited in untranslated program (error information) */

/**
 * @brief Extract an address from second member of instruction
 * 
 * @param second_member The 2nd part of composed instruction
 * @return int the converted address
 */
static int extract_address(char *second_member) {
	char *address_buffer; // address buffer
	char *tmp_ptr; // Copy of second_member ptr
	int len; // second_member length
	int address_buffer_len = 0; // Position in address_buffer
	int address; // Converted address

	// Verify if the second_member is not NULL
	if(second_member == NULL) {
		fprintf(stderr, "\033[31m" "error : " "\033[0m" "invalid member at line %d\n", line_no);
        exit(EXIT_FAILURE);
	}

	// second_member size
	len = strlen(second_member);

	// Modifiying M(xxxx) to M(X)
	tmp_ptr = strstr(second_member, "M(");
	tmp_ptr += 2; // Jump to address begin

	// Alloc an address buffer
	address_buffer = malloc(ADDRESS_BUFFER_SIZE * sizeof(char));
	alloc_ctrl(address_buffer);

	// Copy address in instruction to address_buffer
	while(tmp_ptr[address_buffer_len] >= 48 && tmp_ptr[address_buffer_len] <= 57 && address_buffer_len < ADDRESS_BUFFER_SIZE) {
		address_buffer[address_buffer_len] = tmp_ptr[address_buffer_len];
		address_buffer_len++;
		//tmp_ptr++;
	}

	// Re-normalize the traited instruction
	tmp_ptr[0] = 'X';
	while(tmp_ptr[address_buffer_len-1] != '\0') {
		tmp_ptr[1] = tmp_ptr[address_buffer_len];
		tmp_ptr++;
	}
	tmp_ptr[0] = '\0';

	// Convert address buffer to int
	address = atoi(address_buffer);

	// Cleanup
	free(address_buffer);

	return address;
}

/**
 * @brief Verify if the first member of line is a valid main memory address
 * 
 * @param address the first member
 * @return int 0 it's a valid address else -1
 */
static int is_main_address(char *address) {
	int len;

	// 
	check_ptr(address, "is_main_address");

	len = strlen(address);

	// Too many digit in address
	if(len > 6)
		return -1;

	// Invalid char in address
	for(int i=0 ; i<len ; i++) {
		if(address[i] < 48 || address[i] > 57)
			return -1;
	}

	// Address out of bound
	if(strtoll(address, NULL, 10) > 4095)
		return -1;

	return 0;
}

/**
 * @brief Verify if the token is a data or not.
 * 
 * @param data the token to test
 * @return int 0 it's a data else -1
 */
static int is_data(char *data) {
	int len;
	int begin_char=0;

	// Is the token data not NULL
	check_ptr(data, "is_data");

	len = strlen(data);

	if(data[0] == '-')
		begin_char++;

	// Invalid char in address
	for(int i=begin_char ; i<len ; i++) {
		if(data[i] < '0' || data[i] > '9')
			return -1;
	}

	return 0;
}

/**
 * @brief If the function traited is a pure function, it give his opcode
 * 
 * @param inst1 first member of instruction
 * @param inst2 second member of instruction (in case if it's LOAD)
 * @return int the opcode or -1
 */
static int is_pure_instruction(char *inst1, char *inst2) {

	// Check with symbolic representation
	if(!strcmp(inst1, "LOAD")) {
		if(!strcmp(inst2, "MQ"))
			return 10;			
		else
			return -1;
	}
	else if(!strcmp(inst1, "LSH"))
		return 20;
	else if(!strcmp(inst1, "RSH"))
		return 21;
	else if(!strcmp(inst1, "NOOP"))
		return 0;
	else if(!strcmp(inst1, "EXIT"))
		return 42;

	return -1;
}

/**
 * @brief Verify if the token is a composed instruction (after check pure instruction) 
 * 
 * @param instruction instruction traited
 * @return int 0 if it's an instruction else -1
 */
static int is_instruction(char *instruction) {
	char *instruction_str[] = {"LOAD","STOR","JUMP","JUMP+","ADD","SUB","MUL","DIV"};

	// Verify instruction not NULL
	check_ptr(instruction, "is_instruction");

	// Compare token with instruction_str elements
	for(int i=0 ; i<NB_COMPOSED_INSTRUCTION ; i++) {
		if(!strcmp(instruction, instruction_str[i]))
			return 0;
	}

	return -1;
}

/**
 * @brief Give the opcode of the composed instruction
 * 
 * @param first_member first part of instruction
 * @param second_member second part of instruction
 * @return int the opcode or exit programme and print error
 */
static int find_opcode(char *first_member, char *second_member) {

	//printf("first_member : \"%s\"\n", first_member);
	//printf("second_member : \"%s\"\n", second_member);

	if(!strcmp(first_member, "LOAD")) {
		if(!strcmp(second_member, "MQ,M(X)"))
			return 9;
		else if(!strcmp(second_member, "M(X)"))
			return 1;
		else if(!strcmp(second_member, "-M(X)"))
			return 2;
		else if(!strcmp(second_member, "|M(X)|"))
			return 3;
		else if(!strcmp(second_member, "-|M(X)|"))
			return 4;
	}
	else if(!strcmp(first_member, "STOR")) {
		if(!strcmp(second_member, "M(X)"))
			return 33;
		else if(!strcmp(second_member, "M(X,8:19)"))
			return 22;
		else if(!strcmp(second_member, "M(X,28:39)"))
			return 23;
	}
	else if(!strcmp(first_member, "JUMP")) {
		if(!strcmp(second_member, "M(X,0:19)"))
			return 13;
		else if(!strcmp(second_member, "M(X,20:39)"))
			return 14;
	}
	else if(!strcmp(first_member, "JUMP+")) {
		if(!strcmp(second_member, "M(X,0:19)"))
			return 15;
		else if(!strcmp(second_member, "M(X,20:39)"))
			return 16;
	}
	else if(!strcmp(first_member, "ADD")) {
		if(!strcmp(second_member, "M(X)"))
			return 5;
		else if(!strcmp(second_member, "|M(X)|"))
			return 7;
	}
	else if(!strcmp(first_member, "SUB")) {
		if(!strcmp(second_member, "M(X)"))
			return 6;
		else if(!strcmp(second_member, "|M(X)|"))
			return 8;
	}
	else if(!strcmp(first_member, "MUL")) {
		if(!strcmp(second_member, "M(X)"))
			return 11;
	}
	else if(!strcmp(first_member, "DIV")) {
		if(!strcmp(second_member, "M(X)"))
		return 12;
	}
	else {
		fprintf(stderr, "\033[31m" "error : " "\033[0m" "invalid instruction at line %d\n", line_no);
        exit(EXIT_FAILURE);
	}
}

/**
 * @brief Function to translate a line of input file
 * 
 * @param line_buffer buffer for line of assembly ias file
 * @param len line length
 * @return struct __data* line translated in a structure
 */
static struct __data *translate_line(char *line_buffer, int len) {
	struct __data *tmp_data = NULL;
	char *token_v[MAX_TOKEN];
	int token_c = 0;
	int opcode;
	int next_token;

	// Allocate a structure data
	tmp_data = malloc(sizeof(struct __data));
	alloc_ctrl(tmp_data);

	// NULL all tokens
	for(int i=0 ; i<MAX_TOKEN ; i++)
		token_v[i] = NULL;

	// Tokenize the rest of the string
	token_v[0] = strtok(line_buffer, " ");
	while(token_v[token_c] != NULL) {
		token_c++;
		if(token_c > MAX_TOKEN) { //ERR_CTL
			fprintf(stderr, "\033[31m" "error : " "\033[0m" "too many member at line %d\n", line_no);
        	exit(EXIT_FAILURE);  
		}
		token_v[token_c] = strtok(NULL, " ");
	}
	
	// Find if the first token is an address
	if(is_main_address(token_v[0]) < 0) {
		fprintf(stderr, "\033[31m" "error : " "\033[0m" "first member isn't a main address at line %d\n", line_no);
        exit(EXIT_FAILURE); 
	}
	
	// Add main address to structure data
	tmp_data->main_memory_address.value = strtoll(token_v[0], NULL, 10);

	// If the second member is a data
	if(is_data(token_v[1]) == 0) {
		tmp_data->id = 0;
		tmp_data->word.number = strtoll(token_v[1], NULL, 10);
		return tmp_data;
	}
	else
		tmp_data->id = 1;

	// Is first instruction a pure instruction
	if( (opcode = is_pure_instruction(token_v[1], token_v[2])) >= 0) {
		tmp_data->word.left_opcode = opcode;
		tmp_data->word.left_address = 0;
		if(opcode == 10)
			next_token = 3;
		else
			next_token = 2;
	}
	// Is the first instruction is a composed instruction
	else if( is_instruction(token_v[1]) == 0 ){
		tmp_data->word.left_address = extract_address(token_v[2]);
		tmp_data->word.left_opcode = find_opcode(token_v[1], token_v[2]);
		//
		next_token = 3;
	}
	// First instruction is invalid
	else {
		fprintf(stderr, "\033[31m" "error : " "\033[0m" "first instruction at line %d is invalid\n", line_no);
        exit(EXIT_FAILURE);
	}

	// Is second instruction a pure instruction
	if( (opcode = is_pure_instruction(token_v[next_token], token_v[next_token+1])) >= 0) {
		tmp_data->word.right_opcode = opcode;
		tmp_data->word.right_address = 0;
	}
	// Is the second instruction is a composed instruction
	else if( is_instruction(token_v[next_token]) == 0 ){
		tmp_data->word.right_address = extract_address(token_v[next_token+1]);
		tmp_data->word.right_opcode = find_opcode(token_v[next_token], token_v[next_token+1]);
	}
	// First instruction is invalid
	else {
		fprintf(stderr, "\033[31m" "error : " "\033[0m" "second instruction at line %d is invalid\n", line_no);
        exit(EXIT_FAILURE);
	}

	return tmp_data;
	
}


struct __program *translate_program(FILE *input_file) {
	struct __program *tmp_program = NULL;
	struct __data *tmp_data = NULL;
	char line_buffer[128];
	int len = 0;
	char c;

	// Verify the input file is already openned
	check_ptr(input_file, "translate_program");

	// Allocate a structure program
	tmp_program = malloc(sizeof(struct __program));
	alloc_ctrl(tmp_program);

	tmp_program->data = malloc( NB_MAX_WORD * sizeof(struct __data));
	alloc_ctrl(tmp_program->data);

	// Read and translate the file
	while( ( c = fgetc(input_file)) != EOF ) {
		if(c == '\n') {
			// Add final char to buffer
			line_buffer[len] = '\0';
			// Increment line number (error tracking)
			line_no++;
			// Translate line
			tmp_data = translate_line(line_buffer, len);

			// Add line to struct __program
			tmp_program->data[line_no-1] = tmp_data;

			// Reset buffer length
			len = 0;
		}
		else {
			// Add char to buffer
			line_buffer[len] = c;
			// Increment buffer length
			len++;
		}
	}

	// Add final char to buffer
	line_buffer[len] = '\0';
	// Increment line number (error tracking)
	line_no++;
	// Translate last line
	tmp_data = translate_line(line_buffer, len);

	// Add line to struct __program
	tmp_program->data[line_no-1] = tmp_data;

	// Put number of translated line in program translated
	tmp_program->nb_data = line_no;

	return tmp_program;
}