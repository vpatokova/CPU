#include <stdio.h>
#include "asm.h"
#include "file.h"

int main(void)
{
    const char *input_file_path  = "C://Users/Acer/DedMipt/CPU/src/commands.txt";
    const char *output_file_path = "C://Users/Acer/DedMipt/CPU/src/asm_translation.txt";
    //const char *output_file_path = "test_asm.txt";

    file asm_cmd = {0};

    format_commands(input_file_path, &asm_cmd);

    translate_to_assembly(output_file_path, &asm_cmd);

    return 0;
}