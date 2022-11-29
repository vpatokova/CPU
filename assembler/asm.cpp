#include <stdio.h>
#include "asm.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

void translate_to_assembly(const char *output_file_path, file *asm_cmd)
{    
    assert(output_file_path != nullptr);
    assert(asm_cmd          != nullptr);

    FILE *output_file = fopen(output_file_path, "w"); //кажется что файл надо открывать не здесь
    assert(output_file != nullptr);
    
    for (int i = 0; i < asm_cmd->n_str; i++)
    {
        if (strcmp(asm_cmd->cmd_ptr[i], "PUSH") == 0) //надо ли проверять, что могли налажать с вводом команд?
        {
            fprintf(output_file, "%d ", PUSH);
            fprintf(output_file, "%s ", asm_cmd->cmd_ptr[++i]); //куда девается '\0'?
        }

        else if (strcmp(asm_cmd->cmd_ptr[i], "POP") == 0)
            fprintf(output_file, "%d ", POP);

        else if (strcmp(asm_cmd->cmd_ptr[i], "ADD") == 0)
            fprintf(output_file, "%d ", ADD);

        else if (strcmp(asm_cmd->cmd_ptr[i], "SUB") == 0)
            fprintf(output_file, "%d ", SUB);

        else if (strcmp(asm_cmd->cmd_ptr[i], "MUL") == 0)
            fprintf(output_file, "%d ", MUL);

        else if (strcmp(asm_cmd->cmd_ptr[i], "DIV") == 0)
            fprintf(output_file, "%d ", DIV);

        else if (strcmp(asm_cmd->cmd_ptr[i], "OUT") == 0)
            fprintf(output_file, "%d ", OUT);

        else if (strcmp(asm_cmd->cmd_ptr[i], "HLT") == 0)
            fprintf(output_file, "%d", HLT);
    }

    fclose(output_file);
}