#include "free_perso.h"
#include "malloc_perso.h"

void free_perso(void *ptr)
{
    if(ptr == NULL)
        return;

    t_block* block = (t_block*) ptr -1;
//
//    for(int i = 0; i < block->size; ++i)
//    {
//        ((char*) ptr)[i] <<= 8;
//    }

    memset_perso(ptr, block->size);

    block->free = true;

    try_to_fusion();
}