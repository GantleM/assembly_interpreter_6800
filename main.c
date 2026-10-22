#include <stdio.h>
#include <string.h>

#define MAX_OPERANDS 2
#define MAX_OP_LEN 16

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

int main(int argc, char const *argv[])
{
    /*Creating file pointer and opening file.*/
    // FILE *fp; 
    // fp = fopen(argv[1], 'r');

    // if (fp == NULL) {
    //     printf("Error opening the file!\n");
    //     return 1;
    // }

    char line1[] = "CLR A";
    char line2[] = "ADD A $0020";

    Instruction i1 = set_instruction(line1);
    Instruction i2 = set_instruction(line2);

    // Executing parsed instructions using a switch statement
    switch (i2.op) {
        case OP_ADD:
            printf("Executing ADD: Target=%s, Value=%s\n", i2.operands[0], i2.operands[1]);
            break;
        case OP_CLR:
            printf("Executing CLR: Target=%s\n", i2.operands[0]);
            break;
        default:
            printf("Unknown instruction!\n");
    }

    return 0;
}
