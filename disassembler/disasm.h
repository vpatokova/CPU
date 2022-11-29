#ifndef DISASM_H
#define DISASM_H

typedef struct
{
    int  n_cmd;
    int *arr_cmd;

} commands;

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

void translate_to_smth(const char *output_file_path, commands *cmd_ptr);

#endif // !DISASM_H