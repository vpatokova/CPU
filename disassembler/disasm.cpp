#include <stdio.h>
#include <assert.h>
#include "disasm.h"

void translate_to_smth(const char *output_file_path, commands *cmd_ptr)
{
    assert(output_file_path != nullptr);
    assert(cmd_ptr          != nullptr);

    FILE *disasm_file = fopen(output_file_path, "w");

    assert(disasm_file != nullptr);

    for (int i = 0; i < cmd_ptr->n_cmd; i++)
    {
        if (cmd_ptr->arr_cmd[i] == PUSH)
            fprintf(disasm_file, "PUSH %d\n", cmd_ptr->arr_cmd[++i]);

        else if (cmd_ptr->arr_cmd[i] == POP)
            fprintf(disasm_file, "POP\n");

        else if (cmd_ptr->arr_cmd[i] == ADD)
            fprintf(disasm_file, "ADD\n");

        else if (cmd_ptr->arr_cmd[i] == SUB)
            fprintf(disasm_file, "SUB\n");

        else if (cmd_ptr->arr_cmd[i] == MUL)
            fprintf(disasm_file, "MUL\n");

        else if (cmd_ptr->arr_cmd[i] == DIV)
            fprintf(disasm_file, "DIV\n");

        else if (cmd_ptr->arr_cmd[i] == OUT)
            fprintf(disasm_file, "OUT\n");

        else if (cmd_ptr->arr_cmd[i] == HLT)
            fprintf(disasm_file, "HLT\n");
    }

    fclose(disasm_file);
}