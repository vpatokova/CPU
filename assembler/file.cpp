#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include "file.h"

//нужна ли здесь обработка ошибок или можно оставить ассерты?

static long count_chars(FILE *file);
//static Error_codes get_content(const char *input_file_path, file *asm_cmd);
//static Error_codes split_text(file *asm_cmd);
static void get_commands(const char *input_file_path, file *asm_cmd);
static void split_commands(file *asm_cmd);

static long count_chars(FILE *file)
{
    assert(file != nullptr);

    fseek(file, 0L, SEEK_END);
    
    long n_chars = ftell(file);

    fseek(file, 0L, SEEK_SET);

    return n_chars;
}

void format_commands(const char *input_file_path, file *asm_cmd)
{
    assert(input_file_path != nullptr);
    assert(asm_cmd != nullptr);

    get_commands(input_file_path, asm_cmd);

    split_commands(asm_cmd);
} 

//static Error_codes get_content(const char *input_file_path, file *asm_cmd)
static void get_commands(const char *input_file_path, file *asm_cmd)
{
    assert(input_file_path != nullptr);

    FILE *input_file = fopen(input_file_path, "r");

    if (input_file == nullptr)
    {
        printf("Could not open file.\n");
        //return ERROR_OPEN_FILE;
    }

    asm_cmd->n_chars = count_chars(input_file);

    asm_cmd->buf = (char *) calloc(asm_cmd->n_chars + 1, sizeof(char));

    if (asm_cmd->buf == nullptr)
    {
        printf("Could not find free memory.\n");
        fclose(input_file);
        //return ERROR_BAD_CALLOC;
    }

    if (fread(asm_cmd->buf, sizeof(char), asm_cmd->n_chars, input_file) == 0)
    {
        printf("Could not read chars from the file.\n");
        free(asm_cmd->buf);
        fclose(input_file);
        //return ERROR_READ_FILE;
    }

    fclose(input_file);

    //return SUCCESS;
}

//static Error_codes split_text(file *asm_cmd)
static void split_commands(file *asm_cmd)
{
    assert(asm_cmd != nullptr);

    asm_cmd->cmd_ptr = (char **) calloc(asm_cmd->n_chars + 1, sizeof(char **)); 

    if (asm_cmd->cmd_ptr == nullptr)
    {
        printf("Could not find free memory.\n");
        //return ERROR_BAD_CALLOC;
    }

    asm_cmd->cmd_ptr[0] = &(asm_cmd->buf[0]);
    asm_cmd->n_str = 1;
    
    for (int count = 0; count < asm_cmd->n_chars + 1; count++)
    {
        if (isspace(asm_cmd->buf[count]))
        {
            asm_cmd->buf[count] = '\0';
            asm_cmd->cmd_ptr[asm_cmd->n_str] = &(asm_cmd->buf[count + 1]);
            asm_cmd->n_str++;
        }
    }

    printf("n_str = %d\n", asm_cmd->n_str);
    for (int i = 0; i < asm_cmd->n_str; i++)
        printf("number = %d, cmd = %s\n", i + 1, asm_cmd->cmd_ptr[i]);
}