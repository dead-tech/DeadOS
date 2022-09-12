#pragma once

#include <dts/Assert.hpp>
#include <dts/Types.hpp>
#include <dts/TypeTraits.hpp>

#include "../DescriptorTables/InterruptServiceRoutine.hpp"
#include "../Io/SerialPort.hpp"
#include "Kmalloc.hpp"

namespace Mem {

constexpr static auto KERNEL_ADDRESS = 0x00100000;

constexpr static auto PAGES_PER_TABLE      = 1024;
constexpr static auto TABLES_PER_DIRECTORY = 1024;
constexpr static auto PAGE_SIZE            = 4096;

using PageEntry        = dts::u32;
using TableEntry       = dts::u32;
using physical_address = dts::u32;
using virtual_address  = dts::u32;

enum class PageFlags : dts::u32
{
    PRESENT       = 1,
    READ_WRITE    = (1 << 1),
    USER          = (1 << 2),
    WRITE_THROUGH = (1 << 3),
    CACHE_DISABLE = (1 << 4),
    ACCESSED      = (1 << 5),
    DIRTY         = (1 << 6),
    PAT           = (1 << 7),
    GLOBAL        = (1 << 8),
    FRAME         = 0xFFFFF000,
};

enum class TableFlags : dts::u32
{
    PRESENT       = 1,
    READ_WRITE    = (1 << 1),
    USER          = (1 << 2),
    WRITE_THROUGH = (1 << 3),
    CACHE_DISABLE = (1 << 4),
    ACCESSED      = (1 << 5),
    DIRTY         = (1 << 6),
    PAGE_SIZE     = (1 << 7),
    GLOBAL        = (1 << 8),
    PAT           = (1 << 9),
    FRAME         = 0xFFFFF000,
};

struct PageTable
{
    PageEntry entries[PAGES_PER_TABLE];
};

struct PageDirectory
{
    TableEntry tables[TABLES_PER_DIRECTORY];
};

constexpr static inline auto page_directory_index(const virtual_address address)
{
    return address >> 22;
}

constexpr static inline auto page_table_index(const virtual_address address)
{
    return address >> 12;
}

constexpr static inline auto get_frame(const PageEntry *entry)
{
    return ((*entry) & ~0xFFF);
}

constexpr static inline auto set_flag(PageEntry *entry, const dts::u32 flag)
{
    return ((*entry) |= flag);
}

constexpr static inline auto clear_flag(PageEntry *entry, const dts::u32 flag)
{
    return ((*entry) &= ~flag);
}

constexpr static inline auto
  set_frame(PageEntry *entry, const physical_address address)
{
    return (*entry = (*entry & ~0xFFFFF000) | address);
}

PageEntry *
  get_page_in_table(PageTable *page_table, const virtual_address address);
TableEntry *get_page_table_in_directory(
  PageDirectory        *page_directory,
  const virtual_address address
);

PageEntry *get_page(const virtual_address virtual_address);
void      *allocate_page(PageEntry *page);
void       free_page(PageEntry *page);

bool set_paging_directory(PageDirectory *page_directory);

void flush_tlb_entry(const virtual_address address);

bool map_page(void *phys_address, void *virt_address);
void unmap_page(void *virt_address);

bool init_paging();

} // namespace Mem
