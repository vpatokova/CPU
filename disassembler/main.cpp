#include <stdio.h>
#include "disasm.h"
#include "file.h"

int main(void)
{
    const char *input_file_path  = "C://Users/Acer/DedMipt/CPU/src/asm_translation.txt";
    const char *output_file_path = "C://Users/Acer/DedMipt/CPU/src/disasm_translation.txt";
    //const char *output_file_path = "test_disasm.txt";

    commands cmd = {0};

    format_commands(input_file_path, &cmd);

    translate_to_smth(output_file_path, &cmd); //запуталась с языками

    return 0;
}