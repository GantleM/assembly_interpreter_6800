#include <stdio.h>
#include <string.h>

#define MAX_OPERANDS 2
#define MAX_OP_LEN 16

#define MAX_INSTRUCTIONS 100

typedef enum {
    OP_ADD,
    OP_CLR,
    OP_UNKNOWN
} Opcode;

typedef struct {
    Opcode op;
    char operands[MAX_OPERANDS][MAX_OP_LEN];
    int num_operands;
} Instruction;


// Passing the pointer of the string (first character and read until /0)
// Const to show that it's only being read, not modified
Opcode parse_op(const char *str){

    // Check if it's the same (returns 0)
    if (strcmp(str, "ADD") == 0) {return OP_ADD;}
    if (strcmp(str, "CLR") == 0) {return OP_CLR;}
    else {return OP_UNKNOWN;}

}

Instruction set_instruction(char raw[]){
    //init a struct with all 0 values
    Instruction ins = {0};

    //Tokenise op code
    char *token = strtok(raw, " ");
    if (token == NULL) return ins;
    ins.op = parse_op(token);

    while((token = strtok(NULL, " ")) != NULL && ins.num_operands < MAX_OPERANDS){
        strcpy(ins.operands[ins.num_operands], token);
        ins.num_operands++;
    }

    return ins;
}



void read_inputfile(const char *file_name, Instruction instructions[])
{

    FILE *fp;
    char line[MAX_INSTRUCTIONS];
    int counter = 0;

    fp = fopen(file_name, "r");
    if (fp == NULL) 
    {
        printf("Error opening the file!\n");
    }

    while(fgets(line, MAX_INSTRUCTIONS, fp) != NULL)
    {
        instructions[counter++] = set_instruction(line);
    }

}


int main(int argc, char const *argv[])
{

    Instruction instructions[MAX_INSTRUCTIONS];
    read_inputfile(argv[1], instructions);


    printf("ins1: %d %s", instructions[0].op, instructions[0].operands[0]);

    // // Executing parsed instructions using a switch statement
    // switch (i2.op) {
    //     case OP_ADD:
    //         printf("Executing ADD: Target=%s, Value=%s\n", i2.operands[0], i2.operands[1]);
    //         break;
    //     case OP_CLR:
    //         printf("Executing CLR: Target=%s\n", i2.operands[0]);
    //         break;
    //     default:
    //         printf("Unknown instruction!\n");
    // }

    return 0;
}
