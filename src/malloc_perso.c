#include <unistd.h>
#include "malloc_perso.h"

void initialize_block(t_block *block)
{
    if(head != NULL)
    {
        t_block* walker = NULL;

        for (walker = head; walker->next != NULL ; walker = walker->next);

        walker->next = block;
        block->previous = walker;
        block->next = NULL;
    }
    else
    {
        head = block;

        block->next = NULL;
        block->previous = NULL;
    }

    block->free = false;
}

t_block *extend_heap(size_t size)
{
    if(size == 0)
        return NULL;

    return (t_block*)(sbrk(sizeof(t_block) + size));
}

void *malloc_perso(size_t size)
{
    size = aligned_size(size);

    t_block* new_block = find_block(size);

    if(new_block == NULL)
    {
        new_block = extend_heap(size);

        if(new_block == (t_block*)(-1))
            return NULL;

        initialize_block(new_block);

        new_block->size = size;
    }
    return new_block + 1;
}

size_t aligned_size(size_t size)
{
    if(size % 4 == 0)
        return size;
    else
       return size + 4 - (size % 4);
}

t_block *find_block(size_t size)
{
    if(head != NULL)
    {
        t_block* walker = NULL;

        for(walker = head; walker->next != NULL ; walker = walker->next)
        {
            if(walker->size > size && walker->free == true)
            {
                split_block(walker, size);
                return walker;
            }
        }
        return NULL;
    }
}

void split_block(t_block *b, size_t size)
{
    if(b != NULL && b->size > size + sizeof(t_block))
    {
        t_block* block = b + size + sizeof(t_block);

        block->size = b->size - size - sizeof(t_block);

        b->size = size;

        if(b->next)
            b->next->previous = block;

        block->next = b->next;
        b->next = block;
        block->previous = b;

        block->free = true;
    }
}

void try_to_fusion()
{
    if(head != NULL)
    {
        for(t_block* walker = head; walker != NULL; walker = walker->next)
        {
            if(walker->free == true && walker->previous != NULL && walker->previous->free == true)
            {
                walker->previous->size += walker->size + sizeof(t_block);

                if(walker->next)
                    walker->next->previous = walker->previous;

                walker->previous->next = walker->next;

                memset_perso(walker, sizeof(t_block));
            }
        }
    }
}

void *calloc_perso(size_t number, size_t size)
{
    size = aligned_size(size * number);

    void* ptr = malloc_perso(size);

    memset_perso(ptr, size);

//    t_block* block = (t_block*) ptr -1;
//
//    for(size_t i = 0; i < block->size; ++i)
//    {
//        ((char*) ptr)[i] = 0;
//    }

    return ptr;
}

void* memset_perso(void* ptr, size_t size)
{
    if(size != 0)
    {
        --size;
        ((char*)ptr)[size] <<= 8;
    }
    return ptr;
}