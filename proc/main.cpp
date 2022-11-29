#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "file.h"
#include "proc.h"

int main(void)
{
    stack stk = {0};

    commands cmd = {0};

    const char *input_file_path = "C://Users/Acer/DedMipt/CPU/src/asm_translation.txt";

    get_commands(input_file_path, &cmd); 

    process_commands(&stk, &cmd);

    return 0;
}