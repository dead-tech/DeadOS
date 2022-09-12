#pragma once

#include <dts/Types.hpp>

#include "../Io/SerialPort.hpp"
#include "../Memory/Paging.hpp"
#include "Kmalloc.hpp"

namespace Heap {

// TODO: Rewrite this when we will have linked lists
struct MallocBlock
{
    dts::u32     block_size;
    bool         free;
    MallocBlock *next;
};

extern MallocBlock *list_head;

void  init(const dts::u32 size);
void *malloc(const dts::u32 size);
void  free(void *ptr);
void  merge_free_blocks();

} // namespace Heap
