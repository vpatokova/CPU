#ifndef PROC_H
#define PROC_H

#include <stdio.h>
#include <stdlib.h>

const int MUL_BY = 2;
typedef int stk_elem_t;

 typedef struct
 {
    int         capacity;
    size_t      size;
    stk_elem_t *data;

 } stack;

 typedef struct
 {
    size_t  n_cmd;
    int    *arr_cmd;

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

void process_commands(stack *stk, commands *cmd_ptr);

#endif // !PROC_H