#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "file.h"
#include "disasm.h"

static long count_chars(FILE *file);

void format_commands(const char *input_file_path, commands *cmd_ptr)
{
    assert(input_file_path != nullptr);
    assert(cmd_ptr         != nullptr);

    FILE *asm_file = fopen(input_file_path, "r"); 
    
    assert(asm_file != nullptr); 

    long n_chars = count_chars(asm_file);

    cmd_ptr->arr_cmd = (int *) calloc(n_chars + 1, sizeof(int));

    while (!feof(asm_file))
    {
        fscanf(asm_file, "%d", cmd_ptr->arr_cmd + cmd_ptr->n_cmd);
        cmd_ptr->n_cmd++;
    }

    fclose(asm_file);
}

static long count_chars(FILE *file)
{
    assert(file != nullptr);

    fseek(file, 0L, SEEK_END);
    
    long n_chars = ftell(file);

    fseek(file, 0L, SEEK_SET);

    return n_chars;
}