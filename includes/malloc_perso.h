#ifndef MALLOC_MALLOC_PERSO_H
#define MALLOC_MALLOC_PERSO_H

#include <stdbool.h>
#include <glob.h>
#include <stddef.h>
//#include <zconf.h>

typedef struct s_block
{
    size_t size;

    struct s_block* next;
    struct s_block* previous;

    bool free;

}t_block;

static void* head = NULL;

void initialize_block(t_block* block);

t_block* extend_heap(size_t size);

void* malloc_perso(size_t size);

size_t aligned_size(size_t size);

t_block* find_block(size_t size);

void split_block(t_block* b, size_t size);

void try_to_fusion();

void* calloc_perso(size_t number, size_t size);

void* memset_perso(void* ptr, size_t size);




#endif //MALLOC_MALLOC_PERSO_H