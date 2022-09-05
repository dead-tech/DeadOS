#include "Heap.hpp"

namespace Heap {

static dts::u32 heap_start_virtual_address = 0x300'000;
static dts::u32 malloc_page_count          = 0;

MallocBlock *list_head = nullptr;

// Splits memory block into two if the requested one was smaller
static void split(MallocBlock *node, const dts::u32 size)
{
    auto *new_node       = reinterpret_cast<MallocBlock *>(node + size + sizeof(MallocBlock));
    new_node->block_size = node->block_size - size - sizeof(MallocBlock);
    new_node->free       = true;
    new_node->next       = node->next;

    node->block_size = size;
    node->free       = false;
    node->next       = new_node;
}

void init([[maybe_unused]] const dts::u32 size)
{
    malloc_page_count = size / Mem::PAGE_SIZE;
    if (size % Mem::PAGE_SIZE > 0) { ++malloc_page_count; }

    list_head = reinterpret_cast<MallocBlock *>(heap_start_virtual_address);

    for (dts::u32 i = 0, virt = heap_start_virtual_address; i < malloc_page_count; ++i, virt += Mem::PAGE_SIZE) {
        Mem::map_page(dts::kmalloc_aligned(i * Mem::PAGE_SIZE), reinterpret_cast<void *>(heap_start_virtual_address));

        auto *page = Mem::get_page(heap_start_virtual_address);
        Mem::set_flag(page, dts::to_underlying_type(Mem::PageFlags::READ_WRITE));
    }

    if (list_head != nullptr) {
        list_head->block_size = (malloc_page_count * Mem::PAGE_SIZE) - sizeof(MallocBlock);
        list_head->free       = true;
        list_head->next       = nullptr;
    }
}

void *malloc(const dts::u32 size)
{
    if (size == 0) { return nullptr; }

    if (list_head->block_size == 0) { init(size); }

    MallocBlock *current = list_head;
    //    MallocBlock *previous = nullptr;
    while ((current->block_size < size || !current->free) && current->next != nullptr) {
        //        previous = current;
        current = current->next;
    }

    if (current->block_size == size) {
        // Expected size
        current->free = false;
    } else if (current->block_size > size + sizeof(MallocBlock)) {
        // Node is larger
        split(current, size);
    } else {
        // Node too small, allocate more pages
        dts::u32 num_pages = 1;
        while (current->block_size + num_pages * Mem::PAGE_SIZE < size + sizeof(MallocBlock)) { ++num_pages; }

        dts::u32 virt = heap_start_virtual_address + malloc_page_count * Mem::PAGE_SIZE;

        for (dts::u32 i = 0; i < num_pages; ++i) {
            Mem::PageEntry *page = nullptr;
            auto           *temp = Mem::allocate_page(page);

            Mem::map_page(temp, reinterpret_cast<void *>(virt));
            Mem::set_flag(page, dts::to_underlying_type(Mem::PageFlags::READ_WRITE));

            virt += Mem::PAGE_SIZE;
            current->block_size += Mem::PAGE_SIZE;
            ++malloc_page_count;
        }

        split(current, size);
    }

    // FIXME?: reinterpret_cast<> here
    return current + sizeof(MallocBlock);
}

void merge_free_blocks()
{
    auto *current = list_head;
    //    MallocBlock *previous = nullptr;

    while (current != nullptr && current->next != nullptr) {
        if (current->free && current->next->free) {
            current->block_size += (current->next->block_size + sizeof(MallocBlock));
            current->next = current->next->next;
        }
        //        previous = current;
        current = current->next;
    }
}

void free(void *ptr)
{
    for (MallocBlock *current = list_head; current->next != nullptr; current = current->next) {
        if (current + sizeof(MallocBlock) == ptr) {
            current->free = true;
            merge_free_blocks();
            return;
        }
    }
}

} // namespace Heap
