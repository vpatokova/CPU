#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "file.h"
#include "proc.h"

static long count_chars(FILE *file);

void get_commands(const char *input_file_path, commands *cmd_ptr)
{
    FILE *proc_cmd_file = fopen(input_file_path, "r"); 
    assert(proc_cmd_file != nullptr); 

    long n_chars = count_chars(proc_cmd_file);

    cmd_ptr->arr_cmd = (int *) calloc(n_chars + 1, sizeof(int));

    while (!feof(proc_cmd_file))
    {
        fscanf(proc_cmd_file, "%d", cmd_ptr->arr_cmd + cmd_ptr->n_cmd);
        cmd_ptr->n_cmd++;
    }

    fclose(proc_cmd_file);
}

static long count_chars(FILE *file)
{
    assert(file != nullptr);

    fseek(file, 0L, SEEK_END);
    
    long n_chars = ftell(file);

    fseek(file, 0L, SEEK_SET);

    return n_chars;
}