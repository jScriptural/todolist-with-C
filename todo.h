#ifndef TODO_H
#define TODO_H

#include <stdbool.h>


#define N 1024


typedef char* string;

void init_task(void);
bool is_full(void);
bool is_empty(void);
void clear_tasks(void);

void add_task(void);
void remove_task(void);

void print_task(void);


#endif
