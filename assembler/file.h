#ifndef FILE_H
#define FILE_H

typedef struct
{
    char  *buf;
    char **cmd_ptr;
    int    n_chars;
    int    n_str;
} file; //название не очень

void format_commands(const char *input_file_path, file *asm_cmd);

#endif // !FILE_H