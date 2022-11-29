#ifndef ASM_H
#define ASM_H

#include "file.h"

enum Commands
{
    HLT  = 0,
    PUSH = 1,
    POP  = 2, 
    ADD  = 3,
    SUB  = 4,
    MUL  = 5,
    DIV  = 6,
    OUT  = 7     
};

void translate_to_assembly(const char *output_file_path, file *asm_cmd);

#endif // !ASM_H