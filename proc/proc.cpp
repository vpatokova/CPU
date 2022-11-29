#include <assert.h>
#include "proc.h"

#define POISON 0x7

static void poison_data  (stack *stk);
static void stack_ctor   (stack *stk, int capacity);
static void stack_push   (stack *stk, stk_elem_t value);
static void stack_pop    (stack *stk, stk_elem_t *value_ptr);
static void stack_resize (stack *stk);
static void stack_dtor   (stack *stk);
static void stack_add    (stack *stk);
static void stack_sub    (stack *stk);
static void stack_div    (stack *stk);
static void stack_mul    (stack *stk);
static void stack_out    (stack *stk);

void process_commands(stack *stk, commands *cmd_ptr)
{
    stack_ctor(stk, cmd_ptr->n_cmd);

    for (int i = 0; i < cmd_ptr->n_cmd; i++)
    {
        if (cmd_ptr->arr_cmd[i] == PUSH) //надо ли проверять, что могли налажать с вводом команд?
        {
            int value = cmd_ptr->arr_cmd[++i];
            stack_push(stk, value);
        }

        else if (cmd_ptr->arr_cmd[i] == POP)
        {
            int value = 0;
            stack_pop(stk, &value);
        }

        else if (cmd_ptr->arr_cmd[i] == ADD)
            stack_add(stk);

        else if (cmd_ptr->arr_cmd[i] == SUB)
            stack_sub(stk);

        else if (cmd_ptr->arr_cmd[i] == MUL)
            stack_mul(stk);

        else if (cmd_ptr->arr_cmd[i] == DIV)
            stack_div(stk);

        else if (cmd_ptr->arr_cmd[i] == OUT)
            stack_out(stk);

        else if (cmd_ptr->arr_cmd[i] == HLT)
            stack_dtor(stk);
    }
}

static void stack_ctor(stack *stk, int capacity)
{
    assert(stk != nullptr);
    assert(capacity > 0 && "Capacity is negative");

    stk->capacity = capacity;

    stk->size = 0;

    stk->data = (stk_elem_t *) calloc(stk->capacity, sizeof(stk_elem_t));

    assert(stk->data != nullptr && "Null pointer to data");
}

static void stack_push(stack *stk, stk_elem_t value)
{
    assert(stk != nullptr);

    if (stk->size >= stk->capacity)
        stack_resize(stk);

    stk->data[stk->size++] = value;
}

static void stack_resize(stack *stk)
{
    assert(stk != nullptr);

    if (stk->size >= stk->capacity)
        stk->capacity *= MUL_BY;

    else if (stk->size + 1 == stk->capacity/MUL_BY)
        stk->capacity /= MUL_BY;

    stk->data = (stk_elem_t *) realloc(stk->data, stk->capacity * sizeof(stk_elem_t));

    poison_data(stk);
}

static void stack_pop(stack *stk, stk_elem_t *value_ptr)
{
    assert(stk != nullptr);
    assert(value_ptr != nullptr);

    *value_ptr = stk->data[--(stk->size)];
    
    stk->data[stk->size] = POISON;

    if (stk->size + 1 == stk->capacity/MUL_BY && stk->size >= 10)
        stack_resize(stk);
}

static void stack_dtor(stack *stk)
{
    assert(stk != nullptr);

    free(stk->data);

    stk->data = nullptr;
    stk->capacity = -1;
    stk->size = -1;
}

static void poison_data(stack *stk)
{
    assert(stk != nullptr);

    for (unsigned i = stk->size; i < stk->capacity; i++)
        stk->data[i] = POISON;
}

static void stack_add(stack *stk)
{
    assert(stk != nullptr);
    assert(stk->size > 1 && "Not enough values in stack\n");

    stk_elem_t value1 = 0;
    stk_elem_t value2 = 0;

    stack_pop(stk, &value1);
    stack_pop(stk, &value2);

    stack_push(stk, value1 + value2);
}

static void stack_sub(stack *stk)
{
    assert(stk != nullptr);
    assert(stk->size > 1 && "Not enough values in stack\n");

    stk_elem_t value1 = 0;
    stk_elem_t value2 = 0;

    stack_pop(stk, &value1);
    stack_pop(stk, &value2);

    stack_push(stk, value2 - value1);
}

static void stack_mul(stack *stk)
{
    assert(stk != nullptr);
    assert(stk->size > 1 && "Not enough values in stack\n");

    stk_elem_t value1 = 0;
    stk_elem_t value2 = 0;

    stack_pop(stk, &value1);
    stack_pop(stk, &value2);

    stack_push(stk, value2 * value1);
}

static void stack_div(stack *stk)
{
    assert(stk != nullptr);
    assert(stk->size > 1 && "Not enough values in stack\n");

    stk_elem_t value1 = 0;
    stk_elem_t value2 = 0;

    stack_pop(stk, &value1);
    stack_pop(stk, &value2);

    assert(value1 != 0 && "Can not divide by zero\n");

    stack_push(stk, value2 / value1);
}

static void stack_out(stack *stk)
{
    assert(stk != nullptr);
    stk_elem_t value = stk->data[--stk->size];

    stk->data[stk->size] = POISON;

    if (stk->size + 1 == stk->capacity/MUL_BY && stk->size >= 10)
        stack_resize(stk);

    printf("%d\n", value);
}